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
					<xsl:for-each select="tns:Students/tns:student">
						<tr style="font-family:verdana;font-weight:400">
							<td>
								<xsl:value-of select="tns:ssn" />
							</td>
							<td>
								<xsl:value-of select="tns:name/tns:firstname" />
							</td>
							<td>
								<xsl:value-of select="tns:name/tns:lastname" />
							</td>
							<td>
								<xsl:value-of select="tns:age" />
							</td>
							<td>
								<xsl:value-of select="tns:institution" />
							</td>
							<td>
								<xsl:value-of select="tns:email" />
							</td>

						</tr>
					</xsl:for-each>
				</table>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>