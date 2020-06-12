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
#include "Robot.h"
#include "RobotConsts.h"


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
    pRobot = new Robot[RobotConsts::NUMROBOTS];
    Robot * temp;   // Used to generate New Robots
    std::vector<allRobots> ALLROBOTS;
    
    
    for(int i = 0; i < RobotConsts::GENERATIONS; i++)
    {
        // Main Robot Loop
        std::cout << "Generation " << i << std::endl;
        for (int j = 0; j < RobotConsts::NUMROBOTS; j++)
            pRobot[j].loop();
        
        // Sort the Robots based off their Scores
        std::sort(pRobot, (pRobot + RobotConsts::NUMROBOTS));
        
        //New Set of Robots Generated
        temp = new Robot[RobotConsts::NUMROBOTS];
        
        // Copys Elite Genes of the best performing robots
        for(int j = 0; j < RobotConsts::ELITEROBOTS; j++)
            temp[j].copyGenes(pRobot[j]);
        
        // Breeds the top half of robots
        for (int j = RobotConsts::ELITEROBOTS; j < RobotConsts::NUMROBOTS/2; j+=2)
            temp[j].breed(pRobot[j],pRobot[j+1]);
        
        // Stores all the Robots ID's and Scores to be sorted later
        for (int j = 0; j < RobotConsts::NUMROBOTS; j++)
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
