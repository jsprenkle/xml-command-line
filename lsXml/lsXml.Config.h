/* 
 * File:   lsXml.Config.h
 * Author: Jay Sprenkle
 *
 * DTO objects for containing configuration information
 * 
 * Created on July 30, 2014
 */
#ifndef LSXML_CONFIG_H
#define	LSXML_CONFIG_H

#include <string>
#include <vector>
#include <rapidxml.hpp>

namespace lsXml
{
   class Config
   {
      bool recursive;
      bool dotdot;

      Config( const ::std::string& Name );
      ~Config();
   private:
      char* buffer;

      ::rapidxml::xml_node<>* current_node;
      const char* ReadNode( const char* NodeName, const char* DefaultValue = "" );
      bool ParseBool( const char* str );
   };
}

#endif
