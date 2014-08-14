/* 
 * File:   XmlCmd.Document.cpp
 * Author: Jay Sprenkle
 *
 * Created on June 30, 2014
 */
//#include <assert.h>
#include "XmlCmd.Document.h"
#include <rapidxml_print.hpp>

namespace XmlCmd
{
   Document::Document( const char* NamespaceString, const char* prefix, const char* Declaration )
      : Declaration( Declaration )
      , prefix( prefix )
   {
      // xml declaration. TODO: use parameter
      ::rapidxml::xml_node<>* decl = allocate_node( ::rapidxml::node_declaration );
      decl->append_attribute( allocate_attribute( "version", "1.0" ) );
      decl->append_attribute( allocate_attribute( "encoding", "utf-8" ) );
      append_node( decl );

      // root node
      root = allocate_node( ::rapidxml::node_element, PrefixType( "FileSystem" ) );
      root->append_attribute( allocate_attribute( "xmlns:ns", NamespaceString ) );
      append_node( root );
   }

   const char* Document::PrefixType( const char* type )
   {
      ::std::string temp( prefix );
      if ( !temp.empty() )
         temp.append( ":" );
      temp.append( type );
      return allocate_string( temp.c_str(), temp.size()+1 );
   }
   
   void Document::write( ::std::ostream& OutputStream )
   {
      // write result as an unformatted XML document
      ::rapidxml::print( OutputStream, *this, ::rapidxml::print_no_indenting );
   }

   ::rapidxml::xml_node<>* Document::AppendChildNode( ::rapidxml::xml_node<>* Parent, const char* type )
   {
      ::rapidxml::xml_node<>* ChildElement = allocate_node( ::rapidxml::node_element, PrefixType( type ) );
      Parent->append_node( ChildElement );
      return ChildElement;
   }
   
   void Document::AppendChildNode( ::rapidxml::xml_node<>* Parent, const char* type, const ::std::string& text )
   {
      ::rapidxml::xml_node<>* ChildElement = allocate_node( ::rapidxml::node_element, PrefixType( type ) );
      ::std::string temp = encode( text );
      ChildElement->value( allocate_string( temp.c_str(), temp.size() ), temp.size() );
      Parent->append_node( ChildElement );
   }
   
   void Document::AppendAttribute( ::rapidxml::xml_node<>* Parent, const char* AttributeName, const ::std::string& AttributeValue )
   {
      char* pAttributeValueCopy = allocate_string( AttributeValue.c_str(), AttributeValue.size() );
      Parent->append_attribute( allocate_attribute( AttributeName, pAttributeValueCopy, 0, AttributeValue.size() ) );
   }

   ::std::string Document::encode( const ::std::string& data )
   {
      ::std::string buffer;
      buffer.reserve( data.size() + 40 );
      for ( size_t pos = 0; pos != data.size(); ++pos )
      {
         switch ( data[pos] )
         {
            case '&':
               buffer.append( "&amp;" );
               break;
            case '\"':
               buffer.append( "&quot;" );
               break;
            case '\'':
               buffer.append( "&apos;" );
               break;
            case '<':
               buffer.append( "&lt;" );
               break;
            case '>':
               buffer.append( "&gt;" );
               break;
            default:
               buffer.append( &data[pos], 1 );
               break;
         }
      }
      return buffer;
   }
}
