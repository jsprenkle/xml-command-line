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

#include <XmlCmd.h>
#include "XmlCmdImageToPng.Config.Settings.h"

namespace XmlCmdImageToPng
{
   namespace Config
   {
      class Reader
         : public ::XmlCmd::DocumentReader
      {
      public:
         Reader( const char* FileName );
         
         Settings Parse();
      };
   }
}
#endif
