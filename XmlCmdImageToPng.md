### Introduction ###

XmlCmdImageToPng Creates a Png format image from an Xml command line image document. An [Image](http://code.google.com/p/xml-command-line/source/browse/schemas/ImageXmlCmd-schema.xsd) schema in the schemas directory documents the output.

### Usage ###

```
XmlCmdImageToPng [-c ConfigurationFile] [InputFileName] [OutputFileName]
```

The command line file names may also be specified in the configuration file. The command line names trump the configuration file names if both are specified.

### Example ###

```
XmlCmdImageToPng -c XmlCmdImageToPng.Config.xml XmlCmdGradient.Example.xml Example.png

```

### Source Code ###

The application was written in C++.

The windows and linux versions are both built using two NetBeans IDE projects. The [source](http://code.google.com/p/xml-command-line/source/browse/#git%2FXmlCmdImageToPng) plus two static libraries:

[lodepng](http://code.google.com/p/xml-command-line/source/browse/#git%2Flodepng) for png output file encoding.

[XmlCmd](http://code.google.com/p/xml-command-line/source/browse/#git%2FXmlCmd) for common code.

To build for a specific environment select the target from the project properties page and hit the build button.

Both environments use GCC for the compiler. The windows version is built using the MingW distribution provided from the Qt project.