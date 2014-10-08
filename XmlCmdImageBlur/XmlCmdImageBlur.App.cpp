/* 
 * File:   XmlCmdImageBlur.Interpolate.cpp
 * Author: Jay Sprenkle
 * 
 * Created on September 23, 2014
 */
#include <time.h>
#include <rapidxml_print.hpp>

#include "XmlCmdImageBlur.App.h"

namespace XmlCmdImageBlur
{
   App::App( ::File::Reader& rdr )
      : OutputXmlDoc( "http://www.XmlCommandLine.org/Image/1.0", "", "Image" )
      , InputXmlDoc( rdr, "Image", "http://www.XmlCommandLine.org/Image/1.0" )
   {
   }
   
   App::~App()
   {
   }

   void App::ParseInput()
   {
      ::rapidxml::xml_node<>* ContentNode = InputXmlDoc.root->first_node( "Content" );
      if ( ! ContentNode )
         throw ::std::runtime_error( "The image has no Content node" );

      ::rapidxml::xml_node<>* LayerNode = ContentNode->first_node( "Layer" );
      if ( ! LayerNode )
         throw ::std::runtime_error( "The image has no Layer node" );
      
      layer.z = InputXmlDoc.ReadNumericAttribute( LayerNode, "z" );
      layer.Width = InputXmlDoc.ReadNumericAttribute( LayerNode, "Width" );
      layer.Height = InputXmlDoc.ReadNumericAttribute( LayerNode, "Height" );
      
      ::rapidxml::xml_node<>* RowNode = LayerNode->first_node( "Row" );
      if ( ! RowNode )
         throw ::std::runtime_error( "The image has no Row nodes" );
      while ( RowNode )
      {
         Row row;
         row.y = InputXmlDoc.ReadNumericAttribute( RowNode, "y" );

         ::rapidxml::xml_node<>* PixelNode = RowNode->first_node( "Pixel" );
         while ( PixelNode )
         {
            Pixel pixel;
            pixel.x = InputXmlDoc.ReadNumericAttribute( PixelNode, "x" );
            pixel.r = InputXmlDoc.ReadNumericAttribute( PixelNode, "r" );
            pixel.g = InputXmlDoc.ReadNumericAttribute( PixelNode, "g" );
            pixel.b = InputXmlDoc.ReadNumericAttribute( PixelNode, "b" );
            pixel.a = InputXmlDoc.ReadNumericAttribute( PixelNode, "a" );
            row.PixelMap[pixel.x] = pixel;

            PixelNode = RowNode->next_sibling( "Pixel" );
         }
         layer.RowMap[row.y] = row;
         
         RowNode = LayerNode->next_sibling( "Row" );
      }
   }

//   double const pi = 3.14159;
//   // r = radius
//   void App::gaussBlur_1( float r )
//   {
//      double rs = ceil( r * 2.57f ); // significant radius
//      for ( uint32_t i = 0; i < height; i++ )
//         for ( uint32_t j = 0; j < width; j++ )
//         {
//            double val = 0, wsum = 0;
//            for ( uint32_t iy = i - rs; iy < i + rs + 1; iy++ )
//               for ( uint32_t ix = j - rs; ix < j + rs + 1; ix++ )
//               {
//                  double x = ::min( width - 1, ::max( 0, ix ) );
//                  double y = ::min( height - 1, ::max( 0, iy ) );
//                  double dsq = ( ix - j )*( ix - j )+( iy - i )*( iy - i );
//                  double wght = ::exp( -dsq / ( 2 * r * r ) ) / ( pi * 2 * r * r );
//                  val += png[4 * ((y * width) + x)] * wght;
//                  val += wght;
//               }
//            output[4 * ((i * width) + j)] = ::round( val / wsum );
//         }
//   }      

   void App::Process( const ::XmlCmdImageBlur::Config::Settings& config )
   {
      ParseInput();
//      output.reserve( png.size() );
//      gaussBlur_1( config.sigma );
      
      ::rapidxml::xml_node<>* ContentNode = OutputXmlDoc.AppendChildNode( OutputXmlDoc.root, "Content" );
    
      ::rapidxml::xml_node<>* LayerNode = OutputXmlDoc.AppendChildNode( ContentNode, "Layer" );
      OutputXmlDoc.AppendAttribute( LayerNode, "z", toString< uint32_t >( layer.z ) );
      OutputXmlDoc.AppendAttribute( LayerNode, "Width", toString< uint32_t >( layer.Width ) );
      OutputXmlDoc.AppendAttribute( LayerNode, "Height", toString< uint32_t >( layer.Height ) );

      // if no input is provided use an empty doppelganger
      Row EmptyRow;
      
      // foreach Row
      for ( uint32_t y = 0; y < layer.Height; ++y )
      {
         ::rapidxml::xml_node<>* RowNode = OutputXmlDoc.AppendChildNode( LayerNode, "Row" );
         OutputXmlDoc.AppendAttribute( RowNode, "y", toString< uint32_t >( y ) );

         Row* row;
         ::std::map< uint32_t, Row >::iterator ir = layer.RowMap.find( y );
         if ( ir != layer.RowMap.end() )
            row = &(ir->second);
         else
            row = &EmptyRow;

         // foreach Pixel
         for ( uint32_t x = 0; x < layer.Width; ++x )
         {
            ::rapidxml::xml_node<>* PixelNode = OutputXmlDoc.AppendChildNode( RowNode, "Pixel" );
            OutputXmlDoc.AppendAttribute( PixelNode, "x", toString< uint32_t >( x ) );

            Pixel InterpolatedPixel;
            Pixel* pixel;
            ::std::map< uint32_t, Pixel >::iterator ip = row->PixelMap.find( x );
            if ( ip != row->PixelMap.end() )
               pixel = &(ip->second);
            else
            {
               //InterpolatedPixel = layer.CalculateWeight( x, y );
               //pixel = &InterpolatedPixel;
            }

            OutputXmlDoc.AppendAttribute( PixelNode, "r", toString< uint32_t >( pixel->r ) );
            OutputXmlDoc.AppendAttribute( PixelNode, "g", toString< uint32_t >( pixel->g ) );
            OutputXmlDoc.AppendAttribute( PixelNode, "b", toString< uint32_t >( pixel->b ) );
            OutputXmlDoc.AppendAttribute( PixelNode, "a", toString< uint32_t >( pixel->a ) );
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

   void App::Write( ::File::Writer& wrt )
   {
      // write result as an XML document
      ::File::WriterIterator wit( wrt );
      ::rapidxml::print( wit, OutputXmlDoc, ::rapidxml::print_no_indenting );
   }
}
