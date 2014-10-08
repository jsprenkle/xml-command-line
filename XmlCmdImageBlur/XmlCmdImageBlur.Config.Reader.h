/* 
 * File:   XmlCmdImageBlur.Config.Reader.h
 * Author: Jay Sprenkle
 * 
 * Created on September 23, 2014
 */
#ifndef XMLCMDIMAGEBLUR_CONFIG_READER_H
#define	XMLCMDIMAGEBLUR_CONFIG_READER_H

#include <XmlCmd.h>
#include "XmlCmdImageBlur.Config.Settings.h"

namespace XmlCmdImageBlur
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
