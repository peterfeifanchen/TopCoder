// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

typedef std::vector<std::vector<std::vector<std::vector<int>>>> Array;

class StarAdventure {
 public:
   int mostStars( std::vector<std::string> &m ) {
      int width = m[0].size();
      int height = m.size();
      int maxSum = 0;
     
      // Special case is if m width <= 3, we just sum up all the values in m
      // as they are all reachable.
      if( width <= 3 ) {
         for( int i = 0; i < width; i++ ) {
            for( int j = 0; j < height; j++ ) {
               maxSum += m[j][i] - '0';
            }
         }
         return maxSum;
      }

      // If m width > 3, we have to dynamically get the answer with each substate
      // being the value max3PathSum[row][i][j][k] which is the x coordinate of 
      // each path as it moves down. 
      Array max3PathSum;
      max3PathSum.resize(height);
      for( int r = 0; r < height; r++ ) {
         max3PathSum[r].resize(width);
         for( int i = 0; i < width; i++ ) {
            max3PathSum[r][i].resize(width);
            for( int j = 0; j < width; j++ ) {
               max3PathSum[r][i][j].resize(width, 0);
            }
         }
      }

      // Initialize first row
      for( int k = 0; k < width; k++ ) {
         for( int j = 0; j < k; j++ ) {
            for( int i = 0; i < j; i++ ) {
               // sum 0 -> i + sum i -> j + sum j->k
               for( int ip = 0; ip <= i; ip++ ) {
                  max3PathSum[0][i][j][k] += m[0][ip] - '0';
               }
               for( int jp = i+1; jp <= j; jp++ ) {
                  max3PathSum[0][i][j][k] += m[0][jp] - '0';
               }
               for( int kp = j+1; kp <= k; kp++ ) {
                  max3PathSum[0][i][j][k] += m[0][kp] - '0';
               }
            }
         }
      }

      // Iterate to last row
      for( int r = 1; r < height; r++ ) {
         for( int k = 0; k < width; k++ ) {
            for( int j = 0; j < k; j++ ) {
               for( int i = 0; i < j; i++ ) {
                  int sum_k = 0;
                  //shift i,j,k right
                  for( int sk = k; sk < width; sk++ ) {
                     sum_k += m[r][sk] - '0';
                     int sum_j = 0;
                     for( int sj = j; sj < k; sj++ ) {
                        sum_j += m[r][sj] - '0';
                        int sum_i = 0;
                        for( int si = i; si < j; si++ ) {
                           sum_i += m[r][si] - '0';
                           int sum = sum_i + sum_j + sum_k + max3PathSum[r-1][i][j][k];
                           if( sum > max3PathSum[r][si][sj][sk] ) 
                              max3PathSum[r][si][sj][sk] = sum;
                        }
                     }
                  }
               }
            }
         }
         /*
         for ( int k = 0; k < width; k ++ ) {
            for( int j = 0; j < k; j++ ) {
               for( int i = 0; i < j; i++ ) {
                  std::cout << "Level(" << r << "," << i << "," << j << "," << k << "): " << 
                        max3PathSum[r][i][j][k] << std::endl;
               }
            }
         }
         */
      }

      // Take max of the max3PathSum[height-1][i][j][k]
      for( int k = 0; k < width; k++ ) {
         for( int j = 0; j < k; j++ ) {
           for( int i = 0; i < j; i++ ) {
             if( max3PathSum[height-1][i][j][k] > maxSum )
                maxSum = max3PathSum[height-1][i][j][k];
           }
         }
      }
      return maxSum;
   }
};

int main( int argc, char** argv ) {
   std::vector<std::string> tc1 = { 
      "01", 
      "11", 
   };
   std::vector<std::string> tc2 = {
      "0999999999",
      "9999999999",
      "9999999999",
      "9999999999",
      "9999999999",
      "9999999999",
      "9999999999",
      "9999999999",
      "9999999999",
      "9999999999",
   };
   std::vector<std::string> tc3 = { 
      "012", 
      "012", 
      "012", 
      "012", 
      "012", 
      "012", 
      "012",
   };
   std::vector<std::string> tc4 = {
      "0123456789",
      "1123456789",
      "2223456789",
      "3333456789",
      "4444456789",
      "5555556789",
      "6666666789",
      "7777777789",
      "8888888889",
      "9999999999",
   };

   int result = 0;
   bool passed = true;

   StarAdventure test;
   result = test.mostStars( tc1 );
   if( result != 3 ) {
      passed = false;
      std::cout << "Test Case 1 Failed. Answer: 3, Result: " << result << std::endl;
   }
   result = test.mostStars( tc2 );
   if( result != 450 ) {
      passed = false;
      std::cout << "Test Case 2 Failed. Answer: 450, Result: " << result << std::endl;
   }
   result = test.mostStars( tc3 );
   if( result != 21 ) {
      passed = false;
      std::cout << "Test Case 3 Failed. Answer: 21, Result: " << result << std::endl;
   }
   result = test.mostStars( tc4 );
   if( result != 335 ) {
      passed = false;
      std::cout << "Test Case 4 Failed. Answer: 335, Result: " << result << std::endl;
   }
   
   if( passed ) std::cout << "All test cases passed" << std::endl;
}
