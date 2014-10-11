/* 
 * File:   XmlCmdInterpolate.Config.Reader.cpp
 * Author: Jay Sprenkle
 *
 * I/O for configuration
 * 
 * Created on August 18, 2014
 */
#include "XmlCmdImageToPng.Config.Reader.h"

namespace XmlCmdImageToPng
{
   namespace Config
   {
      Reader::Reader( const char* FileName )
         : ::XmlCmd::DocumentReader( FileName, "Config", "http://www.XmlCommandLine.org/XmlCmdImageToPng/1.0" )
      {
      }

      Settings Reader::Parse()
      {
         Settings result;
         result.OutputFile = ::XmlCmd::Document::ReadNode( root, XmlNamespacePrefix, "OutputFile" );
         result.InputFile = ::XmlCmd::Document::ReadNode( root, XmlNamespacePrefix, "InputFile" );
         return result;
      }
   }
}
