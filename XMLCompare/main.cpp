/* 
 * File:   main.cpp
 * Author: Jay Sprenkle
 *
 * Compare the content of two xml files. Returns exit code of non zero as a boolean difference indicator.
 * 
 * Created on October 11, 2014, 9:54 AM
 */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <XmlCmd.h>

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

bool equal( ::rapidxml::xml_node<>* Node1, ::rapidxml::xml_node<>* Node2 )
{
   // two nodes must be the same and have same content
   if ( ! Node1 || ! Node2 || ! baseequal( Node1, Node2 ) )
      return false;

   // compare attributes
   ::rapidxml::xml_attribute<>* attr1 = Node1->first_attribute();
   ::rapidxml::xml_attribute<>* attr2 = Node2->first_attribute();
   while ( attr1 || attr2 )
   {
      // must both have attribute
      if ( ! attr1 || ! attr2 || ! baseequal( attr1, attr2 ) )
         return false;
      
      attr1 = attr1->next_attribute();
      attr2 = attr2->next_attribute();
   }

   // compare children
   ::rapidxml::xml_node<>* child1 = Node1->first_node();
   ::rapidxml::xml_node<>* child2 = Node2->first_node();
   while ( child1 || child2 )
   {
      // both doms must both have the same child. both must compare, children of the nodes must be equal
      if ( ! child1 || ! child2 || ! baseequal( child1, child2 ) || ! equal( child1, child2 ) )
         return false;
      
      child1 = child1->next_sibling();
      child2 = child2->next_sibling();
   }
   
   return true;
}

/*
 * 
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
         return 3;
   }
   catch ( ::std::runtime_error& ex )
   {
      ::std::cerr << ex.what() << "\n";
      return 1;
   }
   catch (...)
   {
      ::std::cerr << "Unexpected error with no explanation thrown\n";
      return 2;
   }
   
   return 0;
}

