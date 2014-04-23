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
    
    vector<CriticalNode*> criticalPoints;
    
    vector<vector<pair<int, int> > > map;
    
    
};


Graph* copyGraph(Graph* g, Graph* copy){
    copy->numberPoints = g->numberPoints;
    copy->numberConnections = g->numberConnections;
    
    for(int i = 0; i < g->numberPoints; i++){
        
        vector<vector<pair<int, int> > > mapInit(g->numberPoints);
        
        copy->map = mapInit;
        
        
        // for each number of connections
        for (int j = 0; j < g->numberConnections; j++){
            
            copy->map[i][j] = g->map[i][j];
        }
    }
    
    return copy;
    
}

bool bfs(Graph* rGraph, int source, int sink, int parent[]){
    bool visited[rGraph->numberPoints];
    memset(visited, 0, sizeof(visited));
    
    queue <int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        
        for (int v=0; v<rGraph->numberPoints; v++) {
            if (visited[v]==false && rGraph->map[u][v].second>0) {
                q.push(v);
                parent[v]=u;
                visited[v]=true;
            }
        }
    }
    return (visited[sink] == true);
}



int fordFulkerson(Graph* g, int source, int sink){
    int u;
    int v;
    
    Graph* rGraph = new Graph();
    
    copyGraph(g, rGraph);
    
    
    int parent[g->numberPoints];
    
    int max_flow = 0;
    
    while(bfs(rGraph, source, sink, parent)){
        int path_flow = INT_MAX;
        
        for(v=sink; v!=source; v=parent[v]){
            u=parent[v];
            path_flow=min(path_flow, rGraph->map[u][v].second);
        }
        
        for(v=sink; v!=source; v=parent[v]){
            u=parent[v];
            rGraph->map[u][v].second -= path_flow;
            rGraph->map[v][u].second += path_flow;
            
        }
        
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

    vector<vector<pair<int, int> > > mapInit(n);
    
    graph->map = mapInit;
    
    
    // for each number of connections
    for (int j = 0; j < m; j++){
        
        // gets the connection points
        scanf ("%d %d",&u, &v);
        
        graph->map[u].push_back(make_pair(v,1));
        graph->map[v].push_back(make_pair(u,1));
        
    }
    
    // read the number of problems
    scanf("%d", &h);
    
    graph->criticalPoints.reserve(h);
    
    for (int y = 0; y < h; y++) {
        
        CriticalNode* node = new CriticalNode();
        
        graph->criticalPoints.push_back(node);
        
        
        // gets number of critical points on this line
        scanf ("%d", &k);
        
        graph->criticalPoints[y]->input.reserve(k);
        
        for(int j = 0; j <=  k; j++){
            graph->criticalPoints[y]->input.push_back(0);
            
        }
        graph->criticalPoints[y]->input[0] = k;
        
        // read line of critival points
        for (int auxY=1; auxY <= k; auxY++) {
            int auxInsert = 0;
            
            // read each critial point
            scanf("%d", &auxInsert);
            
            graph->criticalPoints[y]->input[auxY] = auxInsert;
            
            
            
            // insert critical point on the insertCriticalPoints
            
        }
        
        // insert the list of critical points on the graph
        
    }
    
    // output - TO DO
    
    for (int out=0; out<h; out++) {
        if (graph->criticalPoints[out]->input[0] == 2) {
            cout << fordFulkerson(graph, graph->criticalPoints[out]->input[1], graph->criticalPoints[out]->input[2]) << "\n";
        }
        if(graph->criticalPoints[out]->input[0] > 2) {
            int outAux = fordFulkerson(graph, graph->criticalPoints[out]->input[1], graph->criticalPoints[out]->input[2]);
            for (int i = 3; i<=graph->criticalPoints[out]->input[0]; i++) {
                outAux = min(outAux, fordFulkerson(graph, graph->criticalPoints[out]->input[1], graph->criticalPoints[out]->input[i]));
            }
            cout << outAux << "\n";
        }
    }
}
