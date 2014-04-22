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
#include <limits.h>
#include <queue>

using namespace std;

class UserNode{
public:
    // node id
    int id;
    // List with the connections nodes
    vector<int > connectionList;
};

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
    // list of critical points
    vector<CriticalNode*> criticalPoints;
    // Vector that contais the graph nodes
    vector<UserNode*> nodesVector;
};

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
            if (visited[v]==false && rGraph->nodesVector[u]->connectionList[v]>0) {
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
    
    rGraph->numberPoints = g->numberPoints;
    rGraph->numberConnections = g->numberConnections;
    rGraph->nodesVector.reserve(g->numberPoints);
    
    for(int i = 0; i < g->numberPoints; i++){
        
        // creates a new node
        UserNode* node = new UserNode();
        
        // add node to the nodesVector of graph
        rGraph->nodesVector.push_back(node);
        
        // sets the id of node
        rGraph->nodesVector[i]->id = g->nodesVector[i]->id;
        
        rGraph->nodesVector[i]->connectionList.reserve(g->numberPoints);
        
        for(int j = 0; j < g->numberPoints; j++){
            rGraph->nodesVector[i]->connectionList[j] = 0;
            
        }
        
    }
    
    // for each number of connections
    for (int j = 0; j < g->numberPoints; j++){
        
        for (int m = 0; m < g->numberConnections; m++) {
            rGraph->nodesVector[j]->connectionList[m] = g->nodesVector[j]->connectionList[m];
            
        }
    }
    
    
    
    int parent[g->numberPoints];
    
    int max_flow = 0;
    
    while(bfs(rGraph, source, sink, parent)){
        int path_flow = INT_MAX;
        
        for(v=sink; v!=source; v=parent[v]){
            u=parent[v];
            path_flow=min(path_flow, rGraph->nodesVector[u]->connectionList[v]);
        }
        
        for(v=sink; v!=source; v=parent[v]){
            u=parent[v];
            rGraph->nodesVector[u]->connectionList[v] -= path_flow;
            rGraph->nodesVector[v]->connectionList[u] += path_flow;
            
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
        
        graph->nodesVector[i]->connectionList.reserve(n);
        
        for(int j = 0; j < n; j++){
            graph->nodesVector[i]->connectionList[j] = 0;
            
        }
        
    }
    
    // for each number of connections
    for (int j = 0; j < m; j++){
        
        // gets the connection points
        scanf ("%d %d",&u, &v);
        
        //adds connection point to the connectionList of the node
        graph->nodesVector[u]->connectionList[v] = 1;
        graph->nodesVector[v]->connectionList[u] = 1;
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
        
        for(int j = 0; j <  k; j++){
            graph->criticalPoints[y]->input[j] = 0;
            
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
    
    
    
    
    cout << fordFulkerson(graph, graph->criticalPoints[0]->input[1], graph->criticalPoints[0]->input[2]) << "\n";
    
    cout << fordFulkerson(graph, graph->criticalPoints[1]->input[1], graph->criticalPoints[1]->input[2]) << "\n";
    
    cout << fordFulkerson(graph, graph->criticalPoints[2]->input[1], graph->criticalPoints[2]->input[2]) << "\n";
}
