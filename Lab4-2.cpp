#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Time Complexity of DFS in a Graph of n Nodes:
The time complexity of DFS (Depth-First Search) depends on how the graph is represented:
- Adjacency List: In the adjacency list representation, for each node, we process its neighbors. The sum of the neighbors of all nodes is the number of edges E. Thus, visiting every node V and processing all edges E gives a total time complexity of: O(V + E), where V is the number of vertices (nodes), and E is the number of edges.
- Adjacency Matrix: In the adjacency matrix representation, checking the neighbors of each node involves iterating through all V nodes, even if there isn't an edge. Hence, the time complexity becomes: O(V^2) this is because for each node, we look at every other node to check if an edge exists.
In summary:
- Adjacency List: O(V + E)
- Adjacency Matrix: O(V^2)

Space Complexity of a Graph of n Nodes:
The space complexity of a graph also depends on its representation:
- Adjacency List: Each node stores a list of its neighbors. For V nodes and E edges, the adjacency list requires space proportional to: O(V + E) because we store a list for each node and each edge is represented twice (once for each endpoint in an undirected graph).
- Adjacency Matrix: For an adjacency matrix, we need a V x V matrix, where each element represents whether there is an edge between two nodes. This requires: O(V^2) space, regardless of the number of edges.
In summary:
- Adjacency List: O(V + E)
- Adjacency Matrix: O(V^2)

Utility of Preorder, Inorder, and Postorder Traversals:
Traversal techniques such as Preorder, Inorder, and Postorder are typically discussed in the context of tree data structures. However, they have specific applications and interpretations when applied to general graphs, especially when modeling certain hierarchical structures like spanning trees derived from the graph.
1. Preorder Traversal:
   - In preorder traversal, the current node is visited first, before its children (or neighbors). This traversal is useful when you need to explore the structure as soon as you encounter a node, often for problems requiring early access to nodes.
   - Use Cases:
     - Generating hierarchical structures: Preorder traversal can be used to serialize a tree structure or generate a prefix expression.
     - Backtracking algorithms: In backtracking or recursive algorithms, such as solving puzzles or optimization problems, preorder traversal helps explore a solution space early before deeper exploration.
     - File systems: When traversing directories, a preorder traversal can list the root directory before its subdirectories and files.
2. Inorder Traversal:
   - In the context of binary trees, inorder traversal visits the left child, then the current node, and finally the right child. For general graphs, simulating an inorder traversal (by sorting or structuring neighbors) is uncommon but can still be useful in specific cases.
   - Use Cases:
     - Binary search trees: Inorder traversal is particularly useful for binary search trees (BSTs) because it returns the nodes in sorted order.
     - Arithmetic expressions: In an expression tree (which is a binary tree representing arithmetic operations), inorder traversal can help reconstruct the infix notation of an arithmetic expression.
3. Postorder Traversal:
   - In postorder traversal, the node is visited last, after all its children (or neighbors) have been explored. This traversal is useful when you need to perform actions after processing all dependencies or subcomponents.
   - Use Cases:
     - Dependency resolution: Postorder traversal is crucial in applications where a node depends on its children (e.g., compilation tasks where dependencies must be resolved first).
     - Tree deletion: To safely delete a tree structure from memory, postorder traversal ensures you delete children before the parent.
     - Graph-based dynamic programming: In some dynamic programming algorithms (e.g., in games or optimization problems), postorder traversal helps in accumulating results from subproblems before making decisions at the parent node.
Summary:
- Preorder: Useful for exploring early, prefix generation, and solving recursive problems.
- Inorder: Mainly for binary trees, retrieves sorted order, helps with arithmetic expressions.
- Postorder: Useful when actions depend on all children, helpful in tasks like dependency resolution and cleanup.
*/

class Graph {
    int numNodes;
    vector<vector<int>> adjList;      // Adjacency list
    vector<vector<int>> adjMatrix;    // Adjacency matrix
    vector<int> nodes;               // List of nodes (A, B, C, etc.)

public:
    // Constructor to initialize graph with 'n' nodes
    Graph(vector<int> nodes) {
        numNodes = nodes.size();
        this->nodes = nodes;
        adjList.resize(numNodes);
        adjMatrix.resize(numNodes, vector<int>(numNodes, 0));
    }

    // Function to add an undirected edge
    void addEdge(int u, int v) {
        int u_idx = getNodeIndex(u);
        int v_idx = getNodeIndex(v);
        
        // Adjacency list
        adjList[u_idx].push_back(v_idx);
        adjList[v_idx].push_back(u_idx);
        
        // Adjacency matrix
        adjMatrix[u_idx][v_idx] = 1;
        adjMatrix[v_idx][u_idx] = 1;
    }

    // Helper function to find the index of a node
    int getNodeIndex(int node) {
        return find(nodes.begin(), nodes.end(), node) - nodes.begin();
    }

    // Function to print adjacency list
    void printAdjList() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < numNodes; i++) {
            cout << nodes[i] << ": ";
            for (int neighbor : adjList[i]) {
                cout << nodes[neighbor] << " ";
            }
            cout << endl;
        }
    }

    // Function to print adjacency matrix
    void printAdjMatrix() {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // DFS Preorder Traversal (Node -> Neighbors)
    void dfsPreorder(int startNode) {
        vector<bool> visited(numNodes, false);
        dfsPreorderUtil(getNodeIndex(startNode), visited);
    }

    void dfsPreorderUtil(int nodeIdx, vector<bool>& visited) {
        visited[nodeIdx] = true;
        cout << nodes[nodeIdx] << " ";

        for (int neighbor : adjList[nodeIdx]) {
            if (!visited[neighbor]) {
                dfsPreorderUtil(neighbor, visited);
            }
        }
    }

    // DFS Postorder Traversal (Neighbors -> Node)
    void dfsPostorder(int startNode) {
        vector<bool> visited(numNodes, false);
        dfsPostorderUtil(getNodeIndex(startNode), visited);
    }

    void dfsPostorderUtil(int nodeIdx, vector<bool>& visited) {
        visited[nodeIdx] = true;

        for (int neighbor : adjList[nodeIdx]) {
            if (!visited[neighbor]) {
                dfsPostorderUtil(neighbor, visited);
            }
        }

        cout << nodes[nodeIdx] << " ";
    }

    // DFS Inorder Traversal (Sorted Neighbors -> Node -> Remaining Neighbors)
    void dfsInorder(int startNode) {
        vector<bool> visited(numNodes, false);
        dfsInorderUtil(getNodeIndex(startNode), visited);
    }

    void dfsInorderUtil(int nodeIdx, vector<bool>& visited) {
        visited[nodeIdx] = true;

        vector<int> neighbors = adjList[nodeIdx];
        sort(neighbors.begin(), neighbors.end()); // Sort neighbors

        int mid = neighbors.size() / 2;

        // Visit first half of sorted neighbors
        for (int i = 0; i < mid; i++) {
            if (!visited[neighbors[i]]) {
                dfsInorderUtil(neighbors[i], visited);
            }
        }

        // Visit the node itself
        cout << nodes[nodeIdx] << " ";

        // Visit the remaining half of sorted neighbors
        for (int i = mid; i < neighbors.size(); i++) {
            if (!visited[neighbors[i]]) {
                dfsInorderUtil(neighbors[i], visited);
            }
        }
    }
};

int main() {
    // Create a graph with 6 nodes (A, B, C, D, E, F)
    vector<int> nodes = {0, 1, 2, 3, 4, 5};
    Graph graph(nodes);

    // Add edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);

    // Print adjacency list and matrix
    graph.printAdjList();
    graph.printAdjMatrix();

    // Perform DFS Traversals
    cout << "\nDFS Preorder Traversal:\n";
    graph.dfsPreorder(0);

    cout << "\n\nDFS Postorder Traversal:\n";
    graph.dfsPostorder(0);

    cout << "\n\nDFS Inorder Traversal (simulated):\n";
    graph.dfsInorder(0);

    return 0;
}
