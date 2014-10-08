/* 
 * File:   XmlCmdToJpg.Config.Reader.h
 * Author: Jay Sprenkle
 *
 * I/O for DTO object
 * 
 * Created on July 30, 2014
 */
#ifndef XMLCMDTOJPG_CONFIG_READER_H
#define	XMLCMDTOJPG_CONFIG_READER_H

#include "XmlCmdToJpg.Config.Settings.h"

namespace XmlCmdToJpg
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
