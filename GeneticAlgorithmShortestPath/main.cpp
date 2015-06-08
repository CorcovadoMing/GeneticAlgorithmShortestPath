#include <iostream>
#include <sstream>
#include "GeneticAlgorithm.h"
#include <json/json.h>

int main(int argc, const char * argv[])
{
    std::stringstream src_ss, dst_ss;
    std::string raw_graph;
    int src, dst;
    src_ss << argv[2];
    src_ss >> src;
    dst_ss << argv[3];
    dst_ss >> dst;
    
    if (argc != 4) return 0;
    else
    {
        raw_graph = argv[1];
        
        Json::Value root;
        Json::Reader reader;
        
        bool parsingSuccessful = reader.parse(raw_graph, root);
        if ( !parsingSuccessful )
        {
            std::cout << "[Error] when parse graph" << std::endl;
            return 1;
        }
        else
        {
            const Json::Value nodes = root["nodes"];
            const int graph_size = nodes.size();
            
            GeneticAlgorithm geneticAlgorithm(0.4);
            geneticAlgorithm.setGraphSize(graph_size);
            
            
            const Json::Value links = root["links"];
            for (int i = 0; i < links.size(); i += 1)
            {
                geneticAlgorithm.buildGraph(links[i]["source"].asInt(), links[i]["target"].asInt(), links[i]["weight"].asInt());
            }
            
            geneticAlgorithm.goal(src-1, dst-1);
            geneticAlgorithm.initial();
            
            do
            {
                geneticAlgorithm.selection();
                geneticAlgorithm.crossover();
                geneticAlgorithm.mutation();
            }
            while (geneticAlgorithm.notConverge());
            
            std::cout << geneticAlgorithm.getSolution();
            
            return 0;
        }
    }
}
