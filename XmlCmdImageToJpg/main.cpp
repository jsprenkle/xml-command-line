/* 
 * File:   main.cpp
 * Author: Jay Sprenkle
 * 
 * A program (XmlCmdToJpg) to output a bmp format image to an xml document.
 * Intended to be part of larger system of xml enabled command line processes.
 * Derived from the bmptopnm program by David W. Sanderson.
 *
 * Created on August 21, 2014
 */
#include <cstdlib>
#include <iostream>
#include <algorithm>

#include "XmlCmdToJpg.ImageWriter.h"
#include "XmlCmdToJpg.Config.Reader.h"
#include "XmlCmdToJpg.File.Reader.h"

int main( int argc, char** argv )
{
   try
   {
      // execution options
      ::XmlCmdToJpg::Config::Settings config;

      // default to reading stdin
      char* FileName = 0;
      ::XmlCmdToJpg::File::Reader rdr;

      // <editor-fold defaultstate="collapsed" desc="command line argument parsing">
      for ( int i = 1; i < argc; ++i )
      {
         ::std::string arg( argv[i] );

         // if '-c'...
         if ( arg == "-c" )
         {
            // if there's a file name following...
            if ( ++i < argc )
            {
               // try to parse the configuration file
               try
               {
                  ::XmlCmdToJpg::Config::Reader ConfigReader( argv[i] );
                  config = ConfigReader.Parse();
               }
               catch ( ::std::runtime_error& e )
               {
                  ::std::cerr << e.what() << "\n";
                  return 2;
               }
               catch ( ... )
               {
                  ::std::cerr << "Error reading configuration file\n";
                  return 2;
               }
               continue;
            }
         }
         
         if ( ! arg.empty() && ! FileName )
         {
            FileName = argv[i];
            continue;
         }

         throw ::std::runtime_error( ::std::string( "Invalid command line parameter: " ) + arg );
      }
      // </editor-fold>

      // Read the image data
      if ( FileName )
         rdr.open( FileName );
      else
         rdr.open( stdin );
      ::XmlCmdToJpg::ImageReader imgRdr( rdr );

      // Write the image
      ::XmlCmdToJpg::ImageWriter iw( config, imgRdr );
      ::XmlCmdToJpg::File::Writer wrt;
      if ( config.OutputFile.empty() )
         wrt.open( stdout );
      else
         wrt.open( config.OutputFile.c_str() );
      iw.write( wrt );
   }
   catch ( ::std::runtime_error& ex )
   {
      ::std::cerr << ex.what() << "\n";
      return 1;
   }
   catch (...)
   {
      ::std::cerr << "Unexpected error with no explanation thrown\n";
      return 2;
   }
   
   return 0;
}
