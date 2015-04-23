### Introduction ###

XmlCmdImageMake creates the content of an xml document that defines an image. The [ImageXmlCmd](http://code.google.com/p/xml-command-line/source/browse/schemas/ImageXmlCmd-schema.xsd) schema in the schemas directory documents the output.

Instead of command line parameters the program accepts an xml document containing all run time options. The default name is 'XmlCmdImageMake.Config.xml'.

### Example configuration file ###

```
<Config xmlns="http://www.XmlCommandLine.org/XmlCmdMake/1.0">
    <Content>true</Content>
    <Width>128</Width>
    <Height>128</Height>
    <Pixel r="0" g="0" b="0" a="4294967295" />
</Config>
```

No installation is required. Works with either Xalan-C or msxml xsl interpreters.

### Usage ###

```
msxsl XmlCmdMake.Config.xml XmlCmdMake.xslt >XmlCmdMake.Example.xml
```

The 'Content' node in the configuration file determines if the program produces content. I'm not sure why you'd want to invoke it if you didn't want output but...

The 'Width' and 'Height' nodes in the configuration file determines the size of the image to create.

The 'Pixel' node determines the color and transparency of the output image.


### Source Code ###

The xslt script, configuration file, and example batch file are located [here](http://code.google.com/p/xml-command-line/source/browse/#git%2FXmlCmdImageMake)