//
//  RobotConsts.h
//  Robot
//
//  Created by Nathaniel Clark on 6/12/20.
//  Copyright © 2020 Nathaniel Clark. All rights reserved.
//

#ifndef RobotConsts_h

namespace RobotConsts
{
    // CONTROLABLE CONSTANTS
    const int NUMROBOTS = 100;
    const int GENERATIONS = 100;
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
}

#define RobotConsts_h


#endif /* RobotConsts_h */
