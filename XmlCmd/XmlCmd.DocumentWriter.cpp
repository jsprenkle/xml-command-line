/* 
 * File:   XmlCmd.DocumentWriter.cpp
 * Author: Jay Sprenkle
 * 
 * Created on October 9, 2014
 */
#include "XmlCmd.DocumentWriter.h"
#include <rapidxml_print.hpp>

namespace XmlCmd
{
   DocumentWriter::DocumentWriter( const char* NamespaceString, const char* prefix, const char* type, const char* Declaration )
      : Document( NamespaceString, prefix, type, Declaration )
   {
   }

   void DocumentWriter::Write( ::File::Writer& wrt )
   {
      // write result as an XML document
      ::File::WriterIterator wit( wrt );
      ::rapidxml::print( wit, *this, ::rapidxml::print_no_indenting );
   }
}
