# -*- coding: utf-8 -*-
import math,string,itertools,fractions,heapq,collections,re,array,bisect

class TwoRobots:
    def move(self, plan):	
	n = len(plan)
	m = len(plan[0])
        dist = dict()
	for i in range(n):
	    for j in range(m):
		if plan[i][j] == 'A':
		    xA, yA = i,j
		if plan[i][j] == 'B':
		    xB, yB = i,j
		if plan[i][j] == 'a':
		    xa, ya = i,j
		if plan[i][j] == 'b':
		    xb, yb = i,j
	q = [(xA,yA,xB,yB)]
	dist[(xA, yA, xB, yB)] = 0
	dir = [(0,1),(-1,0),(0,-1),(1,0)]
	cnt = 0
	while q:
	    xA, yA, xB, yB = q[0]
            #print xA, yA, xB, yB
	    if xA == xa and yA == ya and xB == xb and yB == yb:
		return dist[(xA,yA,xB,yB)]
	    d = dist[(xA,yA,xB,yB)]
	    dir = [(0,1),(-1,0),(0,-1),(1,0)]
	    cnt += 1
	    #if cnt%1000 == 0:
	    #print xA, yA, xB, yB, d
	    q.pop(0)
	    for dx, dy in dir:
		newxA, newyA = xA + dx, yA + dy
		if newxA >= 0 and newyA >= 0 and newxA < n and newyA < m and plan[newxA][newyA] != '#':
		    for d1, d2 in dir:
			newxB, newyB = xB + d1, yB + d2
                        			
		        if newxB >= 0 and newyB >= 0 and newxB < n and newyB < m and plan[newxB][newyB] != '#':
			    if newxA == newxB and newyA == newyB:
				continue
			    if newxA == xB and newyA == yB and newxB == xA and newyB == yA:
				continue
			    
		            if (newxA,newyA,newxB,newyB) not in dist:
				dist[(newxA,newyA,newxB,newyB)] = d+1
				q.append((newxA, newyA, newxB, newyB))
        return -1



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

def do_test(plan, __expected):
    startTime = time.time()
    instance = TwoRobots()
    exception = None
    try:
        __result = instance.move(plan);
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
    sys.stdout.write("TwoRobots (1000 Points)\n\n")

    passed = cases = 0
    case_set = set()
    for arg in sys.argv[1:]:
        case_set.add(int(arg))

    with open("TwoRobots.sample", "r") as f:
        while True:
            label = f.readline()
            if not label.startswith("--"): break

            plan = []
            for i in range(0, int(f.readline())):
                plan.append(f.readline().rstrip())
            plan = tuple(plan)
            f.readline()
            __answer = int(f.readline().rstrip())

            cases += 1
            if len(case_set) > 0 and (cases - 1) in case_set: continue
            sys.stdout.write("  Testcase #%d ... " % (cases - 1))
            passed += do_test(plan, __answer)

    sys.stdout.write("\nPassed : %d / %d cases\n" % (passed, cases))

    T = time.time() - 1603485148
    PT, TT = (T / 60.0, 75.0)
    points = 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))
    sys.stdout.write("Time   : %d minutes %d secs\n" % (int(T/60), T%60))
    sys.stdout.write("Score  : %.2f points\n" % points)

if __name__ == '__main__':
    run_tests()

# }}}
# CUT end
