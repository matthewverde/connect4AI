//
//  c4AI.h
//  connectFour
//
//  Created by Matthew Green on 2/15/18.
//  Copyright (c) 2018 Matthew Green. All rights reserved.
//

#ifndef connectFour_c4AI_h
#define connectFour_c4AI_h

#include <vector>
#include <iostream>

#include "board.h"

using namespace std;

typedef struct Location
{
    int row;
    int col;
}location;

vector<int> getMax(vector<int> arr)
{
    int max = arr[0];
    int maxIndex = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            maxIndex = i;
        }
    }
    
    vector<int> toRet;
    toRet.push_back(max);
    toRet.push_back(maxIndex);
    return toRet;
}

vector<int> getMin(vector<int> arr)
{
    int min = arr[0];
    int minIndex = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
            minIndex = i;
        }
    }
    
    vector<int> toRet;
    toRet.push_back(min);
    toRet.push_back(minIndex);
    return toRet;
}

class c4AI
{
private:
    pieceType myColor;
    pieceType oppColor;
    int maxDepth;
    
    //returns 1 if is a winning loc, and 0 if not, index 0 is AI, index 1 is opponent
    vector<int> checkHorizontal(vector<vector<pieceType> > aBoard, int col, int row)
    {
        int myCount = 0, oppCount = 0, curCol = col, curRow = row;
        vector<int> toRet;
        
        curCol--;
        while(curCol >= 0)
        {
            if(aBoard[curCol][curRow] == myColor)
            {
                myCount++;
            }
            else if(aBoard[curCol][curRow] != empty)
            {
                oppCount++;
            }
            else
            {
                //we reached an empty tile, we dont care anymore
                break;
            }
            
            if(curCol != 0)
            {
                if(aBoard[curCol][curRow] != aBoard[curCol - 1][curRow])
                {
                    break;
                }
            }
            
            curCol--;
        }
        
        curCol = col + 1;
        while(curCol < NUMCOL)
        {
            if(aBoard[curCol][curRow] == myColor)
            {
                myCount++;
            }
            else if(aBoard[curCol][curRow] != empty)
            {
                oppCount++;
            }
            else
            {
                //we reached an empty tile, we dont care anymore
                break;
            }
            
            if(curCol != NUMCOL - 1)
            {
                if(aBoard[curCol][curRow] != aBoard[curCol + 1][curRow])
                {
                    break;
                }
            }
            
            curCol++;
        }
        
        if(myCount == 3)
        {
            toRet.push_back(1);
        }
        else
        {
            toRet.push_back(0);
        }
        
        if(oppCount == 3)
        {
            toRet.push_back(1);
        }
        else
        {
            toRet.push_back(0);
        }
        
        return toRet;
    }
    
    //returns 1 if is a winning loc, and 0 if not, index 0 is AI, index 1 is opponent
    vector<int> checkVertical(vector<vector<pieceType> > aBoard, int col, int row)
    {
        int myCount = 0, oppCount = 0, curCol = col, curRow = row;
        vector<int> toRet;
        
        curRow--;
        while(curRow >= 0)
        {
            if(aBoard[curCol][curRow] == myColor)
            {
                myCount++;
            }
            else if(aBoard[curCol][curRow] != empty)
            {
                oppCount++;
            }
            else
            {
                //we reached an empty tile, we dont care anymore
                break;
            }
            
            if(curRow != 0)
            {
                if(aBoard[curCol][curRow] != aBoard[curCol][curRow - 1])
                {
                    break;
                }
            }
            
            curRow--;
        }
        
        curRow = row + 1;
        while(curRow < NUMROW)
        {
            if(aBoard[curCol][curRow] == myColor)
            {
                myCount++;
            }
            else if(aBoard[curCol][curRow] != empty)
            {
                oppCount++;
            }
            else
            {
                //we reached an empty tile, we dont care anymore
                break;
            }
            
            if(curRow != NUMROW - 1)
            {
                if(aBoard[curCol][curRow] != aBoard[curCol][curRow + 1])
                {
                    break;
                }
            }
            
            curRow++;
        }
        
        if(myCount == 3)
        {
            toRet.push_back(1);
        }
        else
        {
            toRet.push_back(0);
        }
        
        if(oppCount == 3)
        {
            toRet.push_back(1);
        }
        else
        {
            toRet.push_back(0);
        }
        
        return toRet;
    }
    
    //returns 1 if is a winning loc, and 0 if not, index 0 is AI, index 1 is opponent
    vector<int> checkPosSlope(vector<vector<pieceType> > aBoard, int col, int row)
    {
        int myCount = 0, oppCount = 0, curCol = col, curRow = row;
        vector<int> toRet;
        
        //check down and to the left
        curRow--;
        curCol--;
        while(curRow >= 0 && curCol >= 0)
        {
            if(aBoard[curCol][curRow] == myColor)
            {
                myCount++;
            }
            else if(aBoard[curCol][curRow] != empty)
            {
                oppCount++;
            }
            else
            {
                //we reached an empty tile, we dont care anymore
                break;
            }
            
            if(curCol != 0 && curRow != 0)
            {
                if(aBoard[curCol][curRow] != aBoard[curCol - 1][curRow - 1])
                {
                    break;
                }
            }
            
            curCol--;
            curRow--;
        }
        
        //check up and to the right
        curRow = row + 1;
        curCol = col + 1;
        while(curRow < NUMROW && curCol < NUMCOL)
        {
            if(aBoard[curCol][curRow] == myColor)
            {
                myCount++;
            }
            else if(aBoard[curCol][curRow] != empty)
            {
                oppCount++;
            }
            else
            {
                //we reached an empty tile, we dont care anymore
                break;
            }
            
            if(curRow != NUMROW - 1 && curCol != NUMCOL - 1)
            {
                if(aBoard[curCol][curRow] != aBoard[curCol + 1][curRow + 1])
                {
                    break;
                }
            }
            
            curRow++;
            curCol++;
        }
        
        if(myCount == 3)
        {
            toRet.push_back(1);
        }
        else
        {
            toRet.push_back(0);
        }
        
        if(oppCount == 3)
        {
            toRet.push_back(1);
        }
        else
        {
            toRet.push_back(0);
        }
        
        return toRet;
    }
    
    //returns 1 if is a winning loc, and 0 if not, index 0 is AI, index 1 is opponent
    vector<int> checkNegSlope(vector<vector<pieceType> > aBoard, int col, int row)
    {
        int myCount = 0, oppCount = 0, curCol = col, curRow = row;
        vector<int> toRet;
        
        //check down and to the right
        curRow--;
        curCol++;
        while(curRow >= 0 && curCol < NUMCOL)
        {
            if(aBoard[curCol][curRow] == myColor)
            {
                myCount++;
            }
            else if(aBoard[curCol][curRow] != empty)
            {
                oppCount++;
            }
            else
            {
                //we reached an empty tile, we dont care anymore
                break;
            }
            
            if(curCol != NUMCOL - 1 && curRow != 0)
            {
                if(aBoard[curCol][curRow] != aBoard[curCol + 1][curRow - 1])
                {
                    break;
                }
            }
            
            curCol++;
            curRow--;
        }
        
        //check up and to the left
        curRow = row + 1;
        curCol = col - 1;
        while(curRow < NUMROW && curCol >= 0)
        {
            if(aBoard[curCol][curRow] == myColor)
            {
                myCount++;
            }
            else if(aBoard[curCol][curRow] != empty)
            {
                oppCount++;
            }
            else
            {
                //we reached an empty tile, we dont care anymore
                break;
            }
            
            if(curRow != NUMROW - 1 && curCol != 0)
            {
                if(aBoard[curCol][curRow] != aBoard[curCol - 1][curRow + 1])
                {
                    break;
                }
            }
            
            curRow++;
            curCol--;
        }
        
        if(myCount == 3)
        {
            toRet.push_back(1);
        }
        else
        {
            toRet.push_back(0);
        }
        
        if(oppCount == 3)
        {
            toRet.push_back(1);
        }
        else
        {
            toRet.push_back(0);
        }
        
        return toRet;
    }
    
    int getBoardScore(vector<vector<pieceType> > aBoard)
    {
        vector< vector<location> > winningLocs = findWinningLocations(aBoard);
        
        int myScore = (int)winningLocs[0].size() * 100;
        int oppScore = (int)winningLocs[1].size() * 100;
        
        return myScore - oppScore;
    }
    
    //TODO add pruning
    int minMax(board state, bool myTurn, int depth, int &indexToPick)
    {
        board newBoard = board(state);
        vector<int> stateScores;
        int winner = 0;
        int i = 0;
        
        for(i = 0; i < NUMCOL; i++)
        {
            if(state.getHeightAt(i) != NUMROW)
            {
                if(myTurn)
                {
                    winner = newBoard.placePieceOnCol(i, myColor);
                    if(winner == 10)
                    {
                        stateScores.push_back(1000);
                    }
                    else if(depth == maxDepth)
                    {
                        stateScores.push_back(getBoardScore(newBoard.getBoardState()));
                    }
                    else
                    {
                        stateScores.push_back(minMax(newBoard, false, depth + 1, indexToPick));
                    }
                    newBoard.removeTopAtCol(i);
                }
                else
                {
                    winner = newBoard.placePieceOnCol(i, oppColor);
                    
                    if(winner == 10)
                    {
                        stateScores.push_back(-1000);
                    }
                    else if(depth == maxDepth)
                    {
                        stateScores.push_back(getBoardScore(newBoard.getBoardState()));
                    }
                    else
                    {
                        stateScores.push_back(minMax(newBoard, true, depth + 1, indexToPick));
                    }
                    newBoard.removeTopAtCol(i);
                }
            }
            else
            {
                if(myTurn)
                {
                    stateScores.push_back(-1000000);
                }
                else
                {
                    stateScores.push_back(1000000);
                }
            }
        }
        
        vector<int> bestScore;
        
        if(stateScores.size() == 0)
        {
            if(myTurn)
            {
                return -100000;
            }
            else
            {
                return 100000;
            }
        }
        
        if(depth == 0)
        {
            int num = 0;
            num++;
        }
        
        if(myTurn)
        {
            bestScore = getMax(stateScores);
            indexToPick = bestScore[1];
            return bestScore[0];
        }
        bestScore = getMin(stateScores);
        indexToPick = bestScore[1];
        return bestScore[0];
    }
    
public:
    
    board curState;
    
    c4AI(pieceType setColor, int depth)
    {
        if(setColor == blue)
        {
            oppColor = red;
        }
        else
        {
            oppColor = blue;
        }
        
        myColor = setColor;
        maxDepth = depth;
    }
    
    int chooseCol()
    {
        int colToChoose = 0;
        int score = 0;
        score = minMax(curState, true, 0, colToChoose);
        cout << "AI current score: " << score << endl;
        return colToChoose;
    }
    
    //board access is col row...
    vector< vector<location> > findWinningLocations(vector<vector<pieceType> > aBoard)
    {
        vector<location> myWinningLocs, oppWinningLocs;
        vector<int> winTup;
        bool meWin, oppWin;
        location loc;
        
        
        for(int i = 0; i < NUMCOL; i++)
        {
            for(int j = 0; j < NUMROW; j++)
            {
                meWin = false;
                oppWin = false;
                loc.col = i;
                loc.row = j;
                //here we want to check empty locations, because these are the potential winning locations
                if(aBoard[i][j] == empty)
                {
                    winTup = checkHorizontal(aBoard, i, j);
                    if(winTup[0])
                    {
                        meWin = true;
                    }
                    if(winTup[1])
                    {
                        oppWin = true;
                    }
                    
                    winTup = checkVertical(aBoard, i, j);
                    if(winTup[0])
                    {
                        meWin = true;
                    }
                    if(winTup[1])
                    {
                        oppWin = true;
                    }
                    
                    winTup = checkPosSlope(aBoard, i, j);
                    if(winTup[0])
                    {
                        meWin = true;
                    }
                    if(winTup[1])
                    {
                        oppWin = true;
                    }
                    
                    winTup = checkNegSlope(aBoard, i, j);
                    if(winTup[0])
                    {
                        meWin = true;
                    }
                    if(winTup[1])
                    {
                        oppWin = true;
                    }
                    
                    
                }
                
                if(meWin)
                {
                    myWinningLocs.push_back(loc);
                }
                if(oppWin)
                {
                    oppWinningLocs.push_back(loc);
                }
            }
        }
        
        vector< vector<location> > toRet;
        toRet.push_back(myWinningLocs);
        toRet.push_back(oppWinningLocs);
        
        return toRet;
    }
    
    void setState(board curBoard)
    {
        this->curState = board(curBoard);
        curState.placePieceOnCol(0, red);
        curState.placePieceOnCol(1, red);
        cout << "Ai Board" << endl;
        curState.printBoardState();
    }
    
};


#endif
