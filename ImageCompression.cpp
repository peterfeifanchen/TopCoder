// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

// SRM715

class ImageCompression {

   public:
      std::string isPossible( const std::vector<std::string> &im, int factor ) {
         int scanWidth = im[ 0 ].size();
         int scanHeight = im.size();
         std::vector<int> scanline( scanWidth / factor );

         std::cout << "scanWidth: " << scanWidth 
                   << " scanHeight: " << scanHeight 
                   << " scanline: " << scanWidth / factor << std::endl;

         for( int i = 0; i < scanHeight; i++ ) {
            for( int j = 0; j < scanWidth; j++ ) {
               if( i % factor == 0 && j % factor == 0 ) {
                  scanline[ j / factor ] = im[ i ][ j ] - '0';
                  //std::cout << "scanline[ " << j / factor << " ] = " 
                  //          << scanline[ j / factor ] << std::endl;
               } else {
                  int color = im[ i ][ j ] - '0';
                  //std::cout << "im[" << i << "][" << j << "] = " << color << std::endl;
                  if( color != scanline[ j / factor ] ) {
                     std::cout << "failed @ (" << i << "," << j << ")" << std::endl;
                     return "Impossible";
                  }
               }
            }
         }

         return "Possible";
      }
};

int main( int argc, char** argv ) {
   std::vector<std::string> tc1 = {   
      "0011",
      "0011",
      "1100",
      "1100",
      "0000",
      "0000"
   };
   
   std::vector<std::string> tc2 = {
      "0011",
      "0011",
      "1100",
      "1100",
      "0010",
      "0000"
   };
   
   std::vector<std::string> tc3 = {
      "001100",
      "001100",
      "110011",
      "110011",
      "001100",
      "001100"
   };
   
   std::vector<std::string> tc4 = {
      "001100",
      "001100",
      "110011",
      "110011",
      "001100",
      "001100"
   };

   std::vector<std::string> tc5 = {
      "11111111",
      "11111111",
      "11111111",
      "11111111",
      "11111111",
      "11111111",
      "11111111",
      "11111111"
   };
   
   std::vector<std::string> tc6 = {
      "111000111",
      "111000111",
      "111000111"
   };
   
   std::string result;
   bool        passed = true;
   ImageCompression test;
   
   result = test.isPossible( tc1, 2 );
   if( result.compare( "Possible" ) != 0 ) {
      std::cout << "Test Case 1 Failed. Answer: Possible, Result: " << result << std::endl;
      passed = false;
   }
   
   result = test.isPossible( tc2, 2 );
   if( result.compare( "Impossible" ) != 0 ) {
      std::cout << "Test Case 2 Failed. Answer: Impossible, Result: " << result << std::endl;
      passed = false;
   }
   
   result = test.isPossible( tc3, 6 );
   if( result.compare( "Impossible" ) != 0 ) {
      std::cout << "Test Case 3 Failed. Answer: Impossible, Result: " << result << std::endl;
      passed = false;
   }
   
   result = test.isPossible( tc4, 2 );
   if( result.compare( "Possible" ) != 0 ) {
      std::cout << "Test Case 4 Failed. Answer: Possible, Result: " << result << std::endl;
      passed = false;
   }

   result = test.isPossible( tc5, 4 );
   if( result.compare( "Possible" ) != 0 ) {
      std::cout << "Test Case 5 Failed. Answer: Possible, Result: " << result << std::endl;
      passed = false;
   }
   
   result = test.isPossible( tc6, 3 );
   if( result.compare( "Possible" ) != 0 ) {
      std::cout << "Test Case 6 Failed. Answer: Possible, Result: " << result << std::endl;
      passed = false;
   }

   if( passed ) std::cout << "All test cases passed" << std::endl;
}
