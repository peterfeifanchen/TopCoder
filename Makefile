CheatCode: CheatCode.cpp
	g++ -std=c++11 $< -o $@

Boxing: Boxing.cpp
	g++ -std=c++11 $< -o $@

StarAdventure: StarAdventure.cpp
	g++ -std=c++11 $< -o $@

QueenInterference: QueenInterference.cpp
	g++ -std=c++11 -g -O0 $< -o $@

Parking: Parking.cpp
	g++ -std=c++11 -g -O0 $< -o $@

.PHONY: clean
clean:
	rm Boxing StarAdventure CheatCode QueenInterference Parking
