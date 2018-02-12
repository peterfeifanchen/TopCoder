#include<iostream>
#include<new>
#include<tuple>
#include<vector>
#include<algorithm>
#include<string>

class StepsConstruct{
 bool search( int curX, int curY, int dstX, int dstY, int k, int*** visited, 
			  std::vector<std::string> board, std::string &moves ) {
	if( k == 0 && (curX == dstX && curY == dstY ) ) {
		return true;
	} else if ( k == 0 ) return false;

	//std::cout << "k: " << k << std::endl;
	//std::cout << "(" << curX << "," << curY << ")" << std::endl;

	bool res = false;
	if( visited[curX][curY][k] != -1 ) return visited[curX][curY][k];
	if( curX - 1 >= 0 && board[curY][ curX - 1 ] != '#' ) {
		moves.push_back( 'L' );
		res = search( curX - 1, curY, dstX, dstY, k - 1, visited, board, moves );
		if( res ) { 
			//std::cout << "res is True" << std::endl;
			return res;
		}
		moves.pop_back();	
	}
	if( curX + 1 <= dstX && board[curY][ curX + 1 ] != '#' ) {
		moves.push_back( 'R' );
		res = search( curX + 1, curY, dstX, dstY, k - 1, visited, board, moves );
		if( res ) { 
			//std::cout << "res is True" << std::endl;
			return res;
		}
		moves.pop_back();	
	}
	if( curY - 1 >= 0 && board[ curY - 1 ][ curX ] != '#' ) {
		moves.push_back( 'U' );
		res = search( curX, curY - 1, dstX, dstY, k - 1, visited, board, moves );
		if( res ) { 
			//std::cout << "res is True" << std::endl;
			return res;
		}
		moves.pop_back();	
	}
	if( curY + 1 <= dstY && board[ curY + 1 ][ curX ] != '#' ) {
		moves.push_back( 'D' );
		res = search( curX, curY + 1, dstX, dstY, k - 1, visited, board, moves );
		if( res ) {
			//std::cout << "res is True" << std::endl;
			return res;
		}
		moves.pop_back();	
	}

	visited[curX][curY][k] = res;
	return res;
 } 
		
 public:
	std::string construct( std::vector<std::string> board, int k ) {
		if( board[ 0 ][ 0 ] == '#' ) return "";
	

		int startX = 0, startY = 0;		
		int ***visited = new int**[ board[0].length() ];
		for( int i = 0; i < board[ 0 ].length(); i++ ) {
			visited[i] = new int*[ board.size() ];
			for( int j = 0; j < board.size(); j++ ) {
				visited[i][j] = new int[ k+1 ];
			}	
		}

		for( int i = 0; i < board[ 0 ].length(); i++ ) {
			for( int j = 0; j < board.size(); j++ ) {
				for( int l = 0; l < k+1; l++ ) {
					visited[i][j][l] = -1;
				}
			}
		}

		std::string moves;
		bool res = search( startX, startY, board[0].length()-1, board.size()-1, k, 
						   visited, board, moves );

		for( int i = 0; i < board[ 0 ].length(); i++ ) {
			for( int j = 0; j < board.size(); j++ ) {
				delete [] visited[i][j];
			}
			delete [] visited[i];
		}
		delete [] visited;

		if( res ) {
			std::cout << moves << std::endl;
			return moves;
		}
		return "";
	}

	bool verify( std::vector<std::string> board, std::string steps ) {
		int startX = 0, startY = 0;
		int endX = board[0].length() - 1;
		int endY = board.size() - 1;

		std::cout << "(" << startX << "," << startY 
				  << ") -> (" << endX << "," << endY << ")" << std::endl;
		std::cout << steps << std::endl;

		int curX = startX, curY = startY;
		int nextX = 0, nextY = 0;

		for( int i = 0; i < steps.length(); i++ ) {
			if( steps[i] == 'U' ) {
				nextY = curY - 1;
			} else if( steps[i] == 'D' ) {
				nextY = curY + 1;
			} else if( steps[i] == 'L' ) {
				nextX = curX - 1;
			} else if( steps[i] == 'R' ) {
				nextX = curX + 1;
			}

			std::cout << "(" << nextX << "," << nextY << ")" << std::endl;

			if( nextX < 0 || nextX > endX || nextY < 0 || nextY > endY ) {
				// Off the grid
				std::cout << "off grid" << std::endl;
				return false;
			}

			if( board[nextY][nextX] == '#' ) {
				// blocked
				std::cout << "blocked" << std::endl;
				return false;
			}

			curX = nextX;
			curY = nextY;
		}
		
		if( curX == endX && curY == endY ) return true;
		return false;
	}
};

int main( int argc, char** argv ) {
	std::string board1[] = {"...",
			 			    ".#.",
			  			    "..."};
	std::vector<std::string> vector1( board1, board1 + sizeof( board1 ) / sizeof( std::string ) );
	std::tuple<std::vector<std::string>, int, bool> tc1( vector1, 4, true );
	std::string board2[] = {"...",
			 			    ".#.",
			  			    "..."};
	std::vector<std::string> vector2( board2, board2 + sizeof( board2 ) / sizeof( std::string ) );
	std::tuple<std::vector<std::string>, int, bool> tc2( vector2, 12, true );
	std::string board3[] = {"...#.",
			 				"..#..",
			  				".#..."};
	std::vector<std::string> vector3( board3, board3 + sizeof( board3 ) / sizeof( std::string ) );
	std::tuple<std::vector<std::string>, int, bool> tc3( vector3, 100, false );
	std::string board4[] = {"..#",
			 				"#.#",
			  				"..#",
			   				".#.",
			    			"..."};
	std::vector<std::string> vector4( board4, board4 + sizeof( board4 ) / sizeof( std::string ) );
	std::tuple<std::vector<std::string>, int, bool> tc4( vector4, 6, false );
	std::string board5[] = {".#...",
			 				".#.#.",
			  				".#.#.",
			   				".#.#.",
			    			"...#."};
	std::vector<std::string> vector5( board5, board5 + sizeof( board5 ) / sizeof( std::string ) );
	std::tuple<std::vector<std::string>, int, bool> tc5( vector5, 16, true );
	std::string board6[] = {"#.", 
		    				".."};
	std::vector<std::string> vector6( board6, board6 + sizeof( board6 ) / sizeof( std::string ) );
	std::tuple<std::vector<std::string>, int, bool> tc6( vector6, 2, false );

	StepsConstruct test;
	bool answer, result;
   	bool	fail = false;
	result = test.verify( std::get<0>( tc1 ), 
					      test.construct( std::get<0>( tc1 ), std::get<1>( tc1 ) ) );
	answer = std::get<2>( tc1 );
	if( result != answer ) {
		std::cout << "FAIL TC1: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.verify( std::get<0>( tc2 ),
					      test.construct( std::get<0>( tc2 ), std::get<1>( tc2 ) ) );
	answer = std::get<2>( tc2 );
	if( result != answer ) {
		std::cout << "FAIL TC2: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.verify( std::get<0>( tc4 ),
						  test.construct( std::get<0>( tc4 ), std::get<1>( tc4 ) ) );
	answer = std::get<2>( tc4 );
	if( result != answer ) {
		std::cout << "FAIL TC5: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.verify( std::get<0>( tc5 ),
						  test.construct( std::get<0>( tc5 ), std::get<1>( tc5 ) ) );
	answer = std::get<2>( tc5 );
	if( result != answer ) {
		std::cout << "FAIL TC5: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.verify( std::get<0>( tc6 ), 
						  test.construct( std::get<0>( tc6 ), std::get<1>( tc6 ) ) );
	answer = std::get<2>( tc6 );
	if( result != answer ) {
		std::cout << "FAIL TC6: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.verify( std::get<0>( tc3 ),
					      test.construct( std::get<0>( tc3 ), std::get<1>( tc3 ) ) );
	answer = std::get<2>( tc3 );
	if( result != answer ) {
		std::cout << "FAIL TC3: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	if( !fail ) {
		std::cout << "PASS ALL" << std::endl;
	}
}

