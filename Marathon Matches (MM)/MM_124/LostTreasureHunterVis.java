import java.util.*;

import com.topcoder.marathon.*;

public class LostTreasureHunterVis extends MarathonTester {

int numChambers = 100;
int treasureValue;
int stepCost;
int maxChambers;
int maxTreasurePickup;
int numSteps = 0;
int numTreasures = 0;
boolean[][] adj = new boolean[numChambers][numChambers];
boolean[] gen = new boolean[numChambers];
int[] tCount = new int[numChambers];
int[][] paths = new int[numChambers][0];
int chamberCount = 0;
int[] nextChamber = new int[500];
int curChamber = 0;
int lastChamber = 1;
int nextChamberSelection = 0;

protected void generate() {
  treasureValue = randomInt(10, 100);
  stepCost = randomInt(1, treasureValue);
  maxChambers = randomInt(10, 100);
  maxTreasurePickup = randomInt(1, 10);
  curChamber = 0;
  lastChamber = 1;
  nextChamber[0] = 0;
  while (curChamber < lastChamber) {
    generateChamber(nextChamber[curChamber]);
    curChamber++;
  }
  for (int i = 0; i < numChambers; i++) {
    ArrayList<Integer> p = new ArrayList<Integer>();
    for (int j = 0; j < numChambers; j++)
      if (i != j && adj[i][j])
        p.add(j);
    paths[i] = new int[p.size()];
    for (int j = 0; j < p.size(); j++)
      paths[i][j] = p.get(j);
  }
}

private void generateChamber(int c) {
  if (gen[c]) return;
  tCount[c] = randomInt(0, 50);
  int pathCount = randomInt(2, 4);
  int i = 0;
  int tries = 0;
  while (i < pathCount) {
    int n = randomInt(0, maxChambers - 1);
    if (n == c || adj[c][n]) {
      tries++;
      if (tries>maxChambers*2) break;
      continue;
    }
    tries = 0;
    adj[c][n] = adj[n][c] = true;
    nextChamber[lastChamber] = n;
    lastChamber++;
    i++;
  }
  chamberCount++;
  gen[c] = true;
}

private boolean moveNextChamber() {
  if (nextChamberSelection < -1 || nextChamberSelection >= paths[curChamber].length) {
    return false;
  }
  if (debug) System.out.println("Taking path " + nextChamberSelection);
  if (nextChamberSelection == -1) {
    if (lastChamber == -1) return false;
    int temp = lastChamber;
    lastChamber = curChamber;
    curChamber = temp;
  } else {    
    lastChamber = curChamber;
    curChamber = paths[curChamber][nextChamberSelection];
  }
  if (debug) {
    System.out.println("Moving to chamber " + curChamber);
  }
  return true;
}

private void errorMessage(String error) {
  System.out.println(error);
}

protected double run() throws Exception {
  curChamber = 0;
  lastChamber = -1;
  if (debug) {
    System.out.println("Treasure Value: " + treasureValue);
    System.out.println("Step Cost: " + stepCost);
    System.out.println("Chamber Count: " + chamberCount);
    System.out.println("Max Treasure Pickup: " + maxTreasurePickup);
    System.out.println("");
  }
  writeLine(treasureValue);
  writeLine(stepCost);
  writeLine(chamberCount);
  writeLine(maxTreasurePickup);
  flush();
  int ret;
  try {
    ret = callNextStep();
  } catch (Exception e) {
    return fatalError("Error calling nextStep()");
  }
  while (ret != -1 && numSteps < 1000) {
    if (tCount[curChamber] < ret || ret < -1 || ret > maxTreasurePickup) {
      return fatalError("Invalid return value for number of treasures to pick up.");
    }
    tCount[curChamber] -= ret;
    numTreasures += ret;
    if (!moveNextChamber()) {
      return fatalError("Invalid return value for next chamber selection:" + nextChamberSelection);
    }
    numSteps++;
    try {
      ret = callNextStep();
    } catch (Exception e) {
      if (debug) {
        System.out.println(e.toString());
      }
      return fatalError("Error calling nextStep()");
    }
  }
  return Math.max(0, numTreasures * treasureValue - numSteps * stepCost);
}

protected boolean isMaximize() {
  return true;
}

private int callNextStep() throws Exception {
  if (debug) {
    System.out.println("Steps = " + numSteps);
    System.out.println("TreasureCount = " + tCount[curChamber]);
    System.out.println("PathCount = " + paths[curChamber].length);
    System.out.println("Collected = " + numTreasures);
    System.out.println("Score = " + (numTreasures * treasureValue - numSteps * stepCost));
  }
  writeLine(tCount[curChamber]);
  writeLine(paths[curChamber].length);
  writeLine("" + getRunTime());
  flush();
  startTime();
  int ret = readLineToInt();
  if (ret > -1)
    nextChamberSelection = readLineToInt();
  stopTime();
  if (debug) {
    System.out.println("Treasures taken = " + ret);
    System.out.println("");
  }
  return ret;
}

public static void main(String[] args) {
  new MarathonController().run(args);
}


}
