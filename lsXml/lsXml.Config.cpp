/* 
 * File:   lsXml.Config.cpp
 * Author: Jay Sprenkle
 *
 * Created on June 30, 2014
 */
#include "lsXml.Config.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <algorithm>
#include <stdexcept>

namespace lsXml
{
   Config::Config( const ::std::string& Name )
      : buffer( 0 )
      , recursive( true )
      , dotdot( false )
   {
      // <editor-fold defaultstate="collapsed" desc="Load the xml into buffer">
      FILE* fd = fopen( Name.c_str(), "rt" );
      if ( ! fd )
         throw ::std::runtime_error( "Config file could not be opened" );

      // get file size
      struct stat buf;
      stat( Name.c_str(), &buf );
      size_t size = buf.st_size;

      // allocate space for content
      char* buffer = (char*) new char[size + 1];
      
      // read content
      size_t bytesRead = fread( buffer, size, 1, fd );
      fclose( fd );
      if ( bytesRead < size )
         throw ::std::runtime_error( "Config file could not be read" );
      // ensure null termination. text mode on windows/dos may return a smaller result than is stored on disk
      buffer[bytesRead] = 0;
      // </editor-fold>

      // parse configuration file
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

      ::rapidxml::xml_node<>* current_node;
      current_node = doc.first_node();
      if ( current_node )
      {
         recursive = ParseBool( ReadNode( "recursive" ) );
         dotdot = ParseBool( ReadNode( "dotdot" ) );
      }

      delete [] buffer;
      buffer = 0;
   }
   
   Config::~Config()
   {
      if ( buffer )
         delete [] buffer;
   }
   
   const char* Config::ReadNode( const char* NodeName, const char* DefaultValue )
   {
      ::rapidxml::xml_node<>* cur_node;
      cur_node = current_node->first_node( NodeName );
      if ( cur_node )
         return cur_node->value();
      return DefaultValue;
   }
   
   bool Config::ParseBool( const char* str )
   {
      ::std::string data( str );
      ::std::transform( data.begin(), data.end(), data.begin(), ::tolower );      
      return data == "true" || data == "1";
   }
}

