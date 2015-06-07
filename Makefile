all:
	@g++ ./GeneticAlgorithmShortestPath/*.cpp -std=c++11 -O3 -o routing

run:
	@./routing

clean:
	@rm routing
