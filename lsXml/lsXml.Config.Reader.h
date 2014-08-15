/* 
 * File:   lsXml.Config.Reader.h
 * Author: Jay Sprenkle
 *
 * I/O for DTO object
 * 
 * Created on July 30, 2014
 */
#ifndef LSXML_CONFIG_READER_H
#define	LSXML_CONFIG_READER_H

#include "lsXml.Config.Settings.h"

namespace lsXml
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
