/* 
 * File:   XmlCmdImageToPng.Convert.h
 * Author: dsprenkle
 *
 * Created on September 19, 2014, 1:52 PM
 */

#ifndef XMLCMDIMAGETOPNGCONVERT_H
#define	XMLCMDIMAGETOPNGCONVERT_H

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

#include "conversion.h"

#include "File.Reader.h"
#include "File.Writer.h"
#include "XmlCmdImageToPng.Config.Settings.h"
#include "XmlCmd.Document.h"

namespace XmlCmdImageToPng
{
   class Convert
   {
   public:
      Convert();
      virtual ~Convert();

      void Read( ::File::Reader& rdr );
      void Process( const ::XmlCmdImageToPng::Config::Settings& config );
      void Write( ::File::Writer& wrt );

   protected:
      char* buffer;
      ::XmlCmd::Document InputXmlDoc;
      std::vector<unsigned char> png;
   };
}
#endif

