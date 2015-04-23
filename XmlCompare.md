### Introduction ###

This utility was written for unit testing. It compares the content of two xml documents recursively. If the nodes, attributes, and content are identical the exit code is zero.

### Usage ###

```
XmlCompare firstfile.xml secondfile.xml
```

### Source Code ###

The application was written in C++.

The windows and linux versions are both built using two NetBeans IDE projects. The [source](http://code.google.com/p/xml-command-line/source/browse/#git%2FXMLCompare) plus one static library [XmlCmd](http://code.google.com/p/xml-command-line/source/browse/#git%2FXmlCmd) for common code.

To build for a specific environment select the target from the project properties page and hit the build button.

Both environments use GCC for the compiler. The windows version is built using the MingW distribution provided from the Qt project.

### Binaries ###
[Windows](http://code.google.com/p/xml-command-line/source/browse/#git%2Fbin%2Fwin%253Fstate%253Dclosed)

[linux](http://code.google.com/p/xml-command-line/source/browse/#git%2Fbin%2Flinux)