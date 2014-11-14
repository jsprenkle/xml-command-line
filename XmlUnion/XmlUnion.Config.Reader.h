/* 
 * File:   XmlUnion.Config.Reader.h
 * Author: Jay Sprenkle
 * 
 * Created on September 23, 2014
 */
#ifndef XMLUNION_CONFIG_READER_H
#define	XMLUNION_CONFIG_READER_H

#include <XmlCmd.h>
#include "XmlUnion.Config.Settings.h"

namespace XmlUnion
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
