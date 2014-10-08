/* 
 * File:   XmlCmdImageBlur.Layer.h
 * Author: Jay Sprenkle
 *
 * Created on September 17, 2014
 */
#ifndef XMLCMDIMAGEBLUR_LAYER_H
#define	XMLCMDIMAGEBLUR_LAYER_H

#include "XmlCmdImageBlur.Row.h"

namespace XmlCmdImageBlur
{
   class Layer
   {
   public:
      Layer();
      
      uint32_t    z;
      uint32_t    Width;
      uint32_t    Height;

      ::std::map< uint32_t, Row > RowMap;
      
      Pixel CalculateWeight( uint32_t x, uint32_t y );
   };
}
#endif
