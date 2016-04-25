#find sum of all perfect numbers within 10000
#A perfect number is any integer which is equal to the sum of its proper divisors (all its divisors except for itself)
def getSum():
	return sum(i for i in xrange(1,10001) if sum( j for j in xrange(1,i) if i%j==0 ) == i)

#output should be 8658
print getSum()