declare namespace tns = "http://www.example.org/student";

let  $students :=  doc("student.xml")//tns:student
let  $participations :=  doc("participation.xml")//tns:participation
let  $conferences :=  doc("conference.xml")//tns:conference

for $c in $conferences
let $attendcount := count(for $p in $participations 
            where data($p/tns:conferencename) = data($c/tns:name) and
                  data($p/tns:conferenceyear) = data($c/tns:year)
            return $p)
return 
<row>
<name>{$c/tns:name/text()}</name>
<year>{$c/tns:year/text()}</year>
<topic>{$c/tns:topic/text()}</topic>
<number-of-attendees
>{$attendcount}</number-of-attendees>
</row>
                       

