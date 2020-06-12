//
//  Board.h
//  Robot
//
//  Created by Nathaniel Clark on 6/1/20.
//  Copyright © 2020 Nathaniel Clark. All rights reserved.
//

#include "RobotConsts.h"

#ifndef Board_h
#define Board_h

class Board
{
private:
    int bSqurt;
public:
    std::array<int, RobotConsts::BOARDSIZE> board;
    
    Board()
    {
        bSqurt = sqrt(RobotConsts::BOARDSIZE);
        
        for (int i = 0; i < RobotConsts::BOARDSIZE; i++)
        {
            if (i < bSqurt)
                board[i] = 0;
            else if( i % bSqurt == 0)
                board[i] = 0;
            else if (i % bSqurt == (bSqurt - 1))
                board[i] = 0;
            else if (i >= (RobotConsts::BOARDSIZE - bSqurt))
                board[i] = 0;
            else
                board[i] = (rand() %  2 ) + 1;
        }
    }

    void print()
    {
      for(int i = 1; i < RobotConsts::BOARDSIZE+1; i++)
      {
        std::cout << board[i-1] << " ";
        if(i%bSqurt == 0)
        std::cout << std::endl;
      }
    }

};

#endif /* Board_h */
