/* 
 * File:   main.cpp
 * Author: Jay Sprenkle
 *
 * Compare the content of two xml files for equality
 * 
 * Created on November 11, 2014
 */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <XmlCmd.h>
#include "XmlUnion.App.h"
#include "XmlUnion.Config.Reader.h"

/*
 * program entry point
 */
int main( int argc, char** argv )
{
   try
   {
      // execution options
      ::XmlUnion::Config::Settings config;

      char* InputFileName1 = 0;
      char* InputFileName2 = 0;
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
                  ::XmlUnion::Config::Reader rdr( argv[i] );
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
         if ( ! arg.empty() && ! InputFileName1 )
         {
            InputFileName1 = argv[i];
            continue;
         }

         // output file name next
         if ( ! arg.empty() && ! InputFileName2 )
         {
            InputFileName2 = argv[i];
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

      if ( ! InputFileName1 || ! InputFileName2 )
         throw ::std::runtime_error( "Invalid command line parameters: two different files must be specified" );
      // </editor-fold>

      // Reader for the first input document
      ::File::Reader rdr1;
      rdr1.open( InputFileName1 );

      // Reader for the second input document
      ::File::Reader rdr2;
      rdr2.open( InputFileName2 );

      ::XmlUnion::App app( rdr1, rdr2 );
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
      return 2;
   }
   catch (...)
   {
      ::std::cerr << "Unexpected error with no explanation thrown\n";
      return 3;
   }
   
   // equal. return success
   return 0;
}

