### Introduction ###

lsXmlCmd lists the content of a file system to an xml document. A [FileSystem](http://code.google.com/p/xml-command-line/source/browse/schemas/FileSystem.xsd) schema in the schemas directory documents the output. It can optionally recursively traverse the file system.

### Example output ###

```
<?xml version="1.0" encoding="us-ascii"?>
<ns:FileSystem xmlns:ns="http://www.XmlCommandLine.org/FileSystem/1.0">
  <ns:Directory>
    <ns:Name>lsXml</ns:Name>
    <ns:Owner />
    <ns:GroupOwner />
    <ns:File>
      <ns:Name>.dep.inc</ns:Name>
      <ns:Owner>Administrators</ns:Owner>
      <ns:GroupOwner />
      <ns:Permissions>0000</ns:Permissions>
      <ns:CreationDateTime>2014-06-30T21:06:47</ns:CreationDateTime>
      <ns:LastReadDateTime>2014-06-30T21:06:47</ns:LastReadDateTime>
      <ns:LastChangeDateTime>2014-07-25T19:37:01</ns:LastChangeDateTime>
      <ns:Size>144</ns:Size>
    </ns:File>
...
```

Binary for [windows](https://code.google.com/p/xml-command-line/source/browse/bin/win/lsXmlCmd.exe). No installation is required. Copy to desired directory and set your PATH variable so it can be found.

Configuration [file](https://code.google.com/p/xml-command-line/source/browse/bin/win/lsXmlCmd.Config.xml)

### Usage ###

```
lsXmlCmd [-c ConfigurationFile] DirectoriesToList  ...
```

The 'Recursive' node in the configuration file determines if recursive traversal is enabled.

The 'DotDot' node in the configuration file determines if the '.' and '..' LINK nodes are included in the output document.

The 'Context' node determines if the run time context is added to the result document.

### Example ###

```
lsXmlCmd -c lsXmlCmd.Config.xml "d:/test" d:/test2 "c:/My Documents"
```

### xsl scripts that use lsXmlCmd output ###

XmlFileSystemDiff : Shows changes to the filesystem by comparing two outputs.


### Source Code ###

The application was written in C++.

The windows and linux versions are both built using two NetBeans IDE projects. The [source](http://code.google.com/p/xml-command-line/source/browse/#git%2FlsXmlCmd) plus one static library [XmlCmd](http://code.google.com/p/xml-command-line/source/browse/#git%2FXmlCmd) for common code.

To build for a specific environment select the target from the project properties page and hit the build button.

Both environments use GCC for the compiler. The windows version is built using the MingW distribution provided from the Qt project.