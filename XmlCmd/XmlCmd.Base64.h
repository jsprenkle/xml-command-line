/* 
 * File:   XmlCmd.Base64.h
 * Author: Jay Sprenkle
 *
 * Created on July 15, 2014, 1:32 PM
 */
#ifndef XMLCMD_BASE64_H
#define	XMLCMD_BASE64_H

#include <string>

namespace XmlCmd
{
   ::std::string base64_encode( unsigned char const* bytes_to_encode, unsigned int in_len );
   ::std::string base64_decode( ::std::string const& encoded_string );
}
#endif

