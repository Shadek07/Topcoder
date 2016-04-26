
import urllib
from bs4 import BeautifulSoup

url = raw_input('Enter - ')
html = urllib.urlopen(url).read()

soup = BeautifulSoup(html)

# Retrieve all of the span tags
tags = soup('span')
sum=0
for tag in tags:
    # Look at the parts of a tag
    print 'TAG:',tag
    print 'Contents:',tag.contents[0]
    sum += int(tag.contents[0])
    print 'Attrs:',tag.attrs

print sum
