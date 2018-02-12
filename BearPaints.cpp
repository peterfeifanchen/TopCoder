#include<iostream>
#include<tuple>
#include<algorithm>

class BearPaints{
 public:
	long long maxArea( int W, int H, long long M ) {
		long long max_area = 0;
		long long i = W, j = H;
		if( i*j <= M ) {
			return i*j;
		}

		for( ; i > 0; i-- ) {
			long long h = M / i;
			if( h < j ) {
				max_area = std::max( max_area, h * i );	
			} else {
				break;
			}
		}
		return max_area;
	}
};

int main( int argc, char** argv ) {
	std::tuple<int, int, long long, long long> tc1( 3, 5, 14, 12 );
	std::tuple<int, int, long long, long long> tc2( 4, 4, 10, 9 );
	std::tuple<int, int, long long, long long> tc3( 1000000, 12345, 1000000000000, 12345000000 );
	std::tuple<int, int, long long, long long> tc4( 1000000, 1000000, 720000000007, 720000000000 );
	std::tuple<int, int, long long, long long> tc5( 1000000, 1000000, 999999999999, 999999000000 );

	BearPaints test;
	long long result = 0, answer;
	bool fail = false;
	result = test.maxArea( std::get<0>( tc1 ), std::get<1>( tc1 ), std::get<2>( tc1 ) );
	answer = std::get<3>( tc1 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.maxArea( std::get<0>( tc2 ), std::get<1>( tc2 ), std::get<2>( tc2 ) );
	answer = std::get<3>( tc2 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.maxArea( std::get<0>( tc3 ), std::get<1>( tc3 ), std::get<2>( tc3 ) );
	answer = std::get<3>( tc3 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.maxArea( std::get<0>( tc4 ), std::get<1>( tc4 ), std::get<2>( tc4 ) );
	answer = std::get<3>( tc4 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.maxArea( std::get<0>( tc5 ), std::get<1>( tc5 ), std::get<2>( tc5 ) );
	answer = std::get<3>( tc5 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	if( !fail ) {
		std::cout << "PASS" << std::endl;
	}
}
