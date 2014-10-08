/* 
 * File:   XmlCmdImageBlur.Pixel.h
 * Author: Jay Sprenkle
 *
 * Created on September 23, 2014
 */
#ifndef XMLCMDIMAGEBLUR_PIXEL_H
#define	XMLCMDIMAGEBLUR_PIXEL_H

#include <stdint.h>

namespace XmlCmdImageBlur
{
   class Pixel
   {
   public:
      Pixel();
      
      uint32_t    x;
      uint32_t    r;
      uint32_t    g;
      uint32_t    b;
      uint32_t    a;
   };
}
#endif
