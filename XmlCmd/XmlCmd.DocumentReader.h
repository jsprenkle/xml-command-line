/* 
 * File:   XmlCmd.DocumentReader.h
 * Author: Jay Sprenkle
 *
 * I/O for Configuration files
 * 
 * Created on October 7, 2014
 */
#ifndef XMLCMD_DOCUMENTREADER_H
#define	XMLCMD_DOCUMENTREADER_H

#include <XmlCmd.h>

namespace XmlCmd
{
   class DocumentReader
      : public Document
   {
   public:
      /**
       * Constructor
       * @param rdr file reader object to load document from
       * @param RootNodeName
       * @param Namespace
       */
      DocumentReader( ::File::Reader& rdr, const char* RootNodeName, const char* Namespace );
      
      /**
       * Constructor
       * @param FileName
       * @param RootNodeName
       * @param Namespace
       */
      DocumentReader( const char* FileName, const char* RootNodeName, const char* Namespace );
      
      /**
       * Destructor
       */
      virtual ~DocumentReader();

      /**
       * Read a named node and convert to an integer
       * @param Node
       * @param name
       * @return 
       */
      uint32_t ReadNumericAttribute( ::rapidxml::xml_node<>* Node, const char* name );

      size_t   size;
   private:
      char* buffer;
      
      void Validate( const char* RootNodeName, const char* Namespace );
   };
}
#endif
