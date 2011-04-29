f = open("/home/jude/Data/study/judesnippets/database_systems/DBHomework4/src/hotel.txt")
hotel_string = '''
<tns:hotel>
    <tns:chainname>{chainname}</tns:chainname>
    <tns:branchname>{branchname}</tns:branchname>
    <tns:address>
      <tns:city>{city}</tns:city>
      <tns:zip>{zip}</tns:zip>
      <tns:state>{state}</tns:state>
      <tns:streetno>{streetno}</tns:streetno>
      <tns:streetname>{streetname}</tns:streetname>
    </tns:address>
    <tns:capacity>{capacity}</tns:capacity>
    <tns:latitude>{latitude}</tns:latitude>
    <tns:longitude>{longitude}</tns:longitude>
  </tns:hotel>'''

for l in f:
    p = l.split(",")
    print hotel_string.format(
        chainname = p[0],
        branchname = p[1],
        latitude = p[2],
        longitude = p[3],
        capacity = p[4],
        streetno = p[5],
        streetname = p[6],
        city = p[7],
        state = p[8],
        zip = p[9]
        )

f.close()
