/* 
 * File:   XmlCmdToJpg.File.Writer.cpp
 * Author: Jay Sprenkle
 *
 * Created on August 28, 2014
 */
#include "XmlCmdToJpg.File.Writer.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string>
#include <stdexcept>

namespace XmlCmdToJpg
{
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
         if ( ! ofP )
         {
            ::std::string msg( "Can't open file: " );
            msg.append( FileName );
            throw ::std::runtime_error( msg.c_str() );
         }
      }

      void Writer::write( unsigned int const bytes, unsigned char* data )
      {
         unsigned int BytesRead = fwrite( data, 1, bytes, ofP );
         if ( BytesRead != bytes )
         {
            ::std::string msg( "File write failed for file: " );
            msg.append( FileName );
            throw ::std::runtime_error( msg.c_str() );
         }
      }
   }
}
