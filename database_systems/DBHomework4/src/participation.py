f = open("/home/jude/Data/study/judesnippets/database_systems/DBHomework4/src/participation.txt")
participation_string = '''
 <tns:participation>
    <tns:ssn>{ssn}</tns:ssn>
    <tns:conferencename>{conferencename}</tns:conferencename>
    <tns:conferenceyear>{year}</tns:conferenceyear>
    <tns:regfee>{regfee}</tns:regfee>
    <tns:regno>{regno}</tns:regno>
  </tns:participation>
'''

for l in f:
    p = l.split(",")
    print participation_string.format(
        ssn = p[0],
        conferencename = p[1],
        year = p[2],
        regfee = p[4],
        regno = p[3]
        )

f.close()
