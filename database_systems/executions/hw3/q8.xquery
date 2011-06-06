declare namespace tns = "http://www.example.org/student";

let  $hotels :=  distinct-values(doc("hotel.xml")//tns:chainname)
let  $conferences :=  doc("conference.xml")//tns:conference

for $h in $hotels
let $totalheld := count(for $c in $conferences 
            where data($c/tns:hotelchainname) = $h
            return $c)
return 
<row>
<name>{$h}</name>
<number-of-conferences> {$totalheld} </number-of-conferences>
</row>

                       

