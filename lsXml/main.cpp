/* 
 * File:   main.cpp
 * Author: Jay Sprenkle
 * 
 * A program to output file system information to an xml document.
 * Intended to be part of larger system of xml enabled command line processes.
 *
 * Created on June 30, 2014
 */
#include <cstdlib>
#include <stdexcept>
#include <iostream>

#include "lsXml.FileSystem.h"

#include "lsXml.Config.Settings.h"
#include "lsXml.Config.Reader.h"

/*
 * entry point
 */
int main( int argc, char** argv )
{
   // execution options
   ::lsXml::Config::Settings config;

   // list of directories to be loaded
   ::std::list< ::std::string > directories;

   // <editor-fold defaultstate="collapsed" desc="command line argument parsing">
   ::std::string path( "." );
   if ( argc < 2 )
   {
      directories.push_back( path );
   }
   else
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
                  ::lsXml::Config::Reader rdr( argv[i] );
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

         directories.push_back( arg );
      }
   // </editor-fold>
   
   ::lsXml::FileSystem fs( config );

   // add a content node
   ::rapidxml::xml_node<>* Content = fs.doc.AppendChildNode( fs.doc.root, "Content" );

   fs.AppendDirectories( Content, directories );

   if ( config.Context )
      fs.AppendContext( fs.doc.root, argc, argv );

   // write result as an XML document
   ::rapidxml::print( ::std::cout, fs.doc, ::rapidxml::print_no_indenting );
   
   return 0;
}
