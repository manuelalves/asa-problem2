/*

Grupo 108

70179 - Manuel Alves     [manuelalves@tecnico.ulisboa.pt]
70298 - Jessica Ribeiro  [jessica.ribeiro@tecnico.ulisboa.pt]

*/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdio.h>

using namespace std;

class UserNode{
    public:
        // node id
        int id;
        // List with the connections nodes
        list<int> connectionList;
};

class Graph{
    public:
        // number of points
        int numberPoints;
        // number of connections
        int numberConnections;
        // number of problems
        int numberProblems;
        // list of critical points
        vector<list<int> > criticalPoints;
        // Vector that contais the graph nodes
        vector<UserNode*> nodesVector;
};

int main(){
    
    // number of points
    int n = 0;
    // number of connections
    int m = 0;
    // points which are connected (0 ≤ u < v < n)
    int u = 0;
    int v = 0;
    // number of problems
    int h = 0;
    // number of critical points on this line (1 ≤ k ≤ n)
    int k = 0;

    // read first line input
    scanf("%d %d", &n, &m);
    
    // creates a new graph
    Graph* graph = new Graph();
    
    // sets number of vertices of graph
    graph->numberPoints = n;
    // sets number of connections of graph
    graph->numberConnections = m;
    // allocates a vector with number of vertices (number of points)
    graph->nodesVector.reserve(n);
    
    // initialize each node of the graph
    for(int i = 0; i < n; i++){
        
        int id_aux = i;
        
        // creates a new node
        UserNode* node = new UserNode();
        
        // add node to the nodesVector of graph
        graph->nodesVector.push_back(node);
        
        // sets the id of node
        graph->nodesVector[i]->id = (id_aux + 1);
    }
    
    // for each number of connections
    for (int j = 0; j < m; j++){
        
        // gets the connection points
        scanf ("%d %d",&u, &v);
        
        //adds connection point to the connectionList of the node
        graph->nodesVector[u]->connectionList.push_back(v);
        graph->nodesVector[v]->connectionList.push_back(u);
    }
    
    // read the number of problems
    scanf("%d", &h);
    
    // allocates a vector with number of problems
    graph->criticalPoints.reserve(h);
    
    for (int y = 0; y < h; y++) {
        
        // list of critical points to insert in the graph
        list<int > insertCriticalPoints;
        
        // gets number of critical points on this line
        scanf ("%d", &k);
        
        // read line of critival points
        for (int auxY=0; auxY < k; auxY++) {
            int auxInsert = 0;
            
            // read each critial point
            scanf("%d", &auxInsert);
            
            // insert critical point on the insertCriticalPoints
            insertCriticalPoints.push_back(auxInsert);
        }
        
        // insert the list of critical points on the graph
        graph->criticalPoints.push_back(insertCriticalPoints);
    }

    
    // output - TO DO
    cout << "\n";
}
