<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:tns="http://www.example.org/student">
	<xsl:template match="/">
		<html>
			<body>
				<h2>Students</h2>
				<table border="1">
					<tr bgcolor="yellow">
						<th>SSN</th>
						<th>First Name</th>
						<th>Last Name</th>
						<th>Age</th>
						<th>Institution Name</th>
						<th>Email</th>
					</tr>
					<xsl:apply-templates />
				</table>
			</body>
		</html>
	</xsl:template>
	<xsl:template match="tns:student">
		<tr style="font-family:verdana;font-weight:400">
			<xsl:apply-templates select="tns:ssn" />
			<xsl:apply-templates select="tns:name" />
			<xsl:apply-templates select="tns:age" />
			<xsl:apply-templates select="tns:institution" />
			<td>
				<xsl:apply-templates select="tns:email" />
			</td>
		</tr>
	</xsl:template>
	<xsl:template match="tns:ssn">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:name">
		<xsl:apply-templates select="tns:firstname" />
		<xsl:apply-templates select="tns:lastname" />
	</xsl:template>

	<xsl:template match="tns:firstname">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:lastname">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:age">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:institution">
		<td>
			<xsl:value-of select="." />
		</td>
	</xsl:template>
	<xsl:template match="tns:email">
		<xsl:value-of select="." />
		<br />
	</xsl:template>

</xsl:stylesheet>