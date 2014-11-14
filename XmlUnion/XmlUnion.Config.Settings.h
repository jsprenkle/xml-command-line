/* 
 * File:   XmlUnion.Config.Settings.h
 * Author: Jay Sprenkle
 *
 * DTO objects for containing configuration information
 * 
 * Created on September 23, 2014
 */
#ifndef XMLUNION_CONFIG_SETTINGS_H
#define	XMLUNION_CONFIG_SETTINGS_H

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <string>

namespace XmlUnion
{
   namespace Config
   {
      class Settings
      {
      public:
         ::std::string OutputFile;
         bool Warnings;

         Settings();
      };
   }
}

#endif
