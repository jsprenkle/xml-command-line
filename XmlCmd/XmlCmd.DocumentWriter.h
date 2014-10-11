/* 
 * File:   XmlCmdDocumentWriter.h
 * Author: Jay Sprenkle
 *
 * Created on October 9, 2014
 */
#ifndef XMLCMD_DOCUMENTWRITER_H
#define XMLCMD_DOCUMENTWRITER_H

#include "XmlCmd.h"

namespace XmlCmd
{
   class DocumentWriter
      : public Document
   {
   public:
      DocumentWriter( const char* NamespaceString = "default", const char* prefix = "ns", const char* type = "root", const char* Declaration = 0 );

      virtual void Write( ::File::Writer& wrt );
   };
}
#endif
