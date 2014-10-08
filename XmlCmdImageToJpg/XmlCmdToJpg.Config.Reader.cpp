/* 
 * File:   XmlCmdToJpg.Config.Reader.cpp
 * Author: Jay Sprenkle
 *
 * I/O for DTO object
 * 
 * Created on July 30, 2014
 */
#include "XmlCmdToJpg.Config.Reader.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <vector>
#include <algorithm>
#include <stdexcept>

#include <rapidxml.hpp>
#include <string.h>

namespace XmlCmdToJpg
{
   namespace Config
   {
      Reader::Reader( const char* FileName )
         : buffer( 0 )
      {
         // get file size
         struct stat buf;
         if ( stat( FileName, &buf ) != 0 )
         {
            ::std::string msg( "Configuration file error: " );
            msg.append( ::strerror( errno ) );
            msg.append( ". FileName: " );
            msg.append( FileName );
            throw ::std::runtime_error( msg.c_str() );
         }
         size_t size = buf.st_size;

         // <editor-fold defaultstate="collapsed" desc="Load the xml into buffer">
         // allocate space for content
         buffer = (char*) new char[size + 1];

         // note: text mode on windows/dos may return a smaller result than is stored on disk. Read as binary
         FILE* fd = ::fopen( FileName, "rb" );
         if ( ! fd )
            throw ::std::runtime_error( "Config file could not be opened" );

         // read content
         size_t bytesRead = ::fread( buffer, 1, size, fd );
         ::fclose( fd );
         if ( bytesRead != size )
            throw ::std::runtime_error( "Config file could not be read" );

         // ensure null termination
         buffer[bytesRead] = 0;
         // </editor-fold>
      }

      Reader::~Reader()
      {
         if ( buffer )
            delete [] buffer;
      }

      const char* ReadNode( ::rapidxml::xml_node<>* current_node, const ::std::string& XmlNamespacePrefix, const char* NodeName, const char* DefaultValue = "" )
      {
          ::std::string XmlNodeName( XmlNamespacePrefix );
          XmlNodeName.append( NodeName );
          
         ::rapidxml::xml_node<>* Nodefound;
         Nodefound = current_node->first_node( XmlNodeName.c_str() );
         if ( Nodefound )
            return Nodefound->value();
         return DefaultValue;
      }

      bool ParseBool( const char* str )
      {
         ::std::string data( str );
         ::std::transform( data.begin(), data.end(), data.begin(), ::tolower );      
         return data == "true" || data == "1";
      }
            
      Settings Reader::Parse()
      {
         ::rapidxml::xml_document<> doc;
         try
         {
            doc.parse< ::rapidxml::parse_no_data_nodes | ::rapidxml::parse_trim_whitespace > ( buffer );
         }
         catch ( ::rapidxml::parse_error e )
         {
            ::std::string msg( e.what() );
            msg.append( " near '" );
            char buffer[64];
            strncpy( buffer, e.where<char>(), sizeof (buffer ) - 2 );
            buffer[sizeof (buffer ) - 1] = 0;
            msg.append( buffer );
            msg.append( "'" );
            throw ::std::runtime_error( msg.c_str() );
         }

         Settings result;
         
         ::rapidxml::xml_node<>* current_node = doc.first_node();
         if ( current_node )
         {
            // check the root and namespace to see if it's an lsXML configuration file

             ::std::string XmlNamespaceAttribName( "xmlns" );
            
             // get the namespace prefix (if present)
             ::std::string XmlNamespacePrefix;
             ::std::string RootNodeName( current_node->name(), current_node->name_size() );
             size_t separator = RootNodeName.find( ":" );
             if ( separator != ::std::string::npos )
             {
                 // extract text prefix
                 XmlNamespacePrefix.assign( RootNodeName.c_str(), separator );

                 // create attribute name
                 XmlNamespaceAttribName.append( ":" );
                 XmlNamespaceAttribName.append( XmlNamespacePrefix );
                 
                 // fix prefix for use with nodes
                 XmlNamespacePrefix.append( ":" );
                 
                 // remove cruft from root node
                 RootNodeName.erase( 0, separator + 1 );
             }

            if ( RootNodeName != "Config" )
               throw ::std::runtime_error( "The configuration file is invalid or is the wrong version (wrong root node name)" );

            ::rapidxml::xml_attribute<>* nsattr = current_node->first_attribute( XmlNamespaceAttribName.c_str() );
            if ( !nsattr )
               throw ::std::runtime_error( "The configuration file is invalid or is the wrong version (no namespace)" );
            
            const char lsXMLNamespace[] = { "http://www.XmlCommandLine.org/XmlCmdToJpg/" };
            if ( ::strncmp( nsattr->value(), lsXMLNamespace, sizeof( lsXMLNamespace ) - 1 ) != 0 )
               throw ::std::runtime_error( "The configuration file is invalid or is the wrong version (wrong namespace)" );

            result.content = ParseBool( ReadNode( current_node, XmlNamespacePrefix, "Content" ) );

            result.Quality = atoi( ReadNode( current_node, XmlNamespacePrefix, "Quality", "80" ) );
            if ( result.Quality < 10 || result.Quality > 100 )
               throw ::std::runtime_error( "The image Quality setting is not between 10 and 100" );

            result.Comment = ReadNode( current_node, XmlNamespacePrefix, "Comment" );
            
            result.OutputFile = ReadNode( current_node, XmlNamespacePrefix, "OutputFile" );
         }

         return result;
      }
   }
}
