#include <iostream>
#include <vector>

// Fabian is in charge of a law firm working on an important case. For a case coming
// up, he needs a specific folder which is stored in one of the filing cabinets
// arranged in a line against the wall of the records room. He has assigned a number
// of workers to find the folder from the filing cabinets. He doesn't want the
// workers to get in each other's way, nor does he want folders from different
// filing cabinets getting mixed up, so he has decided to partition the cabinets,
// and assign a specific section to each worker. Each worker will have at least 1
// cabinet to search through.
//
// More specifically, Fabian wants to divide the line of filing cabinets into N 
// sections (where N is the number of workers) so that every cabinet that the ith
// worker looks through is earlier in the line than every cabinet that the jth
// worker has to look through, for i < j.
//
// His initial thought was to make all the sections equal, giving each worker the
// same number of filing cabinets to look through, but then he realized that the
// filing cabinets differed in the number of folders they contained. He now has
// decided to partition the filing cabinets so as to minimize the maximum number of
// folders that a worker would have to look through. For example, suppose there 
// were three workers and nine filing cabinets with the following number of folders:
//
//   10 20 30 40 50 60 70 80 90
//
// He would divide up the filing cabinets into the following sections:
//
//  10 20 30 40 50 | 60 70 | 80 90
//
// The worker assigned to the first section would have to look through 150 folders.
// The worker assigned to the second section would have to search through 130 
// folders, and the last worker would filter through 170 folders. In this 
// partitioning, the maximum number of folders that a worker looks through is 170.
// No other partitioning has less than 170 folders in the largest partition.
//
// Write a class FairWorkload with a method getMostWork which takes a int[] folders
// (the number of folders for each filing cabinet) and an int workers (the number
// of workers). The method should return an int which is the maximum amount of
// folders that a worker would have to look through in an optimal partitioning of
// the filing cabinets. For the above example, the method would have returned 170.

class FairWorkload {
   int binarySearch( const std::vector<int>& mono, int left, int right, int val ) {
      if( left >= right ) {
         if( left == 0 ) {
            if( val - mono[left] > mono[left+1] - val ) return left + 1;
         } else if( left == mono.size()-1 ) {
            if( mono[left] - val > val - mono[left-1] ) return left - 1;
         } else if( val > mono[left] ) {
            if( val - mono[left] > mono[left+1] - val ) return left + 1;
         } else if( val < mono[left] ) {
            if( mono[left] - val > val - mono[left-1] ) return left - 1;
         }
         return left;
      }
      int mid = (left + right)/2;
      if( val == mono[mid] ) return mid;
      else if( val > mono[mid] ) return binarySearch( mono, mid+1, right, val );
      else return binarySearch( mono, left, mid-1, val );
   }
 public:
   int getMostWork( std::vector<int>& folders, int workers ) {
      std::vector<int> monotonic( folders.size(), 0 );
      monotonic[0] = folders[0];
      for( int i = 1; i < folders.size(); i++ ) {
         monotonic[i] = monotonic[i-1] + folders[i];
      }

      int most = 0;
      int startpos = 0;
      int avg = monotonic[folders.size()-1] / workers;
      for( int i = 1; i <= workers; i++ ) {
         int endpos = binarySearch( monotonic, 0, folders.size()-1, avg * i );
         int sum = 0;
         for( int j = startpos; j <= endpos; j++ ) {
            sum += folders[j];
         }
         if( sum > most ) most = sum;
         startpos = endpos + 1;
      }

      return most;
   }
};

typedef std::pair< std::vector<int>, int > testcase;

int main( int argc, char** argv ) {
   testcase tc1 = testcase( { 10, 20, 30, 40, 50, 60, 70, 80, 90 }, 3 );
   testcase tc2 = testcase( { 10, 20, 30, 40, 50, 60, 70, 80, 90 }, 5 );
   testcase tc3 = testcase( { 568, 712, 412, 231, 241, 393, 865, 287, 
                              128, 457, 238, 98, 980, 23, 782 }, 4 );
   testcase tc4 = testcase( { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1000 }, 2 );
   testcase tc5 = testcase( { 50, 50, 50, 50, 50, 50, 50 }, 2 );
   testcase tc6 = testcase( { 1, 1, 1, 1, 100 }, 5 );
   testcase tc7 = testcase( { 950, 650, 250, 250, 350, 100,
                              650, 150, 150, 700 }, 6 );

   FairWorkload s;
   bool pass = true;
   int result;
  
   result = s.getMostWork( tc1.first, tc1.second );
   if( result != 170 ) {
      pass = false;
      std::cout << "Test #1: Expected 170, got " << result << std::endl;
   }
   result = s.getMostWork( tc2.first, tc2.second );
   if( result != 110 ) {
      pass = false;
      std::cout << "Test #2: Expected 110, got " << result << std::endl;
   }
   result = s.getMostWork( tc3.first, tc3.second );
   if( result != 1785 ) {
      pass = false;
      std::cout << "Test #3: Expected 1785, got " << result << std::endl;
   }
   result = s.getMostWork( tc4.first, tc4.second );
   if( result != 1000 ) {
      pass = false;
      std::cout << "Test #4: Expected 1000, got " << result << std::endl;
   }
   result = s.getMostWork( tc5.first, tc5.second );
   if( result != 200 ) {
      pass = false;
      std::cout << "Test #5: Expected 200, got " << result << std::endl;
   }
   result = s.getMostWork( tc6.first, tc6.second );
   if( result != 100 ) {
      pass = false;
      std::cout << "Test #6: Expected 100, got " << result << std::endl;
   }
   result = s.getMostWork( tc7.first, tc7.second );
   if( result != 950 ) {
      pass = false;
      std::cout << "Test #7: Expected 950, got " << result << std::endl;
   }
   if( pass ) {
      std::cout << "All test passed" << std::endl;
   }
}
