## Introduction ##

A useful addition to your toolkit as a programmer, administrator, or just computer owner is to track changes to your system over time. The lsXml application will capture a snapshot of a file system formatted as an XML document. By comparing two file system snapshots you can see what changes were made.

## Details ##

An xsl script was chosen as a simple way to compare two xml documents. Changes to a file system would include objects added, removed, or changed. The xsl will have three sections in it's result.

To make it easier to use and more attractive the result will be html. The result can contain very long lists of changes. An 'accordian' control lets you compress items when you don't wish to view them. The jquery toolkit offers a simple accordian control so I'll use it here.

The input will be two copies of the output from lsXml. Here's the xslt script:

```
<!--
    This xslt produces a report of changes to a file system.
    Assumes:
    * the first parameter is a file system document
    * the second parameter is a file system document
    * Both documents are for the same filesystem
    * The first document was produced chronologically before the second.

    lsXml "Directory" > FileSystem1.xml
    lsXml "Directory" > FileSystem2.xml
    msxsl FileSystem1.xml -p p1="FileSystem2.xml" Xml.FileSystem.Diff.xslt -o report.html

    Using xalan:
    xalan FileSystem1.xml -p p1 "FileSystem2.xml" Xml.FileSystem.Diff.xslt -o report.html

written by Jay Sprenkle
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:ns="http://www.XmlCommandLine.org/FileSystem/1.0"
                exclude-result-prefixes="ns"
>
    <xsl:output method="html" version="4.0" omit-xml-declaration="yes" indent="yes" encoding="utf-8"/>
    <xsl:param name="p1" select="'FileSystem.xml'"/>

    <!--The first document-->
    <xsl:variable name="fs0" select="//ns:FileSystem/ns:Content" />

    <!--The p1 parameter on the command line-->
    <xsl:variable name="doc1" select="document( $p1 )" />
    <xsl:variable name="fs1" select="$doc1//ns:FileSystem/ns:Content" />

    <!--do not copy unmatched test-->
    <xsl:template match="text()|@*" />

    <xsl:template match="/ns:FileSystem/ns:Content">

        <html>
            <head>
                <title>FileSystem changes</title>
                <link rel="stylesheet" href="http://code.jquery.com/ui/1.11.0/themes/smoothness/jquery-ui.css" />
                <script src="http://code.jquery.com/jquery-1.10.2.js"></script>
                <script src="http://code.jquery.com/ui/1.11.0/jquery-ui.js"></script>
                <link rel="stylesheet" href="/resources/demos/style.css" />
                <script>
                    $(function() {
                    $( "#accordion" ).accordion();
                    });
                </script>
            </head>

            <body>
          
                <h3>FileSystem changes</h3>
                <div id="accordion">

                    <xsl:variable name="removed" select="$fs0//ns:Path[ not( ./text() = $fs1//*/ns:Path/text() ) ]" />
                    <h3>
                        <xsl:text>Removed (</xsl:text>
                        <xsl:value-of select='count($removed)'/>
                        <xsl:text>)</xsl:text>
                    </h3>
                    <div>
                        <ul>
                            <xsl:for-each select="$removed">
                                <li>
                                    <xsl:value-of select='text()'/>
                                </li>
                            </xsl:for-each>
                        </ul>
                    </div>

                    <xsl:variable name="added" select="$fs1//ns:Path[ not( $fs0//ns:Path/text() = text() ) ]" />
                    <h3>
                        <xsl:text>Added (</xsl:text>
                        <xsl:value-of select='count($added)'/>
                        <xsl:text>)</xsl:text>
                    </h3>
                    <div>
                        <ul>
                            <xsl:for-each select="$added">
                                <li>
                                    <xsl:value-of select='text()'/>
                                </li>
                            </xsl:for-each>
                        </ul>
                    </div>

                    <xsl:variable name="changed" select="$fs0//*[ns:LastChangeDateTime][(ns:Path/text() = $fs1//*/ns:Path/text()) and not(ns:LastChangeDateTime/text() = $fs1//ns:LastChangeDateTime/text())]" />
                    <h3>
                        <xsl:text>Changed (</xsl:text>
                        <xsl:value-of select='count($changed)'/>
                        <xsl:text>)</xsl:text>
                    </h3>
                    <div>
                        <table border="1" cellpadding="8">
                            <thead>
                                <tr>
                                    <th>Path</th>
                                    <th>Change date/time</th>
                                </tr>
                            </thead>
                            <tbody>

                                <xsl:for-each select="$changed">
                                    <!-- first node info-->
                                    <xsl:variable name="first" select="." />
                                    <xsl:variable name="FirstPath" select="$first/ns:Path/text()" />
                                    <xsl:variable name="FirstLastChangeDateTime" select="$first/ns:LastChangeDateTime/text()" />

                                    <!-- Get matching node with the same path in the other document -->
                                    <xsl:variable name="second" select="$fs1//*[ns:Path/text() = $FirstPath]" />

                                    <tr>
                                        <td>
                                            <xsl:value-of select='$FirstPath'/>
                                        </td>
                                        <td>
                                            <xsl:value-of select='$second/ns:LastChangeDateTime/text()'/>
                                        </td>
                                    </tr>
                                </xsl:for-each>
                            </tbody>
                        </table>
                    </div>

                </div>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>

```

The html output looks like this:
```
<html>
<head>
<META http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>FileSystem changes</title>
<link rel="stylesheet" href="http://code.jquery.com/ui/1.11.0/themes/smoothness/jquery-ui.css">
<script src="http://code.jquery.com/jquery-1.10.2.js"></script><script src="http://code.jquery.com/ui/1.11.0/jquery-ui.js"></script>
<link rel="stylesheet" href="/resources/demos/style.css">
<script>
                    $(function() {
                    $( "#accordion" ).accordion();
                    });
                </script>
</head>
<body>
<h3>FileSystem changes</h3>
<div id="accordion">
<h3>Removed (1)</h3>
<div>
<ul>
<li>D:/temp/XmlCommandLine/lsXml/FileSystemExample.xml</li>
</ul>
</div>
<h3>Added (1)</h3>
<div>
<ul>
<li>D:/temp/XmlCommandLine/lsXml/FileSystemChanged.xml</li>
</ul>
</div>
<h3>Changed (1)</h3>
<div>
<table border="1" cellpadding="8">
<thead>
<tr>
<th>Path</th><th>Change date/time</th>
</tr>
</thead>
<tbody>
<tr>
<td>D:/temp/XmlCommandLine/lsXml/.dep.inc</td><td>2014-08-14T16:10:42</td>
</tr>
</tbody>
</table>
</div>
</div>
</body>
</html>
```
