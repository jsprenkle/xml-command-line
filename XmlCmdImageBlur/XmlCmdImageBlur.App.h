/* 
 * File:   XmlCmdImageBlur.Interpolate.h
 * Author: Jay Sprenkle
 * 
 * Created on September 23, 2014
 */
#ifndef XMLCMDINTERPOLATE_INTERPOLATE_H
#define	XMLCMDINTERPOLATE_INTERPOLATE_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <vector>
#include <algorithm>

#include <string.h>

#include <XmlCmd.h>

#include "XmlCmdImageBlur.Config.Settings.h"
#include "XmlCmd.ImageReader.h"
#include "XmlCmd.ImageWriter.h"

namespace XmlCmdImageBlur
{
   class App
   {
   public:
      App( ::File::Reader& rdr );

      void Process( const ::XmlCmdImageBlur::Config::Settings& config );

      ::XmlCmd::ImageReader   InputXmlDoc;
      ::XmlCmd::ImageWriter   OutputXmlDoc;

   protected:
      char* buffer;

      void CloneContext();
   };
}
#endif
