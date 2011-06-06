declare namespace tns = "http://www.example.org/student";

let  $students :=  doc("student.xml")//tns:student
let  $participations :=  doc("participation.xml")//tns:participation
let  $conferences :=  doc("conference.xml")//tns:conference

for $c in $conferences
let $totalearned := sum(for $p in $participations 
            where data($p/tns:conferencename) = data($c/tns:name) and
                  data($p/tns:conferenceyear) = data($c/tns:year)
            return number(substring-before(data($p/tns:regfee), '$')))
return 
<row>
<chair-names>{string-join($c/tns:chair/text(), ",")}</chair-names>
<name>{$c/tns:name/text()}</name>
<year>{$c/tns:year/text()}</year>
<total-income>{$totalearned}</total-income>
</row>
                       

