#include<iostream>
#include<vector>
#include<algorithm>



class Boxing {
  
   int get( std::vector<int> &j, int pos ) {
      if( pos < j.size() ) {
         return j[ pos ];
      }
      // -1 to indicate we've reached end of the array
      return -1;
   }

   int findMin( std::vector<int> &val ) {
      int min = -1;
      int init = 0;
      while( min == -1 ) {
         if ( val[init] != -1 ) {
            min = init;
         }
         init++;
      }

      for( int i = init; i < val.size(); i++ ) {
         if( val[i] < val[min] && val[i] != -1 ) {
            min = i;
         }
      }
      return min;
   }

   int calcRemaining( std::vector<int> &val ) {
      int empty = 0;
      for( int i = 0; i < val.size(); i++ ) {
         if( val[i] == -1 ) empty++;
      }
      return val.size() - empty;
   }

   int updatePos( std::vector<int> &val, int curr, int end ) {
      int nextPos = val.size();
      for( int i = curr; i < val.size(); i++ ) {
         if( val[i] > end ) {
            nextPos = i;
            break;
         }
      }
      return nextPos;
   }

 public:
   int maxCredit( std::vector<int> &a, 
                  std::vector<int> &b,
                  std::vector<int> &c,
                  std::vector<int> &d,
                  std::vector<int> &e ) {

      int punches = 0, remaining = 5;
      std::vector<int> currpos = {0,0,0,0,0};
      
      // Need initial check to see if there isn't more than 2 empty arrays, but this 
      // is just extra work. 

      std::vector<int> currVal = { get( a, currpos[0] ),
                                   get( b, currpos[1] ),
                                   get( c, currpos[2] ),
                                   get( d, currpos[3] ),
                                   get( e, currpos[4] ) };

      while( remaining >= 3 ){
         int judge1 = findMin( currVal );
         int intervalStart = currVal[ judge1 ];
         int intervalEnd = -1;

         // We now find another judges with the closest support from current interval start
         std::vector<int> copyVal( currVal );
         copyVal[ judge1 ] = -1;
         int nextJudge = findMin( copyVal );
         if( copyVal[ nextJudge ] - intervalStart < 1000 ) {
            // We find a third judge with the closest support from the current interval start
            copyVal[ nextJudge ] = -1;
            nextJudge = findMin( copyVal );
            if( copyVal[ nextJudge ] - intervalStart < 1000  ) {
               intervalEnd = copyVal[ nextJudge ];
               punches++;
            }
         }

         // Update currpos: (1) interval was not found, update only the position for that judge
         //                 (2) interval was found, update the position for every judge in interval
         if ( intervalEnd == -1 ) {
            currpos[ judge1 ]++;
         } else {
            int newPos = updatePos( a, currpos[0], intervalEnd );
            currpos[ 0 ] = newPos;
            newPos = updatePos( b, currpos[1], intervalEnd );
            currpos[ 1 ] = newPos;
            newPos = updatePos( c, currpos[2], intervalEnd );
            currpos[ 2 ] = newPos;
            newPos = updatePos( d, currpos[3], intervalEnd );
            currpos[ 3 ] = newPos;
            newPos = updatePos( e, currpos[4], intervalEnd );
            currpos[ 4 ] = newPos;
         }
         
         currVal = { get( a, currpos[0] ),
                     get( b, currpos[1] ),
                     get( c, currpos[2] ),
                     get( d, currpos[3] ),
                     get( e, currpos[4] ) };

         remaining = calcRemaining( currVal );
      }
      
      return punches;
   }
};

int main( int argc, char** argv ) {
   std::vector<int> tc1_a = {1,2,3,4,5,6};
   std::vector<int> tc1_b = {1,2,3,4,5,6,7};
   std::vector<int> tc1_c = {1,2,3,4,5,6};
   std::vector<int> tc1_d = {0,1,2};
   std::vector<int> tc1_e = {1,2,3,4,5,6,7,8};
   
   std::vector<int> tc2_a = {100,200,300,1200,6000};
   std::vector<int> tc2_b = {};
   std::vector<int> tc2_c = {900,902,1200,4000,5000,6001};
   std::vector<int> tc2_d = {0,2000,6002};
   std::vector<int> tc2_e = {1,2,3,4,5,6,7,8};
   
   std::vector<int> tc3_a = {5000,6500};
   std::vector<int> tc3_b = {6000};
   std::vector<int> tc3_c = {6500};
   std::vector<int> tc3_d = {6000};
   std::vector<int> tc3_e = {0, 5800, 6000};
   
   int result = 0;

   Boxing test;
   bool failed = false;

   result = test.maxCredit( tc1_a, tc1_b, tc1_c, tc1_d, tc1_e );
   if( result != 6 ) {
      failed = true;
      std::cout << "Test Case 1 Failed. Answer: 6, Result: " << result << std::endl;
   }
   result = test.maxCredit( tc2_a, tc2_b, tc2_c, tc2_d, tc2_e );
   if( result != 3 ) {
      failed = true;
      std::cout << "Test Case 1 Failed. Answer: 3, Result: " << result << std::endl;
   }
   result = test.maxCredit( tc3_a, tc3_b, tc3_c, tc3_d, tc3_e );
   if( result != 1 ) {
      failed = true;
      std::cout << "Test Case 1 Failed. Answer: 1, Result: " << result << std::endl;
   }

   if( !failed ) {
      std::cout << "All test cases passed" << std::endl;
   }
}
