/* 
 * File:   XmlCmdImageBlur.Row.h
 * Author: Jay Sprenkle
 *
 * Created on September 23, 2014
 */
#ifndef XMLCMDIMAGEBLUR_ROW_H
#define	XMLCMDIMAGEBLUR_ROW_H

#include <map>
#include "XmlCmdImageBlur.Pixel.h"

namespace XmlCmdImageBlur
{
   class Row
   {
   public:
      Row();
      
      uint32_t    y;

      ::std::map< uint32_t, Pixel > PixelMap;
   };
}
#endif
