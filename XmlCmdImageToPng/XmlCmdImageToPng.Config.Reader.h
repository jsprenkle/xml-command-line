/* 
 * File:   XmlCmdImageToPng.Config.Reader.h
 * Author: Jay Sprenkle
 *
 * I/O for DTO object
 * 
 * Created on August 18, 2014
 */
#ifndef XMLCMDIMAGETOPNG_CONFIG_READER_H
#define	XMLCMDIMAGETOPNG_CONFIG_READER_H

#include "XmlCmdImageToPng.Config.Settings.h"

namespace XmlCmdImageToPng
{
   namespace Config
   {
      class Reader
      {
      public:
         Reader( const char* FileName );
         ~Reader();
         
         Settings Parse();
         
      private:
         char* buffer;
      };
   }
}
#endif
