/* 
 * File:   main.cpp
 * Author: Jay Sprenkle
 * 
 * A program that reads an XmlCmd image document and creates any missing pixels using a weight average interpolation.
 * 
 * Created on August 18, 2014
 */
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "XmlCmdImageBlur.Config.Reader.h"
#include "XmlCmdImageBlur.App.h"

int main( int argc, char** argv )
{
   try
   {
      // execution options
      ::XmlCmdImageBlur::Config::Settings config;

      // default to reading stdin
      char* InputFileName = 0;
      char* OutputFileName = 0;

      // <editor-fold defaultstate="collapsed" desc="command line argument parsing">

      // could be a bitmap file name or a configuration option
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
                  ::XmlCmdImageBlur::Config::Reader rdr( argv[i] );
                  config = rdr.Parse();
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

         // input file name first
         if ( ! arg.empty() && ! InputFileName )
         {
            InputFileName = argv[i];
            continue;
         }

         // output file name next
         if ( ! arg.empty() && ! OutputFileName )
         {
            OutputFileName = argv[i];
            continue;
         }

         // something unrecognized
         throw ::std::runtime_error( ::std::string( "Invalid command line parameter: " ) + arg );
      }
      // </editor-fold>

      // Reader for the image document
      ::File::Reader rdr;
      if ( InputFileName )
         rdr.open( InputFileName );
      else
         if ( config.InputFile.empty() )
            rdr.open( stdin );
         else
            rdr.open( InputFileName );

      ::XmlCmdImageBlur::App app( rdr );
      app.Process( config );

      ::File::Writer wrt;
      if ( OutputFileName )
         wrt.open( OutputFileName );
      else
         if ( config.OutputFile.empty() )
            wrt.open( stdout );
         else
            wrt.open( config.OutputFile.c_str() );
      app.OutputXmlDoc.Write( wrt );
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
