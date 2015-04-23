### Introduction ###

This utility was written to merge the content of two Xml files. I intend to use it to merge snippets of configuration files on Windows machines. When you install an application it may require configuration changes to the application or machine configuration files. If the installation is repeated it's possible to create multiple entries in the configuration. This application eliminates the possible errors and makes it simpler.

### Usage ###

```
XmlUnion firstfile.xml secondfile.xml OutputFile.xml
```

### Source Code ###

The application was written in C++.

The windows and linux versions are both built using two NetBeans IDE projects. The [source](http://code.google.com/p/xml-command-line/source/browse/#git%2FXmlUnion) plus one static library [XmlCmd](http://code.google.com/p/xml-command-line/source/browse/#git%2FXmlCmd) for common code.

To build for a specific environment select the target from the project properties page and hit the build button.

Both environments use GCC for the compiler. The windows version is built using the MingW distribution provided from the Qt project.

### Binaries ###
[Windows](http://code.google.com/p/xml-command-line/source/browse/#git%2Fbin%2Fwin)