import java.awt.*;
import java.awt.geom.*;
import java.util.*;
import com.topcoder.marathon.*;


public class LinesTester extends MarathonAnimatedVis {
    //parameter ranges
    private static final int minN = 7, maxN = 11;
    private static final int minC = 3, maxC = 9;

    //Inputs
    private int N;      //grid size
    private int C;      //number of colors

    //Manual play
    private int lastR1 = -1;
    private int lastC1;
    private int lastR2;
    private int lastC2;

    //Constants 
    private static final int[] dr = {0,1,0,-1};     //L, U, R, D
    private static final int[] dc = {-1,0,1,0};    
    private static final int[] dr2 = {0,1,1,1};     //R, D, \, /
    private static final int[] dc2 = {1,0,1,-1};        
    private static final int INF = 1000000;
    private static final int maxMoves = 1000;
    private static final int startingBalls = 3;
    private static final int numNextBalls = 3;
    private static final int minMatches = 5;
    private static int EMPTY = 0;

    //State Control
    private int[][] Grid; 
    private int[] nextBalls;
    private boolean gameOver;
    private int numMoves;
    private int score;
    private int moveScore;
    private int emptyLeft;
    private int curBall;
    
    //Painting
    private Color[] colors;    

    
    protected void generate()
    {
      N = randomInt(minN, maxN);
      C = randomInt(minC, maxC);

      //Special cases
      if (seed == 1)
      {
        N = minN;
        C = minC;
      }
      else if (seed == 2)
      {
        N = maxN;
        C = maxC;
      }    
      
      //User defined parameters   
      if (parameters.isDefined("N"))
        N = randomInt(parameters.getIntRange("N"), minN, maxN);
      if (parameters.isDefined("C"))
        C = randomInt(parameters.getIntRange("C"), minC, maxC);
        
      gameOver = false;                 
      emptyLeft=N*N;
      
      //setup the grid with some initial balls
      Grid = new int[N][N];
      for (int i=0; i<startingBalls; )
      {
        int r=randomInt(0,N-1);
        int c=randomInt(0,N-1);
        if (Grid[r][c]==EMPTY)
        {
          Grid[r][c]=randomInt(1,C);
          emptyLeft--;
          i++;
        }
      }
      
      curBall=0;
      nextBalls = new int[(maxMoves+1)*numNextBalls];
      for (int i=0; i<nextBalls.length; i++)
        nextBalls[i] = randomInt(1,C);
        

      //display info
      if (debug)
      {
        System.out.println("Grid Size N = " + N);
        System.out.println("Colors C = " + C);        
        System.out.println("Grid:");          
        for (int r=0; r<N; r++)
        {
          for (int c=0; c<N; c++)        
            System.out.print(Grid[r][c]);
          System.out.println();
        }        
      }
    }
    
    protected boolean isMaximize() {
        return true;
    }
    
    protected double run() throws Exception
    {
      init();
      if (parameters.isDefined("manual")) return 0;
      return runAuto();
    }
    
    protected double runAuto() throws Exception
    {
      score = callSolution();
      if (score < 0) {
        if (!isReadActive()) return getErrorScore();
        return fatalError();
      }
      return score;    
    }    

    protected void updateState()
    {
      if ((numMoves>=0 || lastR1 != -1) && hasVis() && (hasDelay() || !gameOver)) 
      {      
        synchronized (updateLock) 
        {
          addInfo("Moves", numMoves);
          addInfo("Score", score);
          addInfo("Move Score", moveScore);
          addInfo("Time", getRunTime());
        }
        updateDelay();
      }
    }

    protected void contentClicked(double x, double y, int mouseButton, int clickCount)
    {
      if (!parameters.isDefined("manual")) return;
      if (gameOver) return;             //game is over
      
      int r=(int)Math.floor(y);
      int c=(int)Math.floor(x);
      if (!inGrid(r,c)) return;         //not in grid

      //click
      if (mouseButton == java.awt.event.MouseEvent.BUTTON1)
      {
        //first click must be a ball
        if (lastR1==-1)
        {
          if (Grid[r][c]==EMPTY) return;
          
          lastR1 = r;
          lastC1 = c;
          update();
        }
        //second click must be the last location or empty
        else
        {
          if (r==lastR1 && c==lastC1)
          {
            //undo
            lastR1 = lastC1 = -1;
            update();
          }
          else
          {
            if (Grid[r][c]!=EMPTY) return;
            
            //check that move is legal
            java.util.List<Integer> path = getPath(lastR1, lastC1, r, c);

            if (path!=null)
            {       
              lastR2 = r;
              lastC2 = c;            
              makeMove(lastR1, lastC1, lastR2, lastC2, path);
            }
          }
        }
      }
    }    
    
    protected void timeout()
    {
      addInfo("Score", "-1 (Timeout)");
      addInfo("Time", getRunTime());
      update();
    }    
    
    protected boolean inGrid(int r, int c)
    {
      return (r>=0 && r<N && c>=0 && c<N);
    }
    
    private int getMoveScore(int balls)
    {
      return balls*balls-7*balls+20;
    }

    private void makeMove(int r1, int c1, int r2, int c2, java.util.List<Integer> path) 
    {
      moveScore = 0;
      
      updateState(); 
      lastR1 = lastC1 = lastR2 = lastC2 = -1;
      updateState();      

      //move ball
      //fast movement
      if (parameters.isDefined("fastMoves"))
      {
        Grid[r2][c2]=Grid[r1][c1];
        Grid[r1][c1]=EMPTY;
        updateState(); 
      }
      //show every step
      else
      {
        int col=Grid[r1][c1];
        int r=r1;
        int c=c1;
        for (int i=path.size()-2; i>=0; i--)
        {
          int loc=path.get(i);
          Grid[r][c]=EMPTY;
          r=loc/N;
          c=loc%N;
          Grid[r][c]=col;
          updateState();
        }
      }
                   
      
      //check if we made any lines and remove them
      moveScore+=removeLines();

      //if we didn't remove any lines or there are no balls left then add new balls      
      if (moveScore==0 || emptyLeft==N*N)
      {
        addNewBalls();
        
        //IMPORTANT: new balls could have introduced new lines, so remove them
        moveScore+=removeLines();

        //we may have removed all balls above, so add some more, just in case
        if (emptyLeft==N*N) addNewBalls();
      }

      numMoves++;
      score+=moveScore;

      updateState();

      if (emptyLeft==0) gameOver=true;
    }


    private void addNewBalls()
    {
      for (int i=0; i<numNextBalls; )
      {
        int r=randomInt(0,N-1);
        int c=randomInt(0,N-1);
        if (Grid[r][c]==EMPTY)
        {
          Grid[r][c]=nextBalls[curBall];
          curBall++;
          i++;
          
          emptyLeft--;
          if (emptyLeft==0) break;
        }        
      }      
    }
    
    
    //Note it is possible to remove multiple lines of different colour in one move
    private int removeLines()
    {
      Set<Integer> toRemove=new HashSet<Integer>();
    
      for (int r=0; r<N; r++)
        for (int c=0; c<N; c++)
        {
          if (Grid[r][c]==EMPTY) continue;
          
          for (int m=0; m<dr2.length; m++)
          {
            int r2=r;
            int c2=c;

            java.util.List<Integer> list=new ArrayList<Integer>();
            list.add(r*N+c);
            int col=Grid[r][c];
            
            while(true)
            {
              r2+=dr2[m];
              c2+=dc2[m];
                           
              if (inGrid(r2,c2) && Grid[r2][c2]==col) list.add(r2*N+c2);
              else
              {
                if (list.size() >= minMatches)
                {
                  for (int i : list) toRemove.add(i);
                }
                break;
              }
            }
          }
        }        
      
      if (toRemove.size()==0) return 0;
      else
      {
        //remove balls
        for (int i : toRemove)
        {
          Grid[i/N][i%N]=EMPTY;
          emptyLeft++;
        }
        updateState();
        return getMoveScore(toRemove.size());
      }
    }
    
    //checks if the move is legal
    //there needs to be a path of empties from (r1,c1) to (r2,c2)
    private java.util.List<Integer> getPath(int r1, int c1, int r2, int c2) 
    {
      int[][] dist=new int[N][N];
      for (int r=0; r<N; r++) for (int c=0; c<N; c++) dist[r][c]=INF;
      
      //propagate paths
      go(r1,c1,0,dist);
      
//       for (int r=0; r<N; r++)
//       {
//         for (int c=0; c<N; c++)
//           System.out.print(dist[r][c]+" ");
//         System.out.println();
//       }
      
      int steps=dist[r2][c2];
      if (steps==INF) return null;     //goal could not be reached
      
      
      //construct path to goal      
      java.util.List<Integer> path=new java.util.ArrayList<Integer>();
      
      int r=r2;
      int c=c2;
      path.add(r*N+c);      
      
      for (int step=steps-1; step>=0; step--)     
        for (int m=0; m<dr.length; m++)
        {
          int r3=r+dr[m];
          int c3=c+dc[m];              
          if (inGrid(r3,c3) && dist[r3][c3]==step)
          {
            r=r3;
            c=c3;
            path.add(r*N+c);
            break;
          }
        }

      //for (int i : path) System.out.println((i/N)+" "+(i%N));
    
      return path;
    }
    
    private void go(int r, int c, int val, int[][] dist)
    {
      if (!inGrid(r,c) || (val>0 && Grid[r][c]!=EMPTY)) return;   //out of bounds or not empty
      if (dist[r][c]<=val) return;    //shorter path already found
            
      dist[r][c]=val;
      for (int m=0; m<dr.length; m++)
        go(r+dr[m],c+dc[m],val+1,dist);
    }
    

    private int callSolution() throws Exception
    {
      writeLine(N);
      writeLine(C);
      flush();
      if (!isReadActive()) return -1;
      
      if (hasVis() && hasDelay()) {
          updateDelay();
      }               

      numMoves = 0;
      score = 0;        
      while ((numMoves < maxMoves) && !gameOver)
      {
        //write grid
        for (int r=0; r<N; r++)
          for (int c=0; c<N; c++)        
            writeLine(""+Grid[r][c]);   

        //write next balls
        for (int i=0; i<numNextBalls; i++)
          writeLine(""+nextBalls[curBall+i]);
          
        writeLine(""+getRunTime());
        flush();
        
      
        startTime();
        String move = readLine();
        stopTime();
          
        //get move
        int r1, c1, r2, c2;
        try
        {
          String[] temp=move.split(" ");
          if (temp.length!=4)
          {
            setErrorMessage("Error reading move: "+move);
            return -1;            
          }
          r1 = Integer.parseInt(temp[0]);
          c1 = Integer.parseInt(temp[1]);
          r2 = Integer.parseInt(temp[2]);
          c2 = Integer.parseInt(temp[3]);
        }
        catch(Exception e)
        {
          setErrorMessage("Error reading move: "+move);
          return -1;
        }
        if (!inGrid(r1,c1) || !inGrid(r2,c2) || (r1==r2 && c1==c2) || Grid[r1][c1]==EMPTY || Grid[r2][c2]!=EMPTY)
        {
          setErrorMessage("Invalid coordinates of move: "+move);
          return -1;          
        }
        
        //check that move is legal
        java.util.List<Integer> path = getPath(r1, c1, r2, c2);
        if (path==null)
        {
          setErrorMessage("Impossible path for move: "+move);
          return -1;
        }
        
        //if we are here then the move was valid
        //apply the move
        lastC1 = c1;
        lastR1 = r1;
        lastC2 = c2;
        lastR2 = r2;
        makeMove(r1, c1, r2, c2, path);
          
        if (debug)
        {
          System.out.println("Move #" + numMoves + ": " + move + " score = " + score);
        }                      
      }
      gameOver=true;

      return score;
    }
     

    protected void paintContent(Graphics2D g)
    {      
      adjustFont(g, Font.SANS_SERIF, Font.PLAIN, String.valueOf("1"), new Rectangle2D.Double(0, 0, 0.5, 0.5));        
      g.setStroke(new BasicStroke(0.005f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
    
      //draw grid      
      for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
        {
            g.setColor(Color.white);
            g.fillRect(c, r, 1, 1);
            g.setColor(Color.gray);       
            g.drawRect(c, r, 1, 1);
        }      
     
      //draw grid
      for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
          if (Grid[r][c]!=EMPTY)
          {
            g.setColor(colors[Grid[r][c]-1]);
            Ellipse2D t = new Ellipse2D.Double(c + 0.1, r + 0.1, 0.8, 0.8);
            g.fill(t);              
          }
        
      //draw selection squares
      if (lastR1!=-1)
      {
        g.setColor(Color.red);
        g.setStroke(new BasicStroke(0.05f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        g.drawRect(lastC1, lastR1, 1, 1);
      }
      if (lastR2!=-1)
      {
        g.setColor(Color.red);
        g.setStroke(new BasicStroke(0.05f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        g.drawRect(lastC2, lastR2, 1, 1);
      }
      
      //draw next balls
      g.setColor(Color.black);       
      drawString(g, "Next Balls", new Rectangle2D.Double(N/3.0, N+0.5, 0, 0));         
      for (int i = 0; i < numNextBalls; i++)
      {
        g.setColor(colors[nextBalls[curBall+i]-1]);
        Ellipse2D t = new Ellipse2D.Double(N-1-i*0.6+0.3, N + 0.3, 0.4, 0.4);
        g.fill(t);     
      }
    }

    private void init()
    {
      numMoves = 0;
      score = 0;  
      moveScore = 0;
      if (hasVis())
      {
        colors = new Color[] {Color.red,Color.cyan,Color.green,Color.blue,Color.orange,Color.magenta,Color.black,Color.pink,Color.gray};           
      
        lastR1 = lastC1 = lastR2 = lastC2 = -1;
        setContentRect(0, 0, N, N+1);       //extra row for next balls   
        setInfoMaxDimension(18, 10); 
        setDefaultDelay(200);

        addInfo("Seed", seed);
        addInfoBreak();
        addInfo("Size N", N);
        addInfo("Colors C", C);
        addInfoBreak();           
        addInfo("Moves", 0);
        addInfo("Move Score", 0);
        addInfo("Score", 0);
        addInfoBreak();
        addInfo("Time", 0);
        update();
      }
    }
    
    public static void main(String[] args) {
        new MarathonController().run(args);
    }
}