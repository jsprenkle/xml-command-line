/* 
 * File:   XmlCmdPngToImage.Config.Settings.h
 * Author: Jay Sprenkle
 *
 * DTO objects for containing configuration information
 * 
 * Created on Septemver 24, 2014
 */
#ifndef XMLCMDPNGTOIMAGE_CONFIG_SETTINGS_H
#define	XMLCMDPNGTOIMAGE_CONFIG_SETTINGS_H

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <string>

namespace XmlCmdPngToImage
{
   namespace Config
   {
      class Settings
      {
      public:
         ::std::string OutputFile;
         ::std::string InputFile;
         float sigma;

         Settings();
      };
   }
}

#endif
