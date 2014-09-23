/* 
 * File:   XmlCmdImageToPng.Config.Settings.h
 * Author: Jay Sprenkle
 *
 * DTO objects for containing configuration information
 * 
 * Created on August 18, 2014
 */
#ifndef XMLCMDIMAGETOPNG_CONFIG_SETTINGS_H
#define	XMLCMDIMAGETOPNG_CONFIG_SETTINGS_H

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <string>

namespace XmlCmdImageToPng
{
   namespace Config
   {
      class Settings
      {
      public:
         ::std::string OutputFile;
         ::std::string InputFile;

         Settings();
      };
   }
}

#endif
