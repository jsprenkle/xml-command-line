/* 
 * File:   XmlUnion.Config.Reader.cpp
 * Author: Jay Sprenkle
 *
 * I/O for configuration
 * 
 * Created on September 23, 2014
 */
#include "XmlUnion.Config.Reader.h"

namespace XmlUnion
{
   namespace Config
   {
      Reader::Reader( const char* FileName )
         : ::XmlCmd::DocumentReader( FileName, "Config", "http://www.XmlCommandLine.org/XmlUnion/1.0" )
      {
      }

      Settings Reader::Parse()
      {
         Settings result;
         result.OutputFile = ReadNode( root, XmlNamespacePrefix, "OutputFile" );
         
         ::std::string str = ReadNode( root, XmlNamespacePrefix, "Warnings", "true" );
         result.Warnings = ( str == "true" ? true : false );
         
         return result;
      }
   }
}
