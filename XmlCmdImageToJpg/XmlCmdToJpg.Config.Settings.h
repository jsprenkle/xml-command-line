/* 
 * File:   XmlCmdToJpg.Config.Settings.h
 * Author: Jay Sprenkle
 *
 * DTO objects for containing configuration information
 * 
 * Created on August 21, 2014
 */
#ifndef XMLCMDTOJPG_CONFIG_SETTINGS_H
#define	XMLCMDTOJPG_CONFIG_SETTINGS_H

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <string>

namespace XmlCmdToJpg
{
   namespace Config
   {
      class Settings
      {
      public:
         bool           content;
         uint8_t        Quality; // 0 - 100
         ::std::string  Comment;
         ::std::string  OutputFile;

         Settings();
      };
   }
}

#endif
