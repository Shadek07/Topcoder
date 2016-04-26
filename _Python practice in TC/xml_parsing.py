import urllib
import xml.etree.ElementTree as ET
import json

#Sample data: http://python-data.dr-chuck.net/comments_42.xml (Sum=2553)
#Actual data: http://python-data.dr-chuck.net/comments_266009.xml (Sum = 2273)

address = raw_input('Enter url: ')
uh = urllib.urlopen(address)
data = uh.read()
#tree = ET.fromstring(data)
print data
data = ET.fromstring(data)
comments = data.find('comments')
print comments
sum=0
for c in comments:
	sum += int(c.find('count').text)
print sum

"""
<commentinfo>
  <note>This file contains the sample data for testing</note>

  <comments>
    <comment>
       <name>Romina</name>
       <count>97</count>
    </comment>
    <comment>
       <name>Laurie</name>
       <count>97</count>
    </comment>
    ...
    
    
    <comment>
       <name>Inika</name>
       <count>2</count>
    </comment>
  </comments>
</commentinfo>

"""
