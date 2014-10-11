/* 
 * File:   XmlCmdImageBlur.Interpolate.cpp
 * Author: Jay Sprenkle
 * 
 * Created on September 23, 2014
 */
#include <time.h>
#include <math.h>

#include "XmlCmdImageBlur.App.h"

namespace XmlCmdImageBlur
{
   App::App( ::File::Reader& rdr )
      : OutputXmlDoc( "http://www.XmlCommandLine.org/Image/1.0", "", "Image" )
      , InputXmlDoc( rdr )
   {
   }
   
   void App::Process( const ::XmlCmdImageBlur::Config::Settings& config )
   {
      uint32_t mWidth = InputXmlDoc.LayerMap[0].Width;
      uint32_t mHeight = InputXmlDoc.LayerMap[0].Height;
      
      if ( mWidth < 1 || mHeight < 1 )
         throw ::std::runtime_error( "Image is too small to apply blur" );
      
      float sigma2 = 2 * config.radius * config.radius;
      const uint32_t size = 5; //good approximation of filter
      const uint32_t zero = 0;

      // foreach layer
      ::std::map< uint32_t, ::XmlCmd::Layer >::const_iterator il;
      for ( il = InputXmlDoc.LayerMap.begin(); il != InputXmlDoc.LayerMap.end(); ++il )
      {
         ::XmlCmd::Layer layer = il->second;

         // create output document Layer node(s)
         OutputXmlDoc.LayerMap[layer.z] = layer;

         // perform blur
         double sum;

         // blur x components
         ::std::map< uint32_t, ::XmlCmd::Row >::const_iterator ir;
         for ( ir = layer.RowMap.begin(); ir != layer.RowMap.end(); ++ir )
         {
            ::XmlCmd::Row row = ir->second;

            // create row
            OutputXmlDoc.LayerMap[layer.z].RowMap[row.y] = row;

            ::std::map< uint32_t, ::XmlCmd::Pixel >::const_iterator ip;
            for ( ip = row.PixelMap.begin(); ip != row.PixelMap.end(); ++ip )
            {
               ::XmlCmd::Pixel pixel = ip->second;

               double r = 0;
               double g = 0;
               double b = 0;
               sum = 0;
               for ( uint32_t x = ::std::max<int>( zero, pixel.x - size ); x <= ::std::min<int>( mWidth - 1, (int)pixel.x + size ); x++ )
               {
                  ::std::map< uint32_t, ::XmlCmd::Pixel >::const_iterator ipIn = row.PixelMap.find( x );
                  if ( ipIn != row.PixelMap.end() )
                  {
                     ::XmlCmd::Pixel pixelIn = ipIn->second;
                     int dx = x - (float)pixel.x;
                     float factor = exp( -dx * dx / sigma2 );
                     sum += factor;
                     r += pixelIn.r * factor;
                     g += pixelIn.g * factor;
                     b += pixelIn.b * factor;
                  }
               };
               for ( uint32_t y = ::std::max<int>( zero, (int)row.y - size ); y <= ::std::min<int>( mHeight - 1, (int)row.y + size ); y++ )
               {
                  ::std::map< uint32_t, ::XmlCmd::Row >::const_iterator irIn = layer.RowMap.find( y );
                  if ( irIn != layer.RowMap.end() )
                  {
                     ::XmlCmd::Row rowIn = irIn->second;
                     ::std::map< uint32_t, ::XmlCmd::Pixel >::const_iterator ipIn = rowIn.PixelMap.find( y );
                     if ( ipIn != row.PixelMap.end() )
                     {
                        ::XmlCmd::Pixel pixelIn = ipIn->second;
                        int dy = y - (float)rowIn.y;
                        float factor = exp( -dy * dy / sigma2 );
                        sum += factor;
                        r += pixelIn.r * factor;
                        g += pixelIn.g * factor;
                        b += pixelIn.b * factor;
                     }
                  }
               };
               // write result to output document
               OutputXmlDoc.LayerMap[layer.z].RowMap[row.y].PixelMap[pixel.x].r = ::std::min<uint32_t>( r / sum, UINT32_MAX );
               OutputXmlDoc.LayerMap[layer.z].RowMap[row.y].PixelMap[pixel.x].g = ::std::min<uint32_t>( g / sum, UINT32_MAX );
               OutputXmlDoc.LayerMap[layer.z].RowMap[row.y].PixelMap[pixel.x].b = ::std::min<uint32_t>( b / sum, UINT32_MAX );
            }
         }
      }
      
      CloneContext();
   }

   void App::CloneContext()
   {
      ::rapidxml::xml_node<>* OutputContextNode;
      
      // if the input file has context then clone it
      ::rapidxml::xml_node<>* InputContextNode = InputXmlDoc.root->first_node( "Context" );
      if ( InputContextNode )
      {
         OutputContextNode = OutputXmlDoc.clone_node( InputContextNode );
         OutputXmlDoc.root->append_node( OutputContextNode );
      }
      // if no input context then create one
      else
         OutputContextNode = OutputXmlDoc.AppendChildNode( OutputXmlDoc.root, "Context" );
      
      // add update node to context area
      ::rapidxml::xml_node<>* UpdateNode = OutputXmlDoc.AppendChildNode( OutputContextNode, "Update" );
      char time_buf[21];
      time_t now;
      time( &now );
      strftime( time_buf, 21, "%Y-%m-%dT%H:%S:%MZ", gmtime( &now ) );
      OutputXmlDoc.AppendAttribute( UpdateNode, "Updated", time_buf );
      
      ::rapidxml::xml_node<>* SourceNode = OutputXmlDoc.AppendChildNode( UpdateNode, "Source" );
      OutputXmlDoc.AppendAttribute( SourceNode, "Name", "XmlCmdImageBlur" );
      OutputXmlDoc.AppendAttribute( SourceNode, "Version", "1.0" );
   }
}
