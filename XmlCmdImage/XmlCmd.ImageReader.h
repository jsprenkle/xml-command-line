/* 
 * File:   XmlCmd.ImageReader.h
 * Author: Jay Sprenkle
 *
 * Created on October 8, 2014
 */
#ifndef XMLCMD_IMAGEREADER_H
#define	XMLCMD_IMAGEREADER_H

#include "XmlCmd.Image.h"
#include <XmlCmd.h>

namespace XmlCmd
{
   /** class to read an image document. Maps parts of an image for easy access */
   class ImageReader
      : public DocumentReader
   {
   public:
      ImageReader( ::File::Reader& rdr );

      ::std::map< uint32_t, Layer > LayerMap;
   };
}
#endif
