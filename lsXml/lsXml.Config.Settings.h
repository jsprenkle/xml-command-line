/* 
 * File:   lsXml.Config.Settings.h
 * Author: Jay Sprenkle
 *
 * DTO objects for containing configuration information
 * 
 * Created on July 30, 2014
 */
#ifndef LSXML_CONFIG_SETTINGS_H
#define	LSXML_CONFIG_SETTINGS_H

namespace lsXml
{
   namespace Config
   {
      class Settings
      {
      public:
         bool dotdot;
         bool recursive;
         bool Context;

         Settings();
      };
   }
}

#endif
