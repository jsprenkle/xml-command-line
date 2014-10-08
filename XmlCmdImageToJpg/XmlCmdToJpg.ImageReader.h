/* 
 * File:   XmlCmdToJpg.ImageReader.h
 * Author: Jay Sprenkle
 * 
 * Created on August 21, 2014
 */
#ifndef XMLCMDTOJPG_IMAGEREADER_H
#define	XMLCMDTOJPG_IMAGEREADER_H

#include <stdio.h>
#define __STDC_LIMIT_MACROS
#include <stdint.h>

#include <stdexcept>
#include <map>

#include <rapidxml.hpp>

#include "XmlCmdToJpg.File.Reader.h"

namespace XmlCmdToJpg
{
   class ImageReader
   {
   public:
      ImageReader( File::Reader& FileReader );
      virtual ~ImageReader();
      ::std::string ReadScanLine( uint32_t Row );

      uint32_t Width; /* image width and height, in pixels */
      uint32_t Height;

   private:
      ::rapidxml::xml_node<>* GetFirstNode( ::rapidxml::xml_node<>* Parent, const char* LocalName );
      ::rapidxml::xml_node<>* GetSiblingNode( ::rapidxml::xml_node<>* Parent, const char* LocalName );
      uint32_t NumericalAttribute( ::rapidxml::xml_node<>* node, const char* AttributeName );
      uint8_t NormalizePixelAttribute( ::rapidxml::xml_node<>* node, const char* AttributeName );
      
      char* buffer;
      ::rapidxml::xml_document<> doc;
      ::rapidxml::xml_node<>* RootNode;
      ::rapidxml::xml_node<>* LayerNode;
      ::std::string XmlNamespacePrefix;
      
      ::std::map< uint32_t, ::rapidxml::xml_node<>* > RowMap;
   };
}
#endif
