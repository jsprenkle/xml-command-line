/* 
 * File:   File.Writer.h
 * Author: Jay Sprenkle
 *
 * Created on August 28, 2014
 */
#ifndef XMLCMDINTERPOLATE_FILE_WRITER_H
#define	XMLCMDINTERPOLATE_FILE_WRITER_H

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

      WriterIterator( Writer& wrt )
         : _Writer( wrt )
      {
      }

      WriterIterator& operator++()
      {
         return *this;
      }

      WriterIterator& operator++( int )
      {
         return *this;
      }

      WriterIterator& operator*()
      {
         return *this;
      }

      WriterIterator& operator=( WriterIterator it )
      {
         _Writer = it._Writer;
         return *this;
      }

      WriterIterator& operator=( char c )
      {
         _Writer.write( 1, (unsigned char*) &c );
         return *this;
      }
   };
}
#endif
