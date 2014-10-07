/* 
 * File:   XmlCmdPngToImage.Convert.cpp
 * Author: Jay Sprenkle
 * 
 * Created on September 24, 2014
 */
#include <math.h>

#include "lodepng.h"
#include <rapidxml_print.hpp>

#include "XmlCmdPngToImage.App.h"

#undef SQR
#define SQR(a) ((a)*(a))

#include <iostream>

namespace XmlCmdPngToImage
{
   App::App()
      : width( 0 )
      , height( 0 )
      , OutputXmlDoc( "http://www.XmlCommandLine.org/Image/1.0", "", "Image" )
   {
   }

   App::~App()
   {
   }

   void App::Read( ::File::Reader& rdr )
   {
      size_t count = rdr.size();
      char* p = new char[ count ];
      if ( !p )
      {
         ::std::string msg( "Memory allocation failed. Requested " );
         msg.append( toString< size_t >( count ) );
         msg.append( " bytes." );
         throw ::std::runtime_error( msg.c_str() );
      }
      rdr.read( rdr.size(), (unsigned char*) p );
      
      std::vector<unsigned char> buffer( p, p + count );
      unsigned error = ::lodepng::decode( png, width, height, buffer, LCT_RGBA, 8 );
      if ( error )
      {
         ::std::string msg( "decoder failed: " );
         msg.append( lodepng_error_text( error ) );
         throw ::std::runtime_error( msg.c_str() );
      }
      
      delete p;
   }

   ::std::string App::Normalize( uint8_t c )
   {
      uint32_t n = (UINT32_MAX * (uint64_t) c) / UINT8_MAX;
      return toString< uint32_t >( n );
   }

   void App::Process( const Config::Settings& config )
   {
      ::rapidxml::xml_node<>* Content = OutputXmlDoc.AppendChildNode( OutputXmlDoc.root, "Content" );
    
      ::rapidxml::xml_node<>* LayerNode = OutputXmlDoc.AppendChildNode( Content, "Layer" );
      OutputXmlDoc.AppendAttribute( LayerNode, "z", "0" );
      OutputXmlDoc.AppendAttribute( LayerNode, "Width", toString< int >( width ) );
      OutputXmlDoc.AppendAttribute( LayerNode, "Height", toString< int >( height ) );

      uint32_t i = 0;
      for ( uint32_t y = 0; y < height; ++y )
      {
         ::rapidxml::xml_node<>* RowNode = OutputXmlDoc.AppendChildNode( LayerNode, "Row" );
         OutputXmlDoc.AppendAttribute( RowNode, "y", toString< int >( y ) );
         
         for ( uint32_t x = 0; x < width; ++x )
         {
            ::rapidxml::xml_node<>* PixelNode = OutputXmlDoc.AppendChildNode( RowNode, "Pixel" );
            OutputXmlDoc.AppendAttribute( PixelNode, "x", toString< int >( x ) );
            OutputXmlDoc.AppendAttribute( PixelNode, "r", Normalize( png.at(i++) ) );
            OutputXmlDoc.AppendAttribute( PixelNode, "g", Normalize( png.at(i++) ) );
            OutputXmlDoc.AppendAttribute( PixelNode, "b", Normalize( png.at(i++) ) );
            OutputXmlDoc.AppendAttribute( PixelNode, "a", Normalize( png.at(i++) ) );
         }
      }
   }

   void App::Write( ::File::Writer& wrt )
   {
      // write result as an XML document
      ::File::WriterIterator wit( wrt );
      ::rapidxml::print( wit, OutputXmlDoc, ::rapidxml::print_no_indenting );
   }
}
