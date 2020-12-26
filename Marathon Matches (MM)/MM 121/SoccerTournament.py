import copy
import sys
import random
import math

class SimAnneal:
    def __init__(self, scored, conceded, points, W, D, X, T=-1, alpha=-1, stopping_T=-1, stopping_iter=-1):
        self.scored = scored
        self.conceded = conceded
        self.points = points
        self.W = W
        self.D = D
        self.X = X
        self.numRounds = 3
        self.N = len(self.scored)
        self.T = math.sqrt(self.N) if T == -1 else T
        self.T_save = self.T  # save inital T to reset if batch annealing is used
        self.alpha = 0.995 if alpha == -1 else alpha
        self.stopping_temperature = 1e-8 if stopping_T == -1 else stopping_T
        self.stopping_iter = 4000 if stopping_iter == -1 else stopping_iter
        self.iteration = 1

        self.best_solution = None
        self.best_fitness = float("Inf")
        self.fitness_list = []

    def initial_solution(self):
        """
        Greedy algorithm to get an initial solution (closest-neighbour).
        """
        res = [[None for j in range(self.N)] for i in range(self.N)]
        for i in range(self.N):
            for j in range(i+1, self.N):
                a, b = self.simulate(10, 10, 10, 10)
                res[i][j] = (a, b)
                res[j][i] = (b, a)

        cur_fit = self.fitness(res)
        if cur_fit < self.best_fitness:  # If best found so far, update best fitness
            self.best_fitness = cur_fit
            self.best_solution = res
        self.fitness_list.append(cur_fit)
        #print ("initial solution", cur_fit)
        return res, cur_fit

    def fitness(self, res):
        """
        Total distance of the current solution path.
        """
        cs = [[0, 0, 0] for i in range(self.N)]
        for i in range(self.N):
            scored = 0
            conceded = 0
            points = 0
            for j in range(self.N):
                if j == i:
                    continue
                if res[i][j][0] > res[i][j][1]:
                    points += self.W
                elif res[i][j][0] == res[i][j][1]:
                    points += self.D
                scored += res[i][j][0]
                conceded += res[i][j][1]
            cs[i] = [scored, conceded, points]
        cost = self.cost_function([[self.scored[i], self.conceded[i], self.points[i]] for i in range(self.N)], cs)
        return cost

    def p_accept(self, candidate_fitness):
        """
        Probability of accepting if the candidate is worse than current.
        Depends on the current temperature and difference between candidate and current.
        """
        return math.exp(-abs(candidate_fitness - self.cur_fitness) / self.T)

    def accept(self, candidate):
        """
        Accept with probability 1 if candidate is better than current.
        Accept with probabilty p_accept(..) if candidate is worse.
        """
        candidate_fitness = self.fitness(candidate)
        if candidate_fitness < self.cur_fitness:
            self.cur_fitness, self.cur_solution = candidate_fitness, candidate
            if candidate_fitness < self.best_fitness:
                self.best_fitness, self.best_solution = candidate_fitness, candidate
        else:
            if random.random() < self.p_accept(candidate_fitness):
                self.cur_fitness, self.cur_solution = candidate_fitness, candidate

    def anneal(self):
        """
        Execute simulated annealing algorithm.
        """
        # Initialize with the greedy solution.
        self.cur_solution, self.cur_fitness = self.initial_solution()

        #print("Starting annealing.")
        while self.T >= self.stopping_temperature and self.iteration < self.stopping_iter:
            team1 = random.randint(0, self.N-1)
            candidate = [[None for j in range(self.N)] for i in range(self.N)]
            for i in range(self.N):
                for j in range(self.N):
                    candidate[i][j] = self.cur_solution[i][j]
            #candidate = copy.deepcopy(self.cur_solution)
            teams = [i for i in range(self.N)]
            teams[team1], teams[self.N-1] = teams[self.N-1], teams[team1]
            team2 = random.randint(0, self.N-2)
            #while team2 == team1:
            #    team2 = random.randint(0, self.N-1)
            a, b = self.simulate(10, 10, 10, 10)
            candidate[team1][team2] = (a, b)
            candidate[team2][team1] = (b, a)

            self.accept(candidate)
            self.T *= self.alpha
            self.iteration += 1

            self.fitness_list.append(self.cur_fitness)

        #print("Best fitness obtained: ", self.best_fitness)
        #improvement = 100 * (self.fitness_list[0] - self.best_fitness) / (self.fitness_list[0])
        #print(f"Improvement over greedy heuristic: {improvement : .2f}%")

    def simulate(self, a1, d1, a2, d2):  # team1, team2
        scored1 = 0
        scored2 = 0
        for simulation in range(0, self.X):
            for rnd in range(0, self.numRounds):
                attack = random.randint(2, a1)
                defense = random.randint(1, d2)
                if attack > defense:
                    scored1 += 1
                attack = random.randint(2, a2)
                defense = random.randint(1, d1)
                if attack > defense:
                    scored2 += 1
        scored1 = int(scored1 * 1.0 / self.X + 0.5)
        scored2 = int(scored2 * 1.0 / self.X + 0.5)
        return scored1, scored2

    def batch_anneal(self, times=10):
        """
        Execute simulated annealing algorithm `times` times, with random initial solutions.
        """
        for i in range(1, times + 1):
            print(f"Iteration {i}/{times} -------------------------------")
            self.T = self.T_save
            self.iteration = 1
            self.cur_solution, self.cur_fitness = self.initial_solution()
            self.anneal()

    def cost_function(self, ins, cs):
        total = 0
        weight = [0.25, 0.25, 0.50]
        for i in range(0, self.N):
            tmp = 0
            for j in range(3):
                tmp += ((ins[i][j] - cs[i][j]) ** 2) * weight[j]
                total += tmp
        return total

class SoccerTournament:
  def __init__(self, N, W, D, X, scored, conceded, points):
    self.N = N
    self.W = W
    self.D = D
    self.X = X
    self.scored = scored
    self.conceded = conceded
    self.points = points
    self.numRounds = 3
    self.astrength = [1]*N
    self.dstrength = [1]*N
    self.lose_range = [(-1, -1)]*N
    for i in range(N):
      p = self.points[i]
      self.lose_range[i] = (N-1-(p+self.D-1//self.D), N-1-(p+self.W-1)//self.W)
    self.sorted_teams = [(-self.points[i], -self.scored[i], self.conceded[i], i) for i in range(self.N)]
    self.sorted_teams = sorted(self.sorted_teams)



1
  def findSolution(self, N):
    n = int(N*(N-1)/2)
    results = [""] * n
    sa = SimAnneal(self.scored, self.conceded, self.points, self.W, self.D, self.X)
    sa.anneal()
    cnt = 0
    for a in range(self.N):
        for b in range(a+1, self.N):
            results[cnt] = str(sa.cur_solution[a][b][0]) + " " + str(sa.cur_solution[a][b][1])
            cnt += 1
    return results


N = int(input())
W = int(input())
D = int(input())
X = int(input())

scored = [0] * N
conceded = [0] * N
points = [0] * N
for i in range(N):
  temp = input().split()
  scored[i] = int(temp[0])
  conceded[i] = int(temp[1])
  points[i] = int(temp[2])
 
prog = SoccerTournament(N, W, D, X, scored, conceded, points)
ret = prog.findSolution(N)

print(len(ret))
for st in ret:
  print(st)
sys.stdout.flush()
