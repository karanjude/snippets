declare namespace tns = "http://www.example.org/student";

let  $students :=  doc("student.xml")//tns:student
let  $participations :=  doc("participation.xml")//tns:participation
let  $conferences :=  doc("conference.xml")//tns:conference
let $years := distinct-values($participations//tns:conferenceyear)

for $s in $students 
  for $yr in $years
let $totalfee := sum(for $p in $participations 
            where data($p/tns:ssn) = data($s/tns:ssn) and
                   data($p/tns:conferenceyear) = data($yr) 
            return number(substring-before(data($p/tns:regfee), '$')))
order by $totalfee descending , data($s/tns:ssn) ascending
return 
<row>
<ssn>{$s/tns:ssn/text()}</ssn>
<institution>{$s/tns:institution/text()}</institution>
<year>{$yr}</year>
<total-fee>{$totalfee}</total-fee>
</row>
                       

