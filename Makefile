CheatCode: CheatCode.cpp
	g++ -std=c++11 $< -o $@

Boxing: Boxing.cpp
	g++ -std=c++11 $< -o $@

StarAdventure: StarAdventure.cpp
	g++ -std=c++11 $< -o $@

.PHONY: clean
clean:
	rm Boxing StarAdventure
