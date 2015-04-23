This project seeks to expand the functionality of modern operating systems via a large suite of interoperable programs. Using simple single purpose tools that can be used together the possibilities grow exponentially. I intend to build the tools so you can use your computer for whatever you can dream up.


### Project goals: ###

  * Provide source code
  * Provide binary versions for common operating systems
  * Define standardized XML [schemas](schemas.md) for exchange of structured data using the [canonical](canonical.md) concept
  * Act as a home base for those standards
  * Encourage participation and contribution

### Currently available tools: ###

  * [XmlCompare](XmlCompare.md) Compare the content of two xml files and return 0 exit code if identical
  * XmlUnion use set theory on Xml documents. Merge Xml files without duplication.
  * [lsXmlCmd](lsXmlCmd.md) Document content of file system(s)
  * [du](du.md) Produce statistics of file systems listed by lsXmlCmd
  * [XmlCmdImageMake](XmlCmdImageMake.md) creates an image of arbitrary size, color, and transparency
  * [XmlCmdImageToPng](XmlCmdImageToPng.md) creates a Png format image from an Xml command line image document. Includes transparency in output image
  * [XmlCmdPngToImage](XmlCmdPngToImage.md) creates an Xml command line image document from a Png format image. Includes transparency

  * [schemas](schemas.md) Image canonical is uploaded

### Current projects in the works: ###

  * using lsXmlCmd output to create File system copy scripts
  * using lsXmlCmd output to create File system comparison
  * image canonical to jpg (with Mozilla changes)
  * image canonical create gradient
  * image canonical sub image cut
  * game of life and mandelbrot set fractal to image canonical

### External tools: ###

  * [xslt](xslt.md) xslt processors
  * [XsdToDDL script](http://www.annlewkowicz.com/2007/03/create-ddl-from-dataset-xsd-file.html) create SQL database tables using an XSD
