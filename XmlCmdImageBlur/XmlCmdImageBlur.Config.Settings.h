/* 
 * File:   XmlCmdImageBlur.Config.Settings.h
 * Author: Jay Sprenkle
 *
 * DTO objects for containing configuration information
 * 
 * Created on September 23, 2014
 */
#ifndef XMLCMDIMAGEBLUR_CONFIG_SETTINGS_H
#define	XMLCMDIMAGEBLUR_CONFIG_SETTINGS_H

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <string>

namespace XmlCmdImageBlur
{
   namespace Config
   {
      class Settings
      {
      public:
         uint32_t Amount;
         
         ::std::string OutputFile;
         ::std::string InputFile;

         Settings();
      };
   }
}

#endif
