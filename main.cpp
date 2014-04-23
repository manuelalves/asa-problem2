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
#include <string.h>
#include <limits.h>
#include <queue>

using namespace std;

// class that saves the critical nodes per line
class CriticalNode{
    public:
        vector<int > input;
};

class Graph{
    public:
        // number of points
        int numberPoints;
        // number of connections
        int numberConnections;
        // number of problems
        int numberProblems;
    
        // vector with critical nodes
        vector<CriticalNode*> criticalPoints;
    
        // map table that has a pair representing the vertice and the flow
        vector<vector<pair<int, int> > > map;
};


// function that copy one graph and return the new graph
Graph* copyGraph(Graph* g, Graph* copy){
    
    // copy the number of points to the new graph
    copy->numberPoints = g->numberPoints;
    // copy the number of connections to the new graph
    copy->numberConnections = g->numberConnections;
    
    // new map table
    vector<vector<pair<int, int> > > mapInit(g->numberPoints);
    
    // copy the map to the new graph
    copy->map = mapInit;
    
    // fill the new map table using the original
    for(int i = 0; i < g->numberPoints; i++){
        for (unsigned int j = 0; j < g->map[i].size(); j++){
            copy->map[i].push_back(make_pair(g->map[i][j].first, g->map[i][j].second));
        }
    }
    
    return copy;
}

// Returns true if there is a path from source to sink in
//residual graph
bool bfs(Graph* rGraph, int source, int sink, int parent[]){
    // Create a visited array
    bool visited[rGraph->numberPoints];
    // Mark all vertices as not visited
    memset(visited, 0, sizeof(visited));
    // Create a queue
    queue <int> q;
    // Put the source vertex in the queue
    q.push(source);
    // Mark the source vertex as visited
    visited[source] = true;
    // Set the parent of source vertex as undifined
    parent[source] = -1;
    
    // BFS loop to search the path from source to sink
    while(!q.empty()){
        int u = q.front();
        q.pop();
        
        for (unsigned int pos = 0; pos<rGraph->map[u].size(); pos++) {
            int v = rGraph->map[u][pos].first;
            
            if (visited[v]==false && rGraph->map[u][pos].second>0) {
                q.push(v);
                parent[v]=u;
                visited[v]=true;
            }
        }
    }
    
    // If we can reach sink from source returns true, else returns false
    return (visited[sink] == true);
}

// Ford Fulkerson function algorithm
// Returns tne maximum flow from source to sink in the graph g
int fordFulkerson(Graph* g, int source, int sink){
    int u;
    int v;
    
    Graph* rGraph = new Graph();
    
    //creates a residual graph equals to the original graph
    copyGraph(g, rGraph);
    
    // Array filled by the BFS algorithm with the paths
    int parent[g->numberPoints];
    
    // No flow defined initially
    int max_flow = 0;
    
    // Apply BFS algorithm while there is a path from source to sink
    while(bfs(rGraph, source, sink, parent)){
        // set path_flow as "infinit"
        int path_flow = INT_MAX;
        
        // Find the minimum residual capacity of the edges
        for(v=sink; v!=source; v=parent[v]){
            u=parent[v];
            
            for(unsigned int i = 0; i< rGraph->map[u].size(); i++){
                int elem1 = rGraph->map[u][i].first;
                if(elem1 == v){
                    
                    path_flow=min(path_flow, rGraph->map[u][i].second);
                }
            }
        }
        // Update residual capacities of the edges and reverse edges
        for(v=sink; v!=source; v=parent[v]){
            u=parent[v];
            
            for(unsigned int i = 0; i< rGraph->map[u].size(); i++){
                int elem1 = rGraph->map[u][i].first;
                if(elem1 == v){
                    rGraph->map[u][i].second -= path_flow;
                    break;
                }
            }
            
            for(unsigned int i = 0; i< rGraph->map[v].size(); i++){
                int elem2 = rGraph->map[v][i].first;
                if(elem2 == u){
                    rGraph->map[v][i].second += path_flow;
                    break;
                }
            }
        }
        // Actualize max_flow with the path_flow
        max_flow += path_flow;
    }
    return max_flow;
}

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
    
    // map table init
    vector<vector<pair<int, int> > > mapInit(n);
    
    // put the map table in the graph
    graph->map = mapInit;
    
    // for each number of connections
    for (int j = 0; j < m; j++){
        
        // gets the connection points
        scanf ("%d %d",&u, &v);
        
        // set the pair (node, flow)
        graph->map[u].push_back(make_pair(v,1));
        graph->map[v].push_back(make_pair(u,1));
    }
    
    // read the number of problems
    scanf("%d", &h);
    
    // reserve memory for the critical points vector
    graph->criticalPoints.reserve(h);
    
    
    // read each problem line
    for (int y = 0; y < h; y++) {
        CriticalNode* node = new CriticalNode();
        graph->criticalPoints.push_back(node);
        
        // gets number of critical points on this line
        scanf ("%d", &k);
        
        graph->criticalPoints[y]->input.reserve(k);
        
        // init input vector
        for(int j = 0; j <=  k; j++){
            graph->criticalPoints[y]->input.push_back(0);
            
        }
        
        // insert the number of critical points in the first position of the input vector
        graph->criticalPoints[y]->input[0] = k;
        
        // read line of critical points
        for (int auxY=1; auxY <= k; auxY++) {
            int auxInsert = 0;
            
            // read each critial point
            scanf("%d", &auxInsert);
            
            // insert the critical point on the right position
            graph->criticalPoints[y]->input[auxY] = auxInsert;
  
        }
    }
    
    // output
    
    // go through the lines with the critical points
    for (int out=0; out<h; out++) {
        // 2 critical points
        if (graph->criticalPoints[out]->input[0] == 2) {
            cout << fordFulkerson(graph, graph->criticalPoints[out]->input[1], graph->criticalPoints[out]->input[2]) << "\n";
        }
        
        // more than 2 critical points
        if(graph->criticalPoints[out]->input[0] > 2) {
            
            // test the two first critical points
            int outAux = fordFulkerson(graph, graph->criticalPoints[out]->input[1], graph->criticalPoints[out]->input[2]);
            
            // see the minimum value between the first critical point and the others points
            for (int i = 3; i<=graph->criticalPoints[out]->input[0]; i++) {
                outAux = min(outAux, fordFulkerson(graph, graph->criticalPoints[out]->input[1], graph->criticalPoints[out]->input[i]));
            }
            cout << outAux << "\n";
        }
    }
}
