/* 
 * File:   XmlCmd.DocumentReader.cpp
 * Author: Jay Sprenkle
 *
 * Created on October 7, 2014
 */
#include "XmlCmd.DocumentReader.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <vector>
#include <algorithm>

#include <string.h>

namespace XmlCmd
{
   DocumentReader::DocumentReader( const char* FileName, const char* RootNodeName, const char* Namespace )
      : buffer( 0 )
   {
      // get file size
      struct stat buf;
      if ( stat( FileName, &buf ) != 0 )
      {
         ::std::string msg( "Configuration file error: " );
         msg.append( ::strerror( errno ) );
         throw ::std::runtime_error( msg.c_str() );
      }
      size = buf.st_size;

      // <editor-fold defaultstate="collapsed" desc="Load the xml into buffer">
      // allocate space for content
      buffer = (char*) new char[size + 1];

      // note: text mode on windows/dos may return a smaller result than is stored on disk. Read as binary
      FILE* fd = ::fopen( FileName, "rb" );
      if ( !fd )
         throw ::std::runtime_error( "Config file could not be opened" );

      // read content
      size_t bytesRead = ::fread( buffer, 1, size, fd );
      ::fclose( fd );
      if ( bytesRead != size )
         throw ::std::runtime_error( "Config file could not be read" );

      // ensure null termination
      buffer[bytesRead] = 0;
      // </editor-fold>

      Validate( RootNodeName, Namespace );
   }
   
   DocumentReader::DocumentReader( ::File::Reader& rdr, const char* RootNodeName, const char* Namespace )
      : buffer( 0 )
   {
      size = rdr.size();

      // <editor-fold defaultstate="collapsed" desc="Load the xml into buffer">
      // allocate space for content
      buffer = (char*) new char[size + 1];
      rdr.read( size, (unsigned char*) buffer );
      // ensure null termination
      buffer[size] = 0;
      // </editor-fold>

      Validate( RootNodeName, Namespace );
   }

   DocumentReader::~DocumentReader()
   {
      if ( buffer )
         delete [] buffer;
   }
   
   void DocumentReader::Validate( const char* RootNodeName, const char* Namespace )
   {
      // <editor-fold defaultstate="collapsed" desc="validate the document">
      try
      {
         parse< ::rapidxml::parse_no_data_nodes | ::rapidxml::parse_trim_whitespace >( buffer );
      }
      catch ( ::rapidxml::parse_error e )
      {
         ::std::string msg( e.what() );
         msg.append( " near '" );
         char buffer[64];
         strncpy( buffer, e.where<char>(), sizeof(buffer) - 2 );
         buffer[sizeof(buffer) - 1] = 0;
         msg.append( buffer );
         msg.append( "'" );
         throw ::std::runtime_error( msg.c_str() );
      }
      // </editor-fold>

      // check the root node name and namespace
      ValidateRootNode( RootNodeName, Namespace );
   }
   
   uint32_t DocumentReader::ReadNumericAttribute( ::rapidxml::xml_node<>* Node, const char* name )
   {
      ::rapidxml::xml_attribute<>* attr = Node->first_attribute( name );
      if ( attr )
         return stringTo< uint32_t >( ::std::string( attr->value(), attr->value_size() ) );
      return 0;
   }
}
