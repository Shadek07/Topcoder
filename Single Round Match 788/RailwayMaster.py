# -*- coding: utf-8 -*-
import math,string,itertools,fractions,heapq,collections,re,array,bisect

class RailwayMaster:
    def maxProfit(self, N, M, K, a, b, v):
        edges = []

        p = [i for i in range(N) ]

        def findGroup(x):
            while p[x] != x:
                x = p[x]
            return x
        def mergeGroup(x,y):
            x = findGroup(x)
            y = findGroup(y)
            p[x] = y
        for i in range(M):
            edges.append((a[i], b[i], v[i]))
        edges.sort(key = lambda x: x[2])
        vis = [False]*M
        for i, (a,b,c) in enumerate(edges):
            g1 = findGroup(a)
            g2 = findGroup(b)
            if g1 != g2:
                mergeGroup(g1, g2)
                vis[i] = True
        i = M-1
        cnt = 0
        ans = 0
        while i>=0:
            if vis[i] == False:
                ans += edges[i][2]
                cnt += 1
                if cnt >= K:
                    break
            i -= 1
        return ans



        return 0

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

def do_test(N, M, K, a, b, v, __expected):
    startTime = time.time()
    instance = RailwayMaster()
    exception = None
    try:
        __result = instance.maxProfit(N, M, K, a, b, v);
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
    sys.stdout.write("RailwayMaster (250 Points)\n\n")

    passed = cases = 0
    case_set = set()
    for arg in sys.argv[1:]:
        case_set.add(int(arg))

    with open("RailwayMaster.sample", "r") as f:
        while True:
            label = f.readline()
            if not label.startswith("--"): break

            N = int(f.readline().rstrip())
            M = int(f.readline().rstrip())
            K = int(f.readline().rstrip())
            a = []
            for i in range(0, int(f.readline())):
                a.append(int(f.readline().rstrip()))
            a = tuple(a)
            b = []
            for i in range(0, int(f.readline())):
                b.append(int(f.readline().rstrip()))
            b = tuple(b)
            v = []
            for i in range(0, int(f.readline())):
                v.append(int(f.readline().rstrip()))
            v = tuple(v)
            f.readline()
            __answer = int(f.readline().rstrip())

            cases += 1
            if len(case_set) > 0 and (cases - 1) in case_set: continue
            sys.stdout.write("  Testcase #%d ... " % (cases - 1))
            passed += do_test(N, M, K, a, b, v, __answer)

    sys.stdout.write("\nPassed : %d / %d cases\n" % (passed, cases))

    T = time.time() - 1595635389
    PT, TT = (T / 60.0, 75.0)
    points = 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
    sys.stdout.write("Time   : %d minutes %d secs\n" % (int(T/60), T%60))
    sys.stdout.write("Score  : %.2f points\n" % points)

if __name__ == '__main__':
    run_tests()

# }}}
# CUT end
