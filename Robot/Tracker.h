//
//  Tracker.h
//  Robot
//
//  Created by Nathaniel Clark on 6/12/20.
//  Copyright © 2020 Nathaniel Clark. All rights reserved.
//
#include "Robot.h"
#ifndef Tracker_h
#define Tracker_h

class Tracker
{
public:
    std::vector <Robot> allRobots;
    
    void addRobots(const Robot & r)
    {
        allRobots.push_back(r);
    }
    
    void sort()
    {
        std::sort(allRobots.begin(), allRobots.end());
    }
    
    void print()
    {
        for (long i = allRobots.size()-1; i >= 0; i--)
            std::cout <<"\nRobot " << allRobots[i].robotID << "\nScore " << allRobots[i].score << "\n";
    }
};



#endif /* Tracker_h */
