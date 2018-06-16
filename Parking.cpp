#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <map>
#include <algorithm>
#include <climits>

// The implementation of the graph is a bit dumb, probably should have used a 2D
// matrix. But too lazy to go back and change everything.

class Parking {
   class Location{
    public:
      Location() : x_(-1), y_(-1) {}
      Location( int x, int y ) : x_(x), y_(y) {}
      inline bool operator==( const Location &rhs ) const { 
         if( this->x_ == rhs.x_ && this->y_ == rhs.y_ ) return true;
         return false;
      }
      inline bool operator=( const Location &rhs ) { 
         x_ = rhs.x_;
         y_ = rhs.y_;
      }
      Location( const Location&& l ) : x_(l.x_), y_(l.y_) {}
      Location( const Location& l ) : x_(l.x_), y_(l.y_) {}
   
      int x_;
      int y_;
   };
      
   class Vertex {
    public:
      Vertex() : loc_( Location( -1, -1 ) ) {}
      Vertex( const Location&& loc ) : loc_(loc) {}
      Vertex( const Location& loc ) : loc_(loc) {}
      inline bool operator==( const Vertex &rhs ) const {
         if( this->loc_ == rhs.loc_ ) return true;
         return false;
      }
     
      inline bool operator=( const Vertex &rhs ) {
         loc_.x_ = rhs.loc_.x_;
         loc_.y_ = rhs.loc_.y_;
      }

      Location                   loc_;
   };

   class Edge {
    public:
      Edge( int w, Location& source, Location& sink ) : w_(w), 
         source_(source), sink_(sink) {}
      Edge( const Edge& e ) : w_(e.w_), source_(e.source_), sink_(e.sink_) {}
      Edge( const Edge&& e ) : w_(e.w_), source_(e.source_), sink_(e.sink_) {}
      inline bool operator=( const Edge &e ) {
         w_ = e.w_;
         source_ = e.source_;
         sink_ = e.sink_;

      }
     
      int         w_;
      Location    source_;
      Location    sink_;
   };
   
   class Path {
    public:
      class PathComparator {
       public:
         bool operator() (const Path& lhs, const Path rhs ) {
            return lhs.capacity < rhs.capacity;
         }
      };

      Path() : capacity(INT_MAX) {}

      Path( Vertex& v ) : cur( &v ), capacity(INT_MAX) {
         p.push_back( &v );
      }

      Path( const Path& curPath ) : cur( curPath.cur ), 
         p( std::vector<Vertex*>( curPath.p ) ), capacity(curPath.capacity) {}
     
      bool hasVertex( Vertex &v ) {
         for( auto it = p.begin(); it != p.end() - 1; it++ ) {
            if( (**it) == v ) return true; 
         }
         return false;
      }

      Vertex*              cur;
      std::vector<Vertex*> p; 
      int                  capacity;
   };

   class Graph {
    public:
       Graph() : start( Location( -2, -2 ) ), end( Location( -3, -3 ) ) {}
       Graph( const Graph &g ) : start( g.start.loc_ ), end( g.end.loc_ ), 
               cars( std::vector<Vertex>( g.cars ) ), 
               parkings( std::vector<Vertex>( g.parkings ) ),
               e( std::vector<Edge>( g.e ) ) {}

       Vertex& getCar( const Location& loc ) {
         for (auto it = cars.begin(); it != cars.end(); it++) {
            if( it->loc_ == loc ) {
               return *it;
            }
         }
      }
      
      Vertex& getParking( const Location& loc ) {
         for (auto it = parkings.begin(); it != parkings.end(); it++) {
            if( it->loc_ == loc ) return *it;
         }
      }

      Vertex& getVertex( const Location& loc ) {
         if( loc == start.loc_ ) return start;
         if( loc == end.loc_ ) return end;
         for( auto it = parkings.begin(); it != parkings.end(); it++ ) {
            if( it->loc_ == loc ) return *it;
         }
         return getCar( loc );
      }

      Edge* getEdge( const Vertex& source, const Vertex& sink ) {
         for (auto it = e.begin(); it != e.end(); it++ ) {
            if( it->source_ == source.loc_ && it->sink_ == sink.loc_ ) 
               return &(*it);
         }
         //std::cout << " Edge " << source << "->" << sink << " not found" << std::endl;
         return NULL;
      }

      void removeEdge( const Edge& edge ) {
         auto it = e.begin();
         while( it != e.end() ) {
            if( it->source_ == edge.source_ && it->sink_ == edge.sink_ ) {
               e.erase(it);
               break;
            }
            it++;
         }
      }

      void removeEdge( const Vertex& source, const Vertex& sink ) {
         auto it = e.begin();
         while( it != e.end() ) {
            //std::cout << "edge source_: " << it->source_ << " sink_: " <<it->sink_ << std::endl;
            if( it->source_ == source.loc_ && it->sink_ == sink.loc_ ) {
               e.erase(it);
               break;
            }
            it++;
         }
      }

      void printGraph() {
         std::cout << "All edges: " << std::endl;
         for( auto it = e.begin(); it != e.end(); it++ ) {
            std::cout << "  " << *it << std::endl;
         }

         std::cout << "All vertices: " << std::endl;
         std::cout << " " << start << std::endl;
         for( auto it = cars.begin(); it != cars.end(); it++ ) {
            std::cout << " " << *it << std::endl;
         }
         for( auto it = parkings.begin(); it != parkings.end(); it++ ) {
            std::cout << " " << *it << std::endl;
         }
         std::cout << " " << end << std::endl;
      }
   
      Vertex              start;
      Vertex              end;
      std::vector<Vertex> cars;
      std::vector<Vertex> parkings;
      std::vector<Edge>   e;
   };

   // validMoveBFS checks if the location can be moved to. E.g., not out of bounds,
   // is an 'X'.
   bool validMoveBFS( std::vector<std::string> &map, const Location& loc ) {
      if( loc.x_ < 0 || loc.x_ >= map.size() ) return false;
      else if( loc.y_ < 0 || loc.y_ >= map[0].size() ) return false;
      else if( map[ loc.x_ ][ loc.y_ ] == 'X' ) return false;
      return true;
   }

   // buildGraphBFS bfs searches the input grid 'in' to find the distance to each
   // parking spot
   void buildGraphBFS( std::vector<std::string> &map, 
            const Location& car, Graph &g ) {
      // Visited grid
      std::vector<int> row( map[0].size(), -1 );
      std::vector<std::vector<int>> visited( map.size(), row );
      
      std::queue<Location> lqueue;
      lqueue.push( car );
      Vertex& c = g.getCar( car );
      visited[ car.x_][ car.y_ ] = 0;
      //std::cout << "buildGraphBFS: car " << c << std::endl;
      int parkingFound = 0;
      while( !lqueue.empty() && parkingFound < g.parkings.size() ) {
         Location &l = lqueue.front();
         if ( map[ l.x_ ][ l.y_ ] == 'P' ) {
            parkingFound++;
            Vertex& p = g.getParking( l );
            //std::cout << "buildGraphBFS: car->parking found " << c << "->" << p
            //      << " w=" << visited[ l.x_ ][ l.y_ ] << std::endl;
            g.e.push_back( Edge( visited[ l.x_ ][ l.y_ ], c.loc_, p.loc_ ) );
         }
         if( validMoveBFS( map, Location( l.x_-1, l.y_ ) ) && 
            ( visited[ l.x_-1 ][ l.y_ ] == -1 ) ) {
            visited[ l.x_-1 ][ l.y_ ] = visited[ l.x_ ][ l.y_ ] + 1; 
            lqueue.push( Location( l.x_-1, l.y_ ) );
         } 
         if( validMoveBFS( map, Location( l.x_, l.y_-1 ) ) && 
            ( visited[ l.x_ ][ l.y_-1 ] == -1 ) ) {
            visited[ l.x_ ][ l.y_-1 ] = visited[ l.x_ ][ l.y_ ] + 1; 
            lqueue.push( Location( l.x_, l.y_-1 ) );
         }
         if( validMoveBFS( map, Location( l.x_, l.y_+1 ) ) && 
            ( visited[ l.x_ ][ l.y_+1 ] == -1 ) ) {
            visited[ l.x_ ][ l.y_+1 ] = visited[ l.x_ ][ l.y_ ] + 1; 
            lqueue.push( Location( l.x_, l.y_+1 ) );
         }
         if( validMoveBFS( map, Location( l.x_+1, l.y_ ) ) &&
            ( visited[ l.x_+1 ][ l.y_ ] == -1 ) ) {
            visited[ l.x_+1 ][ l.y_ ] = visited[ l.x_ ][ l.y_ ] + 1; 
            lqueue.push( Location( l.x_+1, l.y_ ) );
         }
         lqueue.pop();
      }
   }

   void printVertexMap( std::map<Vertex*, bool> &m ) {
      for( auto it = m.begin(); it != m.end(); it++ ) {
         std::cout << "Vertex " << *it->first << "=" << it->second  << std::endl;
      }
   }

   bool findPathPriority( Graph &g ) {
      // construct visted vector
      std::map<Vertex*, bool> visited;
      visited.insert( std::pair<Vertex*, bool>( &(g.start), false ) );
      visited.insert( std::pair<Vertex*, bool>( &(g.end), false ) );
      for( auto c = g.cars.begin(); c != g.cars.end(); c++ ) {
         visited.insert( std::pair<Vertex*, bool>( &(*c), false ) );
      }
      for( auto p = g.parkings.begin(); p != g.parkings.end(); p++ ) {
         visited.insert( std::pair<Vertex*, bool>( &(*p), false ) );
      }
      //printVertexMap( visited );

      // find path with maximum capacity
      Path finalPath;
      std::priority_queue<Path, std::vector<Path>, Path::PathComparator> pqueue;
      pqueue.push( Path( g.start ) );     
      bool pathFound = false;
      while( !pqueue.empty() && pathFound == false ) {
         Path p = pqueue.top();
         pqueue.pop();
         //std::cout << "Current path: " << p << std::endl;
         if( visited[ p.cur ] == true ) {
            //std::cout << "Already visited vertex: " << *(p.cur) << " " << std::endl;
            continue;
         }
         visited[ p.cur ] = true;
         for( auto it = g.e.begin(); it != g.e.end(); it++ ) {
            if( it->source_ == p.cur->loc_ ) {
               //std::cout << "   Found edge: " << *it << std::endl;
               Path pCopy = Path( p );
               Vertex &v = g.getVertex( it->sink_ );
               pCopy.cur = &v;
               pCopy.capacity = std::min( it->w_, pCopy.capacity ); 
               pCopy.p.push_back( &v );
               //std::cout << "   Copy path: " << pCopy << std::endl;
               if( it->sink_ == g.end.loc_ ) {
                  finalPath = pCopy;
                  pathFound = true;
                  break;
               } else {
                  pqueue.push( pCopy );
               }
            }
         }
      }
 
      if( pathFound == false ) return false;

      //std::cout << "    FinalPath: " << finalPath << std::endl;

      // reconstruct residual graph g and the path chosen
      for( int i = 0; i < finalPath.p.size()-1; i++ ) {
         Edge *forward = g.getEdge( *(finalPath.p[i]), *(finalPath.p[i+1]) );
         if( forward == NULL ) {
            std::cout << "findPathPriority(): no edge " << *(finalPath.p[i])
               << "->" << *(finalPath.p[i+1]) << std::endl;
            exit(0);
         }
         forward->w_ -= finalPath.capacity;
         if( forward->w_ == 0 ) g.removeEdge( *forward );
         Edge *backward = g.getEdge( *(finalPath.p[i+1]), *(finalPath.p[i]) );
         if( backward == NULL ) {
            g.e.push_back( Edge( finalPath.capacity, finalPath.p[i+1]->loc_, 
                     finalPath.p[i]->loc_ ) );
         } else {
            backward->w_ += finalPath.capacity;
         }
      }

      return true;
   }

   // maxFlow calculates the maximum flow that can occur in the bipartite graph g.
   // It returns the set of paths that forms maximum flow.
   int maxFlow( Graph g, Graph& origG ) {
     
      // maxFlow algorithm with modifications:
      //    (1) find a path (priority first search)
      //        a. if not found, exit loop
      //        b. if found, iterate
      //    (2) find all paths that lead from end->start 
      
      //int i = 0;
      while( true ) {
         //std::cout << std::endl << "max flow iteration: " << i 
         //   << std::endl << std::endl;
         //g.printGraph();
         if( !findPathPriority( g ) ) break; 
         //i++;
      }

      // Find selected maxFlow paths
      // 1) remove all paths from cars->parkings
      // 2) walk from end-> start
      for( auto c = g.cars.begin(); c != g.cars.end(); c++ ) {
         for( auto p = g.parkings.begin(); p != g.parkings.end(); p++ ) {
            g.removeEdge( *c, *p ); 
         }
      }
     
      //g.printGraph();

      std::vector<Path> paths; 
      std::queue<Path> pQueue; 
      pQueue.push( Path( g.end ) );
      while( !pQueue.empty() ) {
         Path& p = pQueue.front();
         for( auto it = g.e.begin(); it != g.e.end(); it++ ) {
            if( it->source_ == p.cur->loc_ ) {
               Path pCopy = Path( p );
               Vertex &v = g.getVertex( it->sink_ );
               pCopy.cur = &v;
               pCopy.p.push_back( &v );
               if( v == g.start ) {
                  paths.push_back( pCopy );
               } else {
                  // if we did not create a cycle (e.g., sink vertex
                  // is not any of the vertex on our current path
                  if( !pCopy.hasVertex(v) ) {
                     pQueue.push( pCopy );
                  }
               }
            }
         }
         pQueue.pop();
      }

      //std::cout << "    Found " << paths.size() << " paths" << std::endl;
      
      if( paths.size() != g.cars.size() ) return -1; 
      
      // Calculate the time cost of the bipartite graph with min max-flow 
      // solution.
      int totalTime = 0;
      //std::cout << "Paths: " << std::endl;
      for( auto it = paths.begin(); it != paths.end(); it++ ) {
         //std::cout << " " << *it << std::endl;
         int cost = 0;
         for( auto v = it->p.begin(); v != it->p.end(); v++ ) {
            //std::cout << " looking at vertex " << **v << std::endl;
            if( **v == origG.end ) continue;
            if( **v == origG.start ) continue;
            Edge *tmp = origG.getEdge( **(v+1), **v );
            cost = tmp->w_;
            break;
         }
         totalTime = std::max( totalTime, cost );
      }

      //std::cout << "Time: " << totalTime << std::endl;
      return totalTime;
   }

   friend std::ostream& operator<<( std::ostream& out, 
         const Parking::Location& loc );
   friend std::ostream& operator<<( std::ostream& out, const Parking::Vertex& v );
   friend std::ostream& operator<<( std::ostream& out, const Parking::Edge& e ); 
   friend std::ostream& operator<<( std::ostream& out, const Parking::Path& p ); 

 public:
   int minTime( std::vector<std::string> &in ) { 
      // 1. Transform vector<string> into a bipartite graph of cars and parking.
      //    A single source connects to all cars with weight 1.
      //    A single sink node connects to all parking with weight 1.
      //    a) Find location of all cars
      //    b) Find location of all parking
      //    c) For each car and parking, bfs search the shortest path
      Graph g;
      for( int i = 0; i < in.size(); i++ ) {
         for( int j = 0; j < in[0].size(); j++ ) {
            switch ( in[i][j] ) {
               case 'C':
                  g.cars.push_back( Location( i, j ) ); 
                  break;
               case 'P':
                  g.parkings.push_back( Location( i, j) ); 
                  break;
            }
         }
      }
      
      for( auto it = g.cars.begin(); it != g.cars.end(); it++ ) {
         this->buildGraphBFS( in, it->loc_, g );
         g.e.push_back( Edge( 1, g.start.loc_, it->loc_ ) );
      }
      for( auto it = g.parkings.begin(); it != g.parkings.end(); it++ ) {
         g.e.push_back( Edge( 1, it->loc_, g.end.loc_ ) );
      }

      //g.printGraph();
      // 2. Run maximum flow algorithm. Check if returned graph contains all cars.
      //    If not, return -1. This can be found by comparing the number of paths 
      //    returned vs. number of cars. If there is a solution, calculate its cost
      //    by max( path_cost( car, parking ) )
      int res =  this->maxFlow( g, g );  
      int lastRes = -1;

      // 3. In a loop, successively remove the highest edge between cars and parking
      //    in the bipartitie graph until no solution can be found. On each iter, we
      //    perform maximum flow on a copy of the current graph.
      while( res != -1 ) {
         //g.printGraph();
         lastRes = res;
         
         std::vector<Edge*> highestEdgePerCar;
         Edge* edgeToRemove = NULL;
         for( auto c = g.cars.begin(); c != g.cars.end(); c++ ) {
            int count = 0;
            Edge *highest = NULL;
            for( auto p = g.parkings.begin(); p != g.parkings.end(); p++ ) {
               //std::cout << "  car " << *c << " parking " << *p << std::endl;
               Edge *tmp = g.getEdge( *c, *p );
               if( tmp != NULL ) {
                  count++;
                  if( highest != NULL ) {
                     if ( tmp->w_ > highest->w_ ) highest = tmp;
                  } else {
                     highest = tmp;
                  }
               }
            }

            if( count > 1 ) {
               highestEdgePerCar.push_back( highest );
            }
         }

         for( auto it = highestEdgePerCar.begin(); it != highestEdgePerCar.end(); 
               it++ ) {
            if( edgeToRemove == NULL || edgeToRemove->w_ < (*it)-> w_ ) {
               edgeToRemove = *it;
            }
         }

         if( edgeToRemove == NULL ) break;
         g.removeEdge( *edgeToRemove );

         res = this->maxFlow( g, g );
         //std::cout << "res: " << res << " lastRes: " << lastRes << std::endl;
      }

      return lastRes;
   }

};
   
std::ostream& operator<<( std::ostream& out, const Parking::Location& loc ) {
   return out << "[" << loc.x_  << "," << loc.y_ << "]";
}
            
std::ostream& operator<<( std::ostream& out, const Parking::Vertex& v ) {
   return out << v.loc_ << " addr=" << &v;
}

std::ostream& operator<<( std::ostream& out, const Parking::Edge& e ) {
   return out << e.source_ << "->" << e.sink_ << " w=" << e.w_ << " addr=" << &e;
}

std::ostream& operator<<( std::ostream& out, const Parking::Path& p ) {
   for( auto it = p.p.begin(); it != p.p.end(); it++ ) {
        out << **it << " -> ";
   }
   out << " cur=" << *(p.cur) << " capacity=" << p.capacity;
   return out;
}

int main( int argc, char** argv ) {
   std::vector<std::string> tc1 = {
      "C.....P",
      "C.....P",
      "C.....P"
   };
   int expected1 = 6;

   std::vector<std::string> tc2 = {
      "C.X.....",
      "..X..X..",
      "..X..X..",
      ".....X.P"
   };
   int expected2 = 16;

   std::vector<std::string> tc3 = {
      "XXXXXXXXXXX",
      "X......XPPX",
      "XC...P.XPPX",
      "X......X..X",
      "X....C....X",
      "XXXXXXXXXXX"
   };
   int expected3 = 5;

   std::vector<std::string> tc4 ={
      ".C.",
      "...",
      "C.C",
      "X.X",
      "PPP"
   };
   int expected4 = 4;
   
   std::vector<std::string> tc5 = {
      "CCCCC",
      ".....",
      "PXPXP"
   };
   int expected5 = -1;

   std::vector<std::string> tc6 = {
      "..X..",
      "C.X.P",
      "..X.."
   };
   int expected6 = -1;

   Parking test;
   int     result;
   bool    failed = false;

   result = test.minTime(tc1);
   if( result != expected1 ) {
      std::cout << "Test Case 1 Failed. Result: " << result << 
                  " Expected: " << expected1 << std::endl;
      failed = true;
   }
   
   result = test.minTime(tc2);
   if( result != expected2 ) {
      std::cout << "Test Case 2 Failed. Result: " << result << 
                  " Expected: " << expected2 << std::endl;
      failed = true;
   }
   
   result = test.minTime(tc3);
   if( result != expected3 ) {
      std::cout << "Test Case 3 Failed. Result: " << result << 
                  " Expected: " << expected3 << std::endl;
      failed = true;
   }
   
   result = test.minTime(tc4);
   if( result != expected4 ) {
      std::cout << "Test Case 4 Failed. Result: " << result << 
                  " Expected: " << expected4 << std::endl;
      failed = true;
   }
   
   result = test.minTime(tc5);
   if( result != expected5 ) {
      std::cout << "Test Case 5 Failed. Result: " << result << 
                  " Expected: " << expected5 << std::endl;
      failed = true;
   }
   
   result = test.minTime(tc6);
   if( result != expected6 ) {
      std::cout << "Test Case 6 Failed. Result: " << result << 
                  " Expected: " << expected6 << std::endl;
      failed = true;
   }

   if( !failed ) {
      std::cout << "All test passed." << std::endl; 
   }
}
