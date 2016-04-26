
import urllib
from bs4 import BeautifulSoup

#url: http://python-data.dr-chuck.net/known_by_Cuillin.html
url = raw_input('Enter url: ')
count = input('Enter count: ')
position = input('Enter position: ')


while count > 0 :
	html = urllib.urlopen(url).read()
	soup = BeautifulSoup(html)
	tags = soup('a')
	#get anchor at (position-1)'th position
	target = tags[position-1]
	print 'Attrs: ', target.attrs
	#get new url from href attribute
	url = target.attrs.get("href",None)
	print url
	count= count-1

