//
//  Robot.h
//  Robot
//
//  Created by Nathaniel Clark on 6/1/20.
//  Copyright © 2020 Nathaniel Clark. All rights reserved.
//

#ifndef Robot_h
#define Robot_h
#include "Genes.h"
#include "Board.h"
#include "RobotConsts.h"

class Robot
{
    private:
    std::array<Genes, RobotConsts::NUMGENES> genes;
    Board board;
    int battery;
    int position;
    int positionMove;
    std::array <int, RobotConsts::GENESIZE> sensor;

    public:
    int robotID;
    static int sRobotID;
    int score;
        
    Robot()
    {
        battery = RobotConsts::BATTERYLEVEL;
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
        for (int i = 0; i < RobotConsts::NUMGENES; i+=2)
        {
            int randomGene = rand()%(RobotConsts::NUMGENES);
            genes[i].gene = r1.genes[randomGene].gene;
            randomGene = rand()%(RobotConsts::NUMGENES);
            genes[i+1].gene = r2.genes[randomGene].gene;
        }
    }
    
    void copyGenes (const Robot & r) { genes = r.genes; }

    // Sets the starting position of the robot to a random location
    void randomStart()
    {
        do { position = rand()% 99; } while(position % 10 == 0 || position % 10 == 9 || position < 10 || position > 89);
        // Set Player token to correct Position
        board.board[position] = RobotConsts::ROBOTTOKEN;
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
            if (positionMove == 0) { position += RobotConsts::UP; }
            if (positionMove == 1) { position += RobotConsts::RIGHT; }
            if (positionMove == 2) { position += RobotConsts::DOWN; }
            if (positionMove == 3) { position += RobotConsts::LEFT; }
            
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
                board.board[position] = RobotConsts::ROBOTTOKEN;
            }
        }
    }
    
    // Sets the sensors state to locations around the robot Token
    void setSensor()
    {
        sensor[0] = board.board[position + RobotConsts::UP];
        sensor[1] = board.board[position + RobotConsts::RIGHT];
        sensor[2] = board.board[position + RobotConsts::DOWN];
        sensor[3] = board.board[position + RobotConsts::LEFT];
        sensor[4] = 5;
    }

    //Checks the position of the board and genes to see if there is a match. If true it sets the final gene to the position move.

    void checkBoard()
    {
        setSensor();
        
        // Runs through the Set of Genes and checks if they match the current board state, if so position move is set to the move gene
        for (int i = 0; i < RobotConsts::NUMGENES; i ++)
        {
            //Sets the sensors move position to the same as the gene so it can check if the contents are ==
            sensor[4] = genes[i].gene[4];
            
            if (sensor == genes[i].gene)
            {
                //Set Position Move = To the move gene
                positionMove = genes[i].gene[RobotConsts::GENESIZE-1];
                
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
        int g = rand()%RobotConsts::NUMGENES;
        genes[g].mutateGene();
    }
};

int Robot::sRobotID = 0;

#endif /* Robot_h */
