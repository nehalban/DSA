#pragma once

#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include <utility>
#include <vector>

struct GraphNodeBase {
    std::vector<std::pair<GraphNodeBase*, int>> adj;

    void add_to_adj(GraphNodeBase* to, int weight = 1) {
        if (!to) throw std::invalid_argument("Cannot add edge to a null node");
        adj.push_back({to, weight});
    }
};

struct GraphBase {
    int n = 0;
    std::deque<GraphNodeBase> vertices;

    GraphNodeBase* add_vertex() {
        vertices.emplace_back();
        n = static_cast<int>(vertices.size());
        return &vertices.back();
    }

    GraphNodeBase* vertex(int index) {
        if (index < 0 || index >= n) throw std::out_of_range("Graph vertex index out of bounds");
        return &vertices[index];
    }

    const GraphNodeBase* vertex(int index) const {
        if (index < 0 || index >= n) throw std::out_of_range("Graph vertex index out of bounds");
        return &vertices[index];
    }

    std::vector<GraphNodeBase*> BFS(GraphNodeBase* start) {
        std::vector<GraphNodeBase*> order;
        if (!start) return order;

        std::queue<GraphNodeBase*> q;
        std::unordered_set<GraphNodeBase*> visited;
        visited.insert(start);
        q.push(start);

        while (!q.empty()) {
            GraphNodeBase* curr = q.front();
            q.pop();
            order.push_back(curr);

            for (auto& edge : curr->adj) {
                GraphNodeBase* next = edge.first;
                if (next && visited.insert(next).second) q.push(next);
            }
        }

        return order;
    }

    std::vector<GraphNodeBase*> BFS() {
        std::vector<GraphNodeBase*> order;
        std::unordered_set<GraphNodeBase*> visited;

        for (auto& node : vertices) {
            GraphNodeBase* start = &node;
            if (!visited.insert(start).second) continue;

            std::queue<GraphNodeBase*> q;
            q.push(start);
            while (!q.empty()) {
                GraphNodeBase* curr = q.front();
                q.pop();
                order.push_back(curr);

                for (auto& edge : curr->adj) {
                    GraphNodeBase* next = edge.first;
                    if (next && visited.insert(next).second) q.push(next);
                }
            }
        }

        return order;
    }

    std::vector<GraphNodeBase*> DFS_iterative(GraphNodeBase* start) {
        std::vector<GraphNodeBase*> order;
        if (!start) return order;

        std::stack<GraphNodeBase*> s;
        std::unordered_set<GraphNodeBase*> visited;
        s.push(start);

        while (!s.empty()) {
            GraphNodeBase* curr = s.top();
            s.pop();
            if (!visited.insert(curr).second) continue;

            order.push_back(curr);
            for (auto it = curr->adj.rbegin(); it != curr->adj.rend(); ++it) {
                if (it->first && !visited.count(it->first)) s.push(it->first);
            }
        }

        return order;
    }

    std::vector<GraphNodeBase*> DFS_iterative() {
        std::vector<GraphNodeBase*> order;
        std::unordered_set<GraphNodeBase*> visited;

        for (auto& node : vertices) {
            GraphNodeBase* start = &node;
            if (visited.count(start)) continue;

            std::stack<GraphNodeBase*> s;
            s.push(start);
            while (!s.empty()) {
                GraphNodeBase* curr = s.top();
                s.pop();
                if (!visited.insert(curr).second) continue;

                order.push_back(curr);
                for (auto it = curr->adj.rbegin(); it != curr->adj.rend(); ++it) {
                    if (it->first && !visited.count(it->first)) s.push(it->first);
                }
            }
        }

        return order;
    }

    void DFS_recursive_helper(GraphNodeBase* curr,
                              std::unordered_set<GraphNodeBase*>& visited,
                              std::vector<GraphNodeBase*>& order) {
        if (!curr || !visited.insert(curr).second) return;
        order.push_back(curr);
        for (auto& edge : curr->adj) {
            DFS_recursive_helper(edge.first, visited, order);
        }
    }

    std::vector<GraphNodeBase*> DFS_recursive(GraphNodeBase* start) {
        std::vector<GraphNodeBase*> order;
        std::unordered_set<GraphNodeBase*> visited;
        DFS_recursive_helper(start, visited, order);
        return order;
    }

    std::vector<GraphNodeBase*> DFS_recursive() {
        std::vector<GraphNodeBase*> order;
        std::unordered_set<GraphNodeBase*> visited;
        for (auto& node : vertices) {
            DFS_recursive_helper(&node, visited, order);
        }
        return order;
    }
};

struct UndirectedGraphBase : public GraphBase {
    void add_edge(GraphNodeBase* n1, GraphNodeBase* n2, int weight = 1) {
        if (!n1 || !n2) throw std::invalid_argument("Cannot add edge with a null node");
        n1->add_to_adj(n2, weight);
        n2->add_to_adj(n1, weight);
    }

    void add_edge(int u, int v, int weight = 1) {
        add_edge(vertex(u), vertex(v), weight);
    }

    int connected_component_count() {
        int count = 0;
        std::unordered_set<GraphNodeBase*> visited;

        for (auto& node : vertices) {
            GraphNodeBase* start = &node;
            if (visited.count(start)) continue;

            ++count;
            std::queue<GraphNodeBase*> q;
            visited.insert(start);
            q.push(start);

            while (!q.empty()) {
                GraphNodeBase* curr = q.front();
                q.pop();
                for (auto& edge : curr->adj) {
                    GraphNodeBase* next = edge.first;
                    if (next && visited.insert(next).second) q.push(next);
                }
            }
        }

        return count;
    }

    bool isTree() {
        if (n == 0) return true;
        if (connected_component_count() != 1) return false;

        long long directed_edges = 0;
        for (const auto& node : vertices) directed_edges += static_cast<long long>(node.adj.size());
        return directed_edges / 2 == n - 1;
    }
};

struct DirectedGraphBase : public GraphBase {
    void add_edge(GraphNodeBase* n1, GraphNodeBase* n2, int weight = 1) {
        if (!n1 || !n2) throw std::invalid_argument("Cannot add edge with a null node");
        n1->add_to_adj(n2, weight);
    }

    void add_edge(int from, int to, int weight = 1) {
        add_edge(vertex(from), vertex(to), weight);
    }
};

template<typename T>
struct GraphNode : public GraphNodeBase {
    T data;

    GraphNode() = default;
    explicit GraphNode(const T& value) : data(value) {}
};

struct UndirectedGraph : public UndirectedGraphBase {};

struct DirectedGraph : public DirectedGraphBase {};
