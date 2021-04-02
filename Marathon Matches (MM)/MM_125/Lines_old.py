import sys
from collections import defaultdict

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


    def find_emptycells_around(self):
        self.empty_cells_around = [ [0 for j in range(N)] for i in range(N)]
        for i in range(self.N):
            for j in range(self.N):
                visit = dict()
                q = [(i,j)]
                while q:
                    a, b = q[0]
                    q.pop(0)
                    visit[(a,b)] = 1
                    for k in range(4):
                        x, y =a+self.dr[k], b+self.dc[k]
                        if x>=0 and x<self.N and y>= 0 and y<self.N:
                            if self.grid[x][y] == 0 and (x,y) not in visit:
                                visit[(x,y)]=  1
                                q.append((x,y))
                self.empty_cells_around[i][j] = len(visit)
                    

    def runFloydWarshall(self):
        self.dist = [ [float('inf') for j in range(self.cells)] for i in range(self.cells)]
        for i in range(self.N):
            for j in range(self.N):
                for k in range(4):
                    x, y = i+self.dr[k], j+self.dc[k]
                    if x>= 0 and x<self.N and y>=0 and y < self.N:
                        if self.grid[i][j] != 0 and self.grid[x][y] == 0:
                            self.dist[i*self.N+j][x*self.N+y] = 1
                            self.dist[x*self.N+y] [i*self.N+j]= 1
                        if self.grid[i][j] == 0 and self.grid[x][y] != 0:
                            self.dist[i*self.N+j][x*self.N+y] = 1
                            self.dist[x*self.N+y] [i*self.N+j]= 1
        for k in range(self.cells):
            for i in range(self.cells):
                for j in range(self.cells):
                    if k== i or k==j or i==j:
                        continue
                    i1, i2 = i//self.N, int(i%self.N)
                    j1, j2 = j//self.N, int(j%self.N)
                    k1, k2 = k//self.N, int(k%self.N)
                    if self.dist[i][k] == float('inf') or self.dist[k][j] == float('inf'):
                        continue

                    if self.grid[i1][i2] != 0 and self.grid[j1][j2] != 0:
                        continue
                    if self.grid[i1][i2] == 0 and self.grid[j1][j2] == 0 and self.grid[k1][k2] != 0:
                        continue
                    self.dist[i][j] = min(self.dist[i][j], self.dist[i][k]+self.dist[k][j])
                    
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
        for i in range(self.N):
            for j in range(self.N):
                self.grid[i][j] = int(input())

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
        adj_empty = []
        for k in range(4):
            x, y = a+self.dr[k], b+self.dc[k]
            if x>=0 and x<self.N and y>=0 and y<self.N and self.grid[x][y]==0:
                adj_empty.append((x,y))
        c = self.cell_to_component[(c,d)]
        for x,y in adj_empty:
            if self.cell_to_component[(x,y)] == c:
                return True
        return False
    
    def makeConnected(self):
        self.dist = [ [float('inf') for j in range(self.cells)] for i in range(self.cells)]
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

    def isMovable(self, a, b, dirs, arr):
        colorset = set()
        cnt = 0
        colordict = defaultdict(lambda:0)
        cells = []
        while cnt<5:
            if self.grid[a][b] == 0:
                return False,0,0,0,0
            cnt+=1
            cells.append((a,b))
            colorset.add(self.grid[a][b])
            colordict[self.grid[a][b]]+=1
            a, b = a+dirs[0], b+dirs[1]
        if len(colorset) != 2:
            return False,0,0,0,0
        colorset = list(colorset)
        
        cnt1, cnt2=  colordict[colorset[0]], colordict[colorset[1]]
        if not ((cnt1 == 1 and cnt2 == 4) or (cnt1 == 4 and cnt2 == 1)):
            return False,0,0,0,0
        for a, b in cells:
            if colordict[self.grid[a][b]] == 1:
                for _,_,x,y,_ in arr[::-1]:
                    if self.isConnected(a,b,x,y):
                        return True,a,b,x,y
        return False,0,0,0,0
        

    def makeMove(self):
        #self.runFloydWarshall()
        self.makeConnected()
#        self.find_emptycells_around()
        self.arr = []

        self.dir = [(0,-1), (0,1),(-1,0),(1,0),(-1,1),(1,-1), (-1,-1),(1,1)]
        self.dir2 = [(0,1), (1,0), (-1,1), (1,1)]
        self.reachable = dict()

        for i in range(self.N):
            for j in range(self.N):
                if self.grid[i][j] == 0:
                    maxcount, color = -1, 0
                    for k in range(0,8,2):
                        hlcount, hlcolor = self.getStreak(i,j, self.dir[k][0], self.dir[k][1])
                        hrcount, hrcolor = self.getStreak(i,j,self.dir[k+1][0], self.dir[k+1][1])
                        if hlcolor == hrcolor:
                            h = hlcount+hrcount
                            maxcount, color = self.update_dominant(maxcount, color, h, hlcolor)                                                
                        else:
                            maxcount, color = self.update_dominant(maxcount, color, hlcount, hlcolor)                                                
                            maxcount, color = self.update_dominant(maxcount, color, hrcount, hrcolor)                                                
                    if color != 0:
                        compo = self.cell_to_component[(i,j)]
                        component_size = len(self.component[compo])
                        self.arr.append((-maxcount,color, i,j, component_size))

        self.arr = sorted(self.arr, key=lambda x: (x[0]))

        if len(self.arr) == 0:
            for i in range(self.cells):
                for j in range(self.cells):
                    if i==j:
                        continue
                    a, b = i//self.N, int(i%self.N)
                    x,y = j//self.N, int(j%self.N)
                    if self.grid[a][b] != 0 and self.grid[x][y] == 0 and self.isConnected(a, b, x, y): 
                        return str(a)+ " " + str(b)+ " " + str(x) + " " +str(y)
        else:
            srcx, srcy, destx, desty = None,None, None, None
            for cnt, c, a, b,_ in self.arr:
                if srcx != None:
                    break
                for x, y in self.same[c]:
                    if cnt >= 4 and self.isFarther(a,b, x, y) and self.isConnected(x,y,a,b):
                        srcx, srcy, destx, desty = x,y,a,b
                        break
            if srcx == None:
                for i in range(self.N):
                    for j in range(self.N):
                        if self.grid[i][j] != 0:
                            for k in range(4):
                                x, y =  i+4*self.dir2[k][0], j+4*self.dir2[k][1]
                                if x>=0 and x<self.N and y>=0 and y<self.N:
                                    Movable, fx, fy, movex, movey = self.isMovable(i,j, self.dir2[k], self.arr)
                                    if Movable:
                                        return str(fx)+" " + str(fy)+" " + str(movex)+" " + str(movey)
                
                for cnt, c, a, b,_ in self.arr:
                    for x, y in self.same[c]:
                        if  self.isFarther(a,b, x, y) and self.isConnected(x,y,a,b):
                            return str(x)+ " " + str(y)+ " " + str(a) + " " +str(b)
            else:
                return str(srcx)+" "+str(srcy)+" "+str(destx)+" "+str(desty)
                
            tmp = []
            for cnt, c, a,b,_ in self.arr:
                tmp.append((cnt, min(a,b), a, b))
            tmp = sorted(tmp)
            for _, _, a, b in tmp:
                for i in range(self.N):
                    for j in range(self.N):
                        if self.grid[i][j]!= 0 and self.isConnected(i,j,a,b): 
                            return str(i)+" " + str(j)+" "+str(a)+" " + str(b)


N = int(input())
C = int(input())

EMPTY = 0
game = LineGame(N,C)
for i in range(1000):
    game.getInput()
    move=game.makeMove()
    print(move)
    sys.stdout.flush()

