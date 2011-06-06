declare namespace tns = "http://www.example.org/student";

for $student in doc("student.xml")/tns:Students/tns:student
let $emails := $student//tns:email
order by $student/tns:name/tns:lastname
return
<row>
<first-name>{$student/tns:name/tns:firstname/text()}</first-name>
<last-name>{$student/tns:name/tns:lastname/text()}</last-name>
<email>
{string-join($emails/text(), ",")}
</email>
</row>

