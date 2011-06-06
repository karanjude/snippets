declare namespace tns = "http://www.example.org/student";

let $hotels := doc("hotel.xml")/tns:hotels/tns:hotel
for $zip in distinct-values(doc("hotel.xml")/tns:hotels/tns:hotel/tns:address/tns:zip)
let $hotelcount := count(for $hotel in $hotels 
                            where $hotel/tns:address/tns:zip = $zip
                            return $hotel
                        )

let $hotelcapacity := sum(for $hotel in $hotels 
                            where $hotel/tns:address/tns:zip = $zip
                            return $hotel/tns:capacity)
order by $hotelcapacity descending
return 
<row>
<zip-code>{$zip}</zip-code>
<number-of-hotels>{$hotelcount}</number-of-hotels>
<capacity>{$hotelcapacity}</capacity>
</row>