import sys
from typing import List
import random
#random.seed(10)
class LostTreasureHunter :
    def init(self, treasureValue : int, stepCost : int, numChambers : int, maxTreasure : int) :
        self.treasureValue = treasureValue 
        self.stepCost = stepCost 
        self.numChambers = numChambers 
        self.maxTreasure = maxTreasure
        self.numStep = 0
        self.edges = [ None for i in range(self.numChambers)] 
        self.adj = dict()
        self.treasures = [-1 for i in range(self.numChambers)] #treasure count in each chamber currently
        self.pathCounts = [-1 for i in range(self.numChambers)]
        self.chamberCnt = 0
        self.total_treasures = 0
        self.history = []
        self.cur = -1 
        self.treasureTaken = 0
        self.exit = -1
        self.maxPickup = self.maxTreasure
        self.clist = []  #chamber list
        self.last_collect = -1
        self.prev_val = -1
        self.prev_t =-1 
        

    def addChamber(self, treasureCount: int, pathCount: int):
        self.treasures[self.chamberCnt] = treasureCount
        self.pathCounts[self.chamberCnt] = pathCount
        if self.cur >-1:
            self.adj[self.chamberCnt] = [self.cur]
            self.adj[self.cur].append(self.chamberCnt)
            self.edges[self.cur][self.exit] = self.chamberCnt
            self.edges[self.chamberCnt][0] = self.cur #random.randint(0, pathCount-1)
        else:
            self.adj[0] = []
        self.cur = self.chamberCnt
        self.chamberCnt+=1

    def firstUnused(self):
        for i in range(0, self.numChambers):
            if i not in self.clist:
                self.clist.append(i)
                return i
        return 105

    def addEdges(self, chamber: int, t: int, p: int):
        if self.edges[chamber] == None:
            self.edges[chamber] = [105 for j in range(p)]
        else:
            return
        
        so_far_neighbors = [] if chamber not in self.adj else list(self.adj[chamber])
        new_neighbors = []
        for i in range(100):
            new_node = self.firstUnused()
            if new_node not in self.adj:
                self.adj[new_node]= set([chamber])
            else:
                self.adj[new_node].add(chamber)
            new_neighbors.append(new_node)                
        so_far_neighbors.extend(new_neighbors)                
        so_far_neighbors = list(set(so_far_neighbors))
        assert len(so_far_neighbors) == p,"lists not equal"+str(len(so_far_neighbors)) + " " + str(p)
        for i in range(p):
            self.edges[chamber][i] = so_far_neighbors[i]
        
    def collectTreasures(self, chamber: int):
        '''if self.maxPickup == 0:
            print(-1)
            self.treasureTaken = -1
            return'''
        t = min(self.treasures[chamber], self.maxTreasure)
        
        self.total_treasures += t
        self.treasures[chamber] -= t
        #self.maxPickup = min(self.maxPickup, self.treasures[chamber])
        if t>=0:
            print(t)
            self.treasureTaken = t
        else:
            print(-1)
            self.treasureTaken = -1

        
    def addToHistory(self, chamber: int):
        self.history.append(chamber)

    def printPath(self, ind: int):
        if self.treasureTaken != -1:
            self.exit = ind
            print(ind)
        sys.stdout.flush()

    def processChamber(self, t: int, p: int):
        self.numStep += 1
        take = min(t, self.maxTreasure)     
        self.total_treasures += take
        new_value = self.finalvalue()
        if new_value < self.prev_val*0.90:
            print(-1)
            sys.stdout.flush()
        print(take)
        if (self.last_collect > take) or ((self.prev_t > t-take) and self.prev_val >= 0):
            print(-1)
        else:
            print(random.randint(0,p-1))
        self.last_collect = take
        self.prev_t = t - take
        self.prev_val = new_value
        sys.stdout.flush()



        '''existing = []
        if self.cur == -1:
            self.treasures[0] = t
            self.pathCounts[0] = p 
            #self.addChamber(t,p)
            self.clist.append(0)
            self.addEdges(0, t, p)
            self.cur = 0
            self.collectTreasures(self.cur)
            self.printPath(random.randint(0, self.pathCounts[self.cur]-1))
            return

        self.cur = self.edges[self.cur][self.exit]
        self.addEdges(self.cur, t, p)
        if self.treasures[self.cur] == -1:
            self.treasures[self.cur] = t
            self.pathCounts[self.cur] = p
        elif self.treasures[self.cur] != t or self.pathCounts[self.cur] != p:
            print(-1)
            sys.stdout.flush()
        self.collectTreasures(self.cur)
        self.printPath(random.randint(0, self.pathCounts[self.cur]-1))'''
        '''else:
            for k, v in self.adj.items():
                if self.cur != k and self.treasures[k] == t and self.pathCounts[k] == p:
                    existing.append(k)
            if len(existing) == 0:
                if self.chamberCnt < self.numChambers:         
                    self.addChamber(t, p)
                    self.collectTreasures(self.cur)
                    self.printPath(random.randint(0, self.pathCounts[self.cur]-1))
                else:
                    self.treasureTaken = -1
                    print(-1)
                    sys.stdout.flush()
            else:
                candidates = []
                for k in existing:
                    candidates.append((-self.treasures[k],-(self.pathCounts[k]-len(self.adj[k])), k))
                candidates = sorted(candidates)
                best_node = None
                for tp in candidates:
                    if tp[1] < 0:
                        best_node = tp[2]
                        break
                pathindex = None
                if len(self.adj[self.cur]) == self.pathCounts[self.cur]:  #no vacant edge of current chamber
                    print(-1)
                    sys.stdout.flush()
                    return
                if best_node == None:
                    print(-1)
                    sys.stdout.flush()
                    return
                nextindex = self.edges[best_node].index(-1)
                self.createEdge(self.cur, self.exit, best_node, nextindex) 
                self.cur = best_node
                self.collectTreasures(self.cur)
                self.printPath(nextindex)'''

    def createEdge(self, a: int, ind1: int, b: int, ind2: int):
        if b not in self.adj[a]:
            self.adj[a].append(b)
            self.edges[a][ind1] = b
        if a not in self.adj[b]:
            self.adj[b].append(a)
            self.edges[b][ind2] = a

    def finalvalue(self):
        return self.total_treasures*self.treasureValue - self.stepCost*self.numStep

    def findSolution(self, treasureCount : int, pathCount : int, time : str) :
        self.processChamber(treasureCount, pathCount)

treasureValue = int(input())
stepCost = int(input())
numChambers = int(input())
maxTreasure = int(input())

hunter = LostTreasureHunter()
hunter.init(treasureValue,stepCost,numChambers,maxTreasure)
curvalue = 0
#print('here')
while hunter.numStep < 1000:
    treasureCount = int(input())
    pathCount = int(input())
    time = input()

    hunter.findSolution(treasureCount,pathCount,time)
    nextvalue = hunter.finalvalue()
    '''if nextvalue < curvalue*0.95:
        break'''    
    curvalue = nextvalue
    #print('curvalue', curvalue)


