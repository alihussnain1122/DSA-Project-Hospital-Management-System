#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

template <typename T>
class Graph {
private:
    unordered_map<T, list<T>> adjList;

public:
    void addEdge(T u, T v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // For undirected graph, add edge both ways
    }

    void bfs(T start) {
        unordered_map<T, bool> visited;
        queue<T> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            T node = q.front();
            cout << node << " ";
            q.pop();

            for (T neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void dfsUtil(T node, unordered_map<T, bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (T neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited);
            }
        }
    }

    void dfs(T start) {
        unordered_map<T, bool> visited;
        dfsUtil(start, visited);
        cout << endl;
    }

    void display() {
        for (auto& pair : adjList) {
            cout << pair.first << ": ";
            for (T neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

#endif
