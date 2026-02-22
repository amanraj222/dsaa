#include<bits/stdc++.h>
using namespace std;

class Graph {
    public:
    unordered_map<int,list<int>> adjList;
    
    void addEdge(int u,int v,bool direction) {
        adjList[u].push_back(v);
        if(direction==0) adjList[v].push_back(u);
    }
    
    void printAdjacencyList() {
        for(auto node : adjList) {
            cout<<node.first<<"-> ";
            for(auto x: node.second) {
                cout<<x<<", ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void bfs(int src, unordered_map<int,bool>& visited) {
        queue<int> q;
        q.push(src);
        
        while(!q.empty()) {
            int frontNode=q.front();
            q.pop();
            visited[frontNode]=1;
            cout<<frontNode<<" ";
            
            for(auto x: adjList[frontNode]) {
                if(!visited[x]) q.push(x);
            }
        }
    }
    void dfs(int src, unordered_map<int,bool>& visited) {
        cout<<src<<" ";
        visited[src]=1;
        
        for(auto x: adjList[src]) {
            if(!visited[x]) dfs(x,visited);
        }
    }
    bool checkCycleBfs(int src, unordered_map<int,bool>& visited, unordered_map<int,int>& parent) {
        queue<int> q;
        q.push(src);
        visited[src]=1;
        parent[src]=-1;
        
        while(!q.empty()) {
            int frontNode=q.front();
            q.pop();
            
            for(auto x: adjList[frontNode]) {
                if(!visited[x]) {
                    q.push(x);
                    visited[x]=1;
                    parent[x]=frontNode;
                }
                else {
                    if(x != parent[frontNode]) return true;
                }
            }
        }
        return false;
    }
    bool checkCyclicDfs(int src,unordered_map<int,bool>& visited,int parent) {
        visited[src]=1;
        for(auto x: adjList[src]) {
            if(!visited[x]) {
                bool checkAageKaAns=checkCyclicDfs(x,visited,src);
                if(checkAageKaAns == true) return true;
            }
            else if(x != parent) return true;
        }
        return false;
    }
    bool checkCyclicDirectedDfs(int src,unordered_map<int,bool>& visited,unordered_map<int,bool>& dfsVisited) {
        visited[src]=true;
        dfsVisited[src]=true;
        
        for(auto nbr: adjList[src]) {
            if(!visited[nbr]) {
                bool aagekaAns=checkCyclicDirectedDfs(nbr,visited,dfsVisited);
                if(aagekaAns==true) return true; 
            }
            else if(visited[nbr]==true && dfsVisited[nbr]==true) return true;
        }
        dfsVisited[src]=false;
        return false;
    }
    void topoSortDfs(int src,unordered_map<int,bool>& visited,stack<int>& st) {
        visited[src]=1;
        for(auto x: adjList[src]) {
            if(!visited[x]) topoSortDfs(x,visited,st);
        }
        st.push(src);
    }
    
    void topoSortBfs(int n,vector<int>& ans) {
        queue<int> q;
        unordered_map<int,int> indegree;
        
        for(auto x: adjList) {
            for(auto y:x.second) {
                indegree[y]++;
            }
        }
        
        
        for(int i=0;i<n;i++) {
            if(indegree[i]==0) q.push(i);
        }
        
        while(!q.empty()) {
            int frontNode=q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto nbr: adjList[frontNode]) {
                indegree[nbr]--;
                if(indegree[nbr]==0) q.push(nbr);
            }
        }
    }
};
int main() {
    Graph g;
    int n=8;
    unordered_map<int,bool> visited;
    unordered_map<int,bool> dfsVisited;
    unordered_map<int,int> parent;
    stack<int> st;
    g.addEdge(0,1,1);
    g.addEdge(1,2,1);
    g.addEdge(2,3,1);
    g.addEdge(3,4,1);
    g.addEdge(4,6,1);
    g.addEdge(6,7,1);
    g.addEdge(3,5,1);
    g.addEdge(5,6,1);
    
    // g.addEdge(2,0,1);
    // g.addEdge(0,1,0);
    // g.addEdge(1,2,0);
    // g.addEdge(2,3,0);
    // g.addEdge(2,4,0);
    // g.addEdge(3,4,0);
    
    vector<int> ans;
    g.printAdjacencyList();
    g.topoSortBfs(n,ans);
    for(int i=0;i<n;i++) {
        cout<<ans[i]<<" ";
    }
    // g.topoSortDfs(0,visited,st);
    // while(!st.empty()) {
    //     cout<<st.top()<<" ";
    //     st.pop();
    // }
    // bool ans=g.checkCyclicDirectedDfs(0,visited,dfsVisited);
    // cout<<ans;
    // bool ans=g.checkCyclicDfs(0,visited,-1);
    // cout<<ans;
    // bool ans=g.checkCycleBfs(0,visited,parent);
    // cout<<ans;
    // for(int i=0;i<n;i++) {
    //      if(!visited[i]) g.dfs(i,visited);
    // }
    // for(int i=0;i<n;i++) {
    //     if(!visited[i]) g.bfs(i,visited);
    // }
    
}