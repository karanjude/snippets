declare namespace tns = "http://www.example.org/student";
<kml>
<Folder>
<name>Hotel</name>
<open>1</open>
{
for $hotel in doc("hotel.xml")/tns:hotels/tns:hotel
return
<Placemark>
<name> {$hotel/tns:chainname/text()}, {$hotel/tns:branchname/text()}</name>
<Point><coordinates>{$hotel/tns:latitude/text()},{$hotel/tns:longitude/text()}</coordinates></Point>
</Placemark>
}
</Folder>
</kml>