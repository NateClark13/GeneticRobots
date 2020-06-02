//
//  main.cpp
//  Robot
//
//  Created by Nathaniel Clark on 2/17/20.
//  Copyright © 2020 Nathaniel Clark. All rights reserved.
//
// Nate Clark

//Max genes for perfect robot?


#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
#include <array>
#include <iterator>
#include <cmath>
#include <fstream>

// CONTROLABLE CONSTANTS
const int NUMROBOTS = 100;
const int GENERATIONS = 1000;
const int BOARDSIZE = 100;  // OPTIONS 100, 400, 900 / OR any size that is a perfect square
const int NUMGENES = 16;    // 324 for the best Performance / Must be Divisable by 2
const int ELITEROBOTS = 10; // Percent of Robots that are considered the best based off fitness score
const int BATTERYLEVEL = 10; // Amount of battery or spaces a robot can move
const int MUTATIONRATE = 5; // Rate at which genetic mutations occur

// DO NOT CHANGE -----------------------------
const int GENESIZE = 5;
const int ROBOTTOKEN = 7;
const int UP = -10;
const int RIGHT = 1;
const int DOWN = 10;
const int LEFT = -1;
const int ROBOTSMUTATED = (NUMROBOTS * MUTATIONRATE) / 100;
// -------------------------------------------



class Board
{
private:
    int bSqurt;
public:
    std::array<int, BOARDSIZE> board;
    
    Board()
    {
        bSqurt = sqrt(BOARDSIZE);
        
        for (int i = 0; i < BOARDSIZE; i++)
        {
            if (i < bSqurt)
                board[i] = 0;
            else if( i % bSqurt == 0)
                board[i] = 0;
            else if (i % bSqurt == (bSqurt - 1))
                board[i] = 0;
            else if (i >= (BOARDSIZE - bSqurt))
                board[i] = 0;
            else
                board[i] = (rand() %  2 ) + 1;
        }
    }

    void print()
    {
      for(int i = 1; i < BOARDSIZE+1; i++)
      {
        std::cout << board[i-1] << " ";
        if(i%bSqurt == 0)
        std::cout << std::endl;
      }
    }

};

class Genes
{
private:
    // gene[5] = { up, right, down, left, move}
    // Board Positions
    // 0 == Wall
    // 1 == Empty Space
    // 2 == Batery
    // Move Positions
    // 0 Up
    // 1 Right
    // 2 Down
    // 3 Left
        
    std::array <int, GENESIZE> gene = {0,1,2,3,4};
    friend class Robot;
    
public:

    Genes()
    {
        for(int i = 0; i < (GENESIZE-1); i++)
          gene[i] = (rand() %  3 );
        gene[GENESIZE-1] = rand() % 4;
    }

    const void print()
    {
      for (int i = 0; i < GENESIZE; i++)
        std::cout << gene[i] ;
    }
    
    // Copys the genes to be used for checking
    Genes(const Genes & g)
    {
        for(int i = 0; i < (GENESIZE); i++)
          gene[i] = g.gene[i];
    }
    ~Genes()
    {
    }
    
    void mutateGene()
    {
        for(int i = 0; i < (GENESIZE-1); i++)
          gene[i] = (rand() %  3 );
        gene[GENESIZE-1] = rand() % 4;
    }
};




class Robot
{
    private:
    std::array<Genes, NUMGENES> genes;
    Board board;
    int battery;
    int position;
    int positionMove;
    std::array <int, GENESIZE> sensor;

    public:
    int robotID;
    static int sRobotID;
    int score;
        
    Robot()
    {
        battery = BATTERYLEVEL;
        score = 0;
        randomStart();
    }

    void loop()
    {
      robotID = sRobotID++;
      while(battery!= 0)
      {
        checkBoard();
        move();
      }
    }
    
    ~Robot()
    {
    }
    
    // Comparison Overload Used for sorting Robots
    friend bool operator < (Robot const & a, Robot const & b) { return a.score > b.score; }
    
    // Copies the first half of Robot 1's genes and second half of Robot 2's genes
    void breed (const Robot & r1, const Robot & r2)
    {
        for (int i = 0; i < NUMGENES; i+=2)
        {
            int randomGene = rand()%NUMGENES;
            genes[i].gene = r1.genes[randomGene].gene;
            randomGene = rand()%NUMGENES;
            genes[i+1].gene = r2.genes[randomGene].gene;
        }
    }
    
    void copyGenes (const Robot & r) { genes = r.genes; }

    // Sets the starting position of the robot to a random location
    void randomStart()
    {
        do { position = rand()% 99; } while(position % 10 == 0 || position % 10 == 9 || position < 10 || position > 89);
        // Set Player token to correct Position
        board.board[position] = ROBOTTOKEN;
    }
    
    // Moves Robot around the Board
    void move()
    {
        // Stores Robots position for error checking
        int oldPosition = position;
        
        // Reduce Battery Each Turn
        battery--;
        
        // Checks if positionMove is Valid and matched a Gene
        if (positionMove != 5)
        {
            if (positionMove == 0) { position += UP; }
            if (positionMove == 1) { position += RIGHT; }
            if (positionMove == 2) { position += DOWN; }
            if (positionMove == 3) { position += LEFT; }
            
            // Reset Position if robot moves into a wall
            if (board.board[position] == 0)
                position = oldPosition;
            else
            {
                // Recharge Battery
                if (board.board[position] == 2)
                {
                    battery += 2;
                    score++;
                }
                // Sets Board Position to an Empty Token
                board.board[oldPosition] = 1;
                // Moves Robot token to the correct Position
                board.board[position] = ROBOTTOKEN;
            }
        }
    }
    
    // Sets the sensors state to locations around the robot Token
    void setSensor()
    {
        sensor[0] = board.board[position + UP];
        sensor[1] = board.board[position + RIGHT];
        sensor[2] = board.board[position + DOWN];
        sensor[3] = board.board[position + LEFT];
        sensor[4] = 5;
    }

    //Checks the position of the board and genes to see if there is a match. If true it sets the final gene to the position move.

    void checkBoard()
    {
        setSensor();
        
        // Runs through the Set of Genes and checks if they match the current board state, if so position move is set to the move gene
        for (int i = 0; i < NUMGENES; i ++)
        {
            //Sets the sensors move position to the same as the gene so it can check if the contents are ==
            sensor[4] = genes[i].gene[4];
            
            if (sensor == genes[i].gene)
            {
                //Set Position Move = To the move gene
                positionMove = genes[i].gene[GENESIZE-1];
                
                /* Print out Matching Genes;
                std::cout << "\nSENSOR" << std::endl;
                for (int i = 0; i < GENESIZE; i++)
                   std::cout << sensor[i];
                std::cout << "\nGENES" << std::endl;
                genes[i].print();
                std::cout << std::endl;
                 */
                
                break;
            }
            // If No Matches Set position move to an invalid move
            else {positionMove = 5;}
        }
    }
    
    void mutateRobot()
    {
        int g = rand()%NUMGENES;
        genes[g].mutateGene();
    }
};

int Robot::sRobotID = 0;

struct allRobots
{
public:
    int allRobotID;
    int allRobotScore;
};

bool compareByLength(const allRobots &a, const allRobots &b) { return a.allRobotScore < b.allRobotScore; }

int main()
{
    srand(unsigned(time(NULL)));
    std::ios_base::sync_with_stdio(false);

    
    Robot * pRobot; // Main Robot pointer
    pRobot = new Robot[NUMROBOTS];
    Robot * temp;   // Used to generate New Robots
    std::vector<allRobots> ALLROBOTS;
    
    
    for(int i = 0; i < GENERATIONS; i++)
    {
        // Main Robot Loop
        std::cout << "Generation " << i << std::endl;
        for (int j = 0; j < NUMROBOTS; j++)
            pRobot[j].loop();
        
        // Sort the Robots based off their Scores
        std::sort(pRobot, (pRobot + NUMROBOTS));
        
        //New Set of Robots Generated
        temp = new Robot[NUMROBOTS];
        
        // Copys Elite Genes of the best performing robots
        for(int j = 0; j < ELITEROBOTS; j++)
            temp[j].copyGenes(pRobot[j]);
        
        // Breeds the top half of robots
        for (int j = ELITEROBOTS; j < NUMROBOTS/2; j+=2)
            temp[j].breed(pRobot[j],pRobot[j+1]);
        
        // Stores all the Robots ID's and Scores to be sorted later
        for (int j = 0; j < NUMROBOTS; j++)
            ALLROBOTS.push_back({pRobot[j].robotID, pRobot[j].score});
        
        
        // Swaps the Old robots for the New Robots With the bottom half of Randomly Generated Genes
        std::swap(pRobot, temp);
        
        // Deletes old Robots
        delete [] temp;
    }
    
    
    // OUTPUT TO FILE COUT TOO SLOW LMAO
    std::ofstream output;
    output.open("/Users/blu/Documents/Code/C++/Personal/Robot/RobotResults.txt");
    
    std::cout << "WRITING RESULTS TO FILE....." << std::endl;
    // Sorts all the generation of robots
    std::sort(ALLROBOTS.begin(), ALLROBOTS.end(), compareByLength);
    for (long i = ALLROBOTS.size()-1; i >= 0; i--)
        output << "\nRobot " << ALLROBOTS[i].allRobotID << "\nScore " << ALLROBOTS[i].allRobotScore << "\n";
    std::cout << "DONE!" << std::endl;
}
