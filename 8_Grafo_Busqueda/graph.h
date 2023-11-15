#ifndef Graph_H_
#define Graph_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Graph {
private:
  int edgesList;
  int edgesMat;
  int nodes;
  vector<int> *adjList;
  int *adjMatrix;
  // vector<Type> *vect = new vector<Type>

public:
  Graph(int);
  Graph();
  void addEdgeAdjList(int, int);
  void addEdgeAdjMatrix(int, int);
  string printAdjList();
  string printAdjMat();
  string printAdjMat_clean();
  string DFS(int, int);
  string depthHelper(int, int, stack<int> &, list<int> &,
                     vector<vector<int>> &);
  string BFS(int, int);
  string breadthHelper(int, int, queue<int> &, list<int> &,
                       vector<vector<int>> &);
  string print_visited(list<int>);
  string print_path(vector<vector<int>> &, int, int);
  string print_path_q(list<int> q);
  bool contains(list<int>, int);
  void sortAdjList();
  void loadGraphList(string, int, int);
  void loadGraphMat(string, int, int);
};

void Graph::loadGraphList(string name, int a, int b) {
  adjList = new vector<int>[a];
  nodes = a;
  string line;
  ifstream lee(name);
  int u, v;
  if (lee.is_open()) {
    while (getline(lee, line)) {
      u = stoi(line.substr(1, 1));
      v = stoi(line.substr(4, 1));
      addEdgeAdjList(u, v);
    }
    lee.close(); // Closes the file
  } else {
    cout << "Unable to open file";
  }
  sortAdjList();
}

void Graph::loadGraphMat(string name, int a, int b) {
  adjMatrix = new int[a * b];
  nodes = a;
  for (int i = 0; i < a * b; i++)
    adjMatrix[i] = 0;
  string line;
  ifstream lee(name);
  int u, v;
  if (lee.is_open()) {
    while (getline(lee, line)) {
      u = stoi(line.substr(1, 1));
      v = stoi(line.substr(4, 1));
      addEdgeAdjMatrix(u, v);
    }
    lee.close(); // Closes the file
  } else {
    cout << "Unable to open file";
  }
}

Graph::Graph() { edgesList = edgesMat = 0; }

Graph::Graph(int n) {
  nodes = n;
  adjList = new vector<int>[nodes];
  adjMatrix = new int[nodes * nodes];
  for (int i = 0; i < nodes * nodes; i++)
    adjMatrix[i] = 0;
  edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v) {
  adjList[u].push_back(v);
  adjList[v].push_back(u);
  edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v) {
  adjMatrix[u * nodes + v] = 1;
  adjMatrix[v * nodes + u] = 1;
  edgesMat++;
}

string Graph::printAdjList() {
  stringstream aux;
  for (int i = 0; i < nodes; i++) {
    aux << "vertex " << i << " :";
    for (int j = 0; j < adjList[i].size(); j++) {
      aux << " " << adjList[i][j];
    }
    aux << " ";
  }
  return aux.str();
}

void Graph::sortAdjList() {
  for (int i = 0; i < nodes; i++)
    sort(adjList[i].begin(), adjList[i].end());
}

string Graph::printAdjMat() {
  stringstream aux;
  for (int i = 0; i < nodes; i++) {
    for (int j = 0; j < nodes; j++) {
      aux << adjMatrix[i * nodes + j] << " ";
    }
  }
  return aux.str();
}

string Graph::printAdjMat_clean() {
  stringstream aux;
  aux << "\n nodes \t|";
  for (int i = 0; i < nodes; i++) {
    aux << "\t" << i;
  }
  aux << "\n";
  for (int i = 0; i < nodes; i++) {
    aux << "__________";
  }
  aux << "\n";
  for (int i = 0; i < nodes; i++) {
    aux << i << "\t|";
    for (int j = 0; j < nodes; j++) {
      aux << "\t" << adjMatrix[i * nodes + j];
    }
    aux << "\n";
  }
  return aux.str();
}

string Graph::DFS(int start, int goal) {
  stack<int> st;
  list<int> visited;
  vector<vector<int>> paths(nodes, vector<int>(1, -1));
  st.push(start);
  string ans = depthHelper(start, goal, st, visited, paths);
  string path_ans = print_path(paths, start, goal);
  return ans + path_ans;
}

string Graph::depthHelper(int current, int goal, stack<int> &st,
                          list<int> &visited, vector<vector<int>> &paths) {
  if (current == goal)
    return print_visited(visited);
  else if (st.empty())
    return "Node not found";
  else {
    current = st.top();
    st.pop();
    visited.push_back(current);
    for (int i = 0; i < adjList[current].size(); i++) {
      if (!contains(visited, adjList[current][i])) {
        st.push(adjList[current][i]);
        paths[adjList[current][i]][0] = current;
      }
    }
    return depthHelper(current, goal, st, visited, paths);
  }
}

string Graph::BFS(int start, int goal) {
  queue<int> qu;
  list<int> visited;
  vector<vector<int>> paths(nodes, vector<int>(1, -1));
  qu.push(start);
  string visits = breadthHelper(start, goal, qu, visited, paths);
  string path = print_path(paths, start, goal);
  return visits + path;
}

/*
string Graph::breadthHelper(int current, int goal, queue<int> &qu,
                            list<int> &visited, vector<int> &paths) {
  if (current == goal) {
    return print_path_q(visited);
  } else if (qu.empty())
    return "Node not found";
  else {
    qu.pop();
    visited.push_back(current);
    for (auto i : adjList[current]) {
      if (i == goal) {
        visited.push_back(i);
      }
      auto it = find(paths.begin(), paths.end(), i);
      if (i != *it) {
        paths.push_back(i);
      }
      qu.push(i);
    }
    if (visited.back() == goal) {
      return breadthHelper(visited.back(), goal, qu, visited, paths);
    } else {
      return breadthHelper(qu.front(), goal, qu, visited, paths);
    }
  }
}
*/
string Graph::breadthHelper(int current, int goal, queue<int> &qu,
                            list<int> &visited, vector<vector<int>> &paths) {
  if (current == goal)
    return print_visited(visited);
  else if (qu.empty())
    return "Node not found";
  else {
    current = qu.front();
    qu.pop();
    visited.push_back(current);
    for (int i = 0; i < adjList[current].size(); i++) {
      if (!contains(visited, adjList[current][i])) {
        qu.push(adjList[current][i]);
        paths[adjList[current][i]][0] = current;
      }
    }
    return breadthHelper(current, goal, qu, visited, paths);
  }
}

bool Graph::contains(list<int> ls, int node) {
  list<int>::iterator it;
  it = find(ls.begin(), ls.end(), node);
  if (it != ls.end())
    return true;
  else
    return false;
}

string Graph::print_visited(list<int> q) {
  stringstream aux;
  aux << "visited: ";
  for (auto item : q) {
    aux << item << " ";
  }
  return aux.str();
}

string Graph::print_path(vector<vector<int>> &path, int start, int goal) {
  int node = path[goal][0];
  stack<int> reverse;
  reverse.push(goal);
  stringstream aux;
  aux << "path:";
  while (node != start) {
    reverse.push(node);
    node = path[node][0];
  }
  reverse.push(start);
  while (!reverse.empty()) {
    aux << " " << reverse.top();
    reverse.pop();
  }
  return aux.str();
}

#endif /* Graph_H_ */
