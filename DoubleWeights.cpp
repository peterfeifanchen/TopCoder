#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>

struct Node {
   std::vector<int> path;
   int cost1;
   int cost2;
};

class DoubleWeights {

   public:
      int minimalCost( const std::vector<std::string> w1, 
                       const std::vector<std::string> w2 ) {
    
         std::queue<Node> nextNode;
         int numNode = w1[0].size();
         int finalCost = 2147483647;
         bool foundpath = false;
         std::vector<int> minCostToNode( numNode, finalCost );         
         Node start;

         //Initialize the queue
         minCostToNode[0] = 0;
         start.path.push_back( 0 );
         start.cost1 = 0;
         start.cost2 = 0;
         nextNode.push( start );

         while( !nextNode.empty() ) {
            Node node = nextNode.front();
            nextNode.pop();
            int n = node.path.back();
            std::cout << "n: " << n << std::endl;
            if( n == 1 ) {
               foundpath = true;
               if( node.cost1 * node.cost2 < finalCost ) {
                  finalCost = node.cost1 * node.cost2;
               }
            } else {
               for( int i=0; i < numNode; i++ ) {
                  std::cout << i << ": " << w1[n][i] << "," << w2[n][i] << std::endl;
                  if( w1[n][i] == '.' ) continue;
                  else {
                     Node temp = node;
                     int path1Cost = temp.cost1 + w1[n][i] - '0';
                     int path2Cost = temp.cost2 + w2[n][i] - '0';
                     std::cout << path1Cost * path2Cost << "," << minCostToNode[i] << std::endl;
                     if( path1Cost * path2Cost < minCostToNode[i] ) {
                        minCostToNode[i] = path1Cost * path2Cost;
                        std::cout << path1Cost << "," << path2Cost << std::endl;
                        temp.path.push_back(i);
                        temp.cost1 = path1Cost;
                        temp.cost2 = path2Cost;
                        nextNode.push( temp );
                     }
                  }
               }
            }
         }

         if( foundpath == false ) return -1;
         return finalCost;
      }
};

int main( int argc, char** argv ) {
   std::vector<std::string> tc1w1 = 
   {"..14",
    "..94",
    "19..",
    "44.."};
   std::vector<std::string> tc1w2 = {"..94",
    "..14",
    "91..",
    "44.."};

   std::vector<std::string> tc2w1 = {"..14",
    "..14",
    "11..",
    "44.."};
   std::vector<std::string> tc2w2 = {"..94",
    "..94",
    "99..",
    "44.."};
   
   std::vector<std::string> tc3w1 = {"..",
                                     ".."};
   std::vector<std::string> tc3w2 = {"..",
                                     ".."};

   std::vector<std::string> tc4w1 = {".....9",
                                     "..9...",
                                     ".9.9..",
                                     "..9.9.",
                                     "...9.9",
                                     "9...9."};
   std::vector<std::string> tc4w2 = {".....9",
                                     "..9...",
                                     ".9.9..",
                                     "..9.9.",
                                     "...9.9",
                                     "9...9."};

   std::vector<std::string> tc5w1 = {".4...1",
                                     "4.1...",
                                     ".1.1..",
                                     "..1.1.",
                                     "...1.1",
                                     "1...1."};
   std::vector<std::string> tc5w2 = {".4...1",
                                     "4.1...",
                                     ".1.1..",
                                     "..1.1.",
                                     "...1.1",
                                     "1...1."};
   
   int           result;
   bool          passed = true;
   DoubleWeights test;
   
   result = test.minimalCost( tc1w1, tc1w2 );
   if( result != 64 ) {
      std::cout << "Test Case 1 Failed. Answer: 64, Result: " << result << std::endl;
      passed = false;
   }
   result = test.minimalCost( tc2w1, tc2w2 );
   if( result != 36 ) {
      std::cout << "Test Case 1 Failed. Answer: 36, Result: " << result << std::endl;
      passed = false;
   }
   result = test.minimalCost( tc3w1, tc3w2 );
   if( result != -1 ) {
      std::cout << "Test Case 1 Failed. Answer: -1, Result: " << result << std::endl;
      passed = false;
   }
   result = test.minimalCost( tc4w1, tc4w2 );
   if( result != 2025 ) {
      std::cout << "Test Case 1 Failed. Answer: 2025, Result: " << result << std::endl;
      passed = false;
   }
   result = test.minimalCost( tc5w1, tc5w2 );
   if( result != 16 ) {
      std::cout << "Test Case 1 Failed. Answer: 16, Result: " << result << std::endl;
      passed = false;
   }
   
   if( passed ) std::cout << "All test cases passed" << std::endl;
}
