/* 
 * File:   XmlCmdToJpg.ImageWriter.h
 * Author: Jay Sprenkle
 *
 * Class to write an image object to an xml document described by the image schema
 * 
 * Created on August 21, 2014
 */
#ifndef XMLCMDTOJPG_IMAGEWRITER_H
#define	XMLCMDTOJPG_IMAGEWRITER_H

/*
 * Include file for users of JPEG library.
 * You will need to have included system headers that define at least
 * the typedefs FILE and size_t before you can include jpeglib.h.
 * (stdio.h is sufficient on ANSI-conforming systems.)
 * You may also wish to include "jerror.h".
 */
#include "jpeglib.h"

#include "XmlCmdToJpg.Config.Settings.h"
#include "XmlCmdToJpg.ImageReader.h"
#include "XmlCmdToJpg.File.Writer.h"

namespace XmlCmdToJpg
{
   class ImageWriter
   {
   public:
      ImageWriter( const Config::Settings& config, ::XmlCmdToJpg::ImageReader& imgRdr );

      void write( File::Writer& wrt );

      JSAMPLE* image_buffer;	/* Points to large array of R,G,B-order data */
      
   private:
      ::XmlCmdToJpg::ImageReader&   imgRdr;
      const Config::Settings&       config;
   };
}
#endif
