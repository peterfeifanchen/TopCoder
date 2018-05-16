// Copyright (c) 2018 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <climits>

class QueenInterference {

 void print() {
   for( int i = 0; i < grid.size(); i++ ) {
      for( int j = 0; j < grid[i].size(); j++ ) {
         std::cout << grid[j][i];
      }
      std::cout << std::endl;
   }
 }

 int nextRandomInt( int up ) {
   aSeed = ( aSeed * 16807 ) % 2147483647;
   int r = ( aSeed % up ) + 1 ; 
   std::cout << "r: " << r << std::endl;
   return r;
 }

 int queenRow( const std::string &col ) {
   for( int i = 0; i < col.size(); i++ ) {
      if( col[i] == '1' ) return i;
   }
   exit(0);
 }

 std::vector<int> reachableQueens() {
   std::vector<int> reachable( grid.size(), 0 );
   for( int i = 0; i < grid.size(); i++ ) {
      int row = queenRow( grid[i] );
      int reached = 0;
      // move horizontally
      for( int j = i+1; j < grid.size(); j++ ) {
         if( grid[j][row] == '1' ) {
            reached++;
            reachable[j] = 1;
         }
      }
      // move diagonally up
      for( int j = i+1; j < grid.size(); j++ ) {
         if( row - (j-i) <= 0 ) continue;
         if( grid[j][row-(j-i)] == '1' ) {
            reached++;
            reachable[j] = 1;
         }
      }
      // move diagonally down
      for( int j = i+1; j < grid.size(); j++ ) {
         if( row + (j-i) >= grid.size() ) continue;
         if( grid[j][row+(j-i)] == '1' ) {
            reached++;
            reachable[j] = 1;
         }
      }
   
      if( reached ) reachable[i] = 1;
   }
   return reachable;
 }

 std::vector<int> reachableForEachRow( int col ) {
   std::vector<int> column( grid.size(), 0 );
   for( int i = 0; i < grid.size(); i++ ) {
      if( i == col ) continue;
      int row = queenRow( grid[i] );
      int colSep = abs( i - col );
      column[row] += 1;
      if( row + colSep < grid.size() ) column[row+colSep] += 1;
      if( row - colSep >= 0 ) column[row-colSep] += 1;
   }
   return column;
 }

 std::vector<std::string>   grid;
 unsigned int               aSeed = 1;

 public:
   int numSteps( int n ) {
      int iter = 0;
      std::string colStr( n, '0' ); 
      grid = std::vector<std::string>( n, colStr );

      // randomly place a queen on each column
      for( int i = 0; i < n; i++ ) {
         int row = nextRandomInt( n ) - 1;
         grid[i][row] = '1';
      }

      while (true) {
         print();

         // alteration steps according to QueeInterference problem
      
         // 1) Compute T, the number of columns containing reachable queens
         std::vector<int> T = reachableQueens();
         int reachable = 0;
         std::cout << "Reachable: ";
         for( int i = 0; i < T.size(); i++ ) {
            std::cout << T[i];
            reachable += T[i];
         }
         std::cout << " " << reachable << std::endl;
         if( reachable == 0 ) break;

         // 2) Randomly select a column C with a reachable queen using the special 
         //    seed algorithm nextRandomInt
         int col = nextRandomInt( reachable ) - 1;
         std::cout << "Pick Reachable Random Column: " << col << std::endl;
         int adjCol = col;
         int i = 0;
         while( col >= 0 && i < T.size() ) {
            if( T[i] == 0 ) adjCol++;
            if( T[i] == 1 ) col--;
            i++;
         }
         std::cout << "Adjusted Random Column: " << adjCol << std::endl;
         // 3) Calculate the number of queens that can reach each row n of the column C
         std::vector<int> nC = reachableForEachRow( adjCol );
         std::cout << "Reachability of each row in column " << adjCol << ": ";
         for( int k = 0; k < nC.size(); k++ ) {
            std::cout << nC[k];
         }
         std::cout << std::endl;

         // 4) Move the queen for that column to the row with least reachability by 
         //    other queens
         int minVal = INT_MAX;
         int minPos = 0;
         int minTied = 0;
         for( int k=0; k < nC.size(); k++ ) {
            if( nC[k] < minVal ) {
               minPos = k;
               minVal = nC[k];
               minTied = 1;
            } else if ( nC[k] == minVal ) {
               minTied++;
            }
         }

         // 5) if there are more than one min value, randomly select one to move the
         //    queen there
         int newRow = minPos;
         if( minTied > 1 ) {
            int randomRow = nextRandomInt( minTied ) - 1;
            int k = minPos + 1;
            while( randomRow > 0 && k < nC.size() ) {
               if( nC[k] == minVal ) {
                  newRow = k;
                  randomRow--;
               }
               k++;
            }
         }
         std::cout << "minPos: " << minPos << std::endl;
         std::cout << "newRow: " << newRow << std::endl;
         std::cout << "minVal: " << minVal << std::endl;
         std::cout << "minTied: " << minTied << std::endl;

         // 6) move the queen to new selected row
         int curRow = queenRow( grid[adjCol] );
         std::cout << "current column " << adjCol << ": " << grid[adjCol] << std::endl;
         grid[adjCol][curRow] = '0';
         grid[adjCol][newRow] = '1';
         std::cout << "new column " << adjCol << ": " << grid[adjCol] << std::endl;
      
         iter++;
         std::cout << "iter: " << iter << std::endl;
      }

      return iter;
   }
};

int main( int argc, char** argv ) {
   QueenInterference test;
   int result;
   int expected;
   bool testFailed = false;
   // test case 1
   expected = 4;
   result = test.numSteps( 5 );
   if( result != expected ) {
      testFailed = true;
      std::cout << "QueenInterference 5: expected " << expected << ", got " 
                << result << std::endl;
   }
   // test case 2
   expected = 6;
   result = test.numSteps( 7 );
   if( result != expected ) {
      testFailed = true;
      std::cout << "QueenInterference 6: expected " << expected << ", got " 
                << result << std::endl;
   }
   // test case 3
   expected = 475;
   result = test.numSteps( 19 );
   if( result != expected ) {
      testFailed = true;
      std::cout << "QueenInterference 19: expected " << expected << ", got " 
                << result << std::endl;
   }
   
   if( !testFailed ) {
      std::cout << "All Test Cases passed." << std::endl;
   }
}
