/* 
 * File:   File.Writer.cpp
 * Author: Jay Sprenkle
 *
 * Created on August 28, 2014
 */
#include "File.Writer.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <string>
#include <stdexcept>

namespace File
{

   Writer::Writer()
   : ofP( 0 )
   {
   }

   Writer::~Writer()
   {
      if ( ofP )
         fclose( ofP );
   }

   void Writer::open( FILE* handle )
   {
      ofP = handle;
   }

   void Writer::open( const char* filename )
   {
      FileName = filename;

      // open the file
      ofP = fopen( FileName, "wb" );
      if ( !ofP )
      {
         ::std::string msg( "File open failed: " );
         msg.append( ::strerror( errno ) );
         msg.append( ". FileName: " );
         msg.append( FileName );
         throw ::std::runtime_error( msg.c_str() );
      }
   }

   void Writer::write( unsigned int const bytes, unsigned char* data )
   {
      unsigned int count = fwrite( data, 1, bytes, ofP );
      if ( count != bytes )
      {
         ::std::string msg( "File write failed: " );
         msg.append( ::strerror( errno ) );
         msg.append( ". FileName: " );
         msg.append( FileName );
         throw ::std::runtime_error( msg.c_str() );
      }
   }
}
