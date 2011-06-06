declare namespace tns = "http://www.example.org/student";

let  $students :=  doc("student.xml")//tns:student
let  $participations :=  doc("participation.xml")//tns:participation
let  $conferences :=  doc("conference.xml")//tns:conference

for $c in $conferences
let $avgage := avg(for $p in $participations 
            where data($p/tns:conferencename) = data($c/tns:name) and
                  data($p/tns:conferenceyear) = data($c/tns:year)
            return $students[tns:ssn = data($p/tns:ssn)]/data(tns:age))
order by $avgage descending
return 
<row>
<name>{$c/tns:name/text()}</name>
<year>{$c/tns:year/text()}</year>
<students>{$avgage}</students>
</row>
                       

