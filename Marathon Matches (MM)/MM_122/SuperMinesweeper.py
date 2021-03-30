import sys
import random
import heapq
from collections import defaultdict
import copy
''' gh gh fgyy yuj '''

class SuperMinesweeper:
    def remove_from_unrevealed(self, unrevealed):
        newset = []
        for r,c in unrevealed:
            if self.stats[r][c] == -2:
                newset.append((r, c))
        return newset
    def find_neighbors(self):
        for x in range(self.N):
            for y in range(self.N):
                for a in range(x - self.D, x + self.D + 1):
                    for b in range(y - self.D, y + self.D + 1):
                        if a < 0 or a >= self.N or b < 0 or b >= self.N:
                            continue
                        if x == a and x == b:
                            continue
                        d = pow(x - a, 2) + pow(y - b, 2)
                        if d > self.D:
                            continue
                        self.neighbors[(x, y)].append((a, b, d))

    def get_cellstats(self, x, y):
        mine_found = 0
        unrevealedtmp = []
        cellnumber = self.stats[x][y]
        cnt_cells_withnumber = 0
        neighbors = self.neighbors[(x, y)]
        sum_value = 0
        for a, b, dist in neighbors:
            if self.stats[a][b] == -2:
                unrevealedtmp.append((a, b))
            elif self.stats[a][b] == -1:
                mine_found += 1
            elif self.stats[a][b] >= 0:
                cnt_cells_withnumber += 1
                sum_value += self.stats[a][b] #*(self.D+1-dist)
        mine_remaining = cellnumber - mine_found
        if len(unrevealedtmp) > 0 and cellnumber > 0 and mine_remaining == 0:
            for row, col in unrevealedtmp:
                if self.stats[row][col] != -2:
                    continue
                print("G " + str(row) + " " + str(col))
                feedback = input().split(" ")
                if feedback[0][0:5] == "BOOM!":
                    self.stats[row][col] = -1
                    self.minehit += 1
                    self.mineremained -= 1
                    self.update_neighbors_after_mine_find(row, col)
                else:
                    self.stats[row][col] = int(feedback[0])
                    self.place_mines(row, col)
        if self.stats[x][y] == -2:
            if cnt_cells_withnumber == 0:
                avg = 1000000
            else:
                avg = sum_value*1.0/cnt_cells_withnumber
        else:
            avg = 1000000
        return unrevealedtmp, mine_remaining, mine_found, avg
    def cost_function(self, avgvalue, neighbor_unrevealed_len, mine_remaining):
        return avgvalue*0.90 - neighbor_unrevealed_len*0.05 + mine_remaining*0.05

    def find_next_cell(self, unrevealed):
        random.shuffle(unrevealed)
        unrevealed_minvaluewise_dict = dict()
        min_avgvalue = 1000000
        data_to_sort = []
        for r2, c2 in unrevealed:
            if self.stats[r2][c2] == -1:
                continue
            neighbor_unrevealed, mine_remaining, mine_found, avgvalue = self.get_cellstats(r2, c2)
            if avgvalue not in unrevealed_minvaluewise_dict:
                unrevealed_minvaluewise_dict[avgvalue] = [(r2, c2)]
            else:
                unrevealed_minvaluewise_dict[avgvalue].append((r2, c2))
            #data_to_sort.append((self.cost_function(avgvalue, len(neighbor_unrevealed), mine_remaining),  (r2, c2)))
            if min_avgvalue > avgvalue:
                min_avgvalue = avgvalue
        #data_to_sort = sorted(data_to_sort, key=lambda x: (x[0]))
        if min_avgvalue < 1000:
            tmp = unrevealed_minvaluewise_dict[min_avgvalue]
            return tmp[random.randint(0, len(tmp)-1)]
            #return data_to_sort[0][1]
        else:
            #self.f.write('here? ' + str(unrevealed[0][0]) + ' ' + str(unrevealed[0][1]) + '\n')
            return unrevealed[0]

    def adjust_common_mine_cells(self):
        for key in self.cellstat_withnumber.copy():
            x, y = key
            neighbors = self.neighbors[(x, y)]
            for a, b, _ in neighbors:
                if self.stats[a][b] > 0:
                    #un1, mine_remaining1, _, _ = self.get_cellstats(x, y)
                    un1, mine_remaining1, _, _ = self.cellstat_withnumber[(x, y)]
                    un2, mine_remaining2, _, _ = self.cellstat_withnumber[(a, b)]
                    common_unrevealed = set(un1).intersection(un2)
                    common_len = len(common_unrevealed)
                    if common_len == 0:
                        continue
                    un1_len = len(un1)
                    un2_len = len(un2)

                    if mine_remaining1 < mine_remaining2:
                        un2_extra = mine_remaining2 - min(mine_remaining1, common_len)
                        only_in2 = set(un2).difference(un1)
                        if len(list(only_in2)) == un2_extra:
                            for r, c in list(only_in2):
                                if self.stats[r][c] != -2:
                                    continue
                                self.stats[r][c] = -1
                                #print("F " + str(r) + " " + str(c))
                                #feedback = input().split(" ")
                                self.update_neighbors_after_mine_find(r, c)
                    elif mine_remaining2 < mine_remaining1:
                        un1_extra = mine_remaining1 - min(mine_remaining2, common_len)
                        only_in1 = set(un1).difference(un2)
                        if len(list(only_in1)) == un1_extra:
                            for r, c in list(only_in1):
                                if self.stats[r][c] != -2:
                                    continue
                                self.stats[r][c] = -1
                                #print("F " + str(r) + " " + str(c))
                                #feedback = input().split(" ")
                                self.update_neighbors_after_mine_find(r, c)
                    else:
                        if set(un1).issubset(set(un2)):
                            only_in2 = set(un2).difference(un1)
                            for r, c in list(only_in2):
                                if self.stats[r][c] != -2:
                                    continue
                                print("G " + str(r) + " " + str(c))
                                feedback = input()
                                self.process_feedback(feedback, r, c)
                        elif set(un2).issubset(set(un1)):
                            only_in1 = set(un1).difference(un2)
                            for r, c in list(only_in1):
                                if self.stats[r][c] != -2:
                                    continue
                                print("G " + str(r) + " " + str(c))
                                feedback = input()
                                self.process_feedback(feedback, r, c)

    def update_neighbors_after_mine_find(self, r, c): #r, c is mine_location
        neighbors = self.neighbors[(r, c)]
        for a, b, dist in neighbors:
            if self.stats[a][b] > 0:
                if (a, b) not in self.cellstat_withnumber:
                    unrevealed2, mine_remaining, mine_found, cnt_cells_withnumber = self.get_cellstats(a, b)
                    self.cellstat_withnumber[(a, b)] = (set(unrevealed2), mine_remaining, mine_found, cnt_cells_withnumber)

                unrevealed2, mine_remaining, mine_found, cnt_cells_withnumber = self.cellstat_withnumber[(a, b)]
                if (r, c) in unrevealed2:
                    unrevealed2.remove((r, c))
                    mine_remaining -= 1
                    mine_found += 1
                self.cellstat_withnumber[(a, b)] = (set(unrevealed2), mine_remaining, mine_found, cnt_cells_withnumber)
                if len(unrevealed2) > 0 and mine_remaining == 0:
                    tmp = list(unrevealed2)
                    for r1, c1 in tmp:
                        if self.stats[r1][c1] != -2:
                            continue
                        print("G " + str(r1) + " " + str(c1))
                        feedback = input()
                        self.process_feedback(feedback, r1, c1)

    def process_feedback(self, feedback, r, c):
        if feedback[0:5] == "BOOM!":
            self.minehit += 1
            self.mineremained -= 1
            self.stats[r][c] = -1
            self.update_neighbors_after_mine_find(r, c)
            # break
        else:
            temp = feedback.split(" ")
            value = int(temp[0])
            runtime = int(temp[1])
            if value == 0:
                self.stats[r][c] = 0
                self.zero_propagate(r, c)
            else:
                self.stats[r][c] = value
                self.place_mines(r, c)
    def place_mines(self, x, y): #x,y is a number_cell
        unrevealed3, mine_remaining, mine_found, cnt_cells_withnumber = self.get_cellstats(x, y)
        self.cellstat_withnumber[(x, y)] = (set(unrevealed3), mine_remaining, mine_found, cnt_cells_withnumber)
        if len(unrevealed3) == mine_remaining:
            for r3, c3 in unrevealed3:
                if self.stats[r3][c3] != -2:
                    continue
                self.stats[r3][c3] = -1
                #print("F " + str(r3) + " " + str(c3))
                #feedback = input().split(" ")
                self.update_neighbors_after_mine_find(r3, c3)
        '''elif int(0.8*len(unrevealed)) >= mine_remaining:
            random.shuffle(unrevealed)
            for i in range(0, mine_remaining):
                r,c = unrevealed[i]
                self.stats[r][c] = -1
                self.update_neighbors_after_mine_find(r, c)'''

    def zero_propagate(self, r, c):
        queue = [(r, c)]
        while queue:
            x, y = queue.pop(0)
            neighbors = self.neighbors[(x, y)]
            for a, b, dist in neighbors:
                if self.stats[a][b] != -2:
                    continue
                print("G "+str(a)+" "+str(b))
                temp = input().split(" ")
                value = int(temp[0])
                runtime = int(temp[1])
                self.stats[a][b] = value
                if value == 0:
                    queue.append((a, b))
                else:
                    #unrevealed4, mine_remaining, mine_found, cnt_cells_withnumber = self.get_cellstats(a, b)
                    #self.cellstat_withnumber[(a, b)] = (set(unrevealed4), mine_remaining, mine_found, cnt_cells_withnumber)
                    self.place_mines(a, b)



    def __init__(self, N, M, D, inputCell):
        self.N=N
        self.M=M
        self.D=D
        self.stats =[ [-2 for j in range(N)] for i in range(N)]

        self.Grid = [[-1 for r11 in range(N)] for c11 in range(N)]
        temp=inputCell.split()
        r=int(temp[0])
        c=int(temp[1])
        self.Grid[r][c] = 0
        self.stats[r][c] = 0
        self.unrevealed = None
        self.minehit = 0
        self.mineremained = M
        self.neighbors = defaultdict(lambda: [])
        self.find_neighbors()
        self.cellstat_withnumber = dict()
        self.zero_propagate(r, c)


N = int(input())
M = int(input())
D = int(input())
inputCell = input()
 
prog = SuperMinesweeper(N, M, D, inputCell)
maxhit = int(0.1*M)
if N < 10:
    maxhit = int(0.7*M)
elif N>=10 and N < 20:
    maxhit = int(0.6*M)
elif N>=20 and N < 30:
    maxhit = int(0.3*M)
elif N>=30:
    maxhit = int(0.1*M)
cnt = 0
maxhit=1
unrevealed = []
for i in range(N):
    for j in range(N):
        if prog.stats[i][j] == -2:
            unrevealed.append((i, j))
size = len(unrevealed)
mine_remained = M
prog.unrevealed = unrevealed

'''for i in range(N):
            for j in range(N):
                if prog.stats[i][j] > 0:
                    prog.place_mines(i, j)'''
while (prog.minehit < maxhit) and (len(prog.unrevealed) > 0):
    if mine_remained >= len(prog.unrevealed):
        break
    #prog.adjust_common_mine_cells()

    #items = prog.cellstat_withnumber.items()

    items = {k: v for k, v in prog.cellstat_withnumber.items() if v}

    for key in prog.cellstat_withnumber.copy():
        if not prog.cellstat_withnumber[key]:
            prog.cellstat_withnumber.pop(key)
        r, c = key
        prog.place_mines(r, c)
        
    prog.unrevealed = prog.remove_from_unrevealed(prog.unrevealed)
    size = len(prog.unrevealed)
    if size == 0:
        break

    r, c = prog.find_next_cell(prog.unrevealed)

    if prog.stats[r][c] != -2:
        continue

    size -= 1
    print("G "+str(r)+" "+str(c))
    feedback = input()
    prog.process_feedback(feedback, r, c)

    prog.adjust_common_mine_cells()

    #f.write("exited" + "\n")

'''for iter in range(500):
    for i in range(N):
        for j in range(N):
            if prog.stats[i][j] > 0:
                prog.place_mines(i, j)'''
print("STOP")
sys.stdout.flush()

