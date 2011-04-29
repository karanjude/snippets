f = open("/home/jude/Data/study/judesnippets/database_systems/DBHomework4/src/conference.txt")
participation_string = '''
 <tns:conference>
    <tns:name>{name}</tns:name>
    <tns:year>{year}</tns:year>
    {chair}
    <tns:topic>{topic}</tns:topic>
    <tns:city>{city}</tns:city>
    <tns:country>{country}</tns:country>
    <tns:hotelchainname>{hotelchainname}</tns:hotelchainname>
    <tns:hotelbranchname>{hotelbranchname}</tns:hotelbranchname>
  </tns:conference>
'''

for l in f:
    p = l.split(";")
    print participation_string.format(
    name = p[0],
    year = p[1],
    chair = "\n".join( ["<tns:chair>%s</tns:chair>" % (x) for x in p[3].split(",")]),
    topic = p[2],
    city = p[4],
    country = p[5],
    hotelchainname = p[6], 
    hotelbranchname = p[7]
        )

f.close()
