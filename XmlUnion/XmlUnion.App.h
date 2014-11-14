/* 
 * File:   XmlUnion.App.h
 * Author: Jay Sprenkle
 * 
 * Created on September 23, 2014
 */
#ifndef XMLCMDINTERPOLATE_INTERPOLATE_H
#define	XMLCMDINTERPOLATE_INTERPOLATE_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <vector>
#include <algorithm>

#include <string.h>

#include <XmlCmd.h>

#include "XmlUnion.Config.Settings.h"

namespace XmlUnion
{
   class App
   {
   public:
      App( ::File::Reader& rdr1, ::File::Reader& rdr2 );

      void Process( const ::XmlUnion::Config::Settings& config );

      ::XmlCmd::DocumentReader   InputXmlDoc1;
      ::XmlCmd::DocumentReader   InputXmlDoc2;
      ::XmlCmd::DocumentWriter   OutputXmlDoc;

   protected:
      char* buffer;

      /**
       * Clone a node but not it's children
       * @param source
       * @param OutputNode
       * @return pointer to the newly created node
       */
      ::rapidxml::xml_node<>* clone( ::rapidxml::xml_node<>* Node, ::rapidxml::xml_node<>* OutputNode );
      
      /**
       * Determine distinct child nodes from one or more parents. recursively call merge() on them
       * @param Node1
       * @param Node2
       * @param OutputNode
       */
      void merge_children( ::rapidxml::xml_node<>* Node1, ::rapidxml::xml_node<>* Node2, ::rapidxml::xml_node<>* OutputNode );
      
      /**
       * merge two rapidxml nodes. recursively called to create children
       * @param Node1
       * @param Node2
       * @return 
       */
      void merge( ::rapidxml::xml_node<>* Node1, ::rapidxml::xml_node<>* Node2, ::rapidxml::xml_node<>* OutputNode );
   };
}
#endif
