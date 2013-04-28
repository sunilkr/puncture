<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns="http://www.w3.org/1999/xhtml"
>
  <xsl:template match="/puncture">
    <!-- TODO: Auto-generated template -->
    <html>
      <head>
        <title> Puncture: A Pintool for Behaviour Analysis</title>
        <link rel="stylesheet" type="text/css" src="puncture.css" />
        <link rel="javascript" type="text/javascript" src="puncture.js" />
      </head>
      <body>
        <div id="panel-right" class="panel right-align menu-panel">
          <div id="panel-item-images" class="right-panel-item">
            <span id="images" class="right-panel-text">Loaded Images</span>
          </div>
          <div id="panel-item-methods" class="right-panel-item">
            <span id="methods">Called Methods</span>
          </div>
          <div id="panel-item-threads" class="right-panel-item">
            <span id="threads">Execution Threads</span>
          </div>
          <div id="panel-item-calls" class="right-panel-item">
            <span id="calls">All Calls</span>
          </div>
        </div>
        <xsl:apply-templates />
      </body>
    </html>
  </xsl:template>
  <xsl:template match="images">
    <div id="content-div-images" class="content-panel panel center-aligh">
      <table id="image-table" class="content-table">
        <!-- <tr id="image-table-header" class="content-table-header"> -->
        <!-- <td class="image-table-header-cell content-table-hdr-cell">Name</td> -->
        <!-- <td class="image-table-header-cell content-table-hdr-cell">Path</td> -->
        <!-- <td class="image-table-header-cell content-table-hdr-cell">Base 
          Address</td> -->
        <!-- <td class="image-table-header-cell content-table-hdr-cell"></td> -->
        <!-- </tr> -->
        <xsl:for-each select="image">
          <table class="image-detail">
            <tr>
              <td class="image-hdr">Name</td>
              <td class="image-value">
                <xsl:value-of select="@name" />
              </td>
            </tr>
            <tr>
              <td class="image-hdr">Path</td>
              <td class="image-value">
                <xsl:value-of select="path" />
              </td>
            </tr>
            <tr>
              <td class="image-hdr">Base Address</td>
              <td class="image-value">
                <xsl:value-of select="base" />
              </td>
            </tr>
            <tr>
              <td class="image-hdr">Mapped Size</td>
              <td class="image-value">
                <xsl:value-of select="mapped-size" />
              </td>
            </tr>
            <tr>
              <td class="image-hdr">Entry Point</td>
              <td class="image-value">
                <xsl:value-of select="entry-point" />
              </td>
            </tr>
            <xsl:for-each select="methods">
              <tr>
                <td class="image-hdr">Methods</td>
                <td class="image-value">
                  <table class="methods-table">
                    <tr class="methods-hdr">
                      <td>Address</td>
                      <td>Name</td>
                    </tr>
                    <xsl:for-each select="methods/method">
                      <tr class="image-methods">
                        <td>
                          <xsl:value-of select="@adrress" />
                        </td>
                        <td>
                          <xsl:value-of select="."/>
                        </td>
                      </tr>
                    </xsl:for-each>
                  </table>
                </td>
              </tr>
            </xsl:for-each>
          </table>
        </xsl:for-each>
      </table>
    </div>
  </xsl:template>
</xsl:stylesheet>