#include<bits/stdc++.h>
using namespace std;

// template<typename T> -> if we want to make the graph generic we can use it but in int main() {
// we have to use Graph<int> g; int/char/float -> any type and everywhere just use T in place of datatype
class Graph {
    public:
    unordered_map<int,list<int>> adjList;

    void addEdge(int u,int v,bool direction) {
        //direction==0 -> undirected
        //direction==1 -> directed
        adjList[u].push_back(v);
        if(direction == 0) adjList[v].push_back(u);
    }

    void printAdjacencyList() {
        for(auto node: adjList) {
            cout<<node.first<<"->";
            for(auto neighbour: node.second) {
                cout<<neighbour<<", ";
            }
            cout<<endl;
        }
    }
    void bfs(int src,unordered_map<int, bool>& visited) {
        queue<int> q;
        q.push(src);
        visited[src]=true;

        while(!q.empty()) {
            int frontNode=q.front();
            q.pop();
            cout<<frontNode<<", ";

            for(auto i: adjList[frontNode]) {
                if(!visited[i]) {
                    q.push(i);
                    visited[i]=true;
                }
            }
        }
    }
    void dfs(int src,unordered_map<int, bool>& visited2) {
        cout<<src<<", ";
        visited2[src]=true;

        for(auto i: adjList[src]) {
            if(!visited2[i]) dfs(i,visited2);
        }
    }
    bool checkCyclicUsingBfs(int src,unordered_map<int,bool>& visited) {
        queue<int> q;
        unordered_map<int,int> parent;

        q.push(src);
        visited[src]=true;
        parent[src]=-1;

        while(!q.empty()) {
            int frontNode=q.front();
            q.pop();
            for(auto nbr : adjList[frontNode]) {
                if(!visited[nbr]) {
                    q.push(nbr);
                    visited[nbr]=true;
                    parent[nbr]=frontNode;
                }
                else {
                    if(nbr != parent[frontNode]) return true;
                }
            }
        }
        return false;
    }
    bool checkCyclicUsingDfs(int src,unordered_map<int,bool>& visited,int parent) {
        visited[src]=true;
        for(auto nbr : adjList[src]) {
            if(!visited[nbr]) {
                bool checkAageKaAns = checkCyclicUsingDfs(nbr,visited,src);
                if(checkAageKaAns == true) return true;
            }
            if(visited[nbr] && nbr != parent) return true;
        }
        return false;
    }

};
int main() {
    Graph g;
    int n=5;
    g.addEdge(0,1,0);
    g.addEdge(1,2,0);
    g.addEdge(2,3,0);
    g.addEdge(3,4,0);
    g.addEdge(4,0,0);

    g.printAdjacencyList();

    cout<<endl;

    bool ans=false;
    unordered_map<int, bool> visited;
    for(int i=0;i<n;i++) {
        if(!visited[i]) {
            ans=g.checkCyclicUsingBfs(i,visited);
            if(ans == true) break;
        }
    }
    if(ans == true) cout<<"Cycle is present"<<endl;
    else cout<<"No cycle"<<endl;

    bool ans2=false;
    unordered_map<int, bool> visited2;
    for(int i=0;i<n;i++) {
        if(!visited2[i]) {
            ans2=g.checkCyclicUsingDfs(i,visited2,-1);
            if(ans2 == true) break;
        }
    }
    if(ans2 == true) cout<<"Cycle is present"<<endl;
    else cout<<"No cycle"<<endl;


    // unordered_map<int, bool> visited;
    // cout<<"BFS Traversal"<<endl;
    // for(int i=0;i<n;i++) {
    //     if(!visited[i]) {
    //         g.bfs(i,visited);
    //     }
    // }
    // cout<<endl;

    // unordered_map<int, bool> visited2;
    // cout<<"DFS Traversal"<<endl;
    // for(int i=0;i<n;i++) {
    //     if(!visited2[i]) {
    //         g.dfs(i,visited2);
    //     }
    // }


    // cout<<"No of nodes: "<<endl;  
    // int n; cin>>n;
    // cout<<"No of edges: "<<endl;
    // int e; cin>>e;
    // vector<vector<int>> adj(n,vector<int>(n,0));
    // for(int i=0;i<e;i++) {
    //     int u,v;
    //     cin>>u>>v;
    //     adj[u][v]=1;
    // }
    // for(int i=0;i<n;i++) {
    //     for(int j=0;j<n;j++) {
    //         cout<<adj[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
}