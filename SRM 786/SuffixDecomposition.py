# -*- coding: utf-8 -*-
import math,string,itertools,fractions,heapq,collections,re,array,bisect

class SuffixDecomposition:
    def findTotalFun(self, P, A0, X, Y, B0, X1, Y1, N):
        print "abc"
        A = [-1]*N
        B = [-1]*N
        S = [-1]*N
        A[0] = A0
        B[0] = B0
        ps = len(P)
        for i in range(1,N):
            A[i] = (A[i-1]*X + Y)%1812447359
            B[i] = (B[i-1]*X1 + Y1)%1812447359
        for i in range(0,N):
            if i < ps:
                S[i] = P[i]
            else:
                S[i] = max(A[i], B[i])
        st = []
        i = N-1
        #print S
        suffixMin = float('inf')
        ans = 0
        while i >=0:
            while len(st) > 0 and S[i] >= st[-1]:
                st.pop()
            ans += len(st)+1
            suffixMin = min(suffixMin, S[i])
            st.append(suffixMin)
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

def do_test(P, A0, X, Y, B0, X1, Y1, N, __expected):
    startTime = time.time()
    instance = SuffixDecomposition()
    exception = None
    try:
        __result = instance.findTotalFun(P, A0, X, Y, B0, X1, Y1, N);
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
    sys.stdout.write("SuffixDecomposition (1000 Points)\n\n")

    passed = cases = 0
    case_set = set()
    for arg in sys.argv[1:]:
        case_set.add(int(arg))

    with open("SuffixDecomposition.sample", "r") as f:
        while True:
            label = f.readline()
            if not label.startswith("--"): break

            P = []
            for i in range(0, int(f.readline())):
                P.append(int(f.readline().rstrip()))
            P = tuple(P)
            A0 = int(f.readline().rstrip())
            X = int(f.readline().rstrip())
            Y = int(f.readline().rstrip())
            B0 = int(f.readline().rstrip())
            X1 = int(f.readline().rstrip())
            Y1 = int(f.readline().rstrip())
            N = int(f.readline().rstrip())
            f.readline()
            __answer = int(f.readline().rstrip())

            cases += 1
            if len(case_set) > 0 and (cases - 1) in case_set: continue
            sys.stdout.write("  Testcase #%d ... " % (cases - 1))
            passed += do_test(P, A0, X, Y, B0, X1, Y1, N, __answer)

    sys.stdout.write("\nPassed : %d / %d cases\n" % (passed, cases))

    T = time.time() - 1589598011
    PT, TT = (T / 60.0, 75.0)
    points = 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
    sys.stdout.write("Time   : %d minutes %d secs\n" % (int(T/60), T%60))
    sys.stdout.write("Score  : %.2f points\n" % points)

if __name__ == '__main__':
    run_tests()

# }}}
# CUT end
