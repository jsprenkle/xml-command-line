/* 
 * File:   XmlCmd.Document.cpp
 * Author: Jay Sprenkle
 *
 * Created on June 30, 2014
 */
#include <string.h>

#include <stdexcept>

#include "conversion.h"
#include "XmlCmd.Document.h"
#include <rapidxml_print.hpp>

namespace XmlCmd
{
   Document::Document( const char* NamespaceString, const char* prefix, const char* type, const char* Declaration )
      : Declaration( Declaration )
      , prefix( prefix )
   {
      // xml declaration. TODO: use parameter
      ::rapidxml::xml_node<>* decl = allocate_node( ::rapidxml::node_declaration );
      decl->append_attribute( allocate_attribute( "version", "1.0" ) );
      decl->append_attribute( allocate_attribute( "encoding", "utf-8" ) );
      append_node( decl );

      // root node
      root = allocate_node( ::rapidxml::node_element, PrefixType( type ) );

      ::std::string temp( "xmlns" );
      if ( ::strlen( prefix ) != 0 )
      {
         temp.append( ":" );
         temp.append( prefix );
      }
      root->append_attribute( allocate_attribute( allocate_string( temp.c_str(), temp.size()+1 ), NamespaceString ) );
      append_node( root );
   }
   
   void Document::ValidateRootNode( const char* NodeName, const ::std::string& XmlNamespace )
   {
      root = first_node();
      if ( ! root )
         throw ::std::runtime_error( "No root node in document" );
      
      // check the node name and namespace
      ::std::string XmlNamespaceAttribName( "xmlns" );

      // get the namespace prefix (if present)
      ::std::string RootNodeName( root->name(), root->name_size() );
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

      if ( RootNodeName != NodeName )
         throw ::std::runtime_error( "Invalid root node name" );

      if ( ! XmlNamespace.empty() )
      {
         ::rapidxml::xml_attribute<>* nsattr = root->first_attribute( XmlNamespaceAttribName.c_str() );
         if ( !nsattr )
            throw ::std::runtime_error( "Invalid document. no namespace" );

         ::std::string NameSpaceAttribute( nsattr->value(), nsattr->value_size() );
         if ( NameSpaceAttribute != XmlNamespace ) 
            throw ::std::runtime_error( "Invalid namespace" );
      }
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
   
   ::rapidxml::xml_node<>* Document::AppendChildNode( ::rapidxml::xml_node<>* Parent, const char* type, const ::std::string& text )
   {
      ::rapidxml::xml_node<>* ChildElement = AppendChildNode( Parent, type );

      ::std::string temp = encode( text );
      ChildElement->value( allocate_string( temp.c_str(), temp.size() ), temp.size() );
      
      return ChildElement;
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

   ::std::string Document::ReadNode( ::rapidxml::xml_node<>* current_node, const ::std::string& XmlNamespacePrefix, const char* NodeName, const char* DefaultValue )
   {
      ::std::string XmlNodeName( XmlNamespacePrefix );
      XmlNodeName.append( NodeName );
      ::rapidxml::xml_node<>* Nodefound;
      Nodefound = current_node->first_node( XmlNodeName.c_str() );
      if ( Nodefound )
         return ::std::string( Nodefound->value(), Nodefound->value_size() );
      return ::std::string( DefaultValue );
   }
}
