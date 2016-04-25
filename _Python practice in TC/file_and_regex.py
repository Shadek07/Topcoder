import re

#open a file in current directory and print sum of all integer numbers that is present in the file
#file may contain any characters
#for regex_sum.txt file, output should be 541892
print sum( [ int(x) for x in re.findall('[0-9]+',open("regex_sum.txt").read()) ] )
