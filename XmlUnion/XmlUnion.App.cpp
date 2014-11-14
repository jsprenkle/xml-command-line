/* 
 * File:   XmlUnion.App.cpp
 * Author: Jay Sprenkle
 * 
 * Created on September 23, 2014
 */
#include <time.h>
#include <math.h>

#include <utility>
#include <list>

#include "XmlUnion.App.h"

namespace XmlUnion
{
   App::App( ::File::Reader& rdr1, ::File::Reader& rdr2 )
      : OutputXmlDoc( 0, 0, 0 )
      , InputXmlDoc1( rdr1, 0, 0 )
      , InputXmlDoc2( rdr2, 0, 0 )
   {
   }

   // <editor-fold defaultstate="collapsed" desc="Node comparison functions">

   /**
    * Compare two rapidxml base classes for equality. node and attribute are both derived from this class so it works for either
    * @param base1
    * @param base2
    * @return true if equal
    */
   bool baseequal( const ::rapidxml::xml_base<>* base1, const ::rapidxml::xml_base<>* base2 )
   {
      if ( !base1 || !base2 )
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

   void AttributeList( const ::rapidxml::xml_node<>* Node, ::std::list< ::rapidxml::xml_attribute<>* >& List )
   {
      if ( Node )
      {
         ::rapidxml::xml_attribute<>* attr = Node->first_attribute();
         while ( attr )
         {
            List.push_back( attr );
            attr = attr->next_attribute();
         }
      }
   }

   void NodeList( const ::rapidxml::xml_node<>* Node, ::std::list< ::rapidxml::xml_node<>* >& List )
   {
      if ( Node )
      {
         ::rapidxml::xml_node<>* child = Node->first_node();
         while ( child )
         {
            List.push_back( child );
            child = child->next_sibling();
         }
      }
   }
   
   /**
    * Compare two rapidxml nodes for equality
    * ordering of nodes in the documents is respected
    * @param Node1
    * @param Node2
    * @return 
    */
   bool equal( const ::rapidxml::xml_node<>* Node1, const ::rapidxml::xml_node<>* Node2 )
   {
      // two nodes must exist, have the same name, and content
      if ( !Node1 || !Node2 || !baseequal( Node1, Node2 ) )
         return false;

      // compare attributes
      ::std::list< ::rapidxml::xml_attribute<>* > AttrList1;
      AttributeList( Node1, AttrList1 );

      ::std::list< ::rapidxml::xml_attribute<>* > AttrList2;
      AttributeList( Node2, AttrList2 );

      if ( AttrList1.size() != AttrList2.size() )
         return false;

      ::std::list< ::rapidxml::xml_attribute<>* >::const_iterator i1 = AttrList1.begin();
      ::std::list< ::rapidxml::xml_attribute<>* >::const_iterator i2 = AttrList2.begin();
      while ( i1 != AttrList1.end() && i2 != AttrList2.end() )
      {
         if ( ::std::string( (*i1)->name(), (*i1)->name_size() ) != ::std::string( (*i2)->name(), (*i2)->name_size() ) )
            return false;
         if ( ::std::string( (*i1)->value(), (*i1)->value_size() ) != ::std::string( (*i2)->value(), (*i2)->value_size() ) )
            return false;
         ++i1;
         ++i2;
      }
      
      return true;
   }

   // </editor-fold>
   
   ::rapidxml::xml_node<>* App::clone( ::rapidxml::xml_node<>* source, ::rapidxml::xml_node<>* OutputNode )
   {
      // create node
      ::rapidxml::xml_node<>* OutputChildNode = OutputXmlDoc.allocate_node( source->type(), source->name(), source->value(), source->name_size(), source->value_size() );

      // Clone attributes
      for ( ::rapidxml::xml_attribute<> *attr = source->first_attribute(); attr; attr = attr->next_attribute())
          OutputChildNode->append_attribute( OutputXmlDoc.allocate_attribute( attr->name(), attr->value(), attr->name_size(), attr->value_size() ) );

      // if no output node then assume it's to be the root
      if ( ! OutputNode )
      {
         OutputXmlDoc.root = OutputChildNode;
         OutputXmlDoc.append_node( OutputXmlDoc.root );
      }
      else
         OutputNode->append_node( OutputChildNode );
      return OutputChildNode;
   }
   
   /**
    * comparison predicate for node list find_if()
    */
   class nodelist_equal
      : ::std::unary_function< ::rapidxml::xml_node<>*, bool >
   {
   public:
      // save item to find
      nodelist_equal( const ::rapidxml::xml_node<>* idx )
         : idx_( idx )
      {
      }

      bool operator()( const ::rapidxml::xml_node<>* arg ) const
      {
         return equal( arg, idx_ );
      }
   private:
      const ::rapidxml::xml_node<>* idx_;
   };
   
   void App::merge_children( ::rapidxml::xml_node<>* Node1, ::rapidxml::xml_node<>* Node2, ::rapidxml::xml_node<>* OutputNode )
   {
      // get lists of children
      ::std::list< ::rapidxml::xml_node<>* > NodeList1;
      NodeList( Node1, NodeList1 );
      
      ::std::list< ::rapidxml::xml_node<>* > NodeList2;
      NodeList( Node2, NodeList2 );

      // examine each child
      ::std::list< ::rapidxml::xml_node<>* >::const_iterator i1;
      ::std::list< ::rapidxml::xml_node<>* >::const_iterator i2;

      for ( i1 = NodeList1.begin(); i1 != NodeList1.end(); ++i1 )
      {
         // is there a matching node in other doc?
         i2 = ::std::find_if( NodeList2.begin(), NodeList2.end(), nodelist_equal( *i1 ) );
         if ( i2 != NodeList2.end() )
            // merge node that matches in both docs
            merge( *i1, *i2, OutputNode );
         else
            // merge node only in first doc
            merge( *i1, 0, OutputNode );
      }

      for ( i2 = NodeList2.begin(); i2 != NodeList2.end(); ++i2 )
      {
         // is there a matching node in other doc?
         //i1 = NodeList1.find( i2->first );
         i1 = ::std::find_if( NodeList1.begin(), NodeList1.end(), nodelist_equal( *i2 ) );
         if ( i1 == NodeList1.end() )
            // merge node only in second doc
            merge( 0, *i2, OutputNode );
      }
   }
   
   void App::merge( ::rapidxml::xml_node<>* Node1, ::rapidxml::xml_node<>* Node2, ::rapidxml::xml_node<>* OutputNode )
   {
      // If the same then clone one
      if ( equal( Node1, Node2 ) )
      {
         ::rapidxml::xml_node<>* OutputChildNode = clone( Node1, OutputNode );
         merge_children( Node1, Node2, OutputChildNode );
      }
      else
      {
         // if different then clone both
         if ( Node1 )
         {
            ::rapidxml::xml_node<>* OutputChildNode = clone( Node1, OutputNode );
            merge_children( Node1, 0, OutputChildNode );
         }
         if ( Node2 )
         {
            ::rapidxml::xml_node<>* OutputChildNode = clone( Node2, OutputNode );
            merge_children( 0, Node2, OutputChildNode );
         }
      }
   }
   
   void App::Process( const ::XmlUnion::Config::Settings& config )
   {
      if ( config.Warnings )
         if ( ! equal( InputXmlDoc1.root, InputXmlDoc2.root ) )
            ::std::cerr << "Warning: The root nodes of the two input documents are not identical. The output document will not be technically valid XML\n";

      merge( InputXmlDoc1.root, InputXmlDoc2.root, OutputXmlDoc.root );
   }
}
