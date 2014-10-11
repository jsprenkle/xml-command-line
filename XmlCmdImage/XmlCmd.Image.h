/* 
 * File:   XmlCmd.Image.h
 * Author: Jay Sprenkle
 *
 * P.O.D. (Plain old data) classes to map image content
 * 
 * Created on October 9, 2014
 */
#ifndef XMLCMD_IMAGE_H
#define	XMLCMD_IMAGE_H

#include <stdint.h>
#include <map>

#include <XmlCmd.h>

namespace XmlCmd
{
   // <editor-fold defaultstate="collapsed" desc="Pixel P.O.D. class">
   class Pixel
   {
   public:
      Pixel();
      
      const Pixel operator*( const float& factor ) const;
      const Pixel operator/( const float& factor ) const;
      const Pixel operator+( const Pixel& p ) const;
      Pixel& operator+=( const Pixel &rhs );

      uint32_t x;
      uint32_t r;
      uint32_t g;
      uint32_t b;
      uint32_t a;
   };
   // </editor-fold>

   // <editor-fold defaultstate="collapsed" desc="Row P.O.D. class">
   class Row
   {
   public:
      Row();

      uint32_t y;

      ::std::map< uint32_t, Pixel > PixelMap;
   };
   // </editor-fold>

   // <editor-fold defaultstate="collapsed" desc="Layer P.O.D. class">
   class Layer
   {
   public:
      Layer();

      uint32_t z;
      uint32_t Width;
      uint32_t Height;

      ::std::map< uint32_t, Row > RowMap;
   };
   // </editor-fold>
}

#endif
