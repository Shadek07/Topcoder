import urllib
import xml.etree.ElementTree as ET
import json

#url:  http://python-data.dr-chuck.net/comments_42.json,   output: 2553
#or  http://python-data.dr-chuck.net/comments_266013.json,  output: 2726

address = raw_input('Enter location: ')
uh = urllib.urlopen(address)
data = uh.read()
data = json.loads(data)
comments = data['comments']
cnt=0
for c in comments:
	cnt = cnt + c['count']
print cnt

#sum of count values in 'comments' array
"""
{
  comments: [
    {
      name: "Matthias"
      count: 97
    },
    {
      name: "Geomer"
      count: 97
    }
    ...
  ]
}
"""