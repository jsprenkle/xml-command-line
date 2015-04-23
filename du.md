This xslt provides an example of how to get a summary of the statistics a file system. It uses the output from the lsXml program.

I've included FileSystem.xml as an example. The xslt produces output like this:

```
Total bytes in files: 2205204
Total count of files: 136
Total count of Directories: 17
```

The xslt:

```
<!--
This xsl produces a report of the total number of bytes in files, count of files, and count of directories
An example to execute the file in the windows environmtent using the microsoft command line xslt tool:

    lsXml "Your directory to list here" > test.xml
    msxsl test.xml du.xslt -o YourReportNameHere.txt
    del test.xml
    
Example for linux (depends on the xslt processor you install. Assumes xalan here):    

    lsXml "Your directory to list here" | xalan du.xslt > YourReportNameHere.txt
    
written by Jay Sprenkle    
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:ns0="http://www.XmlCommandLine.org/FileSystem/1.0">
    <xsl:output method="text" encoding="us-ascii"/>
    <xsl:template match="/">
        <xsl:text>Total bytes in files: </xsl:text>
        <xsl:value-of select='sum(//ns0:File/ns0:Size)'/>
        <xsl:text>&#xa;</xsl:text>
        
        <xsl:text>Total count of files: </xsl:text>
        <xsl:value-of select='count(//ns0:File)'/>
        <xsl:text>&#xa;</xsl:text>

        <xsl:text>Total count of Directories: </xsl:text>
        <xsl:value-of select='count(//ns0:Directory)'/>
        <xsl:text>&#xa;</xsl:text>
    </xsl:template>
</xsl:stylesheet>
```