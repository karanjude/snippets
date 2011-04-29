f = open("/home/jude/Data/study/judesnippets/database_systems/DBHomework4/src/students.txt")

class Student:
    def __init__(self, ssn, first_name, last_name, age,institution_name):
        self.ssn = ssn
        self.first_name = first_name
        self.last_name = last_name
        self.age = age
        self.institution_name = institution_name
        self.emails = []
        
    def add_email(self, e):
        self.emails.append(e)

    def email_string(self):
        return "\n".join(["<tns:email>%s</tns:email>" % (x) for x in self.emails])

    def __str__(self):
        student_string = '''
<tns:student>
    <tns:ssn>{ssn}</tns:ssn>
    <tns:institution>{institution}</tns:institution>
    <tns:age>{age}</tns:age>
   {e}
    <tns:name>
      <tns:firstname>{firstname}</tns:firstname>
      <tns:lastname>{lastname}</tns:lastname>
    </tns:name>
  </tns:student>
'''
        email_s = self.email_string()
        return student_string.format(
            ssn = self.ssn,
            firstname = self.first_name,
            lastname = self.last_name,
            age = self.age,
            institution = self.institution_name,
            e = email_s
            )

students = {}

for l in f:
    p = l.split(",")
    s = Student(p[0],p[1],p[2],p[3],p[4].strip())
    students[p[0]] = s
f.close()

f = open("/home/jude/Data/study/judesnippets/database_systems/DBHomework4/src/emails.txt")
for l in f:
    p = l.split(",")
    students[p[0]].add_email(p[1].strip())

f.close()

for k,v in students.iteritems():
    print str(v)
