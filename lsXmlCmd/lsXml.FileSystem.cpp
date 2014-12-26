/* 
 * File:   lsXml.FileSystem.cpp
 * Author: Jay Sprenkle
 *
 * Created on June 30, 2014
 */
#include <iostream>
#include <list>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <pwd.h>
#endif

#ifdef WIN32
#include <Winsock2.h>
#include <accctrl.h>
#include <aclapi.h>
typedef _off_t __off_t; // is this only necessary on windows mingw?
#endif

#include "lsXml.FileSystem.h"

namespace lsXml
{
   FileSystem::FileSystem( const ::lsXml::Config::Settings& config )
      : config( config )
      , doc( "http://www.XmlCommandLine.org/FileSystem/1.0", "", "FileSystem" )
   {
   }
   
   /**
    * Convert *nix date time to an xml time stamp.
    * @param when
    * @return gmt date time string required for xml datetime type
    */
   ::std::string DateToString( time_t when )
   {
      //2014-06-30T12:00:00
      struct tm* ptm = gmtime( &when );
      
      char b[20];
      sprintf( b, "%04d-%02d-%02dT%02d:%02d:%02d", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec );
      return ::std::string( b );
   }

   ::std::string NumberToString( __off_t n )
   {
      char b[21];
      sprintf( b, "%ld", n );
      return ::std::string( b );
   }

   void FileSystem::AppendContext( ::rapidxml::xml_node<>* Parent, int argc, char** argv )
   {
      Context = doc.AppendChildNode( Parent, "Context" );

      ::rapidxml::xml_node<>* Create = doc.AppendChildNode( Context, "Create" );
      doc.AppendAttribute( Create, "Created", DateToString( time( 0 ) ) );

      doc.AppendChildNode( Create, "Notes", "Created by lsXmlCmd" );
      
      ::rapidxml::xml_node<>* Source = doc.AppendChildNode( Create, "Source" );
      doc.AppendAttribute( Source, "Name", "lsXmlCmd" );
      doc.AppendAttribute( Source, "Version", "1.0" );

      ::std::string separator;
      ::std::string args;
      for ( int i = 0; i < argc; i++ )
      {
         args.append( separator );
         args.append( argv[i] );
         separator = " ";
      }
      doc.AppendChildNode( Source, "args", args );
      
      doc.AppendChildNode( Source, "User", UserName() );
      doc.AppendChildNode( Source, "Host", HostName() );
   }

   ::rapidxml::xml_node<>* FileSystem::AppendDirectoryElement( ::rapidxml::xml_node<>* Parent, const ::std::string& path, const ::std::string& Owner, const ::std::string& GroupOwner )
   {
      // create directory element in xml document
      ::rapidxml::xml_node<>* DirectoryElement = doc.AppendChildNode( Parent, "Directory" );
      doc.AppendAttribute( DirectoryElement, "Name", basename( path ) );

      doc.AppendChildNode( DirectoryElement, "Path", path );
      doc.AppendChildNode( DirectoryElement, "Owner", Owner );
      doc.AppendChildNode( DirectoryElement, "GroupOwner", GroupOwner );
      
      return DirectoryElement;
   }
   
   void FileSystem::AppendDirectories( ::rapidxml::xml_node<>* Parent, ::std::list< ::std::string >& directories )
   {
      while ( !directories.empty() )
      {
         ::rapidxml::xml_node<>* DirectoryElement = AppendDirectoryElement( Parent, directories.front(), "", "" );

         // read directory content
         DIR* dirp;
         struct dirent *next;

         errno = 0;
         dirp = ::opendir( directories.front().c_str() );
         if ( !dirp )
         {
            LogError( "cannot open directory", directories.front() );
            return;
         }

         // TODO: if there are infinite loops of linked directories this will never exit...

         // read directory entries
         ::std::list< ::std::string > subdirs;
         ::rapidxml::xml_node<>* Content = doc.AppendChildNode( DirectoryElement, "Content" );
         while ( true )
         {
            /* Set errno to zero so we can distinguish between a readdir failure
               and when readdir simply finds that there are no more entries.  */
            errno = 0;
            next = ::readdir( dirp );
            if ( next )
            {
               struct stat _stat;
               ::memset( &_stat, 0, sizeof _stat );

               // get directory entry name
   #ifdef __linux__
               ::std::string EntryName( next->d_name );
   #endif
   #ifdef WIN32
               ::std::string EntryName( next->d_name, next->d_namlen );
   #endif
               ::std::string EntryPath;

               if ( EntryName == "/" )
                  EntryPath = EntryName;
               else
                  EntryPath = BuildPath( directories.front(), EntryName );

               int err = stat( EntryPath.c_str(), &_stat );
               if ( err != 0 )
               {
                  /* Failure to stat a command line argument leads to
                     an exit status of 2.  For other files, stat failure
                     provokes an exit status of 1.  */
                  LogError( "cannot access (stat)", EntryPath );
                  break;
               }

               // is this a directory or a file?
               // TODO: how to determine if it's a *nix device?
               if ( S_ISDIR( _stat.st_mode ) )
               {
                  if ( EntryName == "." || EntryName == ".." )
                  {
                     if ( ! config.dotdot )
                     {
                        ::rapidxml::xml_node<>* element = doc.AppendChildNode( Content, "Link" );
                        doc.AppendAttribute( element, "Name", EntryName );

                        doc.AppendChildNode( element, "Path", EntryPath );
                        doc.AppendChildNode( element, "Owner", "" );
                        doc.AppendChildNode( element, "GroupOwner", "" );
                     }
                  }
                  else
                  {
                     if ( config.recursive )
                        subdirs.push_back( EntryPath );
                     else
                        AppendDirectoryElement( Content, EntryPath, "", "" );
                  }
               }
               else
               {
                  ::std::string Owner;
   #ifdef WIN32
                  // stat on windows:
                  //  st_uid: Numeric identifier of user who owns file (UNIX-specific). This field will always be zero on Windows systems.
                  Owner = getUserName( EntryPath );
   #endif
   #ifdef __linux__
                  Owner = getUserName( _stat.st_uid );
   #endif

                  {
                     ::rapidxml::xml_node<>* element = doc.AppendChildNode( Content, "File" );
                     doc.AppendAttribute( element, "Name", EntryName );

                     doc.AppendChildNode( element, "Path", EntryPath );
                     doc.AppendChildNode( element, "Owner", Owner );
                     doc.AppendChildNode( element, "Permissions", "0000" );

                     doc.AppendChildNode( element, "Created", DateToString( _stat.st_ctime ) );
                     doc.AppendChildNode( element, "LastRead", DateToString( _stat.st_atime ) );
                     doc.AppendChildNode( element, "LastChanged", DateToString( _stat.st_mtime ) );
                     doc.AppendChildNode( element, "Size", NumberToString( _stat.st_size ) );
                  }
               }
            }
            else
               if ( errno != 0 )
               {
                  LogError( "reading directory", directories.front() );
                  if ( errno != EOVERFLOW )
                     break;
               }
               else
                  break;
         }
         if ( ::closedir( dirp ) != 0 )
         {
            LogError( "closing directory", directories.front() );
            // Don't return; return whatever we can get
         }

         // if recursive loading enabled...
         AppendDirectories( Content, subdirs );
         
         directories.pop_front();
      }
   }

   // <editor-fold defaultstate="collapsed" desc="Get User Name">
#ifdef WIN32

   ::std::string FileSystem::UserName()
   {
      char Buffer[256];
      DWORD lpnSize = sizeof( Buffer );
      // documentation says windows 2000 and up have this function
      bool rc = GetUserName( &Buffer[0], &lpnSize );
      ::std::string result;
      if ( rc )
         result = Buffer;
      return result;
   }
#endif
#ifdef __linux__

   ::std::string FileSystem::UserName()
   {
       ::std::string result;
       char* p = getlogin();
       if ( p )
           result = p;
      return result;
   }
#endif
   // </editor-fold>

   // <editor-fold defaultstate="collapsed" desc="get computer host name">
#ifdef __linux__

   ::std::string FileSystem::HostName()
   {
      char Buffer[256];
      Buffer[0] = 0;
      int rc = gethostname( &Buffer[0], sizeof ( Buffer ) );
      return ::std::string( Buffer );
   }
#endif
#ifdef WIN32

   ::std::string FileSystem::HostName()
   {
      ::std::string result;

      /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
      WORD wVersionRequested = MAKEWORD( 2, 0 );

      WSADATA wsaData;
      int err = WSAStartup( wVersionRequested, &wsaData );
      if ( err != 0 )
         return result;

      /* Confirm that the WinSock DLL supports 2.0.*/
      if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 )
      {
         WSACleanup();
         return result;
      }

      char Buffer[256];
      Buffer[0] = 0;
      int rc = gethostname( &Buffer[0], sizeof ( Buffer ) );
      if ( rc == 0 )
         result = Buffer;

      WSACleanup();
      return result;
   }
#endif
   // </editor-fold>

   // <editor-fold defaultstate="collapsed" desc="Get file system object owner name">
#ifdef __linux__

   ::std::string FileSystem::getUserName( uid_t uid )
   {
      register struct passwd *pw = getpwuid( uid );
      if ( pw )
         return ::std::string( pw->pw_name );
      return ::std::string( "" );
   }
#endif

#ifdef WIN32

   ::std::string FileSystem::getUserName( const ::std::string& FileName )
   {
      ::std::string UserName;

      HANDLE hFile = CreateFile( FileName.c_str( ), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
      if ( hFile != INVALID_HANDLE_VALUE )
      {
         PSID pSidOwner = NULL;
         BOOL bRtnBool = TRUE;
         LPTSTR AcctName = NULL;
         LPTSTR DomainName = NULL;
         DWORD dwAcctName = 1, dwDomainName = 1;
         SID_NAME_USE eUse = SidTypeUnknown;
         PSECURITY_DESCRIPTOR pSD = NULL;

         // Get the owner SID of the file.
         DWORD dwRtnCode = GetSecurityInfo( hFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, &pSidOwner, NULL, NULL, NULL, &pSD );
         // Check GetLastError for GetSecurityInfo error condition.
         if ( dwRtnCode == ERROR_SUCCESS )
         {
            // First call to LookupAccountSid to get the buffer sizes.
            bRtnBool = LookupAccountSid(
               NULL, // local computer
               pSidOwner,
               AcctName,
               ( LPDWORD ) & dwAcctName,
               DomainName,
               ( LPDWORD ) & dwDomainName,
               &eUse );

            // Reallocate memory for the buffers.
            AcctName = (LPTSTR) GlobalAlloc( GMEM_FIXED, dwAcctName );
            if ( AcctName )
            {
               DomainName = (LPTSTR) GlobalAlloc( GMEM_FIXED, dwDomainName );
               if ( DomainName )
               {
                  // Second call to LookupAccountSid to get the account name.
                  bRtnBool = LookupAccountSid(
                     NULL, // name of local or remote computer
                     pSidOwner, // security identifier
                     AcctName, // account name buffer
                     ( LPDWORD ) & dwAcctName, // size of account name buffer 
                     DomainName, // domain name
                     ( LPDWORD ) & dwDomainName, // size of domain name buffer
                     &eUse ); // SID type
                  if ( bRtnBool )
                     UserName = AcctName;
               }
            }
         }
      }
      return UserName;
   }
#endif
   // </editor-fold>

   void FileSystem::LogError( const char* msg, const ::std::string& name )
   {
      ::std::cerr 
         << msg
         << ": " << name
         ;
   }

   ::std::string FileSystem::BuildPath( const ::std::string& dirname, const ::std::string& name )
   {
      ::std::string dest;
      // Copy dirname if it is not "."
      if ( dirname != "." )
      {
         dest = dirname;
         // Add '/' if `dirname' doesn't already end with it
         if ( ! dest.empty() )
            if ( *(--dest.end()) != '/' )
               dest.append( "/" );
      }
      dest.append( name );
      return dest;
   }

   ::std::string FileSystem::basename( const ::std::string& Path )
   {
      size_t i = Path.find_last_of( "\\/" );
      if ( i != ::std::string::npos )
         return Path.substr( i + 1 );
      return Path;
   }
}
