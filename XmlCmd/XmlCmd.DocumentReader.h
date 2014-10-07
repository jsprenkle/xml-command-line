/* 
 * File:   XmlCmd.Config.Reader.h
 * Author: Jay Sprenkle
 *
 * I/O for Configuration files
 * 
 * Created on October 7, 2014
 */
#ifndef XMLCMD_CONFIG_READER_H
#define	XMLCMD_CONFIG_READER_H

#include <XmlCmd.h>

namespace XmlCmd
{
   class DocumentReader
   {
   public:
      DocumentReader( ::File::Reader& rdr, const char* RootNodeName, const char* Namespace );
      
      DocumentReader( const char* FileName, const char* RootNodeName, const char* Namespace );
      virtual ~DocumentReader();

      Document doc;
      size_t size;
   private:
      char* buffer;
      
      void Validate( const char* RootNodeName, const char* Namespace );
   };
}
#endif
