/* 
 * File:   main.cpp
 * Author: Jay Sprenkle
 *
 * Compare the content of two xml files for equality
 * 
 * Created on October 11, 2014, 9:54 AM
 */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <XmlCmd.h>

/**
 * Compare two rapidxml base classes for equality. node and attribute are both derived from this class so it works for either
 * @param base1
 * @param base2
 * @return 
 */
bool baseequal( ::rapidxml::xml_base<>* base1, ::rapidxml::xml_base<>* base2 )
{
   if ( ! base1 || ! base2 )
      return false;
   
   // do names match?
   {
      ::std::string name1( base1->name(), base1->name_size() );
      ::std::string name2( base2->name(), base2->name_size() );
      if ( name1 != name2 )
         return false;
   }

   // does content match?
   {
      ::std::string value1( base1->value(), base1->value_size() );
      ::std::string value2( base2->value(), base2->value_size() );
      if ( value1 != value2 )
         return false;
   }

   return true;
}

/**
 * Compare two rapidxml nodes for equality. Recursively calls itself to compare child nodes.
 * Code changed to ignore ordering of nodes in the documents.
 * @param Node1
 * @param Node2
 * @return 
 */
bool equal( ::rapidxml::xml_node<>* Node1, ::rapidxml::xml_node<>* Node2 )
{
   // two nodes must exist, have the same name, and content
   if ( ! Node1 || ! Node2 || ! baseequal( Node1, Node2 ) )
      return false;

   // compare attributes
   ::rapidxml::xml_attribute<>* attr1 = Node1->first_attribute();
   while ( attr1 )
   {
      // find matching attribute in Node2
      ::rapidxml::xml_attribute<>* attr2 = Node2->first_attribute();
      while ( attr2 )
      {
         // must both have attribute
         if ( baseequal( attr1, attr2 ) )
            break;

         attr2 = attr2->next_attribute();
      }
      if ( ! attr2 )
         return false;
      
      // remove attributes that are matched. When finished all attributes should be removed
      Node2->remove_attribute( attr2 );
      attr1 = attr1->next_attribute();
   }
   // all attributes should have been removed from node2
   ::rapidxml::xml_attribute<>* attr2 = Node2->first_attribute();
   if ( attr2 )
      return false;

   // compare children
   ::rapidxml::xml_node<>* child1 = Node1->first_node();
   while ( child1 )
   {
      ::rapidxml::xml_node<>* child2 = Node2->first_node();
      while ( child2 )
      {
         if ( baseequal( child1, child2 ) && equal( child1, child2 ) )
            break;

         child2 = child2->next_sibling();
      }
      if ( ! child2 )
         return false;
      // remove nodes that are matched. When finished all nodes should be removed
      Node2->remove_node( child2 );
      child1 = child1->next_sibling();
   }
   
   // all child nodes should have been removed from node2
   ::rapidxml::xml_node<>* child2 = Node2->first_node();
   if ( child2 )
      return false;
   return true;
}

/**
 * Compare two xml documents for equality.
 * The file names of the two documents must be specified on the command line
 * ignores ordering of nodes in the documents. This code does NOT validate
 * the documents against a schema. It is intended for use as a simple validator
 * for unit testing of Xml Command line programs.
 * Returns exit code of non zero as a boolean difference indicator.
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv)
{
   try
   {
      char* InputFileName1 = 0;
      char* InputFileName2 = 0;

      // <editor-fold defaultstate="collapsed" desc="command line argument parsing">

      // could be a bitmap file name or a configuration option
      for ( int i = 1; i < argc; ++i )
      {
         ::std::string arg( argv[i] );

         // input file name first
         if ( ! arg.empty() && ! InputFileName1 )
         {
            InputFileName1 = argv[i];
            continue;
         }

         // output file name next
         if ( ! arg.empty() && ! InputFileName2 )
         {
            InputFileName2 = argv[i];
            continue;
         }

         // something unrecognized
         throw ::std::runtime_error( ::std::string( "Invalid command line parameter: " ) + arg );
      }

      if ( ! InputFileName1 || ! InputFileName2 )
         throw ::std::runtime_error( "Invalid command line parameters: two different files must be specified" );
      // </editor-fold>

      // Reader for the first input document
      ::File::Reader rdr1;
      rdr1.open( InputFileName1 );

      // Reader for the second input document
      ::File::Reader rdr2;
      rdr2.open( InputFileName2 );

      // open without validation
      ::XmlCmd::DocumentReader   InputXmlDoc1( rdr1, 0, 0 );
      ::XmlCmd::DocumentReader   InputXmlDoc2( rdr2, 0, 0 );

      if ( ! equal( InputXmlDoc1.root, InputXmlDoc2.root ) )
         return 1;
   }
   catch ( ::std::runtime_error& ex )
   {
      ::std::cerr << ex.what() << "\n";
      return 2;
   }
   catch (...)
   {
      ::std::cerr << "Unexpected error with no explanation thrown\n";
      return 3;
   }
   
   // equal. return success
   return 0;
}

