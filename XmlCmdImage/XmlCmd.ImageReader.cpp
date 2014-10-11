/* 
 * File:   XmlCmd.ImageReader.cpp
 * Author: Jay Sprenkle
 * 
 * Created on October 8, 2014
 */
#include "XmlCmd.ImageReader.h"

namespace XmlCmd
{
   ImageReader::ImageReader( ::File::Reader& rdr )
      : DocumentReader( rdr, "Image", "http://www.XmlCommandLine.org/Image/1.0" )
   {
      ::rapidxml::xml_node<>* ContentNode = root->first_node( "Content" );
      if ( ! ContentNode )
         throw ::std::runtime_error( "The image has no Content node" );

      ::rapidxml::xml_node<>* LayerNode = ContentNode->first_node( "Layer" );
      if ( ! LayerNode )
         throw ::std::runtime_error( "The image has no Layer nodes" );
      while ( LayerNode )
      {
         Layer layer;
         layer.z = ReadNumericAttribute( LayerNode, "z" );
         layer.Width = ReadNumericAttribute( LayerNode, "Width" );
         layer.Height = ReadNumericAttribute( LayerNode, "Height" );

         ::rapidxml::xml_node<>* RowNode = LayerNode->first_node( "Row" );
         if ( ! RowNode )
            throw ::std::runtime_error( "The image has no Row nodes" );
         while ( RowNode )
         {
            Row row;
            row.y = ReadNumericAttribute( RowNode, "y" );

            ::rapidxml::xml_node<>* PixelNode = RowNode->first_node( "Pixel" );
            while ( PixelNode )
            {
               Pixel pixel;
               pixel.x = ReadNumericAttribute( PixelNode, "x" );
               pixel.r = ReadNumericAttribute( PixelNode, "r" );
               pixel.g = ReadNumericAttribute( PixelNode, "g" );
               pixel.b = ReadNumericAttribute( PixelNode, "b" );
               pixel.a = ReadNumericAttribute( PixelNode, "a" );
               row.PixelMap[pixel.x] = pixel;

               PixelNode = PixelNode->next_sibling( "Pixel" );
            }
            layer.RowMap[row.y] = row;

            RowNode = RowNode->next_sibling( "Row" );
         }
         LayerMap[layer.z] = layer;

         LayerNode = LayerNode->next_sibling( "Layer" );
      }
   }
}
