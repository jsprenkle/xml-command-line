/* 
 * File:   XmlCmdToJpg.File.Reader.cpp
 * Author: Jay Sprenkle
 *
 * Created on August 21, 2014
 */
#include "XmlCmdToJpg.File.Reader.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <string>
#include <stdexcept>

namespace XmlCmdToJpg
{
   namespace File
   {
      Reader::Reader()
         : ifP( 0 )
      {
      }

      Reader::~Reader()
      {
         if ( ifP )
            fclose( ifP );
      }

      void Reader::open( FILE* handle )
      {
         ifP = handle;
      }
      
      void Reader::open( const char* filename )
      {
         FileName = filename;
         
         // open the file
         ifP = fopen( FileName, "rb" );
         if ( ! ifP )
         {
            ::std::string msg( "Can't open file: " );
            msg.append( FileName );
            throw ::std::runtime_error( msg.c_str() );
         }
      }
      
      void Reader::read( unsigned int const bytes, unsigned char* data )
      {
         unsigned int BytesRead = fread( data, 1, bytes, ifP );
         if ( BytesRead != bytes )
         {
            ::std::string msg( "File read failed for file: " );
            msg.append( FileName );
            throw ::std::runtime_error( msg.c_str() );
         }
      }

      size_t Reader::size()
      {
         struct stat buf;
         if ( stat( FileName, &buf ) != 0 )
         {
            ::std::string msg( "Reader error: " );
            msg.append( ::strerror( errno ) );
            msg.append( ". FileName: " );
            msg.append( FileName );
            throw ::std::runtime_error( msg.c_str() );
         }
         return buf.st_size;
      }
   }
}
