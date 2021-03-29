# -*- coding: utf-8 -*-
import math,string,itertools,fractions,heapq,collections,re,array,bisect

class SecondDiameters:
    def getd(self, x1, y1, x2, y2):
        return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)
    def getSecondDiameters(self, X, Y):
        lst = []
        n = len(X)
        for i in range(n):
            for j in range(n):
                lst.append((self.getd(X[i], Y[i], X[j], Y[j]), i, j))
        lst.sort()
        ans = 0
        if n == 3:
            return 0
        for i in range(n):
            cnt = 0
            last_dist = float('inf')
            ind = len(lst)-1
            while True and ind >= 0:
                d, x, y = lst[ind]
                if x == i or y == i: 
                    ind-=1
                    continue
                elif cnt == 1 and last_dist != d: 
                    ans += d
                    break
                if cnt == 0:
                    cnt = 1
                    last_dist = d
                    ind-=1
                    continue
                ind -= 1
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

def do_test(X, Y, __expected):
    startTime = time.time()
    instance = SecondDiameters()
    exception = None
    try:
        __result = instance.getSecondDiameters(X, Y);
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
    sys.stdout.write("SecondDiameters (1000 Points)\n\n")

    passed = cases = 0
    case_set = set()
    for arg in sys.argv[1:]:
        case_set.add(int(arg))

    with open("SecondDiameters.sample", "r") as f:
        while True:
            label = f.readline()
            if not label.startswith("--"): break

            X = []
            for i in range(0, int(f.readline())):
                X.append(int(f.readline().rstrip()))
            X = tuple(X)
            Y = []
            for i in range(0, int(f.readline())):
                Y.append(int(f.readline().rstrip()))
            Y = tuple(Y)
            f.readline()
            __answer = int(f.readline().rstrip())

            cases += 1
            if len(case_set) > 0 and (cases - 1) in case_set: continue
            sys.stdout.write("  Testcase #%d ... " % (cases - 1))
            passed += do_test(X, Y, __answer)

    sys.stdout.write("\nPassed : %d / %d cases\n" % (passed, cases))

    T = time.time() - 1614170454
    PT, TT = (T / 60.0, 75.0)
    points = 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
    sys.stdout.write("Time   : %d minutes %d secs\n" % (int(T/60), T%60))
    sys.stdout.write("Score  : %.2f points\n" % points)

if __name__ == '__main__':
    run_tests()

# }}}
# CUT end
