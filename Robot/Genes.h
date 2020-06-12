//
//  Genes.h
//  Robot
//
//  Created by Nathaniel Clark on 6/1/20.
//  Copyright © 2020 Nathaniel Clark. All rights reserved.
//

#include "RobotConsts.h"

#ifndef Genes_h
#define Genes_h

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
        
    std::array <int, RobotConsts::GENESIZE> gene = {0,1,2,3,4};
    friend class Robot;
    
public:

    Genes()
    {
        for(int i = 0; i < (RobotConsts::GENESIZE-1); i++)
          gene[i] = (rand() %  3 );
        gene[RobotConsts::GENESIZE-1] = rand() % 4;
    }

    const void print()
    {
      for (int i = 0; i < RobotConsts::GENESIZE; i++)
        std::cout << gene[i] ;
    }
    
    // Copys the genes to be used for checking
    Genes(const Genes & g)
    {
        for(int i = 0; i < (RobotConsts::GENESIZE); i++)
          gene[i] = g.gene[i];
    }
    ~Genes()
    {
    }
    
    void mutateGene()
    {
        for(int i = 0; i < (RobotConsts::GENESIZE-1); i++)
          gene[i] = (rand() %  3 );
        gene[RobotConsts::GENESIZE-1] = rand() % 4;
    }
};

#endif /* Genes_h */
