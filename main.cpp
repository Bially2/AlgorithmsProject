#include <iostream>
#include <cstdio>
#include "Stack.h"
#include "Queue.h"

void descendingMergeSort(long long int n, int* degrees, int* vertices) {
    if (n == 1) return;

    long long int mid = n / 2;
    int* leftDegrees = new int[mid];
    int* rightDegrees = new int[n - mid];
    int* leftVertices = new int[mid];
    int* rightVertices = new int[n - mid];

    for (int i = 0; i < mid; ++i) {
        leftDegrees[i] = degrees[i];
        leftVertices[i] = vertices[i];
    }
    for (int i = mid; i < n; ++i) {
        rightDegrees[i - mid] = degrees[i];
        rightVertices[i - mid] = vertices[i];
    }

    descendingMergeSort(mid, leftDegrees, leftVertices);
    descendingMergeSort(n - mid, rightDegrees, rightVertices);

    int i = 0, j = 0, k = 0;
    while (i < mid && j < n - mid) {
        if (leftDegrees[i] >= rightDegrees[j]) {
            degrees[k] = leftDegrees[i];
            vertices[k++] = leftVertices[i++];
        } else {
            degrees[k] = rightDegrees[j];
            vertices[k++] = rightVertices[j++];
        }
    }

    while (i < mid) {
        degrees[k] = leftDegrees[i];
        vertices[k++] = leftVertices[i++];
    }

    while (j < n - mid) {
        degrees[k] = rightDegrees[j];
        vertices[k++] = rightVertices[j++];
    }

    delete[] leftDegrees;
    delete[] rightDegrees;
    delete[] leftVertices;
    delete[] rightVertices;
}

void Degree(long long int n, int** graph) {
    int* degrees = new int[n];
    int* vertices = new int[n];

    for (int i = 0; i < n; ++i) {
        int degree = 0;
        while (graph[i][degree] != -1) degree++;
        degrees[i] = degree;
        vertices[i] = i;
    }

    descendingMergeSort(n, degrees, vertices);

    for (int i = 0; i < n; ++i) {
        printf("%d ", degrees[i]);
    }
    printf("\n");

    delete[] degrees;
    delete[] vertices;
}

void DFS(int v, int** graph, bool* visited) {
    Stack stack;
    stack.push(v); // first of all push v to stack

    while (!stack.isEmpty()) {  // while stack is not empty
        int wierzcholek = stack.peek(); // get top element of stack and assign it to int
        stack.pop(); //then pop it

        if (!visited[wierzcholek]) {  // if it is not visited yet
            visited[wierzcholek] = true; // mark it as visited

            int i = 0;
            while (graph[wierzcholek][i] != -1) {
                int sasiad = graph[wierzcholek][i];
                if (!visited[sasiad]) { // if neighbour is not visited
                    stack.push(sasiad); // push it to stack
                }
                i++;
            }
        }
    }
    //and repeat it until stack is empty :vvv
}

int findConnectedComponents(long long int n, int** graph) {
    bool* visited = new bool[n]();
    int components = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            DFS(i, graph, visited);
            components++;
        }
    }
    delete[] visited;
    return components;
}

long long int getDegreeSum(long long int n, int** graph) {
    long long int degree_sum = 0;
    for (int i = 0; i < n; ++i) {
        int j = 0;
        while (graph[i][j] != -1) j++;
        degree_sum += j; // sum of degrees of all vertices in graph
    }
    return degree_sum; // return it
}

bool isBipartite(long long int n, int** graph) {
    int* color = new int[n];
    for (int i = 0; i < n; ++i) {
        color[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            Stack stack;
            color[i] = 0; // color 0
            stack.push(i); // push i to stack
            while (!stack.isEmpty()) {
                int wierzcholek = stack.peek();
                stack.pop();
                int j = 0;
                while (graph[wierzcholek][j] != -1) {
                    int sasiad = graph[wierzcholek][j];
                    if (color[sasiad] == -1) {
                        color[sasiad] = 1 - color[wierzcholek]; //1-0=1, 1-1=0 the easiest way to get different color
                        stack.push(sasiad); // push it to stack
                    } else if (color[sasiad] == color[wierzcholek]) {
                        delete[] color;
                        return false; //then final boss, if neighbour is colored and it has the same color as wierzcholek return false
                    }
                    j++;
                }
            }
        }
    }
    delete[] color;
    return true;
}

void Coloring(int** graph, long long int n) {
    int* result = new int[n];
    for (int i = 0; i < n; ++i) {
        result[i] = -1;
    }
    result[0] = 1;
    int* available = new int[n + 1]();

    for (int u = 1; u < n; u++) {
        int j = 0;
        while (graph[u][j] != -1) {
            if (result[graph[u][j]] != -1) {
                available[result[graph[u][j]]] = u + 1;
            }
            j++;
        }

        int c;
        for (c = 1; c <= n; c++) {
            if (available[c] != u + 1) {
                break;
            }
        }

        result[u] = c;
    }

    for (int u = 0; u < n; u++) {
        printf("%d ", result[u]);
    }
    printf("\n");

    delete[] result;
    delete[] available;
}

void largestFirstColoring(long long int n, int** graph) {
    int* degrees = new int[n];
    int* vertices = new int[n];

    for (int i = 0; i < n; ++i) {
        int degree = 0;
        while (graph[i][degree] != -1) degree++;
        degrees[i] = degree;
        vertices[i] = i;
    }

    descendingMergeSort(n, degrees, vertices);

    int* result = new int[n];
    for (int i = 0; i < n; ++i) {
        result[i] = -1;
    }
    result[vertices[0]] = 1;
    int* available = new int[n + 1]();

    for (int u = 1; u < n; u++) {
        int j = 0;
        while (graph[vertices[u]][j] != -1) {
            if (result[graph[vertices[u]][j]] != -1) {
                available[result[graph[vertices[u]][j]]] = vertices[u] + 1;
            }
            j++;
        }

        int c;
        for (c = 1; c <= n; c++) {
            if (available[c] != vertices[u] + 1) {
                break;
            }
        }

        result[vertices[u]] = c;
    }

    for (int u = 0; u < n; u++) {
        printf("%d ", result[u]);
    }
    printf("\n");

    delete[] degrees;
    delete[] vertices;
    delete[] result;
    delete[] available;
}

void calculateEccentricities(long long int n, int** graph) {
    int* distances = new int[n];
    int* visit_mark = new int[n];
    int current_mark = 0;

    for (long long int i = 0; i < n; ++i) {
        int max_distance = 0;
        current_mark++;

        for (long long int j = 0; j < n; ++j) {
            visit_mark[j] = 0;
        }

        Queue queue(n);
        queue.enqueue(i);
        visit_mark[i] = current_mark;
        distances[i] = 0;

        int visited_vertices = 1;
        long long  int vertices_in_graph = n;

        while (!queue.isEmpty() && visited_vertices < vertices_in_graph) {
            int v = queue.dequeue();
            for (int j = 0; graph[v][j] != -1; ++j) {
                int neighbor = graph[v][j];
                if (visit_mark[neighbor] != current_mark) {
                    queue.enqueue(neighbor);
                    visit_mark[neighbor] = current_mark;
                    distances[neighbor] = distances[v] + 1;
                    if (distances[neighbor] > max_distance) {
                        max_distance = distances[neighbor];
                    }
                    visited_vertices++;
                }
            }
        }

        printf("%d ", max_distance);
    }

    printf("\n");
    delete[] distances;
    delete[] visit_mark;
}



int main() {
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        long long int n;
        scanf("%lld", &n);

        int** graph = new int*[n];
        for (int j = 0; j < n; ++j) {
            int s;
            scanf("%d", &s);
            graph[j] = new int[s + 1];
            for (int l = 0; l < s; ++l) {
                int neighbor;
                scanf("%d", &neighbor);
                graph[j][l] = neighbor - 1;
            }
            graph[j][s] = -1;
        }

        Degree(n, graph);
        printf("%d\n", findConnectedComponents(n, graph));
        if (isBipartite(n, graph)) {
            printf("T\n");
        } else {
            printf("F\n");
        }
        calculateEccentricities(n, graph);
        printf("?\n");
        Coloring(graph, n);
        largestFirstColoring(n, graph);
        printf("?\n");
        printf("?\n");
        printf("%lld\n", n * (n - 1) / 2 - getDegreeSum(n, graph) / 2);

        for (int j = 0; j < n; ++j) {
            delete[] graph[j];
        }
        delete[] graph;
    }

    return 0;
}