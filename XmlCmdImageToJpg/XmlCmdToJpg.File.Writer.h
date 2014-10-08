/* 
 * File:   XmlCmdToJpg.File.Writer.h
 * Author: Jay Sprenkle
 *
 * Created on August 28, 2014
 */
#ifndef XMLCMDTOJPGFILEWRITER_H
#define	XMLCMDTOJPGFILEWRITER_H

#include <stdio.h>
#include <stdexcept>

namespace XmlCmdToJpg
{
   namespace File
   {
      class Writer
      {
      public:
         Writer();
         virtual ~Writer();

         void open( const char* filename );
         void open( FILE* handle );
         void write( unsigned int const bytes, unsigned char* data );

         const char* FileName;
         FILE* ofP;
      };
   }
}
#endif
