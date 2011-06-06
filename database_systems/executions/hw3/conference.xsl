<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:tns="http://www.example.org/student">
	<xsl:template match="/">
		<html>
			<body>
				<h2>Conference</h2>
				<table border="1">
					<tr bgcolor="orange">
						<th>Name</th>
						<th>Year</th>
						<th>Topic</th>
						<th>Chair</th>
						<th>Original City</th>
						<th>Original Country</th>
						<th>Hotel Chain Name</th>
						<th>Hotel Branch Name</th>
					</tr>
					<xsl:apply-templates />
				</table>
			</body>
		</html>
	</xsl:template>
	<xsl:template match="tns:conference">
		<tr style="font-family:arial;font-weight:400">
			<xsl:apply-templates select="tns:name" />
			<xsl:apply-templates select="tns:year" />
			<xsl:apply-templates select="tns:topic" />

			<td>
				<xsl:apply-templates select="tns:chair" />
			</td>

			<xsl:apply-templates select="tns:city" />
			<xsl:apply-templates select="tns:country" />
			<xsl:apply-templates select="tns:hotelchainname" />
			<xsl:apply-templates select="tns:hotelbranchname" />
		</tr>
	</xsl:template>
	<xsl:template match="tns:name">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:year">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:topic">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:city">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:country">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:hotelchainname">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:hotelbranchname">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>

	<xsl:template match="tns:chair">
		<xsl:value-of select="." />
		<br />
	</xsl:template>

</xsl:stylesheet>