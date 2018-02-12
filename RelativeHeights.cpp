// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include<iostream>
#include<vector>
#include<algorithm>

// SRM718

class BuildingObj {
   int height_;
   int index_;
 public:
   BuildingObj() : height_( 0 ), index_( 0 ) {}
   BuildingObj( int h, int i ) : height_( h ), index_( i ) { }

   bool operator<( const BuildingObj& r ) const {
      return this->height_ > r.height_;
   }

   int height() {
      return height_;
   }
   
   int index() {
      return index_;
   }
};


class RelativeHeights {
   
 public:
   int countWays( std::vector<int> &h ) {
      std::vector<BuildingObj> hp( h.size() );
      std::vector<int> heightProfile( h.size() );
      int nProfile = 1;

      // Create a vector of building objects
      for( int i = 0; i < h.size(); i++ ) {
         hp[ i ] = BuildingObj( h[ i ], i );
      }
      // Sort
      std::sort( hp.begin(), hp.end() );
  
      // Construct height profile from sorted building obj array
      for( int i = 0; i < h.size(); i++ ) {
         int index = hp[ i ].index();
         heightProfile[ index ] = h.size() - i - 1;
      }

      // Pass through the heightProfile array, everytime the following number
      // is within +/- 1 of the preceding number, we do not increment. The 
      // final result is the number of different height profiles we would have
      // if we dropped one buliding
      for( int i = 0; i < h.size() - 1; i++ ) {
         if( heightProfile[ i ] != heightProfile[ i+1 ] + 1 &&
             heightProfile[ i ] != heightProfile[ i+1 ] - 1 ) {
            nProfile++;
         }
      }

      return nProfile;
   }
};

int main( int argc, char** argv ) {
   int tc1[] = {1,3,6,10,15,21};
   int tc2[] = {4,2,1,3};
   int tc3[] = {6,2,352,43,5,44};
   int tc4[] = {4,5,6,1,2,3};
   int tc5[] = {10,9,7,5,3,1,8,6,4,2};
   int result = 0;

   RelativeHeights test;
   std::vector<int> test_case_1( tc1, tc1 + sizeof( tc1 ) / sizeof( int ) );
   result = test.countWays( test_case_1 );
   if( result != 1 ) {
      std::cout << "Test Case 1 Failed. Answer: 1, Result: " << result << std::endl;
   }

   std::vector<int> test_case_2( tc2, tc2 + sizeof( tc2 ) / sizeof( int ) );
   result = test.countWays( test_case_2 );
   if( result != 3 ) {
      std::cout << "Test Case 2 Failed. Answer: 3, Result: " << result << std::endl;
   }
   
   std::vector<int> test_case_3( tc3, tc3 + sizeof( tc3 ) / sizeof( int ) );
   result = test.countWays( test_case_3 );
   if( result != 6 ) {
      std::cout << "Test Case 3 Failed. Answer: 6, Result: " << result << std::endl;
   }
   
   std::vector<int> test_case_4( tc4, tc4 + sizeof( tc4 ) / sizeof( int ) );
   result = test.countWays( test_case_4 );
   if( result != 2 ) {
      std::cout << "Test Case 4 Failed. Answer: 2, Result: " << result << std::endl;
   }
   
   std::vector<int> test_case_5( tc5, tc5 + sizeof( tc5 ) / sizeof( int ) );
   result = test.countWays( test_case_5 );
   if( result != 9 ) {
      std::cout << "Test Case 5 Failed. Answer: 9, Result: " << result << std::endl;
   }

   std::cout << "All test cases passed" << std::endl;
}
