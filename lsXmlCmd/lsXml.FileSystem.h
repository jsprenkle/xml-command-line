/* 
 * File:   lsxml.FileSystem.h
 * Author: Jay Sprenkle
 *
 * Created on June 30, 2014
 */
#ifndef LSXMLFILESYSTEM_H
#define	LSXMLFILESYSTEM_H

#include <string>
#include <list>

#include <stdio.h>
#include <dirent.h>
#include <stdint.h>

#include "lsXml.Config.Settings.h"
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include "XmlCmd.Document.h"

namespace lsXml
{
   class FileSystem
   {
   public:
      FileSystem( const ::lsXml::Config::Settings& config );

      /**
       * Append content of a directory to an xml node
       * @param Parent parent xml node to add to
       * @param path path of directory to read
       * @param recursive
       * @param dotdot Should the output include the "." and ".." directory entries
       */
      void AppendDirectories( ::rapidxml::xml_node<>* Parent, ::std::list< ::std::string >& directories );
      
      /**
       * Append context of execution to document
       */
      void AppendContext( ::rapidxml::xml_node<>* Parent, int argc, char** argv );
      
      /**
       * Return only file name portion of a path/filename
       * @param Path
       * @return 
       */
      ::std::string basename( const ::std::string& Path );

      ::XmlCmd::Document doc;

      ::rapidxml::xml_node<>* Context;
      
   private:
      const ::lsXml::Config::Settings& config;
      
      /**
       * Append a directory xml node
       * @param Parent parent xml node to add to
       * @param path path of directory to read
       */
      ::rapidxml::xml_node<>* AppendDirectoryElement( ::rapidxml::xml_node<>* Parent, const ::std::string& path, const ::std::string& Owner, const ::std::string& GroupOwner );
      
      static void LogError( const char* msg, const ::std::string& name );
      static ::std::string BuildPath( const ::std::string& dirname, const ::std::string& name );

#ifdef __linux__
      static ::std::string getUserName( uid_t uid );
#endif
#ifdef WIN32
      static ::std::string getUserName( const ::std::string& FileName );
#endif
      
      /**
       * get user name of process that invoked this application
       * @return 
       */
      ::std::string UserName();
      
      /**
       * get computer host name
       * @return 
       */
      ::std::string HostName();
   };
}
#endif
