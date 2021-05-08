// C++11

#include<bits/stdc++.h>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

#define MX 1000000

#define forl(i,a,b) for ( i = a; i < b; i++)
#define fore(i,a,b) for ( i = a; i <= b; i++)
#define forrev(i,a,b) for ( i = a; i >= b; i--)
#define pb push_back
typedef long long  LL;
#define in(a,b,c) ((a) <= (b) && (b) <= (c))
#define ms(a,b) memset((a),(b),sizeof(a))

#define all(v) (v).begin(),(v).end()
#define pb push_back
#define ull unsigned long long int
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

string to_string1(long long x) { stringstream ss; ss << x; return ss.str(); }
long long to_int(const string &s) { stringstream ss; ss << s; long long x; ss >> x; return x; }

#define MAX 100005
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};
string dir[4] = {"R", "U", "L", "D"};

int N;
int C;
int H;
class Grid {
    public:
        vector<vector<int>> grid;
        int n,c,h;
        Grid(int N, int C, int H):grid(N, vector<int>(N,0)), n(N), c(C),h(h){

        }
        Grid(){}
        void readGrid(){
            int i, j;
            forl(i,0,n){
                forl(j,0,n){
                    cin >> grid[i][j];
                }
            }
        }
};

class SimAnneal{
    public:
        Grid grid;
        double T, alpha, stopping_T, stopping_iter;
        vector<string> best_fitness;
        double best_score;
        vector<vector<int>> block_seq;
        double curr_score=0;
        vector<pii> holes;
        int last_index = -1; //last index where we couldn't put the block to any hole
        SimAnneal(Grid grd, double T=-1, double alpha=-1, double stopping_T=-1, double stopping_iter=-1){
            this->grid = grd;
            this->T = T;
            this->alpha = alpha;
            this->stopping_T = stopping_T;
            this->stopping_iter = stopping_iter;
            this->best_score = 0;
            int i,j;
            forl(i,0,this->grid.n){
                forl(j,0,this->grid.n){
                    if(this->grid.grid[i][j] >= 1){
                       vector<int> v = {i,j}; 
                       this->block_seq.pb(v);
                    }
                    if(this->grid.grid[i][j] == -1){
                        this->holes.pb(make_pair(i,j));
                    }
                }
            }
            //random_shuffle(this->block_seq.begin(), this->block_seq.end());
        }
        bool withinGrid(int x, int y){
            if (x >= 0 && x <this->grid.n && y >= 0 and y < this->grid.n){
                return true;
            }
            return false;
        }
        int getDist_to_hole(int x, int y){
            int min_dist = 9999999;
            for(auto hole:this->holes){
                //min_dist = min(min_dist, abs(hole.first-x)+abs(hole.second-y));                
                if(hole.first == x || hole.second == y)
                    return 0;
            }
            return min_dist;
        }
        static bool customBlockSort(const tuple<int, int, int,int,int> &a, const tuple<int,int,int,int,int>&b){
            int amoves,bmoves,avalue,bvalue;
            amoves = get<0>(a);
            avalue = get<1>(a);
            bmoves = get<0>(b);
            bvalue = get<1>(b);
            /*if(a1 == INT_MAX && b1 == INT_MAX){
                return a2>b2;
            }else if(a1 == INT_MAX){
                return false;
            }else if(b1 == INT_MAX){
                return true;
            }else{
                return (N*N-a1)*a2 > (N*N-b1)*b2;
            }*/
            if(amoves!=bmoves){
                return amoves<bmoves;
            }else{
                int a_holedist, b_holedist;
                a_holedist = get<4>(a);
                b_holedist = get<4>(b);
                if(b_holedist < a_holedist)
                    return true;
                return avalue>bvalue;
            }
        }

        void initial_solution(){
            vector<tuple<int,int, int, int, int>> blocks;
            int i;
            bool taken[this->block_seq.size()];
            ms(taken, false);
            Grid gr = this->grid;
            while(true){ 

                vector<tuple<int,int, int, int, int>> tmp_blocks;
                forl(i,0,this->block_seq.size()){
                    if(taken[i])
                        continue;
                    
                    auto res = this->moveBlock(this->block_seq[i][0], this->block_seq[i][1], gr);
                    if (res.size() == 0)
                        continue;
                    taken[i] = true;
                    tmp_blocks.pb(make_tuple(res.size()==0?INT_MAX:res.size(), this->grid.grid[this->block_seq[i][0]][this->block_seq[i][1]], this->block_seq[i][0], this->block_seq[i][1], this->getDist_to_hole(this->block_seq[i][0], this->block_seq[i][1])));
                }
                if(tmp_blocks.size() == 0)
                    break;

                sort(tmp_blocks.begin(), tmp_blocks.end(), this->customBlockSort); 
                blocks.insert(blocks.end(), tmp_blocks.begin(), tmp_blocks.end());
                int j;
                forl(j,0,tmp_blocks.size()){
                    int x,y;
                    x = get<2>(tmp_blocks[j]);
                    y = get<3>(tmp_blocks[j]);
                    gr.grid[x][y] = 0;
                }
            }
            forl(i,0,this->block_seq.size()){
                if(taken[i] == false){
                    blocks.pb(make_tuple(INT_MAX, 1, this->block_seq[i][0], this->block_seq[i][1], N*N));
                }
            }
            vector<vector<int>> tmp;
            forl(i,0,this->block_seq.size()){
                vector<int> v = {get<2>(blocks[i]), get<3>(blocks[i])};
                tmp.pb(v);
            }
            this->block_seq = tmp;
            auto res = this->fitness(this->block_seq);
            this->curr_score = get<0>(res);
            this->best_score = this->curr_score;
            this->best_fitness = get<1>(res);
        }
        string createMoveString(int x, int y, int k, string type){
            return to_string1(x)+ " " + to_string1(y) + " " + type+ " " + dir[k];
        }

        vector<string> moveBlock(int x, int y, Grid grid, int step=-1){
            vector<string> v;
            deque< tuple<pii, vector<string> > > q;
            q.push_back(make_tuple(make_pair(x,y), vector<string>()));
            //map<pii, int> visited;
            //visited[make_pair(x,y)] = 1; 
            bool visited[grid.n][grid.n][4];
            int dist[grid.n][grid.n];
            int i,j;
            int min_dist = INT_MAX;
            ms(visited, false);
            int k;
            grid.grid[x][y] = 0; 
            while(!q.empty()){
                tuple<pii, vector<string> > cell = q.front();
                q.pop_front();
                int currx, curry;
                currx = get<0>(cell).first;
                curry = get<0>(cell).second;
                if(grid.grid[currx][curry] == -1){
                    return get<1>(cell);
                }
                //slide
                forl(k,0,4){
                    int a,b;
                    a = get<0>(cell).first;
                    b = get<0>(cell).second; 
                    vector<string> ops = get<1>(cell);
                    pii next = make_pair(a,b);
                    while (true){
                        a = a+dx[k];
                        b = b+dy[k];
                        if(!this->withinGrid(a,b) || grid.grid[a][b] >= 1){
                            next = make_pair(a-dx[k],b-dy[k]);
                            break;
                        }
                        if(grid.grid[a][b] == -1){
                            next = make_pair(a,b);
                            break;
                        }
                    }
                    if( next.first == get<0>(cell).first and next.second == get<0>(cell).second)
                        continue;
                    if(visited[next.first][next.second][k])
                        continue;
                    ops.pb(this->createMoveString(get<0>(cell).first, get<0>(cell).second, k, "S"));
                    q.push_back(make_tuple(next, ops));
                    visited[next.first][next.second][k] = true;
                }
                //move
                int empties = this->grid.n*this->grid.n - this->block_seq.size() - this->grid.h + step;
                if(empties >= 0.05*this->grid.n*this->grid.n)
                    continue;
                forl(k,0,4){
                    int a,b;
                    a = currx+dx[k];
                    b = curry+dy[k];
                    if(this->withinGrid(a, b)){
                        if(grid.grid[a][b]<=0){
                            if(visited[a][b][k] == false){
                                vector<string> ops2 = get<1>(cell);
                                ops2.pb(this->createMoveString(currx, curry,k, "M"));
                                visited[a][b][k] = true;
                                q.pb(make_tuple(make_pair(a,b), ops2));
                            }

                        }
                    }
                }
            }
            return v;
        }

        tuple<int, vector<string>> fitness(vector<vector<int>> block_seq){
            vector<string> output;
            double score = 0;
            int blocks = block_seq.size();
            Grid tmpGrid = this->grid;
            int i,j,k;
            int Z = this->grid.n*this->grid.n;
            forl(i,0,blocks){
                auto moves = this->moveBlock(block_seq[i][0], block_seq[i][1], tmpGrid,i);
                if(moves.size() == 0 || Z <= moves.size()){
                    this->last_index = i;    
                    return make_tuple(score, output);
                }
                score += (Z - moves.size())*(tmpGrid.grid[block_seq[i][0]][block_seq[i][1]]-1);
                Z -= moves.size();
                tmpGrid.grid[block_seq[i][0]][block_seq[i][1]] = 0;
                output.insert(output.end(), moves.begin(), moves.end());

            }
            this->last_index = -1;
            return make_tuple(score, output);
        }
        double p_accept(double candidate_score){
            return exp(-fabs(candidate_score - this->curr_score)/this->T);
        }
        void accept(vector<vector<int>> candidate){
            auto candidate_fitness = this->fitness(candidate);
            double candidate_score = get<0>(candidate_fitness);
            if (candidate_score > this->curr_score){
                this->block_seq=  candidate;
                this->curr_score = candidate_score;
                if (candidate_score > this->best_score){
                    this->best_score = candidate_score;
                    this->best_fitness = get<1>(candidate_fitness);
                }
            }else{
               double prob = (double)rand()/RAND_MAX; 
               if (prob < this->p_accept(candidate_score)){
                   this->block_seq = candidate;
                   this->curr_score = candidate_score;
               }

            }

        }
        void anneal(){
            int start_time = clock();
            auto start = chrono::steady_clock::now( );
            this->initial_solution();
            int iter = 1;
            while (this->T >= this->stopping_T && iter < this->stopping_iter){
                vector<vector<int>> tmp = this->block_seq;
                int index1, index2;

                double prob = (double)rand()/RAND_MAX; 
                if(prob >= 0.3 && this->last_index != -1){
                    index1 = this->last_index;
                }else{
                    index1 = 0 + rand()%tmp.size();
                }
                index2 = index1;
                while (index2 == index1){
                    index2 = 0 + rand()%(index1+100);
                    if(index2 >= tmp.size()){
                        index2 = index1;
                    }
                }
                swap(tmp[index1], tmp[index2]);
                this->accept(tmp);
                this->T *= this->alpha;
                iter += 1;
                int curr_time = clock();
                auto elapsed = chrono::duration_cast<chrono::milliseconds>( chrono::steady_clock::now( ) - start );
                if(elapsed.count() > 9979){
                    break;
                }
            }
        }
};

int main() 
{

  cin >> N;
  cin >> C;
  cin >> H;
  Grid grid(N, C, H);
  vector<int> gr(N*N);
  //read grid
  grid.readGrid();
  int total_iter = 6000;
  /*if(N >= 25){
      total_iter = 3000;
  }
  if(N <= 15){
      total_iter = 4500;
  }*/
  SimAnneal obj(grid,sqrt(grid.n), 0.995, 0.000000001, total_iter);
  obj.anneal();
  int moves = 0;
  cout << obj.best_fitness.size() << endl;
  int i;
  forl(i,0,obj.best_fitness.size()){
      cout << obj.best_fitness[i] << endl;
  }

  cout.flush();
}
