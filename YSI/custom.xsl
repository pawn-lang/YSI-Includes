<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<!-- Version: $Id: pawndoc.xsl 3612 2006-07-22 09:59:46Z thiadmer $ -->

<xsl:template match="/">
<HTML>
<HEAD>
<META http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<TITLE><xsl:value-of select="doc/assembly/name"/></TITLE>
<STYLE type="text/css">
	BODY { FONT-FAMILY: "Verdana", sans-serif; FONT-SIZE: x-small; }
	CODE { FONT-SIZE: small; }
	DL { MARGIN-LEFT: 4em; DISPLAY: compact }
	DT { FONT-WEIGHT: bold }
	A:link { COLOR: #4e4887 }
	A:visited { COLOR: #8080c8 }
	A:active { COLOR: #f16043 }
	A:hover { COLOR: #f16043 }
	P { MARGIN-BOTTOM: 0.5em; MARGIN-TOP: 0.5em; MARGIN-LEFT: 4em }
	P.noindent { MARGIN-LEFT: 0em }
	P.syntax { FONT-WEIGHT: bold }
	HR.para { HEIGHT: 0; BORDER: 0; COLOR: transparent; BACKGROUND-COLOR: transparent; MARGIN-TOP: 0.5em; MARGIN-BOTTOM: 0; }
	XMP { BACKGROUND-COLOR: #ddeeff; FONT-SIZE: x-small; MARGIN: 1em }
	PRE { BACKGROUND-COLOR: #ddeeff; FONT-SIZE: x-small; MARGIN: 1em }
	TABLE { BORDER-BOTTOM: medium none; BORDER-LEFT: medium none; BORDER-RIGHT: medium none; BORDER-TOP: medium none }
	TABLE.param { BACKGROUND-COLOR: #ddeeff; }
	TABLE.transition { BACKGROUND-COLOR: #ddeeff; }
	TD { BACKGROUND-COLOR: #ddeeff; BORDER-BOTTOM: medium none; BORDER-LEFT: medium none; BORDER-RIGHT: medium none; BORDER-TOP: medium none; FONT-SIZE: x-small; MARGIN: 2px; PADDING-BOTTOM: 2px; PADDING-LEFT: 2px; PADDING-RIGHT: 2px; PADDING-TOP: 2px; TEXT-ALIGN: left }
	TD.header { BACKGROUND-COLOR: transparent; FONT-WEIGHT: bold; COLOR: #4e4887; WIDTH: 3.3em; PADDING-LEFT: 0px; MARGIN-BOTTOM: 0.5em }
	TD.inline { BACKGROUND-COLOR: transparent }
	TD.param { FONT-WEIGHT: bold; FONT-STYLE: italic; PADDING-RIGHT: 20px; }
	TD.transition { PADDING-RIGHT: 10px; }
	TH { BACKGROUND-COLOR: #336699; COLOR: #ddeeff; BORDER-BOTTOM: medium none; BORDER-LEFT: medium none; BORDER-RIGHT: medium none; BORDER-TOP: medium none; FONT-SIZE: x-small; MARGIN: 2px; PADDING-BOTTOM: 2px; PADDING-LEFT: 4px; PADDING-RIGHT: 4px; PADDING-TOP: 2px; TEXT-ALIGN: left }
	UL { MARGIN-TOP: 0.5em; }
	LI.referrer { DISPLAY: inline; PADDING-RIGHT: 8px }
	LI.dependency { DISPLAY: inline; PADDING-RIGHT: 8px }
	LI.seealso { DISPLAY: inline; PADDING-RIGHT: 8px }
	LI.attribute { DISPLAY: inline; PADDING-RIGHT: 8px }
	LI.post { DISPLAY: inline; PADDING-RIGHT: 8px }
	LI.author { DISPLAY: inline; PADDING-RIGHT: 8px }
	LI.fixes { DISPLAY: inline; PADDING-RIGHT: 8px }
	LI.see { DISPLAY: inline; PADDING-RIGHT: 8px }
	LI.changelog { DISPLAY: inline; }
	.symbol { PADDING-RIGHT: 8px }
	OL { MARGIN-TOP: 0.5em; }
	SPAN.paraminfo { FONT-WEIGHT:Bold; COLOR: #336699; }
	H1 { COLOR: #4e4887; FONT-SIZE: x-large; MARGIN-BOTTOM: 0.5em; MARGIN-TOP: 1em; PADDING-LEFT: 4px }
	H2 { BORDER-RIGHT: #4e4887 8px solid; BORDER-TOP: #4e4887 2px solid; COLOR: #4e4887; MARGIN-BOTTOM: 0.5em; MARGIN-TOP: 1em; }
	H2.general { BORDER: none; }
	H3 { COLOR: #4e4887; FONT-SIZE: x-small; MARGIN-BOTTOM: 0.5em }
	H4 { COLOR: #4e4887; FONT-SIZE: x-small; FONT-STYLE: italic; MARGIN-BOTTOM: 0.5em; DISPLAY: inline; MARGIN: 50px 8px 0px 0px }
	H5 { COLOR: #4e4887; FONT-SIZE: xx-small; MARGIN-BOTTOM: 0.5em }
	H6 { COLOR: #4e4887; FONT-SIZE: xx-small; FONT-STYLE: italic; MARGIN-BOTTOM: 0.5em }
	DIV.library { TEXT-ALIGN: center; BORDER-RIGHT: #4e4887 8px solid; BORDER-TOP: #4e4887 2px solid; COLOR: #4e4887; MARGIN-BOTTOM: 0.5em; MARGIN-TOP: 1em; }
	H1.library { TEXT-ALIGN: center; COLOR: #4e4887; MARGIN-TOP: 0.3em; }
	H2.library { TEXT-ALIGN: center; BORDER: none; }
	PRE { BACKGROUND-COLOR: #ddeeff; FONT-SIZE: small; MARGIN: 1em }
</STYLE>
</HEAD>
<BODY>
	<!-- <h1><xsl:value-of select="doc/assembly/name"/></h1> -->
	<xsl:apply-templates select="doc/general"/>
	<xsl:apply-templates select="doc/members/member"/>
</BODY>
</HTML>
</xsl:template>

<xsl:template match="general">
    <xsl:apply-templates/>
    <br/>
</xsl:template>

<xsl:template match="member">
	<xsl:choose>
		<xsl:when test="substring(@name,1,2) = 'T:'">
			<a><xsl:attribute name="name"><xsl:value-of select="substring(@name,3)"/></xsl:attribute><h2><span style="float:right; padding-right:2px">enumeration</span><xsl:value-of select="substring(@name,3)"/></h2></a>
			<xsl:apply-templates select="summary"/>
			<xsl:if test="remarks">
				<h3>Remarks</h3>
				<xsl:apply-templates select="remarks"/>
			</xsl:if>
			<xsl:if test="member">
				<h3>Members</h3>
				<blockquote>
				<xsl:apply-templates select="member"/>
				</blockquote>
			</xsl:if>
			<xsl:apply-templates select="example"/>
			<xsl:if test="referrer">
				<h3>Used by</h3>
				<ul><xsl:apply-templates select="referrer"/></ul>
			</xsl:if>
			<xsl:if test="fixes">
				<h3>Fixes</h3>
				<ul><xsl:apply-templates select="fixes"/></ul>
			</xsl:if>
			<xsl:if test="dependency">
				<h3>Depends on</h3>
				<ul><xsl:apply-templates select="dependency"/></ul>
			</xsl:if>
			<xsl:if test="seealso">
				<h3>See Also</h3>
				<ul><xsl:apply-templates select="seealso"/></ul>
			</xsl:if>
		</xsl:when>
		<xsl:when test="substring(@name,1,2) = 'C:'">
			<a><xsl:attribute name="name"><xsl:value-of select="substring(@name,3)"/></xsl:attribute><h2><span style="float:right; padding-right:2px">constant</span><xsl:value-of select="substring(@name,3)"/></h2></a>
			<p class="noindent"><table><tr><td class="header inline">Value</td><td class="inline"><xsl:value-of select="@value"/></td></tr></table></p>
			<xsl:apply-templates select="summary"/>
			<xsl:apply-templates select="tagname"/>
			<xsl:apply-templates select="size"/>
			<xsl:if test="remarks">
				<h3>Remarks</h3>
				<xsl:apply-templates select="remarks"/>
			</xsl:if>
			<xsl:apply-templates select="example"/>
			<xsl:if test="referrer">
				<h3>Used by</h3>
				<ul><xsl:apply-templates select="referrer"/></ul>
			</xsl:if>
			<xsl:if test="fixes">
				<h3>Fixes</h3>
				<ul><xsl:apply-templates select="fixes"/></ul>
			</xsl:if>
			<xsl:if test="dependency">
				<h3>Depends on</h3>
				<ul><xsl:apply-templates select="dependency"/></ul>
			</xsl:if>
			<xsl:if test="seealso">
				<h3>See Also</h3>
				<ul><xsl:apply-templates select="seealso"/></ul>
			</xsl:if>
		</xsl:when>
		<xsl:when test="substring(@name,1,2) = 'M:'">
			<a><xsl:attribute name="name"><xsl:value-of select="substring(@name,3)"/></xsl:attribute><h2><span style="float:right; padding-right:2px">function</span><xsl:value-of select="substring(@name,3)"/></h2></a>
			<xsl:apply-templates select="summary"/>
			<h3>Syntax</h3><p class="syntax"><xsl:value-of select="@syntax"/></p>
			<xsl:if test="param">
				<p><table class="param"><xsl:apply-templates select="param"/></table></p>
			</xsl:if>
			<xsl:apply-templates select="tagname"/>
			<xsl:apply-templates select="returns"/>
			<xsl:if test="remarks">
				<h3>Remarks</h3>
				<xsl:apply-templates select="remarks"/>
			</xsl:if>
			<xsl:apply-templates select="example"/>
			<xsl:if test="referrer">
				<h3>Used by</h3>
				<ul><xsl:apply-templates select="referrer"/></ul>
			</xsl:if>
			<xsl:if test="fixes">
				<h3>Fixes</h3>
				<ul><xsl:apply-templates select="fixes"/></ul>
			</xsl:if>
			<xsl:if test="dependency">
				<h3>Depends on</h3>
				<ul><xsl:apply-templates select="dependency"/></ul>
			</xsl:if>
			<xsl:if test="attribute">
				<h3>Attributes</h3>
				<ul><xsl:apply-templates select="attribute"/></ul>
			</xsl:if>
			<xsl:apply-templates select="automaton"/>
			<xsl:if test="transition">
				<h3>Transition table</h3>
				<p>
					<table class="transition">
						<tr><th>Source</th><th>Target</th><th>Condition</th></tr>
						<xsl:apply-templates select="transition"/>
					</table>
				</p>
			</xsl:if>
			<xsl:apply-templates select="stacksize"/>
			<xsl:if test="seealso">
				<h3>See Also</h3>
				<ul><xsl:apply-templates select="seealso"/></ul>
			</xsl:if>
		</xsl:when>
		<xsl:when test="substring(@name,1,2) = 'F:'">
			<a><xsl:attribute name="name"><xsl:value-of select="substring(@name,3)"/></xsl:attribute><h2><span style="float:right; padding-right:2px">variable</span><xsl:value-of select="substring(@name,3)"/></h2></a>
			<xsl:apply-templates select="summary"/>
			<xsl:apply-templates select="tagname"/>
			<xsl:if test="remarks">
				<h3>Remarks</h3>
				<xsl:apply-templates select="remarks"/>
			</xsl:if>
			<xsl:apply-templates select="example"/>
			<xsl:if test="referrer">
				<h3>Used by</h3>
				<ul><xsl:apply-templates select="referrer"/></ul>
			</xsl:if>
			<xsl:if test="fixes">
				<h3>Fixes</h3>
				<ul><xsl:apply-templates select="fixes"/></ul>
			</xsl:if>
			<xsl:if test="dependency">
				<h3>Depends on</h3>
				<ul><xsl:apply-templates select="dependency"/></ul>
			</xsl:if>
			<xsl:if test="seealso">
				<h3>See Also</h3>
				<ul><xsl:apply-templates select="seealso"/></ul>
			</xsl:if>
		</xsl:when>
	</xsl:choose>
</xsl:template>

<xsl:template match="summary">
	<p><xsl:apply-templates/></p>
</xsl:template>

<xsl:template match="param">
	<tr>
		<td class="param"><xsl:value-of select="@name"/></td>
		<td><xsl:apply-templates/></td>
	</tr>
</xsl:template>

<xsl:template match="paraminfo">
	<span class="paraminfo">&lt;<xsl:apply-templates/>&gt;</span>
</xsl:template>

<xsl:template match="tagname">
	<p class="noindent"><table><tr>
		<td class="header inline">Tag</td>
		<td class="inline"><xsl:value-of select="@value"/></td>
	</tr></table></p>
</xsl:template>

<xsl:template match="size">
	<p class="noindent"><table><tr>
		<td class="header inline">Size</td>
		<td class="inline"><xsl:value-of select="@value"/></td>
	</tr></table></p>
</xsl:template>

<xsl:template match="returns">
	<h3>Returns</h3>
	<p><xsl:apply-templates/></p>
</xsl:template>

<xsl:template match="remarks">
	<p><xsl:apply-templates/></p>
</xsl:template>

<xsl:template match="example">
	<h3>Example</h3>
	<p><xsl:apply-templates/></p>
</xsl:template>

<xsl:template match="attribute">
	<li class="attribute"><xsl:value-of select="@name"/></li>
</xsl:template>

<xsl:template match="referrer">
	<li class="referrer"><a><xsl:attribute name="href">#<xsl:value-of select="@name"/></xsl:attribute><code><xsl:value-of select="@name"/></code></a></li>
</xsl:template>

<xsl:template match="dependency">
	<li class="dependency"><a><xsl:attribute name="href">#<xsl:value-of select="@name"/></xsl:attribute><code><xsl:value-of select="@name"/></code></a></li>
</xsl:template>

<xsl:template match="stacksize">
	<h3>Estimated stack usage</h3>
	<p><xsl:value-of select="@value"/> cells</p>
</xsl:template>

<xsl:template match="automaton">
	<h3>Automaton</h3>
	<p><xsl:value-of select="@name"/></p>
</xsl:template>

<xsl:template match="transition">
	<tr>
		<td class="transition"><xsl:value-of select="@source"/></td>
		<td class="transition"><xsl:value-of select="@target"/></td>
		<td><xsl:value-of select="@condition"/></td>
	</tr>
</xsl:template>

<xsl:template match="code">
	<pre><xsl:apply-templates/></pre>
</xsl:template>

<xsl:template match="seealso">
	<a><xsl:attribute name="href">#<xsl:value-of select="@name"/></xsl:attribute><code><xsl:value-of select="@name"/></code></a>
</xsl:template>

<xsl:template match="paramref">
	<i><xsl:value-of select="@name"/></i>
</xsl:template>

<xsl:template match="c"><code><xsl:apply-templates/></code></xsl:template>

<xsl:template match="em"><em><xsl:apply-templates/></em></xsl:template>

<xsl:template match="ul"><ul><xsl:apply-templates/></ul></xsl:template>

<xsl:template match="ol"><ol><xsl:apply-templates/></ol></xsl:template>

<xsl:template match="li"><li><xsl:apply-templates/></li></xsl:template>

<xsl:template match="p"><hr class="para"/><xsl:apply-templates/></xsl:template>

<xsl:template match="para"><hr class="para"/><xsl:apply-templates/></xsl:template>

<xsl:template match="section"><h1 class="general"><xsl:apply-templates/></h1></xsl:template>

<xsl:template match="subsection"><h2 class="general"><xsl:apply-templates/></h2></xsl:template>

<xsl:template match="library">
	<div class="library">
		<span style="float:right; padding-right:2px; height: 6em"><h1 class="library">library</h1></span>
		<h1 class="library">
			<xsl:value-of select="@name"/>
		</h1>
		<xsl:if test="@description">
			<h2 class="library"><xsl:value-of select="@description"/></h2>
		</xsl:if>
	</div>
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="br"><br /></xsl:template>
<xsl:template match="indent">&#160;&#160;&#160;&#160;</xsl:template>

<xsl:template match="a">
	<xsl:choose>
		<xsl:when test="node()">
			<a>
				<xsl:attribute name="href"><xsl:value-of select="@href"/></xsl:attribute>
				<xsl:apply-templates/>
			</a>
		</xsl:when>
		<xsl:otherwise>
			<a>
				<xsl:attribute name="href"><xsl:value-of select="@href"/></xsl:attribute>
				<xsl:value-of select="@href"/>
			</a>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template match="symbolref">
	<a><xsl:attribute name="href">#<xsl:value-of select="@name"/></xsl:attribute><code><xsl:value-of select="@name"/></code></a>
</xsl:template>

<xsl:template match="symbol">
	<li><span class="symbol"><a><xsl:attribute name="href">#<xsl:value-of select="@name"/></xsl:attribute><code><xsl:value-of select="@name"/></code></a>:</span><xsl:apply-templates/></li>
</xsl:template>

<xsl:template match="synonym">
	<li><span class="symbol"><code><xsl:value-of select="@name"/></code>:</span>Synonym for <a><xsl:attribute name="href">#<xsl:value-of select="@for"/></xsl:attribute><code><xsl:value-of select="@for"/></code></a><xsl:apply-templates/>.</li>
</xsl:template>

<xsl:template match="changelog">
	<li class="changelog"><h3 class="general"><xsl:value-of select="@date"/></h3>
	<ul><xsl:apply-templates/></ul></li>
</xsl:template>


<!-- fixes.inc -->

<xsl:template match="fix">
	<a><xsl:attribute name="name">FIX_<xsl:value-of select="@name"/></xsl:attribute><h2><span style="float:right; padding-right:2px">fix</span><xsl:value-of select="@name"/></h2></a>
	<xsl:if test="@fixed">
		<p><b>Fixed in <xsl:value-of select="@fixed"/></b></p>
	</xsl:if>
	<xsl:if test="@disabled">
		<xsl:if test="@disabled='true'">
			<p><b>Disabled By Default</b></p>
		</xsl:if>
	</xsl:if>

	<h3>Problem</h3>
	<xsl:apply-templates select="problem"/>
	<h3>Solution</h3>
	<xsl:apply-templates select="solution"/>
	<xsl:if test="see">
		<h3>See</h3>
		<ul><xsl:apply-templates select="see"/></ul>
	</xsl:if>
	<xsl:if test="author">
		<h3>Author(s)</h3>
		<ul><xsl:apply-templates select="author"/></ul>
	</xsl:if>
	<xsl:if test="post">
		<h3>Post(s)</h3>
		<ul><xsl:apply-templates select="post"/></ul>
	</xsl:if>
</xsl:template>

<xsl:template match="post">
	<li class="post"><a><xsl:attribute name="href"><xsl:value-of select="@href"/></xsl:attribute><xsl:value-of select="@href"/></a></li>
</xsl:template>
<xsl:template match="see">
	<li class="see"><a><xsl:attribute name="href">#<xsl:apply-templates/></xsl:attribute><code><xsl:apply-templates/></code></a></li>
</xsl:template>
<xsl:template match="author">
	<li class="author">
		<xsl:choose>
			<xsl:when test="@href">
				<a><xsl:attribute name="href"><xsl:value-of select="@href"/></xsl:attribute><xsl:apply-templates/></a>
			</xsl:when>
			<xsl:otherwise>
				<xsl:apply-templates/>
			</xsl:otherwise>
		</xsl:choose>
	</li>
</xsl:template>
<xsl:template match="problem">
	<p><xsl:apply-templates/></p>
</xsl:template>
<xsl:template match="solution">
	<p><xsl:apply-templates/></p>
</xsl:template>

<xsl:template match="fixeslist"><xsl:apply-templates/></xsl:template>

<xsl:template match="fixes">
	<li class="fixes"><a><xsl:attribute name="href">#FIX_<xsl:apply-templates/></xsl:attribute><xsl:apply-templates/></a></li>
</xsl:template>

</xsl:stylesheet>

