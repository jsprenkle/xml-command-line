/* 
 * File:   XmlCmd.Document.h
 * Author: Jay Sprenkle
 *
 * Created on June 30, 2014
 */
#ifndef XMLCMD_DOCUMENT_H
#define	XMLCMD_DOCUMENT_H

#include <iostream>
#include <rapidxml.hpp>

namespace XmlCmd
{
   class Document
      : public ::rapidxml::xml_document<>
   {
   public:
      /**
       * 
       * @param root
       * @param NamespaceString: namespace to use for xml
       * @param Declaration: xml document declaration
       * 
       */
      Document( const char* NamespaceString = "default", const char* prefix = "ns", const char* type = "root", const char* Declaration = 0 );

      /**
       * recursively write a DOM to xml
       * @param OutputStream: stream to write to
       */
      void write( ::std::ostream& OutputStream );
      
      /**
       * Create and append a child node to the given parent.
       * @param Parent
       * @param type Node name (including namespace prefix)
       * @param text text portion of the node. Will be xml encoded.
       */
      ::rapidxml::xml_node<>* AppendChildNode( ::rapidxml::xml_node<>* Parent, const char* type, const ::std::string& text );
      
      /**
       * Create and append a child node to the given parent.
       * @param Parent
       * @param type Node name (including namespace prefix)
       */
      ::rapidxml::xml_node<>* AppendChildNode( ::rapidxml::xml_node<>* Parent, const char* type );
      
      void AppendAttribute( ::rapidxml::xml_node<>* Parent, const char* AttributeName, const ::std::string& AttributeValue );
      
      const char* PrefixType( const char* type );
      
      ::std::string encode( const ::std::string& data );

      ::rapidxml::xml_node<>* root;
   private:

      const char* Declaration;
      
      // the xml namespace prefix used for the output document
      const char* prefix;
   };
}
#endif
