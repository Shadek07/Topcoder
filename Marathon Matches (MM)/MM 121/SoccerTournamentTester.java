import java.util.*;
import com.topcoder.marathon.*;

public class SoccerTournamentTester extends MarathonTester {
    //Input ranges
    private static final int minN = 6, maxN = 50;
    private static final int minW = 2, maxW = 6;
    private static final int minD = 1;
    private static final int minX = 1, maxX=10;
    private static final int minDefenceStrength = 1, maxDefenceStrength = 10;
    private static final int minAttackStrength = 2, maxAttackStrength = 10;

    //Inputs
    private int N;          //number of teams
    private int W;          //points for a win
    private int D;          //points for a draw
    private int X;          //number of simulations per game

    //Finals
    private static final int correctOutcome = 1;       //points for correct outcome
    private static final int correctScore = 3;         //points for correct scoreline and outcome
    private static final int numRounds = 3;            //number of attacking/defending rounds

    //State Control
    private int[][] goalsScored;   
    private Team[] teams;         

    protected void generate()
    {
        N = randomInt(minN, maxN);
        W = randomInt(minW, maxW);
        D = randomInt(minD, W-1);
        X = randomInt(minX, maxX);

        //Special cases for seeds 1 and 2
        if (seed == 1)
        {
            N = minN;
            W = 3;
            D = 1;
            X = 1;
        }
        else if (seed == 2)
        {
            N = maxN;
        }

        //User defined parameters
        if (parameters.isDefined("N")) N = randomInt(parameters.getIntRange("N"), minN, maxN);
        if (parameters.isDefined("W")) W = randomInt(parameters.getIntRange("W"), minW, maxW);
        if (parameters.isDefined("D")) D = randomInt(parameters.getIntRange("D"), minD, W-1);
        if (parameters.isDefined("X")) X = randomInt(parameters.getIntRange("X"), minX, maxX);

        //create teams
        teams=new Team[N];
        for (int i=0; i<N; i++)
        {
            int attack = randomInt(minAttackStrength, maxAttackStrength);
            int defence = randomInt(minDefenceStrength, maxDefenceStrength);
            teams[i] = new Team(attack,defence);
        }

        //goalsScored[i][k] is the number of goals scored by team i against team k
        goalsScored=new int[N][N];

        //simulate games
        for (int i=0; i<N; i++)
            for (int k=i+1; k<N; k++)
            {
                int scored1=0;
                int scored2=0;
                for (int simulation=0; simulation<X; simulation++)
                {
                    for (int round=0; round<numRounds; round++)
                    {
                        int attack=randomInt(1,teams[i].attackStrength);
                        int defence=randomInt(1,teams[k].defenceStrength);                    
                        if (attack>defence) scored1++;     //team 1 scores!

                        attack=randomInt(1,teams[k].attackStrength);
                        defence=randomInt(1,teams[i].defenceStrength);                    
                        if (attack>defence) scored2++;     //team 2 scores!
                    }
                }

                scored1=(int)Math.round(scored1*1.0/X);
                scored2=(int)Math.round(scored2*1.0/X);
                //System.out.println(teams[i].attackStrength+"/"+teams[i].defenceStrength+" "+teams[k].attackStrength+"/"+teams[k].defenceStrength);                
                //System.out.println(scored1+" "+scored2+"\n");

                goalsScored[i][k]+=scored1;    
                teams[i].scored+=scored1;
                teams[k].conceded+=scored1;    
                
                goalsScored[k][i]+=scored2;    
                teams[k].scored+=scored2;
                teams[i].conceded+=scored2;                                        

                //team 1 won
                if (goalsScored[i][k] > goalsScored[k][i])
                    teams[i].points+=W;
                //team 2 won
                else if (goalsScored[i][k] < goalsScored[k][i])
                    teams[k].points+=W;
                //draw
                else
                {
                    teams[i].points+=D;
                    teams[k].points+=D;
                }
            }


        if (debug)
        {
            System.out.println("teams, N = " + N);
            System.out.println("points for win, W = " + W);
            System.out.println("points for draw, D = " + D);
            System.out.println("simulations, X = " + X);
            for (int i=0; i<N; i++)
                System.out.println("team "+i+" scored "+teams[i].scored+" conceded "+teams[i].conceded+" points "+teams[i].points);
            System.out.println();
        }
    }

    protected boolean isMaximize() {
        return true;
    }

    protected double run() throws Exception {
        String[] solution = callSolution();
        if (solution == null) {
            if (!isReadActive()) return getErrorScore();
            return fatalError();
        }
  
        int score=0;

        for (int team1=0,i=0; team1<N; team1++)
            for (int team2=team1+1; team2<N; team2++,i++)
            {
                String[] temp=solution[i].split(" ");
                if (temp.length!=2) return fatalError("Invalid format of "+i+"th game result: "+solution[i]);

                int scored1=-1, scored2=-1;
                try
                {
                    scored1=Integer.parseInt(temp[0]);
                    scored2=Integer.parseInt(temp[1]);
                    if (scored1<0 || scored1>numRounds || scored2<0 || scored2>numRounds)
                        return fatalError("Invalid format of "+i+"th game result: "+solution[i]);
                }
                catch (Exception e)
                {
                    return fatalError("Invalid format of "+i+"th game result: "+solution[i]);                
                } 

                if (debug)
                    System.out.print("game "+i+", team "+team1+" vs team "+team2+", predicted "+scored1+":"+scored2+" actual "+goalsScored[team1][team2]+":"+goalsScored[team2][team1]);

                //full points!
                if (scored1==goalsScored[team1][team2] && scored2==goalsScored[team2][team1])
                {
                    score+=correctScore;
                    if (debug) System.out.print(" Correct outcome and score!\n");
                }
                //partial points
                else if ((scored1>scored2 && goalsScored[team1][team2]>goalsScored[team2][team1]) ||
                         (scored1<scored2 && goalsScored[team1][team2]<goalsScored[team2][team1]) ||
                         (scored1==scored2 && goalsScored[team1][team2]==goalsScored[team2][team1]))
                {
                    score+=correctOutcome;
                    if (debug) System.out.print(" Correct outcome!\n");
                }
                else if (debug)  System.out.print(" Wrong\n");
            }

        //print team stats
        if (debug)
        {
            System.out.println("\nteam stats:");
            for (int i=0; i<N; i++)
                System.out.println("team "+i+" attackStrength "+teams[i].attackStrength+" defenceStrength "+teams[i].defenceStrength);
            System.out.println();
        }
            
        return score;
    }
    

    private String[] callSolution() throws Exception {
        writeLine(N);
        writeLine(W);
        writeLine(D);
        writeLine(X);
        for (int i=0; i<N; i++)
            writeLine(teams[i].scored+" "+teams[i].conceded+" "+teams[i].points);
        flush();
        if (!isReadActive()) return null;

        startTime();
        int n = readLineToInt(-1);
        if (n != N*(N-1)/2) {
            setErrorMessage("Must have "+(N*(N-1)/2)+" game results, but " + getLastLineRead()+" were returned");
            return null;
        }
        String[] ret = new String[n];
        for (int i = 0; i < ret.length; i++)
            ret[i] = readLine();
 
        stopTime();
        return ret;
    }

    class Team
    {
        int attackStrength;
        int defenceStrength;
        int scored;
        int conceded;
        int points;

        public Team(int a, int d)
        {
            attackStrength=a;
            defenceStrength=d;
        }
    }

    public static void main(String[] args) {
        new MarathonController().run(args);
    }
}