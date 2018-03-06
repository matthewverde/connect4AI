//
//  main.cpp
//  connectFour
//
//  Created by Matthew Green on 2/12/18.
//  Copyright (c) 2018 Matthew Green. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "board.h"
#include "c4AI.h"

using namespace std;

#define RANDMOVES 3

int main(int argc, const char * argv[]) {
    board *myBoard = new board();
    c4AI *ai = new c4AI(blue, 3);
    int retVal = 0, input = -1, aiPlacement = 0, redWins = 0, blueWins = 0, numMoves = 0, ffTries = 0;
    vector<char> colWin;
    vector<int> moves;
    srand(time(NULL));
    myBoard->printBoardState();
    bool redFF = false, blueFF = false;
    
        while(1)
        {
        
            //cout << "Choose col To place piece" << endl;
            input = -1;
            retVal = -1;
            while(input == -1 || retVal == -1)
            {
                cin >> input;
                input = input - 1;
                retVal = myBoard->placePieceOnCol(input, red);
            }
            
            ai->curState.placePieceOnCol(input, red);
            
            myBoard->printBoardState();
            
            //see if red won
            if(retVal == 10)
            {
                cout << "Red wins" << endl;
                redWins++;
                moves.push_back(numMoves);
                colWin.push_back('r');
                break;
            }
            else if(retVal == -1)
            {
                redFF = true;
                ffTries++;
            }
        

            cout << "Blue AI is thinking" << endl;
            aiPlacement = ai->chooseCol();
            
            retVal = myBoard->placePieceOnCol(aiPlacement, blue);
            ai->curState.placePieceOnCol(aiPlacement, blue);
            cout << "AI placed on column: " << aiPlacement + 1 << endl;
        
            myBoard->printBoardState();
            numMoves++;
            
            //see if blue won
            if(retVal == 10)
            {
                cout << "Blue wins" << endl;
                blueWins++;
                moves.push_back(numMoves);
                colWin.push_back('b');
                break;
            }
            else if(retVal == -1)
            {
                blueFF = true;
                ffTries++;
            }
            
        }
    
    cout << "*******STATS*******" << endl;
    int totalMoves = 0;
    for(int j = 0; j < moves.size(); j++)
    {
        cout << "Game " << j << ": ";
        if(colWin[j] == 'b')
        {
            cout << "Blue won in " << moves[j] << " moves" << endl;
        }
        else if(colWin[j] == 'r')
        {
            cout << "Red won in " << moves[j] << " moves" << endl;
        }
        else
        {
            cout << "Draw in " << moves[j] << " moves" << endl;
        }
        totalMoves += moves[j];
    }
    
    cout << "Blue Wins:\t" << blueWins << endl;
    cout << "Red Wins:\t" << redWins << endl;
    cout << "Total Moves:\t" << totalMoves << endl;
    cout << "Average Moves:\t" << (double)totalMoves / (double)moves.size() << endl;
    
    return 0;
}
