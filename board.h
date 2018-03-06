//
//  board.h
//  connectFour
//
//  Created by Matthew Green on 2/12/18.
//  Copyright (c) 2018 Matthew Green. All rights reserved.
//

#ifndef connectFour_board_h
#define connectFour_board_h

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>

#define NUMCOL 7
#define NUMROW 6
#define TOWIN 4

using namespace std;

enum pieceType {blue, red, empty};

class column
{
private:
    vector<pieceType> col;
    int height;
    
public:
    column()
    {
        pieceType emptyPiece = empty;
        this->height = 0;
        
        for(int i = 0; i < NUMROW; i++)
        {
            col.push_back(emptyPiece);
        }
    }
    
    //places a piece and returns the location within the column the piece landed
    //returns -1 if the column is full
    int placePiece(pieceType color)
    {
        //if the column is full return -1
        if(height >= NUMROW)
        {
            return -1;
        }
        
        col[height] = color;
        height++;
        
        return height;
    }
    
    void removeTop()
    {
        height--;
        col[height] = empty;
    }
    
    pieceType at(int rowNum)
    {
        return col[rowNum];
    }
    
    int getHeight()
    {
        return height;
    }
    
    void setHeight(int newHeight)
    {
        height = newHeight;
    }
    
    vector<pieceType> getColState()
    {
        return col;
    }
};

//the way the board is set up, the indexing is more or less set up at (col, row), instead of the usual (row, col)
class board
{
private:
    vector< column* > curBoard;
    int lastCol;
    int lastRow;
    pieceType lastColor;
    
    //returns the color of the piece that won, else returns empty
    bool isGameOver()
    {
        bool isWinner = false;
        
        isWinner = checkVertical(lastColor);
        
        if(isWinner)
        {
            return true;
        }
        
        isWinner = checkHorizontal(lastColor);
        
        if(isWinner)
        {
            return true;
        }
        
        isWinner = checkNegSlope(lastColor);
        
        if(isWinner)
        {
            return true;
        }
        
        isWinner = checkPosSlope(lastColor);
        
        if(isWinner)
        {
            return true;
        }
        
        
        
        return false;
    }
    
    bool checkVertical(const pieceType color)
    {
        int colInARow = 0;
        int columnNum = lastCol;
        pieceType curColor;
        
        //scan from bottom up
        for(int i = 0; i < NUMROW; i++)
        {
            curColor = this->curBoard[columnNum]->at(i);
            
            if(curColor == color)
            {
                colInARow++;
            }
            else
            {
                colInARow = 0;
            }
            
            if(colInARow == TOWIN)
            {
                return true;
            }
        }
        
        return false;
    }
    
    bool checkHorizontal(const pieceType color)
    {
        int colInARow = 0;
        
        //scan from left to right
        for(int i = 0; i < NUMCOL; i++)
        {
            if(this->curBoard[i]->at(lastRow) == color)
            {
                colInARow++;
            }
            else
            {
                colInARow = 0;
            }
            
            if(colInARow == TOWIN)
            {
                return true;
            }
        }
        
        return false;
    }
    
    bool checkNegSlope(const pieceType color)
    {
        int topCol, topRow, botCol, botRow;
        int curRow = lastRow, curCol = lastCol;
        
        
        ///////////////////////////////////////////////////
        //set up diagonal start and end locations
        while(curCol > 0 && curRow < NUMROW - 1)
        {
            curCol--;
            curRow++;
        }
        //set the location of the top point of the diagonal
        topCol = curCol;
        topRow = curRow;
        
        //reset the start pointers
        curRow = lastRow;
        curCol = lastCol;
        
        while(curCol < NUMCOL - 1 && curRow > 0)
        {
            curCol++;
            curRow--;
        }
        
        botCol = curCol;
        botRow = curRow;
        //end set up
        //////////////////////////////////////////////////
        
        curRow = topRow;
        int colInARow = 0;
        pieceType curColor;
        
        //start from the top left and work down and to the right
        for(int i = topCol; i < abs(topCol - botCol) + 1; i++)
        {
            curColor = this->curBoard[i]->at(curRow);
            
            if(curColor == color)
            {
                colInARow++;
            }
            else
            {
                colInARow = 0;
            }
            
            if(colInARow == TOWIN)
            {
                return true;
            }
            
            curRow--;
        }
        
        return false;
    }
    
    bool checkPosSlope(const pieceType color)
    {
        int topCol, topRow, botCol, botRow;
        int curRow = lastRow, curCol = lastCol;
        
        
        ///////////////////////////////////////////////////
        //set up diagonal start and end locations
        while(curCol > 0 && curRow > 0)
        {
            curCol--;
            curRow--;
        }
        //set the location of the top point of the diagonal
        botCol = curCol;
        botRow = curRow;
        
        //reset the start pointers
        curRow = lastRow;
        curCol = lastCol;
        
        while(curCol < NUMCOL - 1 && curRow < NUMROW - 1)
        {
            curCol++;
            curRow++;
        }
        
        topCol = curCol;
        topRow = curRow;
        //end set up
        //////////////////////////////////////////////////
        
        curRow = botRow;
        int colInARow = 0;
        pieceType curColor;
        
        //start from the bottom left and work up and to the right
        for(int i = botCol; i < abs(topCol - botCol) + 1; i++)
        {
            curColor = this->curBoard[i]->at(curRow);
            
            if(curColor == color)
            {
                colInARow++;
            }
            else
            {
                colInARow = 0;
            }
            
            if(colInARow == TOWIN)
            {
                return true;
            }
            
            curRow++;
        }
        
        return false;
    }
    
public:
    
    board()
    {
        for(int i = 0; i < NUMCOL; i++)
        {
            column *newCol = new column;
            curBoard.push_back(newCol);
        }
        
        lastCol = -1;
        lastRow = -1;
    }
    
    board(const board& toCopy)
    {
        pieceType pieceToAdd;
        int j = 0;
        
        for(int i = 0; i < NUMCOL; i++)
        {
            column *newCol = new column();
            curBoard.push_back(newCol);
            
            j = 0;
            while(j < NUMROW && (pieceToAdd = toCopy.curBoard[i]->at(j)) != empty)
            {
                curBoard[i]->placePiece(pieceToAdd);
                j++;
            }
        }
    }
    
    ~board()
    {
        for(int i = NUMCOL - 1; i >= 0; i--)
        {
            delete curBoard[i];
        }
    }
    
    //returns -1 if the placement failed, else it returns the row number the piece fell on
    int placePieceOnCol(int colNumber, pieceType color)
    {
        bool gameOver = false;
        if(colNumber < 0 || colNumber >= NUMCOL)
        {
            return -1;
        }
        
        int rowNum = curBoard[colNumber]->placePiece(color);
        
        if(rowNum != -1)
        {
            lastColor = color;
            lastCol = colNumber;
            lastRow = rowNum - 1;
            
            gameOver = isGameOver();
        }
        
        if(gameOver)
        {
            return 10;
        }
        
        return rowNum;
    }
    
    int getColHeight(int col)
    {
        return curBoard[col]->getHeight();
    }
    
    void printBoardState()
    {
        vector<vector<pieceType> > fullBoard;
        
        for(int i = 0; i < NUMCOL; i++)
        {
            fullBoard.push_back(curBoard[i]->getColState());
        }
        
        for(int i = NUMROW - 1; i >= 0; i--)
        {
            cout << i + 1 << " ";
            for(int j = 0; j < NUMCOL; j++)
            {
                char curCol;
                if(fullBoard[j][i] == blue)
                {
                    curCol = 'b';
                }
                else if(fullBoard[j][i] == red)
                {
                    curCol = 'r';
                }
                else
                {
                    curCol = ' ';
                }
                
                cout << curCol << " ";
            }
            cout << endl;
        }
        cout << "  1 2 3 4 5 6 7" << endl;
    }
    
    vector<vector<pieceType> > getBoardState()
    {
        vector<vector<pieceType> > fullBoard;
        
        for(int i = 0; i < NUMCOL; i++)
        {
            fullBoard.push_back(curBoard[i]->getColState());
        }
        
        return fullBoard;
    }
    
    void removeTopAtCol(int col)
    {
        curBoard[col]->removeTop();
    }
    
    int getHeightAt(int col)
    {
        return curBoard[col]->getHeight();
    }
    
    
    
};

#endif
