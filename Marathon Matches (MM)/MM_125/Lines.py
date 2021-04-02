import sys
from collections import defaultdict
from collections import Counter
import copy

class LineGame:
    def __init__(self, N, C):
        self.N = N
        self.cells = N*N
        self.C = C
        self.nextBalls = [0] * 3
        self.dist = [ [float('inf') for j in range(self.N)] for i in range(self.N)]

        self.dr = [0,1,0,-1]
        self.dc = [-1,0,1,0]    
        self.empty_cells_around = [ [0 for j in range(N)] for i in range(N)]
        self.segment_scores = None
        self.powers = dict()
        for i in range(-100,100):
            self.powers[i] = pow(self.N,i)
        self.diagonal_percentage = 1
        self.elapsed = None
        self.move_num = 0
        self.ballcnt = 0
        self.access= [ [ [ 0 for c in range(self.C+1)] for j in range(self.N)] for i in range(self.N)]
                    
    def getStreak(self, a, b, dx, dy):
        colorcnt, color = 0, 0
        cnt = 0
        while cnt < self.N:
            a, b = a+dx, b+dy
            if a<0 or a>=self.N or b<0 or b>=self.N:
                break
            if color != 0 and self.grid[a][b] != 0 and  color != self.grid[a][b]:
                break
            if color == 0 and self.grid[a][b] == 0:
                return -9999, 0
            if self.grid[a][b] != 0:
                color = self.grid[a][b]
                colorcnt += 1
            cnt += 1                
        return colorcnt, color
            
    def getInput(self):
        self.grid = [[0 for j in range(self.N)] for i in range(self.N)]
        self.balls = []
        self.empty_slots = []
        for i in range(self.N):
            for j in range(self.N):
                self.grid[i][j] = int(input())
                if self.grid[i][j] == 0:
                    self.empty_slots.append((i,j))
                else:
                    self.balls.append((i,j))

        for k in range(3): 
            self.nextBalls[k] = int(input())	
        self.elapsed = int(input())

    def isFarther(self, ex, ey, a, b):
        if ex-a == 0 or ey-b == 0:
            return abs(ex-a)+abs(ey-b)>4
        elif abs(ex-a) == abs(ey-b):
            return abs(ex-a) > 4
        return True 

    def update_dominant(self, maxcount, color, cnt, cl):
        if cnt > maxcount:
            return (cnt, cl)
        else:
            return (maxcount, color)

    def componentVisit(self, component_num, a, b):
        self.component[component_num].add((a,b))
        self.cell_to_component[(a,b)] = component_num
        for k in range(4):
            x,y = a+self.dr[k], b+self.dc[k]
            if x>=0 and x<self.N and y>=0 and y<self.N and self.grid[x][y] == 0 and ((x,y) not in self.component[component_num]):
                self.componentVisit(component_num, x,y)
    

    def isConnected(self, a, b, c, d):
        if self.grid[a][b] == 0:
            return False
        if (c,d) not in self.cell_to_component:
            return False

        for k in range(4):
            x, y = a+self.dr[k], b+self.dc[k]
            if x>=0 and x<self.N and y>=0 and y<self.N and self.grid[x][y]==0:
                if self.cell_to_component[(x,y)] == self.cell_to_component[(c,d)]:
                    return True
        return False
    
    def makeConnected(self):
        self.component = defaultdict(set)
        self.cell_to_component = dict()
        self.visited = dict()         
        self.component_cnt = 0
        for i in range(self.N):
            for j in range(self.N):
                if self.grid[i][j] == 0 and (i,j) not in self.visited:
                    self.componentVisit(self.component_cnt, i,j)
                    for a, b in self.component[self.component_cnt]:
                        self.visited[(a,b)] = 1
                    self.component_cnt+=1
        self.same = defaultdict(list)            
        for i in range(self.N):
            for j in range(self.N):
                if self.grid[i][j] != 0:
                    self.same[self.grid[i][j]].append((i,j))
        
        self.access= [ [ [ set() for c in range(self.C+1)] for j in range(self.N)] for i in range(self.N)] #number of colored cells that are accessible from (i,j)
        for i in range(self.N):
            for j in range(self.N):
                if self.grid[i][j] != 0:
                    q = [(i,j)]
                    cell_color = self.grid[i][j]
                    visited = [ [False for j1 in range(self.N)] for i1 in range(self.N)]
                    visited[i][j] = True
                    while q:
                        a,b = q[0]
                        q.pop(0)
                        for k in range(4):
                            x,y = a+self.dr[k],b+self.dc[k]
                            if x>=0 and x<self.N and y>=0 and y<self.N:
                                if self.grid[x][y] == 0 and visited[x][y] == False:
                                    if self.isFarther(i,j,x,y):
                                        self.access[x][y][cell_color].add((i,j))
                                    q.append((x,y))
                                    visited[x][y] = True
                                    
#(N-4)*N
    def getHorizontalSegment(self, i,j):
        return (self.N-4)*i+j

    def getVerticalSegment(self, i,j):
        return (self.N-4)*self.N + (self.N-4)*j+i

    def isAlone(self,a,b):
        dx = [  -1, 0, 0, 1]
        dy = [  0, -1, 1, 0 ]
        for k in range(4):
            x,y=a+dx[k],b+dy[k]
            if x>=0 and x<self.N and y>=0 and y<self.N and self.grid[a][b] == self.grid[x][y]:
                return False
        return True

    def isBridgeCell(self,a,b):
        set1 = set()
        set2 = set()
        for dx,dy in [(0,1),(0,-1)]:
            x,y=a+dx,b+dy
            if x>=0 and x<self.N and y>=0 and y<self.N:
                set1.add(self.grid[x][y])               
        for dx,dy in [(-1,0),(1,0)]:
            x,y=a+dx,b+dy
            if x>=0 and x<self.N and y>=0 and y<self.N:
                set2.add(self.grid[x][y])               
        set1 = list(set1)
        set2 = list(set2)
        
        return len(set1) == 2 and len(set2) == 1

    def getSegmentScore(self, a, b, dx, dy, movex, movey):
        cnt = 0
        freq = defaultdict(lambda:0)
        empties = []
        while cnt < 5:
            if self.grid[a][b] != 0:
                freq[self.grid[a][b]]+=1
            else:
                empties.append((a,b))
            cnt += 1                
            a, b = a+dx, b+dy
        arr = []
        max_cnt = -1
        dominant_color =0
        for k,v in freq.items():
            arr.append(v)
            if v>max_cnt:
                max_cnt = v
                dominant_color = k
        if len(arr)>0:
            arr = sorted(arr)[::-1]
            fillup_score = 0
            taken = set()
            for ex,ey in empties:            
                for px, py in self.access[ex][ey][dominant_color]:
                    if (px==movex and py == movey):
                        continue
                    if (px,py) not in taken :
                        taken.add((px,py))
                        break
            
            if len(empties)>0:
                fillup_score = self.powers[int(len(taken)/ len(empties)+0.5)]
            #+ self.N*(len(self.same[dominant_color])/len(self.balls)) 2 red, 3 empties
            return self.powers[arr[0]-4*sum(arr[1:])] + fillup_score #+ nextball_score*(1.0/self.component_cnt) # + self.powers[accessible_dominant-(5-sum(arr))]
        return 0      


    def boardEvaluate(self, sx, sy, dx, dy):
        self.grid[sx][sy], self.grid[dx][dy] = self.grid[dx][dy], self.grid[sx][sy]
        score = 0 

        for x, y in [(sx,sy),(dx,dy)]:
            if x==dx and y==dy:
                movex, movey = x,y
            else:
                movex, movey = -1,-1
            for i in range(y-4,y+1):
                if i<0:
                    continue
                if i+4>=self.N:
                    break
                score += self.getSegmentScore(x,i,0,1, movex, movey)
            for i in range(x-4,x+1):
                if i<0:
                    continue
                if i+4>=self.N:
                    break
                score += self.getSegmentScore(i,y,1,0,movex,movey)
            #forward diagonal score adjustment
            for k in range(0,5):
                a,b = x-k, y+k
                if a<0 or b>=self.N:
                    break
                if a+4>=self.N or b-4<0:
                    continue
                score += self.getSegmentScore(a,b,1,-1, movex, movey)
            #backward \ diagonal score adjustment
            for k in range(0,5):
                a,b = x-k,y-k
                if a<0 or b<0:
                    break
                if a+4>=self.N or b+4>= self.N:
                    continue
                score += self.getSegmentScore(a,b,1,1, movex, movey)
        self.grid[sx][sy], self.grid[dx][dy] = self.grid[dx][dy], self.grid[sx][sy]
        return score

    def makeMove(self):
        self.makeConnected()
        arr = []
        periods = [0,0,0,0,0,0,0,15,10,7,7,7]
#if self.elapsed > 9900 or (self.move_num>0 and self.move_num%periods[self.N] == 0):
        if self.elapsed > 9800:
            for _,a,b,x,y in self.arr:
                if self.isConnected(a,b,x,y):
                    return str(a) + " "+str(b)+" "+str(x)+" "+str(y)

        for a,b  in self.balls: 
            for x,y in self.empty_slots:
                if self.isConnected(a, b, x, y): 
                    arr.append((self.boardEvaluate(a,b,x,y),a,b,x,y))
        arr = sorted(arr, key=lambda x:(-x[0]))                    
        self.arr = arr
        return str(arr[0][1]) + " "+str(arr[0][2])+" "+str(arr[0][3])+" "+str(arr[0][4])


N = int(input())
C = int(input())

game = LineGame(N,C)
for i in range(1000):
    game.getInput()
    move=game.makeMove()
    print(move)
    game.move_num += 1
    sys.stdout.flush()

