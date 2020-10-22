# -*- coding: utf-8 -*-
import math,string,itertools,fractions,heapq,collections,re,array,bisect

class AqaAsadiPlays:
    def getMin(self, A):
	prefix = [-1]*len(A)
	A = sorted(A)
	A = A[::-1]
	#print A
	prefix[0] = A[0]
	def gcd(a,b):
	    if b == 0:
	        return a
	    return gcd(b, a%b)
	for i in range(1,len(A)):
	    prefix[i] = gcd(prefix[i-1], A[i])
        if len(A) == 1:
	    return -1
        ans = -1
	i = len(A)-2
	while i >=0:
	    if prefix[i] > A[i+1]:
		return i+1
	    i-=1
	    
        return ans

# CUT begin
# TEST CODE FOR PYTHON {{{
import sys, time, math

def tc_equal(expected, received):
    try:
        _t = type(expected)
        received = _t(received)
        if _t == list or _t == tuple:
            if len(expected) != len(received): return False
            return all(tc_equal(e, r) for (e, r) in zip(expected, received))
        elif _t == float:
            eps = 1e-9
            d = abs(received - expected)
            return not math.isnan(received) and not math.isnan(expected) and d <= eps * max(1.0, abs(expected))
        else:
            return expected == received
    except:
        return False

def pretty_str(x):
    if type(x) == str:
        return '"%s"' % x
    elif type(x) == tuple:
        return '(%s)' % (','.join( (pretty_str(y) for y in x) ) )
    else:
        return str(x)

def do_test(A, __expected):
    startTime = time.time()
    instance = AqaAsadiPlays()
    exception = None
    try:
        __result = instance.getMin(A);
    except:
        import traceback
        exception = traceback.format_exc()
    elapsed = time.time() - startTime   # in sec

    if exception is not None:
        sys.stdout.write("RUNTIME ERROR: \n")
        sys.stdout.write(exception + "\n")
        return 0

    if tc_equal(__expected, __result):
        sys.stdout.write("PASSED! " + ("(%.3f seconds)" % elapsed) + "\n")
        return 1
    else:
        sys.stdout.write("FAILED! " + ("(%.3f seconds)" % elapsed) + "\n")
        sys.stdout.write("           Expected: " + pretty_str(__expected) + "\n")
        sys.stdout.write("           Received: " + pretty_str(__result) + "\n")
        return 0

def run_tests():
    sys.stdout.write("AqaAsadiPlays (500 Points)\n\n")

    passed = cases = 0
    case_set = set()
    for arg in sys.argv[1:]:
        case_set.add(int(arg))

    with open("AqaAsadiPlays.sample", "r") as f:
        while True:
            label = f.readline()
            if not label.startswith("--"): break

            A = []
            for i in range(0, int(f.readline())):
                A.append(int(f.readline().rstrip()))
            A = tuple(A)
            f.readline()
            __answer = int(f.readline().rstrip())

            cases += 1
            if len(case_set) > 0 and (cases - 1) in case_set: continue
            sys.stdout.write("  Testcase #%d ... " % (cases - 1))
            passed += do_test(A, __answer)

    sys.stdout.write("\nPassed : %d / %d cases\n" % (passed, cases))

    T = time.time() - 1592791936
    PT, TT = (T / 60.0, 75.0)
    points = 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
    sys.stdout.write("Time   : %d minutes %d secs\n" % (int(T/60), T%60))
    sys.stdout.write("Score  : %.2f points\n" % points)

if __name__ == '__main__':
    run_tests()

# }}}
# CUT end
