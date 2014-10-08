/* 
 * File:   XmlCmdToJpg.ImageReader.cpp
 * Author: Jay Sprenkle
 * 
 * Created on August 21, 2014
 */
#include "XmlCmdToJpg.ImageReader.h"

#include <stdio.h>
#include <errno.h>

#include <vector>
#include <algorithm>

#include <string.h>

namespace XmlCmdToJpg
{
   ImageReader::ImageReader( File::Reader& FileReader )
      : buffer( 0 )
      , Width( 0 )
      , Height( 0 )
   {
      // <editor-fold defaultstate="collapsed" desc="Load the xml into buffer">
      // allocate space for content
      size_t size = FileReader.size();
      buffer = (char*) new char[size + 1];
      FileReader.read( size, (unsigned char*) buffer );

      // ensure null termination
      buffer[size] = 0;
      // </editor-fold>

      try
      {
         doc.parse< ::rapidxml::parse_no_data_nodes | ::rapidxml::parse_trim_whitespace > ( buffer );
      }
      catch ( ::rapidxml::parse_error e )
      {
         ::std::string msg( e.what() );
         msg.append( " near '" );
         char buffer[64];
         strncpy( buffer, e.where<char>(), sizeof (buffer ) - 2 );
         buffer[sizeof (buffer ) - 1] = 0;
         msg.append( buffer );
         msg.append( "'" );
         throw ::std::runtime_error( msg.c_str() );
      }

      RootNode = doc.first_node();
      if ( !RootNode )
         throw ::std::runtime_error( "The input file is invalid or has no root node" );

      // check the root and namespace to see if it's an lsXML configuration file
      ::std::string XmlNamespaceAttribName( "xmlns" );

      // get the namespace prefix (if present)
      ::std::string RootNodeName( RootNode->name(), RootNode->name_size() );
      size_t separator = RootNodeName.find( ":" );
      if ( separator != ::std::string::npos )
      {
         // extract text prefix
         XmlNamespacePrefix.assign( RootNodeName.c_str(), separator );

         // create attribute name
         XmlNamespaceAttribName.append( ":" );
         XmlNamespaceAttribName.append( XmlNamespacePrefix );

         // fix prefix for use with nodes
         XmlNamespacePrefix.append( ":" );

         // remove cruft from root node
         RootNodeName.erase( 0, separator + 1 );
      }

      if ( RootNodeName != "Image" )
         throw ::std::runtime_error( "The Image file is invalid or is the wrong version (wrong root node name)" );

      {
         ::rapidxml::xml_attribute<>* nsattr = RootNode->first_attribute( XmlNamespaceAttribName.c_str() );
         if ( !nsattr )
            throw ::std::runtime_error( "The Image file is invalid or is the wrong version (no namespace)" );

         const char lsXMLNamespace[] = { "http://www.XmlCommandLine.org/Image/" };
         if ( ::strncmp( nsattr->value(), lsXMLNamespace, sizeof ( lsXMLNamespace ) - 1 ) != 0 )
            throw ::std::runtime_error( "The Image file is invalid or is the wrong version (wrong namespace)" );
      }
      
      // get the content node
      ::rapidxml::xml_node<>* ContentNode = GetFirstNode( RootNode, "Content" );
      if ( !ContentNode )
         throw ::std::runtime_error( "The input file has no Content" );

      // <editor-fold defaultstate="collapsed" desc="get the lowest numbered layer">
      {
         LayerNode = GetFirstNode( ContentNode, "Layer" );
         if ( !LayerNode )
            throw ::std::runtime_error( "The input file has no Layer" );
         uint32_t IndexNumber = NumericalAttribute( LayerNode, "z" );

         while ( true )
         {
            ::rapidxml::xml_node<>* node = GetSiblingNode( RootNode, "Layer" );
            if ( !node )
               break;
            uint32_t n = NumericalAttribute( node, "z" );
            if ( IndexNumber > n )
            {
               IndexNumber = n;
               LayerNode = node;
            }
         }
      }
      // </editor-fold>
         
      Width = NumericalAttribute( LayerNode, "Width" );
      Height = NumericalAttribute( LayerNode, "Height" );
      
      // Create a map of the rows
      ::rapidxml::xml_node<>* RowNode = GetFirstNode( LayerNode, "Row" );
      while ( RowNode )
      {
         uint32_t Row = NumericalAttribute( RowNode, "y" );
         RowMap[Row] = RowNode;
         
         RowNode = GetSiblingNode( RowNode, "Row" );
      }
   }

   ImageReader::~ImageReader()
   {
      if ( buffer )
         delete [] buffer;
   }

   // <editor-fold defaultstate="collapsed" desc="XML Helpers">

   ::rapidxml::xml_node<>* ImageReader::GetFirstNode( ::rapidxml::xml_node<>* Parent, const char* LocalName )
   {
      ::std::string XmlNodeName( XmlNamespacePrefix );
      XmlNodeName.append( LocalName );
      return Parent->first_node( XmlNodeName.c_str() );
   }

   ::rapidxml::xml_node<>* ImageReader::GetSiblingNode( ::rapidxml::xml_node<>* Parent, const char* LocalName )
   {
      ::std::string XmlNodeName( XmlNamespacePrefix );
      XmlNodeName.append( LocalName );
      return Parent->next_sibling( XmlNodeName.c_str() );
   }
   // </editor-fold>

   uint32_t ImageReader::NumericalAttribute( ::rapidxml::xml_node<>* node, const char* AttributeName )
   {
      ::rapidxml::xml_attribute<>* attr = node->first_attribute( AttributeName );
      if ( !attr )
      {
         ::std::string msg( "Attribute " );
         msg.append( AttributeName );
         msg.append( " missing" );
         throw ::std::runtime_error( msg );
      }

      ::std::string val( attr->value(), attr->value_size() );
      return atoi( val.c_str() );
   }

   uint8_t ImageReader::NormalizePixelAttribute( ::rapidxml::xml_node<>* node, const char* AttributeName )
   {
      ::rapidxml::xml_attribute<>* attr = node->first_attribute( AttributeName );
      if ( !attr )
      {
         ::std::string msg( "Attribute " );
         msg.append( AttributeName );
         msg.append( " missing" );
         throw ::std::runtime_error( msg );
      }
      uint64_t l = atol( ::std::string( attr->value(), attr->value_size() ).c_str() );
      return (uint8_t) ( ( l * UINT8_MAX ) / UINT32_MAX ) & 0xFF;
   }

   ::std::string ImageReader::ReadScanLine( uint32_t Row )
   {
      ::std::string result;

      // find the correct row. If not present return empty result
      ::std::map< uint32_t, ::rapidxml::xml_node<>* >::iterator ir = RowMap.find( Row );
      if ( ir == RowMap.end() )
         return result;
      ::rapidxml::xml_node<>* RowNode =  ir->second;
      
      // Create a map of the Pixels
      ::std::map< uint32_t, ::rapidxml::xml_node<>* > PixelMap;
      ::rapidxml::xml_node<>* PixelNode = GetFirstNode( RowNode, "Pixel" );
      while ( PixelNode )
      {
         uint32_t x = NumericalAttribute( PixelNode, "x" );
         PixelMap[x] = PixelNode;
         
         PixelNode = GetSiblingNode( PixelNode, "Pixel" );
      }
      
      // process pixels in sequential order not order of occurrence
      for ( ir = PixelMap.begin(); ir != PixelMap.end(); ++ir )
      {
          PixelNode = ir->second;
          
         uint8_t rgb[3];
         rgb[0] = NormalizePixelAttribute( PixelNode, "r" );
         rgb[1] = NormalizePixelAttribute( PixelNode, "g" );
         rgb[2] = NormalizePixelAttribute( PixelNode, "b" );
         result.append( (const char*) &rgb[0], 3 );
      }

      return result;
   }
}
