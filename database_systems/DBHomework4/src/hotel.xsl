<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:tns="http://www.example.org/student">
	<xsl:template match="/">
		<html>
			<body>
				<h2>Hotels</h2>
				<table border="2">
					<tr bgcolor="blue">
						<th>Hotel Chain</th>
						<th>Hotel Branch Name</th>
						<th>Latitude</th>
						<th>Longitude</th>
						<th>Capacity</th>
						<th>Street No</th>
						<th>Street Name</th>
						<th>City</th>
						<th>State</th>
						<th>Zip</th>
					</tr>
					<xsl:for-each select="tns:hotels/tns:hotel">
						<tr style="font-family:times;font-weight:600">
							<td>
								<xsl:value-of select="tns:chainname" />
							</td>
							<td>
								<xsl:value-of select="tns:branchname" />
							</td>
							<td>
								<xsl:value-of select="tns:latitude" />
							</td>
							<td>
								<xsl:value-of select="tns:longitude" />
							</td>
							<td>
								<xsl:value-of select="tns:capacity" />
							</td>
							<td>
								<xsl:value-of select="tns:address/tns:streetno" />
							</td>
							<td>
								<xsl:value-of select="tns:address/tns:streetname" />
							</td>
							<td>
								<xsl:value-of select="tns:address/tns:city" />
							</td>
							<td>
								<xsl:value-of select="tns:address/tns:state" />
							</td>
							<td>
								<xsl:value-of select="tns:address/tns:zip" />
							</td>
						</tr>
					</xsl:for-each>
				</table>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>