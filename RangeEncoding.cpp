// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include<iostream>
#include<vector>
#include<algorithm>

// SRM714

class RangeEncoding {
   
 public:
   int minRanges( std::vector<int> &h ) {
      // Greedy algorithm, if h[n+1] is consecutive with h[n], then 
      // they are part of the same range
      int nRanges = 1;
      for( int i = 0; i < h.size() - 1; i++ ) {
         if( h[ i ] + 1 != h[ i+1 ] ) nRanges++;
      }
      return nRanges;
   }
};

int main( int argc, char** argv ) {
   int tc1[] = {1,2,3,4,5,6,7,8,9,10};
   int tc2[] = {1,6,10,20,32,49};
   int tc3[] = {2,4,5,6,8,9,10,11,12,15};
   int tc4[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
   int tc5[] = {10,11,12,13,14,15,20,21,22,23,25,27,28,29,30,31,32,33};
   int tc6[] = {33};
   int result = 0;

   bool          fail = false;
   RangeEncoding test;
   std::vector<int> test_case_1( tc1, tc1 + sizeof( tc1 ) / sizeof( int ) );
   result = test.minRanges( test_case_1 );
   if( result != 1 ) {
      fail = true;
      std::cout << "Test Case 1 Failed. Answer: 1, Result: " << result << std::endl;
   }

   std::vector<int> test_case_2( tc2, tc2 + sizeof( tc2 ) / sizeof( int ) );
   result = test.minRanges( test_case_2 );
   if( result != 6 ) {
      fail = true;
      std::cout << "Test Case 2 Failed. Answer: 6, Result: " << result << std::endl;
   }
   
   std::vector<int> test_case_3( tc3, tc3 + sizeof( tc3 ) / sizeof( int ) );
   result = test.minRanges( test_case_3 );
   if( result != 4 ) {
      fail = true;
      std::cout << "Test Case 3 Failed. Answer: 4, Result: " << result << std::endl;
   }
   
   std::vector<int> test_case_4( tc4, tc4 + sizeof( tc4 ) / sizeof( int ) );
   result = test.minRanges( test_case_4 );
   if( result != 14 ) {
      fail = true;
      std::cout << "Test Case 4 Failed. Answer: 14, Result: " << result << std::endl;
   }
   
   std::vector<int> test_case_5( tc5, tc5 + sizeof( tc5 ) / sizeof( int ) );
   result = test.minRanges( test_case_5 );
   if( result != 4 ) {
      fail = true;
      std::cout << "Test Case 5 Failed. Answer: 4, Result: " << result << std::endl;
   }

   std::vector<int> test_case_6( tc6, tc6 + sizeof( tc6 ) / sizeof( int ) );
   result = test.minRanges( test_case_6 );
   if( result != 1 ) {
      fail = true;
      std::cout << "Test Case 6 Failed. Answer: 1, Result: " << result << std::endl;
   }
  
   if( !fail ) std::cout << "All test cases passed" << std::endl;
}
