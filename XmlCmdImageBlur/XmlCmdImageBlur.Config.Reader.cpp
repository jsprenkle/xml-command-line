/* 
 * File:   XmlCmdImageBlur.Config.Reader.cpp
 * Author: Jay Sprenkle
 *
 * I/O for configuration
 * 
 * Created on September 23, 2014
 */
#include "XmlCmdImageBlur.Config.Reader.h"

namespace XmlCmdImageBlur
{
   namespace Config
   {
      Reader::Reader( const char* FileName )
         : ::XmlCmd::DocumentReader( FileName, "Config", "http://www.XmlCommandLine.org/XmlCmdImageBlur/1.0" )
      {
      }

      Settings Reader::Parse()
      {
         Settings result;
         result.OutputFile = ReadNode( root, XmlNamespacePrefix, "OutputFile" );
         result.InputFile = ReadNode( root, XmlNamespacePrefix, "InputFile" );
         return result;
      }
   }
}
