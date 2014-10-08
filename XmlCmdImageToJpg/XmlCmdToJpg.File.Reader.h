/* 
 * File:   XmlCmdToJpg.File.Reader.h
 * Author: Jay Sprenkle
 *
 * Created on August 21, 2014
 */
#ifndef XMLCMDTOJPG_FILE_READER_H
#define	XMLCMDTOJPG_FILE_READER_H

#include <stdio.h>
#include <stdexcept>

namespace XmlCmdToJpg
{
   namespace File
   {
      class Reader
      {
      public:
         Reader();
         virtual ~Reader();

         void open( const char* filename );
         void open( FILE* handle );
         void read( unsigned int const bytes, unsigned char* data );
         
         size_t size();

         const char* FileName;

      private:
         FILE* ifP;
      };
   }
}
#endif
