all:
	@g++ ./GeneticAlgorithmShortestPath/*.cpp -std=c++11 -ljsoncpp -O3 -o routing

run:
	@./routing 'Graph:  {"directed": false, "graph": [], "nodes": [{"id": 1}, {"id": 2}, {"id": 3}, {"id": 4}, {"id": 5}, {"id": 6}, {"id": 7}, {"id": 8}], "links": [{"source": 0, "target": 1, "weight": 1}, {"source": 0, "target": 2, "weight": 1}, {"source": 0, "target": 3, "weight": 1}, {"source": 1, "target": 4, "weight": 1}, {"source": 2, "target": 5, "weight": 1}, {"source": 3, "target": 6, "weight": 1}, {"source": 4, "target": 7, "weight": 1}, {"source": 5, "target": 7, "weight": 1}, {"source": 6, "target": 7, "weight": 1}], "multigraph": false}' 0 7

clean:
	@rm routing
