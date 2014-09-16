<!--
    This xslt produces a single color image of any arbitrary size.

    Using Microsoft msxsl:
    msxsl XmlCmdMake.Config.xml XmlCmdMake.xslt -o XmlCmdMake.Output.xml

    Using xalan:
    xalan -o XmlCmdMake.Output.xml XmlCmdMake.Config.xml XmlCmdMake.xslt

written by Jay Sprenkle
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:ns="http://www.XmlCommandLine.org/XmlCmdMake/1.0"
                xmlns:img="http://www.XmlCommandLine.org/ImageXml/1.0"
                exclude-result-prefixes="ns img"
>
    <xsl:output method="xml" version="1.0" omit-xml-declaration="yes" indent="no" encoding="utf-8"/>

    <!--do not copy unmatched text-->
    <xsl:template match="text()|@*" />

    <xsl:template name="PixelTemplate">
        <xsl:param name="ColumnNumber" />
        <xsl:param name="Count" />
        
        <xsl:if test="$ColumnNumber &lt; $Count">
            <Pixel xmlns="http://www.XmlCommandLine.org/Image/1.0">
                <xsl:attribute name="x">
                    <xsl:value-of select="$ColumnNumber"/>
                </xsl:attribute>
                <xsl:attribute name="r">
                    <xsl:value-of select="ns:Pixel/@r"/>
                </xsl:attribute>
                <xsl:attribute name="g">
                    <xsl:value-of select="ns:Pixel/@g"/>
                </xsl:attribute>
                <xsl:attribute name="b">
                    <xsl:value-of select="ns:Pixel/@b"/>
                </xsl:attribute>
                <xsl:attribute name="a">
                    <xsl:value-of select="ns:Pixel/@a"/>
                </xsl:attribute>
            </Pixel>

            <xsl:call-template name="PixelTemplate">
                <xsl:with-param name="ColumnNumber" select="$ColumnNumber+1" />
                <xsl:with-param name="Count" select="$Count" />
            </xsl:call-template>            
        </xsl:if>
    </xsl:template>

    <xsl:template name="Row">
        <xsl:param name="RowNumber" />
        <xsl:param name="Count" />
        <xsl:if test="$RowNumber &lt; $Count">
            <Row xmlns="http://www.XmlCommandLine.org/Image/1.0">
                <xsl:attribute name="y">
                    <xsl:value-of select="$RowNumber"/>
                </xsl:attribute>
                <xsl:call-template name="PixelTemplate">
                    <xsl:with-param name="ColumnNumber" select="0" />
                    <xsl:with-param name="Count" select="ns:Width" />
                </xsl:call-template>            
            </Row>

            <xsl:call-template name="Row">
                <xsl:with-param name="RowNumber" select="$RowNumber+1"  />
                <xsl:with-param name="Count" select="$Count"  />
            </xsl:call-template>            
        </xsl:if>
    </xsl:template>

    <xsl:template match="/ns:Config">
        <!--ensure the configuration file is valid-->
        <xsl:if test="/ns:Config[not(ns:Pixel)]">
            <xsl:message terminate="yes" >The configuration file does not contain a Pixel node.</xsl:message>
        </xsl:if>
        <xsl:if test="/ns:Config[not(ns:Width)]">
            <xsl:message terminate="yes" >The configuration file does not contain a Width node.</xsl:message>
        </xsl:if>
        <xsl:if test="/ns:Config[not(ns:Height)]">
            <xsl:message terminate="yes" >The configuration file does not contain a Height node.</xsl:message>
        </xsl:if>
    
        <Image xmlns="http://www.XmlCommandLine.org/Image/1.0">
            <xsl:if test="ns:Content[.='true']">
                <Content>
                    <Layer>
                        <xsl:attribute name="z">
                            <xsl:text>0</xsl:text>
                        </xsl:attribute>
                        <xsl:attribute name="Width">
                            <xsl:value-of select="ns:Width" />
                        </xsl:attribute>
                        <xsl:attribute name="Height">
                            <xsl:value-of select="ns:Height" />
                        </xsl:attribute>
                        
                        <xsl:call-template name="Row">
                            <xsl:with-param name="RowNumber" select="0" />
                            <xsl:with-param name="Count" select="ns:Height" />
                        </xsl:call-template>
                    </Layer>
                </Content>
            </xsl:if>
            <xsl:if test="ns:Context[.='true']">
                <Context>
<!--                    todo: add current datetime -->
                    <Creation Created="">
                        <Source Name="XmlCmdMake.xslt" Version="1.0" />
                    </Creation>
                </Context>
            </xsl:if>
        </Image>
    </xsl:template>
</xsl:stylesheet>

