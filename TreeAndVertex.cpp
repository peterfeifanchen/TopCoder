#include<iostream>
#include<tuple>
#include<vector>
#include<algorithm>

class TreeAndVertex{
 public:
	int get( std::vector<int> v ) {
		std::vector<int> count( v.size()+1, 0 );
		for( int i = 0; i < v.size(); i++ ) {
			int vertex = v[ i ];
			count[ vertex ]++;
		}

		//find max
		int max_val = count[ 0 ];
		for( int j = 1; j < count.size(); j++ ) {
			max_val = std::max( max_val, count[j] + 1 );	
		}

		return max_val;
	}
};

int main( int argc, char** argv ) {
	int test_case_1[] = {0,0,0};
	std::vector<int> vector_1( test_case_1, test_case_1 + sizeof( test_case_1 )/ sizeof( int ) );
	
	std::cout << test_case_1 << " " << &test_case_1[2] << std::endl;
	std::cout << sizeof( test_case_1 )/ sizeof( int ) << std::endl;
	std::cout << test_case_1 + sizeof( test_case_1 )/ sizeof( int ) << std::endl;

	std::tuple<std::vector<int>, int> tc1( vector_1, 3 );
	int test_case_2[] = {0,1,2,3};
	std::vector<int> vector_2( test_case_2, test_case_2 + sizeof( test_case_2 )/ sizeof( int ) );
	std::tuple<std::vector<int>, int> tc2( vector_2, 2 );
	int test_case_3[] = {0,0,2,2};
	std::vector<int> vector_3( test_case_3, test_case_3 + sizeof( test_case_3 )/ sizeof( int ) );
	std::tuple<std::vector<int>, int> tc3( vector_3, 3 );
	int test_case_4[] = {0,0,0,1,1,1};
	std::vector<int> vector_4( test_case_4, test_case_4 + sizeof( test_case_4 )/ sizeof( int ) );
	std::tuple<std::vector<int>, int> tc4( vector_4, 4 );
	int test_case_5[] = {0, 1, 2, 0, 1, 5, 6, 1, 7, 4, 2, 5, 5, 8, 6, 2, 14, 12, 18, 10, 0, 6, 18, 2, 20, 11, 0, 11, 7, 12, 17, 3, 18, 31, 14, 34, 30, 11, 9};
	std::vector<int> vector_5( test_case_5, test_case_5 + sizeof( test_case_5 )/ sizeof( int ) );
	std::tuple<std::vector<int>, int> tc5( vector_5, 5 );
	
	TreeAndVertex test;
	long long result = 0, answer;
	bool fail = false;
	result = test.get( std::get<0>( tc1 ) );
	answer = std::get<1>( tc1 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.get( std::get<0>( tc2 ) );
	answer = std::get<1>( tc2 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.get( std::get<0>( tc3 ) );
	answer = std::get<1>( tc3 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.get( std::get<0>( tc4 ) );
	answer = std::get<1>( tc4 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.get( std::get<0>( tc5 ) );
	answer = std::get<1>( tc5 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	
	if( !fail ) {
		std::cout << "PASS" << std::endl;
	}
}
