/* 
 * File:   XmlCmdImageToPng.Convert.cpp
 * Author: jay
 * 
 * Created on September 19, 2014
 */
#include "XmlCmdImageToPng.Convert.h"

#include "lodepng.h"

namespace XmlCmdImageToPng
{
   Convert::Convert()
      : buffer( 0 )
   {
   }

   Convert::~Convert()
   {
      if ( buffer )
         delete [] buffer;
   }

   const char* ReadNode( ::rapidxml::xml_node<>* current_node, const ::std::string& XmlNamespacePrefix, const char* NodeName, const char* DefaultValue = "" )
   {
      ::std::string XmlNodeName( XmlNamespacePrefix );
      XmlNodeName.append( NodeName );

      ::rapidxml::xml_node<>* Nodefound;
      Nodefound = current_node->first_node( XmlNodeName.c_str() );
      if ( Nodefound )
         return Nodefound->value();
      return DefaultValue;
   }

   void Convert::Read( ::File::Reader& rdr )
   {
      size_t size = rdr.size();
      if ( size )
      {
         // <editor-fold defaultstate="collapsed" desc="Load the xml into buffer">
         // allocate space for content
         buffer = (char*) new char[size + 1];
         rdr.read( size, (unsigned char*) buffer );
         // ensure null termination
         buffer[size] = 0;
         // </editor-fold>

         // <editor-fold defaultstate="collapsed" desc="Parse xml document">
         try
         {
            InputXmlDoc.parse< ::rapidxml::parse_no_data_nodes | ::rapidxml::parse_trim_whitespace > ( buffer );
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
         // </editor-fold>
      }

      // <editor-fold defaultstate="collapsed" desc="Validate XML">
      ::rapidxml::xml_node<>* current_node = InputXmlDoc.first_node( );
      if ( current_node )
      {
         // check the root and namespace to see if it's an lsXML configuration file
         ::std::string XmlNamespaceAttribName( "xmlns" );

         // get the namespace prefix (if present)
         ::std::string XmlNamespacePrefix;
         ::std::string RootNodeName( current_node->name( ), current_node->name_size( ) );
         size_t separator = RootNodeName.find( ":" );
         if ( separator != ::std::string::npos )
         {
            // extract text prefix
            XmlNamespacePrefix.assign( RootNodeName.c_str( ), separator );

            // create attribute name
            XmlNamespaceAttribName.append( ":" );
            XmlNamespaceAttribName.append( XmlNamespacePrefix );

            // fix prefix for use with nodes
            XmlNamespacePrefix.append( ":" );

            // remove cruft from root node
            RootNodeName.erase( 0, separator + 1 );
         }

         if ( RootNodeName != "Image" )
            throw ::std::runtime_error( "The image file is invalid or is the wrong version (root node name is not Image)" );

         ::rapidxml::xml_attribute<>* nsattr = current_node->first_attribute( XmlNamespaceAttribName.c_str( ) );
         if ( !nsattr )
            throw ::std::runtime_error( "The image file is invalid or is the wrong version (no namespace)" );

         const char lsXMLNamespace[] = { "http://www.XmlCommandLine.org/Image/" };
         if ( ::strncmp( nsattr->value( ), lsXMLNamespace, sizeof ( lsXMLNamespace ) - 1 ) != 0 )
            throw ::std::runtime_error( "The image file is invalid or is the wrong version (wrong namespace)" );
      }
      // </editor-fold>
   }

   uint32_t ReadAttribute( ::rapidxml::xml_node<>* Node, const char* name )
   {
      ::rapidxml::xml_attribute<>* attr = Node->first_attribute( name );
      if ( attr )
         return stringTo< uint32_t >( ::std::string( attr->value(), attr->value_size() ) );
      return 0;
   }
   
   uint8_t ReadNormalizedAttribute( ::rapidxml::xml_node<>* Node, const char* name )
   {
      ::rapidxml::xml_attribute<>* attr = Node->first_attribute( name );
      if ( attr )
      {
         ::std::string val( attr->value(), attr->value_size() );
         uint64_t l = stringTo< uint64_t>( val );
         return (uint8_t) ( ( l * UINT8_MAX ) / UINT32_MAX ) & 0xFF;
      }
      return 0;
   }
   
   
   void Convert::Process( const ::XmlCmdImageToPng::Config::Settings& config )
   {
      InputXmlDoc.root = InputXmlDoc.first_node();
      if ( ! InputXmlDoc.root )
         throw ::std::runtime_error( "The image has no Root node" );

      ::rapidxml::xml_node<>* ContentNode = InputXmlDoc.root->first_node( "Content" );
      if ( ! ContentNode )
         throw ::std::runtime_error( "The image has no Content node" );

      ::rapidxml::xml_node<>* LayerNode = ContentNode->first_node( "Layer" );
      if ( ! LayerNode )
         throw ::std::runtime_error( "The image has no Layer node" );
      
      uint32_t z = ReadAttribute( LayerNode, "z" );
      uint32_t Width = ReadAttribute( LayerNode, "Width" );
      uint32_t Height = ReadAttribute( LayerNode, "Height" );

      // allocate space for output image
      ::std::vector<unsigned char> image;
      image.assign( Width * Height * 4, 0 );
      
      ::rapidxml::xml_node<>* RowNode = LayerNode->first_node( "Row" );
      if ( ! RowNode )
         throw ::std::runtime_error( "The image has no Row nodes" );
      while ( RowNode )
      {
         uint32_t y = ReadAttribute( RowNode, "y" );

         ::rapidxml::xml_node<>* PixelNode = RowNode->first_node( "Pixel" );
         while ( PixelNode )
         {
            // The image argument has width * height RGBA pixels or width * height * 4 bytes
            uint32_t x = ReadAttribute( PixelNode, "x" );

            uint32_t n = 4 * ( (Width * y) + x );
            image.at(n++) = ReadNormalizedAttribute( PixelNode, "r" );
            image.at(n++) = ReadNormalizedAttribute( PixelNode, "g" );
            image.at(n++) = ReadNormalizedAttribute( PixelNode, "b" );
            image.at(n) = ReadNormalizedAttribute( PixelNode, "a" );

            PixelNode = PixelNode->next_sibling();
         }
         
         RowNode = RowNode->next_sibling();
      }
      
      // todo: add a test for the comment configuration option and call lodepng_add_text() to add the comment
      unsigned error = ::lodepng::encode( png, image, Width, Height, LCT_RGBA, 8 );
      if ( error )
      {
         ::std::string msg( "encoder failed: " );
         msg.append( lodepng_error_text( error ) );
         throw ::std::runtime_error( msg.c_str() );
      }
   }

   void Convert::Write( ::File::Writer& wrt )
   {
      try
      {
         wrt.write( png.size(), &png[0] );
      }
      catch ( ::std::runtime_error ex )
      {
         ::std::string msg( "Write failed for fileName: " );
         msg.append( wrt.FileName );
         msg.append( ", exception: " );
         msg.append( ex.what() );
         throw ::std::runtime_error( msg.c_str() );
      }
   }
}

