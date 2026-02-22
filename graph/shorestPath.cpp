#include<bits/stdc++.h>
using namespace std;

class Graph {
    public:
    unordered_map<int,list<pair<int,int>>> adjList;

    void addEdge(int u, int v, int wt, bool direction) {
        //direction = 1 -> directed graph
        //direction = 0 -> undirected graph
        adjList[u].push_back({v,wt});
        if(direction == 0) adjList[v].push_back({u,wt});
    }

    void printAdjList() {
        for(auto i: adjList) {
            cout<<i.first<<"-> ";
            for(auto j: i.second) {
                cout<<"(" << j.first<<", "<<j.second<<"), ";
            }
            cout<<endl;
        }
    }
    void shortestPathBfs(int src, int dest) {
        queue<int> q;
        unordered_map<int,bool> visited;
        unordered_map<int,int> parent;

        //inital steps for src
        q.push(src);
        visited[src]=1;
        parent[src]=-1;

        while(!q.empty()) {
            int fNode = q.front();
            q.pop();

            for(auto nbr: adjList[fNode]) {
                if(!visited[nbr.first]) {
                    q.push(nbr.first);
                    visited[nbr.first]=1;
                    parent[nbr.first]=fNode;
                }
            }
        }
        vector<int> ans;
        int node = dest;
        while(node != -1) {
            ans.push_back(node);
            node=parent[node];
        }
        reverse(ans.begin(),ans.end());
        cout<<"Printing ans: "<<endl;
        for(auto i: ans) {
            cout<<i<<", ";
        }
        cout<<endl;
    }

    void topoSortDfs(int src,unordered_map<int,bool>& visited,stack<int>& ans) {
        visited[src]=true;
        for(auto neighbour : adjList[src]) {
            if(!visited[neighbour.first]) {
                topoSortDfs(neighbour.first,visited,ans);
            }
        }
        ans.push(src);
    }
    void shortestPathDfs(int dest, stack<int> topoOrder, int n) {
        vector<int> dist(n, INT_MAX);
        int src=topoOrder.top();
        topoOrder.pop();
        dist[src]=0;

        for(auto nbr: adjList[0]) {
            if(dist[0] + nbr.second < dist[nbr.first]) {
                dist[nbr.first] = dist[0] + nbr.second;
            }
        }

        while(!topoOrder.empty()) {
            int topElement=topoOrder.top();
            topoOrder.pop();

            if(dist[topElement] != INT_MAX) {
                for(auto nbr: adjList[topElement]) {
                    if(dist[topElement] + nbr.second < dist[nbr.first]) {
                        dist[nbr.first] = dist[topElement] + nbr.second;
                    }
                }
            }

        }
        cout<<"Printing ans: "<<endl;
        for(int i=0;i<n;i++) {
            cout<<i<<"-> "<<dist[i]<<endl;
        }
    }
};
int main() {
    Graph g;

    g.addEdge(0,1,5,0);
    g.addEdge(1,2,3,0);
    g.addEdge(2,1,2,0);

    g.addEdge(1,3,3,0);
    g.addEdge(2,3,5,0);
    g.addEdge(2,4,6,0);

    g.addEdge(4,3,1,0);

    // g.addEdge(0,1,1,1);
    // g.addEdge(1,2,1,1);
    // g.addEdge(2,3,1,1);

    // g.addEdge(3,4,1,1);
    // g.addEdge(0,5,1,1);
    // g.addEdge(5,4,1,1);

    // g.addEdge(0,6,1,1);
    // g.addEdge(6,7,1,1);
    // g.addEdge(7,8,1,1);
    // g.addEdge(8,4,1,1);

    g.printAdjList();

    stack<int> topoOrder;
    unordered_map<int, bool> visited;
    g.topoSortDfs(0,visited, topoOrder);
    g.shortestPathDfs(3,topoOrder,5);

    // int src=0;
    // int dest=4;

    // g.shortestPathBfs(src,dest);

    return 0;
}