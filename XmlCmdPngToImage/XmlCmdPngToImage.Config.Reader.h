/* 
 * File:   XmlCmdPngToImage.Config.Reader.h
 * Author: Jay Sprenkle
 *
 * I/O for DTO object
 * 
 * Created on September 24, 2014
 */
#ifndef XMLCMDPNGTOIMAGE_CONFIG_READER_H
#define	XMLCMDPNGTOIMAGE_CONFIG_READER_H

#include <XmlCmd.h>
#include "XmlCmdPngToImage.Config.Settings.h"

namespace XmlCmdPngToImage
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
