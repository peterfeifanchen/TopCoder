#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<tuple>

// SRM717

class LexmaxReplace {
   
 public:
   std::string get( std::string ws, std::string cs ) {
      int j = 0;
      std::sort( cs.begin(), cs.end(), std::greater<char>() );
      for( int i = 0; i < ws.length(); i++ ) {
         if( ws[ i ] < cs[ j ] ) {
            ws[ i ] = cs[ j ];
            j++;
         }
      }
      return ws;
   }

   bool operator<( std::string rhs ) const {
      return true; 
   }
};

int main( int argc, char** argv ) {
   std::tuple<std::string, std::string, std::string> tc1( std::string( "abb" ), 
                                                          std::string( "c" ),
                                                          std::string( "cbb" ) );
   std::tuple<std::string, std::string, std::string> tc2( std::string( "z" ), 
                                             std::string( "f" ),
                                             std::string( "z" ) );
   std::tuple<std::string, std::string, std::string> tc3( std::string( "fedcba" ), 
                                             std::string( "ee" ),
                                             std::string( "feeeba" ) );
   std::tuple<std::string, std::string, std::string> tc4( std::string( "top" ), 
                                             std::string( "coder" ),
                                             std::string( "trp" ) );
   std::tuple<std::string, std::string, std::string> tc5( 
         std::string( "xldyzmsrrwzwaofkcxwehgvtrsximxgdqrhjthkgfucrjdvwlr" ), 
         std::string( "xfpidmmilhdfzypbguentqcojivertdhshstkcysydgcwuwhlk" ), 
         std::string( "zyyyzyxwwwzwvuuttxwtssvtssxrqxppqrontmmllukrkjvwlr" ) );
   
   std::string result, answer;
   LexmaxReplace test;
   bool fail = false;
   result = test.get( std::get<0>( tc1 ), std::get<1>( tc1 ) );
   answer = std::get<2>( tc1 );
   if( result != answer ) {
      std::cout << "Test Case 1 Failed. Answer: " << answer << " Result: " << result << std::endl;
      fail = true;
   }
   result = test.get( std::get<0>( tc2 ), std::get<1>( tc2 ) );
   answer = std::get<2>( tc2 );
   if( result != answer ) {
      std::cout << "Test Case 2 Failed. Answer: " << answer << " Result: " << result << std::endl;
      fail = true;
   }
   result = test.get( std::get<0>( tc3 ), std::get<1>( tc3 ) );
   answer = std::get<2>( tc3 );
   if( result != answer ) {
      std::cout << "Test Case 3 Failed. Answer: " << answer << " Result: " << result << std::endl;
      fail = true;
   }
   result = test.get( std::get<0>( tc4 ), std::get<1>( tc4 ) );
   answer = std::get<2>( tc4 );
   if( result != answer ) {
      std::cout << "Test Case 4 Failed. Answer: " << answer << " Result: " << result << std::endl;
      fail = true;
   }
   result = test.get( std::get<0>( tc5 ), std::get<1>( tc5 ) );
   answer = std::get<2>( tc5 );
   if( result != answer ) {
      std::cout << "Test Case 5 Failed. Answer: " << answer << " Result: " << result << std::endl;
      fail = true;
   }

   if( !fail ) std::cout << "All test cases passed" << std::endl;
   
}
