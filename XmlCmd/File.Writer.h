/* 
 * File:   File.Writer.h
 * Author: Jay Sprenkle
 *
 * Created on August 28, 2014
 */
#ifndef XMLCMD_FILE_WRITER_H
#define	XMLCMD_FILE_WRITER_H

#include <stdio.h>
#include <stdexcept>
#include <iterator>

namespace File
{
   class Writer
   {
   public:
      Writer();
      virtual ~Writer();

      void open( const char* filename );
      void open( FILE* handle );
      void write( unsigned int const bytes, unsigned char* data );

      const char* FileName;
      FILE* ofP;
   };

   class WriterIterator
      : public ::std::iterator< ::std::output_iterator_tag, Writer >
   {
   protected:
      Writer& _Writer;

   public:

      WriterIterator( Writer& wrt );

      WriterIterator& operator++();

      WriterIterator& operator++( int );

      WriterIterator& operator*();

      WriterIterator& operator=( WriterIterator it );

      WriterIterator& operator=( char c );
   };
}
#endif
