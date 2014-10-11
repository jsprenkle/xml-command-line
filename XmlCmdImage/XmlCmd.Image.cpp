/* 
 * File:   XmlCmd.Image.cpp
 * Author: Jay Sprenkle
 * 
 * Created on October 9, 2014
 */
#include "XmlCmd.Image.h"

namespace XmlCmd
{
   // <editor-fold defaultstate="collapsed" desc="Pixel P.O.D. class">
   Pixel::Pixel()
      : x( 0 )
      , r( 0 )
      , g( 0 )
      , b( 0 )
      , a( 0 )
   {
   }
   
   const Pixel Pixel::operator*( const float& factor ) const
   {
      Pixel result;
      result.r = r * factor;
      result.g = g * factor;
      result.b = b * factor;
      result.a = a;
      result.x = x;
      return result;
   }

   const Pixel Pixel::operator/( const float& factor ) const
   {
      Pixel result;
      result.r = r / factor;
      result.g = g / factor;
      result.b = b / factor;
      result.a = a;
      result.x = x;
      return result;
   }
   
   const Pixel Pixel::operator+( const Pixel& p ) const
   {
      Pixel result;
      result.r = r + p.r;
      result.g = g + p.g;
      result.b = b + p.b;
      result.a = p.a;
      result.x = p.x;
      return result;
   }

   Pixel& Pixel::operator+=( const Pixel &rhs )
   {
      r += rhs.r;
      g += rhs.g;
      b += rhs.b;
      return *this;
   }
   // </editor-fold>

   // <editor-fold defaultstate="collapsed" desc="Row P.O.D. class">
   Row::Row()
      : y( 0 )
   {
   };
   // </editor-fold>

   // <editor-fold defaultstate="collapsed" desc="Layer P.O.D. class">
   Layer::Layer()
      : z( 0 )
      , Width( 0 )
      , Height( 0 )
   {
   }
   // </editor-fold>
}
