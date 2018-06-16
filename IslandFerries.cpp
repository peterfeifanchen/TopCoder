#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>

// SRM194

class BoatTraveler{
 public:
   bool operator>( const BoatTraveler& rhs ) const {
      int totalCostA = cost;
      int totalCostB = rhs.cost;
      if( service[0] != -1 ) totalCostA += tickets[0];
      if( service[1] != -1 ) totalCostA += tickets[1];
      if( rhs.service[0] != -1 ) totalCostB += rhs.tickets[0];
      if( rhs.service[1] != -1 ) totalCostB += rhs.tickets[1];
      
      return totalCostA > totalCostB;
   }
   
   bool operator<( const BoatTraveler& rhs ) const {
      return this->cost < rhs.cost;
   }

   BoatTraveler( int usedTicket, int to, 
                 int ticket1, int ticket2, 
                 int service1, int service2, int numIslands ) { 
      this->cost = usedTicket;
      this->toIsland = to;
      this->tickets[0] = ticket1;
      this->tickets[1] = ticket2;
      this->service[0] = service1;
      this->service[1] = service2;
      for( int i = 0; i < numIslands; i++ ) {
         visited.push_back(-1);
      }
   }

   BoatTraveler( const BoatTraveler& a ) {
      cost = a.cost;
      toIsland = a.toIsland;
      tickets[0] = a.tickets[0];
      tickets[1] = a.tickets[1];
      service[0] = a.service[0];
      service[1] = a.service[1];
      for( int i = 0; i < a.visited.size(); i++ ) {
         visited.push_back(a.visited[i]);
      }
   }
   
   int cost;
   int toIsland;
   int ticketUsed;
   int tickets[2];
   int service[2];
   std::vector<int> visited;
};

std::ostream& operator<<( std::ostream& out, const BoatTraveler &b ) {
   out << "[ cost: " << b.cost << "  island: " << b.toIsland << "  ticket1: " 
       << b.tickets[0] << "/" << b.service[0] << "  ticket2: " << b.tickets[1] << "/" 
       << b.service[1] << " visited: ";
   for( int i = 0; i < b.visited.size(); i++ ) {
      out << b.visited[i] << " ";
   }
   std::cout << " ]" << std::endl;
   return out;
}

class Route {
 public:
   Route( int from, int to, int s ) {
      fromIsland = from;
      toIsland = to;
      service = s;
   }
   int fromIsland;
   int toIsland;
   int service;
};

std::ostream& operator<<( std::ostream& out, const Route &r ) {
   return out << "[ from: " << r.fromIsland << " to: " << r.toIsland << " service: "
              << r.service << " ]" << std::endl;
}

class IslandFerries {

   typedef std::priority_queue<BoatTraveler, std::vector<BoatTraveler>, std::greater<BoatTraveler> > heap;

   public:
      std::vector<int> parsePrices( std::string price ) {
         std::size_t pos = 0;
         std::vector<int> intPrices;
         while( pos != std::string::npos ) {
            //std::cout << "parsePrices(): parse string " << price << std::endl;
            std::size_t nextPos = price.find(" ", pos);
            //std::cout << "parsePrices(): nextPos " << nextPos << std::endl;
            std::string substr = price.substr(pos, nextPos - pos);
            //std::cout << "parsePrices(): substr " << substr << std::endl;
            intPrices.push_back(std::stoi(substr));
            pos = nextPos;
            if( pos != std::string::npos ) {
               pos += 1;
            }
            //std::cout << "parsePrices(): pos " << pos << " " << std::string::npos <<  std::endl;
         }
         //std::cout << "parsePrices(): Finished" << std::endl;
         return intPrices;
      }

      void parseReachable( std::vector<bool> &r, std::vector<std::string> legs ) {
         std::vector<Route> reacheableFrom0 = parseRoutes( legs, 0 );
         for( int i = 0; i < reacheableFrom0.size(); i++ ) {
            if( reacheableFrom0[i].service != -1 ) {
               r[reacheableFrom0[i].toIsland-1] = true;
            }
         }
         
         for( int i = 0; i < r.size(); i++ ) {
            std::vector<Route> routes = parseRoutes( legs, i+1 );
            for( int i = 0; i < routes.size(); i++ ) {
               if( routes[i].service != -1 && routes[i].toIsland != 0 ) {
                  r[routes[i].toIsland-1] = true;
               }
            }
         }

      }

      std::vector<Route> parseRoutes( std::vector<std::string> leg, int island ) {
         std::vector<Route> routes;
         for( int i = 0; i < leg.size(); i++ ) { 
            //std::cout << "parseRoutes(): Leg " << leg[i] << std::endl; 
            std::size_t pos = 0;
            bool found = false;
            while( pos != std::string::npos ) {
               std::size_t nextPos = leg[i].find("-", pos);
               std::string from  = leg[i].substr(pos, nextPos - pos);
               pos = nextPos + 1;
               nextPos = leg[i].find(" ", pos);
               std::string to;
               if( nextPos == std::string::npos ) {
                  to = leg[i].substr(pos);
                  pos = nextPos;
               } else {
                  to  = leg[i].substr(pos, nextPos - pos);
                  pos = nextPos + 1;
               }
               //std::cout << "parseRoute(): From " << from << " To " << to << std::endl;
               if( std::stoi(from) == island ) {
                  Route newRoute( std::stoi(from), std::stoi(to), i );
                  routes.push_back( newRoute );
                  found = true;
               }
            }
            if( !found ) {
               Route newRoute( -1, -1, -1 );
               routes.push_back( newRoute );
            }
         }
   
         //std::cout << "parseRoute(): ";
         //for( int i = 0; i < routes.size(); i ++ ) {
         //   std::cout << routes[i];
         //}
         //std::cout << std::endl;

         return routes;
      }

      void addToQueue( heap &q, BoatTraveler &p, std::vector<int> islandTicketPrices, 
               std::vector<Route> routesFromIsland, std::vector<int> &cheapest ) {

         if( p.toIsland != 0 ) {
            if( cheapest[p.toIsland-1] == -1 || cheapest[p.toIsland-1] > p.cost ) 
               cheapest[p.toIsland-1] = p.cost;
            //std::cout << "addToQueue(): cheapest[" << p.toIsland-1 << "]=" << p.cost << std::endl; 
         }

         for( int i = 0; i < routesFromIsland.size(); i++ ) {
            // Service provides a route off the current island
            //std::cout << "addToQueue(): service " << routesFromIsland[i].service << " "  
            //          << routesFromIsland[i].fromIsland << "-" << routesFromIsland[i].toIsland << std::endl;
            if( routesFromIsland[i].service == -1 || p.visited[routesFromIsland[i].toIsland] >= 1 ) {
               //std::cout << "addToQueue(): skip" << std::endl;
               continue;
            }

            BoatTraveler nextLeg( p );
            nextLeg.toIsland = routesFromIsland[i].toIsland;
            if( nextLeg.service[0] == routesFromIsland[i].service ) {
               nextLeg.cost += nextLeg.tickets[0];
               nextLeg.service[0] = -1;
            } else if( nextLeg.service[1] == routesFromIsland[i].service ) {
               nextLeg.cost += nextLeg.tickets[1];
               nextLeg.service[1] = -1;
            } else {
               nextLeg.cost += islandTicketPrices[routesFromIsland[i].service];
            }
            //std::cout << "addToQueue(): i " << i << " push " << nextLeg  << std::endl;
            nextLeg.visited[ routesFromIsland[i].toIsland ]++;
            q.push( nextLeg );
            if( nextLeg.service[0] != -1 && nextLeg.service[1] != -1 ) continue;
            
            for( int j = 0; j < islandTicketPrices.size(); j++ ) {
               //std::cout << " j " << j << std::endl;
               if( j == routesFromIsland[i].service ) {
                  //std::cout << "addToQueue(): service " << j << " already used" << std::endl;
                  continue;
               }
               if( nextLeg.service[0] == j || nextLeg.service[1] == j ) {
                 //std::cout << "addToQueue(): service " << j << " ticket already previously purchased" << std::endl;   
                 continue;
               }

               BoatTraveler buyExtraTicket( nextLeg );
               //std::cout << "addToQueue(): buyExtraTicket " << buyExtraTicket << std::endl;
               if( buyExtraTicket.service[0] == -1 ) {
                  buyExtraTicket.service[0] = j;
                  buyExtraTicket.tickets[0] = islandTicketPrices[j];
               } else if( buyExtraTicket.service[1] == -1 ) {
                  buyExtraTicket.service[1] = j;
                  buyExtraTicket.tickets[1] = islandTicketPrices[j];
               }
               q.push( buyExtraTicket );
               //std::cout << "addToQueue(): i " << i << " j " << j << " push " << buyExtraTicket << std::endl;
               if( nextLeg.service[0] != -1 && nextLeg.service[1] != -1 ) continue;
               
               for( int k = 0; k < islandTicketPrices.size(); k++ ) {
                  if( k == routesFromIsland[i].service || k == routesFromIsland[j].service ) continue;
                  if( buyExtraTicket.service[0] == k || buyExtraTicket.service[1] == k ) continue;

                  BoatTraveler buyAnotherTicket( buyExtraTicket );
                  //std::cout << "addToQueue(): buyAnotherTicket " << buyExtraTicket << std::endl;
                  if( buyAnotherTicket.service[0] == -1 ) {
                     buyAnotherTicket.service[0] = k;
                     buyAnotherTicket.tickets[0] = islandTicketPrices[k];
                  } else if( buyAnotherTicket.service[1] == -1 ) {
                     buyAnotherTicket.service[1] = k;
                     buyAnotherTicket.tickets[1] = islandTicketPrices[k];
                  }
                  q.push( buyAnotherTicket );
                  //std::cout << "addToQueue(): push i " << i << " j " << j << " k " << k << " " << buyAnotherTicket << std::endl;
               }
            }
         }
      }
         

      std::vector<int> cost( std::vector<std::string> legs, 
                             std::vector<std::string> prices ) {
         
         // Create a c++ priority queue with root having the smallest value
         heap bfs_search;
         
         // Create an array of min costs to each island all set to -1
         std::vector<int> cheapest( prices.size()-1, -1 );
         std::vector<bool> reachable( prices.size()-1, false);
         parseReachable( reachable, legs );
         std::cout << "reachable: ";
         for( int i = 0; i < reachable.size(); i++ ) {
            std::cout << reachable[i] << " ";
         }
         std::cout << std::endl;

         // Starting at island 0, add a boat traveler for every route from the
         // island with every combination of tickets
         BoatTraveler first( 0, 0, 0, 0, -1, -1, prices.size() );
         //std::cout << "cost(): first " << first << std::endl;
         std::vector<int> ticketPricesFromIsland0 = parsePrices( prices[ 0 ] );
         std::vector<Route> servicesFromIsland0 = parseRoutes( legs, 0 );
         //std::cout << "cost(): ";
         //for( int i = 0; i < servicesFromIsland0.size(); i ++ ) {
         //   std::cout << servicesFromIsland0[i];
         //}
         addToQueue( bfs_search, first, ticketPricesFromIsland0, 
                     servicesFromIsland0, cheapest );
         //std::cout << "cost(): bfs_search " << bfs_search.size() << " elements" << std::endl;

         int index = 0;
         while( !bfs_search.empty() ) {
            //std::cout << "cost(): bfs_search size " << bfs_search.size() << " " << index++ << std::endl;
            BoatTraveler next = const_cast<BoatTraveler&>( bfs_search.top() );
            std::vector<int> ticketPricesFromNextIsland = parsePrices( prices[ next.toIsland ] );
            std::vector<Route> servicesFromNextIsland = parseRoutes( legs, next.toIsland );
            //std::cout << "cost(): Next " << next << std::endl;
            //for( int i = 0; i < ticketPricesFromNextIsland.size(); i++ ) {
            //   std::cout << "cost(): Service " << i << " Price " 
            //             << ticketPricesFromNextIsland[i] << std::endl;
            //}
            //for( int i = 0; i < servicesFromNextIsland.size(); i++ ) {
            //   std::cout << "cost(): Service " << i << " Route " 
            //             << servicesFromNextIsland[i] << std::endl;
            //}
            bfs_search.pop();
            index++;
            addToQueue( bfs_search, next, ticketPricesFromNextIsland, servicesFromNextIsland, cheapest );
            //std::cout << "cheapest: [ ";
            bool allFound = true;
            for( int i = 0; i < cheapest.size(); i++ ) {
               //std::cout << cheapest[i] << " ";
               if( cheapest[i] == -1 && reachable[i] == true ) allFound = false;
            }
            //std::cout << "]" << std::endl;
            if( allFound ) break;
         }
         std::cout << "Iterations: " << index << std::endl;
         // Pop the next island to visit from the priority queue
         // Calculate the cost so far to reach that island and update the cost array
         // Stop when the queue is empty or every island has been visited
        
         return cheapest;
      }
};

int main( int argc, char** argv ) {
   std::vector<std::string> tc1_legs = { "0-1 0-3", "0-2" };
   std::vector<std::string> tc1_prices = { "5 7", "1000 1000", "1000 1000", "1000 1000" };
   std::vector<int> tc1_result = { 5,  7,  5 };

   std::vector<std::string> tc2_legs = { "0-1 1-2 2-3", "0-1 2-3" }; 
   std::vector<std::string> tc2_prices = { "1 10", "20 25", "50 50", "1000 1000", "1000 1000" };
   std::vector<int> tc2_result = { 1,  11,  31,  -1 };

   std::vector<std::string> tc3_legs = { "0-1", "1-0", "0-2", "2-3" };
   std::vector<std::string> tc3_prices = { "1 1 1000 1000", "1000 1000 10 100", 
                                           "1000 1000 1000 1000", "1000 1000 1000 1000" };
   std::vector<int> tc3_result = { 1,  12,  112 };

   std::vector<std::string> tc4_legs = { "1-0" }; 
   std::vector<std::string> tc4_prices = { "793", "350" };
   std::vector<int> tc4_result = { -1 };

   std::vector<std::string> tc5_legs = 
   {
    "8-18 4-11 15-5 7-12 11-8 0-15 15-2 3-11 4-18 2-3",
    "16-2 18-3 15-18 11-19 18-2 18-7 19-17 3-15 12-19",
    "2-17 0-12 1-2 14-12 6-2 4-2 11-5 4-11 11-6 17-16",
    "0-18 13-18 16-0 3-7 14-12 3-1 19-18 3-19 10-3 8-15",
    "18-19 3-16 13-6 0-19 12-14 5-17 1-12 7-13 9-14 1-2",
    "14-5 17-9 2-10 16-13 11-15 10-17 14-10 0-14 2-13",
    "4-5 0-17 6-9 17-7 12-6 5-6 6-18 10-18 0-2 13-0 8-4",
    "3-12 4-11 10-17 13-12 3-0 3-7 13-0 9-15 10-9 0-10" 
   };
   std::vector<std::string> tc5_prices = 
   {
    "592 219 88 529 324 86 503 610",
    "2 94 8 600 34 95 6 494",
    "638 301 10 246 290 97 85 74",
    "118 8 939 393 450 79 317 99",
    "99 806 698 740 2 26 525 818",
    "95 9 615 972 23 23 5 666",
    "6 448 440 710 83 4 419 496",
    "4 47 182 4 185 70 718 770",
    "3 321 6 855 968 65 10 6",
    "173 224 300 3 79 2 707 49",
    "21 10 7 10 4 9 5 8",
    "6 600 4 724 7 1 960 247",
    "83 16 901 50 437 780 658 2",
    "763 923 125 576 45 423 3 1",
    "7 324 391 898 8 59 281 973",
    "9 44 49 364 78 744 43 5",
    "10 62 75 418 216 90 32 919",
    "764 534 778 605 80 647 821 74",
    "65 449 102 867 421 94 6 7",
    "67 155 362 789 189 316 107 595" 
   };
   std::vector<int> tc5_result = { 170,  160,  155,  173,  145,  150,  
      158,  168,  153,  145,  162,  88,  162,  86,  163,  159,  153,  150,  104 };

   std::vector<int>     result;
   bool                 passed = true;
   IslandFerries        test;
   
   result = test.cost( tc1_legs, tc1_prices );
   if( result != tc1_result ) {
      std::cout << "Test Case 1 Failed. Result: ";
      for( int i = 0; i < result.size(); i++ ) {
         std::cout << result[i] << " ";
      }
      std::cout << " Answer: ";
      for( int i = 0; i < tc1_result.size(); i++ ) {
         std::cout << tc1_result[i] << " ";
      }
      std::cout << std::endl;
      passed = false;
   }


   result = test.cost( tc2_legs, tc2_prices );
   if( result != tc2_result ) {
      std::cout << "Test Case 2 Failed. Result: ";
      for( int i = 0; i < result.size(); i++ ) {
         std::cout << result[i] << " ";
      }
      std::cout << " Answer: ";
      for( int i = 0; i < tc2_result.size(); i++ ) {
         std::cout << tc2_result[i] << " ";
      }
      std::cout << std::endl;
      passed = false;
   }
   
   result = test.cost( tc3_legs, tc3_prices );
   if( result != tc3_result ) {
      std::cout << "Test Case 3 Failed. Result: ";
      for( int i = 0; i < result.size(); i++ ) {
         std::cout << result[i] << " ";
      }
      std::cout << " Answer: ";
      for( int i = 0; i < tc3_result.size(); i++ ) {
         std::cout << tc3_result[i] << " ";
      }
      std::cout << std::endl;
      passed = false;
   }
   
   result = test.cost( tc4_legs, tc4_prices );
   if( result != tc4_result ) {
      std::cout << "Test Case 4 Failed. Result: ";
      for( int i = 0; i < result.size(); i++ ) {
         std::cout << result[i] << " ";
      }
      std::cout << " Answer: ";
      for( int i = 0; i < tc4_result.size(); i++ ) {
         std::cout << tc4_result[i] << " ";
      }
      std::cout << std::endl;
      passed = false;
   }
   
   result = test.cost( tc5_legs, tc5_prices );
   if( result != tc5_result ) {
      std::cout << "Test Case 5 Failed. Result: ";
      for( int i = 0; i < result.size(); i++ ) {
         std::cout << result[i] << " ";
      }
      std::cout << " Answer: ";
      for( int i = 0; i < tc5_result.size(); i++ ) {
         std::cout << tc5_result[i] << " ";
      }
      std::cout << std::endl;
      passed = false;
   }

   if( passed ) std::cout << "All test cases passed" << std::endl;
}
