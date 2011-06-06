<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:tns="http://www.example.org/student">
	<xsl:template match="/">
		<html>
			<body>
				<h2>Participation</h2>
				<table border="3">
					<tr bgcolor="green">
						<th>Student SSN</th>
						<th>Conference Name</th>
						<th>Conference Year</th>
						<th>Registration Number</th>
						<th>Registration fee</th>
					</tr>
					<xsl:for-each select="tns:participations/tns:participation">
						<tr style="font-family:nina;font-weight:500;font-style:italic">
							<td>
								<xsl:value-of select="tns:ssn" />
							</td>
							<td>
								<xsl:value-of select="tns:conferencename" />
							</td>
							<td>
								<xsl:value-of select="tns:conferenceyear" />
							</td>
							<td>
								<xsl:value-of select="tns:regno" />
							</td>
							<td>
								<xsl:value-of select="tns:regfee" />
							</td>
						</tr>
					</xsl:for-each>
				</table>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>