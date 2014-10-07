/* 
 * File:   conversion.h
 * Author: jsprenkle
 *
 * string conversion utilities
 *
 * Created on August 23, 2010
 */

#ifndef CONVERSION_H
#define	CONVERSION_H

#include <sstream>

//---------------------------------------------------------------------------
// utility routines to string transformations
// templates require  #include <sstream>
//---------------------------------------------------------------------------
template<typename T> T stringTo( const ::std::string& s )
   {
      ::std::istringstream iss(s);
      T x;
      iss >> x;
      return x;
   };

template<typename T> inline ::std::string toString( const T& x )
   {
      ::std::ostringstream o;
      o << x;
      return o.str();
   }

#endif
