/* 
 * File:   XmlCmdPngToImage.Convert.h
 * Author: Jay Sprenkle
 *
 * Created on September 24, 2014, 1:52 PM
 */

#ifndef XMLCMDPNGTOIMAGE_APP_H
#define	XMLCMDPNGTOIMAGE_APP_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <vector>
#include <algorithm>
#include <stdexcept>

#include <string.h>

#include <rapidxml.hpp>

#include "File.Reader.h"
#include "File.Writer.h"
#include "XmlCmdPngToImage.Config.Settings.h"
#include "XmlCmd.h"

namespace XmlCmdPngToImage
{
   class App
   {
   public:
      App();
      virtual ~App();

      void Read( ::File::Reader& rdr );
      void Process( const Config::Settings& config );
      void Write( ::File::Writer& wrt );

   protected:
      ::std::string Normalize( uint8_t c );
//      void gaussBlur_1( float r );
      
      ::XmlCmd::Document OutputXmlDoc;
      ::std::vector<unsigned char> png;
      unsigned width, height;
   };
}
#endif

