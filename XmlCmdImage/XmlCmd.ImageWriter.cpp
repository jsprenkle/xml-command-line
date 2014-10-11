/* 
 * File:   XmlCmd.ImageWriter.cpp
 * Author: Jay Sprenkle
 * 
 * Created on October 8, 2014
 */
#include "XmlCmd.ImageWriter.h"

namespace XmlCmd
{
   ImageWriter::ImageWriter( const char* NamespaceString, const char* prefix, const char* type, const char* Declaration )
      : DocumentWriter( NamespaceString, prefix, type, Declaration )
   {
   }

   void ImageWriter::Write( ::File::Writer& wrt )
   {
      // create output document content node
      ::rapidxml::xml_node<>* ContentNode = AppendChildNode( root, "Content" );

      // foreach layer
      ::std::map< uint32_t, ::XmlCmd::Layer >::const_iterator il;
      for ( il = LayerMap.begin(); il != LayerMap.end(); ++il )
      {
         ::XmlCmd::Layer layer = il->second;
      
         ::rapidxml::xml_node<>* LayerNode = AppendChildNode( ContentNode, "Layer" );
         AppendAttribute( LayerNode, "z", toString< uint32_t >( layer.z ) );
         AppendAttribute( LayerNode, "Width", toString< uint32_t >( layer.Width ) );
         AppendAttribute( LayerNode, "Height", toString< uint32_t >( layer.Height ) );
         
         ::std::map< uint32_t, ::XmlCmd::Row >::const_iterator ir;
         for ( ir = layer.RowMap.begin(); ir != layer.RowMap.end(); ++ir )
         {
            ::XmlCmd::Row row = ir->second;

            ::rapidxml::xml_node<>* RowNode = AppendChildNode( LayerNode, "Row" );
            AppendAttribute( RowNode, "y", toString< uint32_t >( row.y ) );
            
            ::std::map< uint32_t, ::XmlCmd::Pixel >::const_iterator ip;
            for ( ip = row.PixelMap.begin(); ip != row.PixelMap.end(); ++ip )
            {
               ::XmlCmd::Pixel pixel = ip->second;
               
               ::rapidxml::xml_node<>* PixelNode = AppendChildNode( RowNode, "Pixel" );
               AppendAttribute( PixelNode, "x", toString< uint32_t >( pixel.x ) );
               AppendAttribute( PixelNode, "r", toString< uint32_t >( pixel.r ) );
               AppendAttribute( PixelNode, "g", toString< uint32_t >( pixel.g ) );
               AppendAttribute( PixelNode, "b", toString< uint32_t >( pixel.b ) );
               AppendAttribute( PixelNode, "a", toString< uint32_t >( pixel.a ) );
            }
         }
      }

      // write result as an XML document
      DocumentWriter::Write( wrt );
   }
}

