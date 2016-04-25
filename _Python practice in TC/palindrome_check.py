
def isPalindrome(str):
	n = len(str)//2
	len1 = len(str)
	return not any(str[i:i+1] != str[len1-1-i:len1-i] for i in range(n))


print isPalindrome("ACBBCA")
#check if a string is palindrome