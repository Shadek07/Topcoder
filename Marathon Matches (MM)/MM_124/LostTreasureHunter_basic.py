import sys
from typing import List

class LostTreasureHunter :
    def init(self, treasureValue : int, stepCost : int, numChambers : int, maxTreasure : int) :
        self.treasureValue = treasureValue 
        self.stepCost = stepCost 
        self.numChambers = numChambers 
        self.maxTreasure = maxTreasure
        self.numStep = 0

    def findSolution(self, treasureCount : int, pathCount : int, time : str) -> List[int] :
        if self.numStep >= 1 :
            return [-1,0]

        self.numStep += 1

        return [min(treasureCount,maxTreasure), pathCount - 1]


treasureValue = int(input())
stepCost = int(input())
numChambers = int(input())
maxTreasure = int(input())

o = LostTreasureHunter()
o.init(treasureValue,stepCost,numChambers,maxTreasure)

while True :
    treasureCount = int(input())
    pathCount = int(input())
    time = input()

    res = o.findSolution(treasureCount,pathCount,time)

    print(res[0])
    if(res[0]>-1) :
        print(res[1])
    sys.stdout.flush()


