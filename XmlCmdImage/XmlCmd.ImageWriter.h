/* 
 * File:   XmlCmd.ImageWriter.h
 * Author: Jay Sprenkle
 * 
 * Created on October 8, 2014
 */
#ifndef XMLCMD_IMAGEWRITER_H
#define	XMLCMD_IMAGEWRITER_H

#include "XmlCmd.Image.h"
#include <XmlCmd.h>

namespace XmlCmd
{
   class ImageWriter
      : public DocumentWriter
   {
   public:
      ImageWriter( const char* NamespaceString = "default", const char* prefix = "ns", const char* type = "root", const char* Declaration = 0 );

      void Write( ::File::Writer& wrt );

      ::std::map< uint32_t, Layer > LayerMap;
   };
}
#endif
