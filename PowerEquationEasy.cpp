#include<iostream>
#include<tuple>
#include<algorithm>
#include <iostream>
 
using namespace std;
 
class PowerEquationEasy{
 public:			
	int gcd(int a, int b){
		if(a==0) return b;
		return gcd(b%a, a);										      
	}
						    					    
	long long add(int n, int a, int b){						      
		return n*gcd(a,b)/max(a, b);									   
	}
							    						    
	int count(int n){								        
		long long v = n;										
		int b[25];
		long long m = 1000000007;

		for(int k=0; k<25; k++){
			b[k] = 0;
			for(int i=1; i<=k; i++){
				for(int j=1; j<=k; j++){
					b[k]+=add(n, i, j);
					b[k]%=m;

				}
			}
			cout << k << ": " << b[k] << endl;
		}
		bool c[1000007];
		for(long long i=0; i<=v; i++){
        	c[i] = false;           
		}                            
		long long t = (v*v)%m;         
		for(long long i=2; i<=v; i++){
			if(!c[i]){
				int num = 0;      
				long long k = i;
				while(k<=v){
					c[k] = true;
					k*=i;       
					num++;
				}
				t+=b[num];
				t%=m;
			}
		}
		return t;
	}
};

int main( int argc, char** argv ) {
	std::tuple<int, int> tc1( 1, 1 );
	std::tuple<int, int> tc2( 2, 6 );
	std::tuple<int, int> tc3( 3, 15 );
	std::tuple<int, int> tc4( 4, 32 );
	std::tuple<int, int> tc5( 5, 49 );
	std::tuple<int, int> tc6( 6, 72 );
	std::tuple<int, int> tc7( 100, 21620 );
	std::tuple<int, int> tc8( 22306, 68467 );

	PowerEquationEasy test;
	long long result = 0, answer;
	bool fail = false;
	result = test.count( std::get<0>( tc1 ) );
	answer = std::get<1>( tc1 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.count( std::get<0>( tc2 ) );
	answer = std::get<1>( tc2 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.count( std::get<0>( tc3 ) );
	answer = std::get<1>( tc3 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.count( std::get<0>( tc4 ) );
	answer = std::get<1>( tc4 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.count( std::get<0>( tc5 ) );
	answer = std::get<1>( tc5 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.count( std::get<0>( tc6 ) );
	answer = std::get<1>( tc6 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.count( std::get<0>( tc7 ) );
	answer = std::get<1>( tc7 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	result = test.count( std::get<0>( tc8 ) );
	answer = std::get<1>( tc8 );
	if( result != answer ) {
		std::cout << "FAIL: Result - " << result << " Answer - " << answer << std::endl;
		fail = true;
	}
	if( !fail ) {
		std::cout << "PASS" << std::endl;
	}
}
