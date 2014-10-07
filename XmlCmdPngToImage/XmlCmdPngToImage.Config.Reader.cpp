/* 
 * File:   XmlCmdPngToImage.Config.Reader.cpp
 * Author: Jay Sprenkle
 *
 * I/O for configuration
 * 
 * Created on September 24, 2014
 */
#include "XmlCmdPngToImage.Config.Reader.h"

namespace XmlCmdPngToImage
{
   namespace Config
   {
      Reader::Reader( const char* FileName )
         : ::XmlCmd::DocumentReader( FileName, "Config", "http://www.XmlCommandLine.org/XmlCmdPngToImage/1.0" )
      {
      }

      Settings Reader::Parse()
      {
         Settings result;
         result.OutputFile = ::XmlCmd::Document::ReadNode( doc.root, doc.XmlNamespacePrefix, "OutputFile" );
         result.InputFile = ::XmlCmd::Document::ReadNode( doc.root, doc.XmlNamespacePrefix, "InputFile" );
         result.sigma = stringTo< float >( ::XmlCmd::Document::ReadNode( doc.root, doc.XmlNamespacePrefix, "InputFile" ) );
         return result;
      }
   }
}
