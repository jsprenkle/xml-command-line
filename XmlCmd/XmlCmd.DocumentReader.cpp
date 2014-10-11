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
   
   void DocumentReader::Validate( const char* NodeName, const ::std::string& XmlNamespace )
   {
      // <editor-fold defaultstate="collapsed" desc="Parse the document xml">
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

      // <editor-fold defaultstate="collapsed" desc="validate the document">
      // check the root node name and namespace
      root = first_node();
      if ( ! root )
         throw ::std::runtime_error( "No root node in document" );
      
      // check the node name and namespace
      ::std::string XmlNamespaceAttribName( "xmlns" );

      // get the namespace prefix (if present)
      ::std::string RootNodeName( root->name(), root->name_size() );
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

      if ( RootNodeName != NodeName )
         throw ::std::runtime_error( "Invalid root node name" );

      if ( ! XmlNamespace.empty() )
      {
         ::rapidxml::xml_attribute<>* nsattr = root->first_attribute( XmlNamespaceAttribName.c_str() );
         if ( !nsattr )
            throw ::std::runtime_error( "Invalid document. no namespace" );

         ::std::string NameSpaceAttribute( nsattr->value(), nsattr->value_size() );
         if ( NameSpaceAttribute != XmlNamespace ) 
            throw ::std::runtime_error( "Invalid namespace" );
      }
      // </editor-fold>
   }
   
   uint32_t DocumentReader::ReadNumericAttribute( ::rapidxml::xml_node<>* Node, const char* name )
   {
      ::rapidxml::xml_attribute<>* attr = Node->first_attribute( name );
      if ( attr )
         return stringTo< uint32_t >( ::std::string( attr->value(), attr->value_size() ) );
      return 0;
   }
}
