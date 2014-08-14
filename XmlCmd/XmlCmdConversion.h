/* 
 * File:   XmlCmdConversion.h
 * Author: Jay Sprenkle
 * 
 * Created on July 14, 2014
 */
#ifndef XMLCMD_CONVERSION_H
#define	XMLCMD_CONVERSION_H

#include <sstream>
#include <iomanip>

// use zero for unspecified width
template <typename T>
  ::std::string NumberToString ( T Number, int width )
  {
     ::std::ostringstream ss;
     ss << ::std::setw(width) << ::std::setfill('0') << Number;
     return ss.str();
  }



#endif
