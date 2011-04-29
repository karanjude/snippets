<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<body>
				<h2>Students</h2>
				<table border="1">
					<tr bgcolor="yellow">
						<th>Title</th>
						<th>Artist</th>
					</tr>
					<xsl:for-each select="Students/student">
						<tr>
							<td>
							 <font><xsl:value-of select="ssn" /></font>
								
							</td>
							<td>
							<font><xsl:value-of select="age" /></font>
								<xsl:value-of select="age" />
							</td>
						</tr>
					</xsl:for-each>
				</table>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>