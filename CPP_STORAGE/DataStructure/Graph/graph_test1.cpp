#include <iostream>
#include <windows.h>
#include <queue>
#include <algorithm>
using namespace std;

typedef char vertexType;
typedef int edgeType;
#define MAXVEX 100 // the maxium of vertex
#define INFINITE 65535
boolean visited[MAXVEX]; // the mark of accessed array element

char const VexChr = 'V';

// Establish the adjacency matrix representation of the undirected network graph
typedef struct mGraph
{
    vertexType vexs[MAXVEX];
    edgeType arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} mGraph;
void whichMatrixYouWantCall(mGraph *G, int order)
{
    if (order == 1)
    {
        G->arc[0][1] = 10;
        G->arc[0][5] = 11;
        G->arc[1][6] = 16;
        G->arc[1][8] = 12;
        G->arc[1][2] = 18;
        G->arc[2][3] = 22;
        G->arc[2][8] = 8;
        G->arc[3][8] = 21;
        G->arc[3][6] = 24;
        G->arc[3][7] = 16;
        G->arc[3][4] = 20;
        G->arc[6][7] = 19;
        G->arc[5][6] = 17;
        G->arc[4][5] = 26;
        G->arc[4][7] = 7;
    }
    if (order == 2)
    {
        G->arc[0][1] = 1;
        G->arc[0][2] = 5;
        G->arc[1][2] = 3;
        G->arc[1][3] = 7;
        G->arc[1][4] = 5;
        G->arc[2][4] = 1;
        G->arc[2][5] = 7;
        G->arc[3][4] = 2;
        G->arc[3][6] = 3;
        G->arc[4][5] = 3;
        G->arc[4][6] = 6;
        G->arc[4][7] = 9;
        G->arc[5][7] = 5;
        G->arc[6][7] = 2;
        G->arc[6][8] = 7;
        G->arc[7][8] = 4;
    }
    if (order == 3)
    {
    }
    // Non-net
    //  G->arc[0][1] = 1;
    //  G->arc[0][5] = 1;
    //  G->arc[1][6] = 1;
    //  G->arc[1][8] = 1;
    //  G->arc[1][2] = 1;
    //  G->arc[2][3] = 1;
    //  G->arc[3][8] = 1;
    //  G->arc[3][6] = 1;
    //  G->arc[3][7] = 1;
    //  G->arc[3][4] = 1;
    //  G->arc[6][7] = 1;
    //  G->arc[5][6] = 1;
    //  G->arc[4][5] = 1;
    //  G->arc[4][7] = 1;
    //  G->arc[1][6] = 1;
}
void creatMGraph(mGraph *G)
{
    int i, j, k, w;
    // cout << "please input the number(<" << MAXVEX << o09") of vertex and edge\n";
    // cin >> G->numVertexes;
    // cin >> G->numEdges;
    G->numVertexes = 9;
    // G->numEdges = 15;
    G->numEdges = 16;
    // cout << "please input the number of vertexes\n";
    for (i = 0; i < G->numVertexes; i++) // Read the vertex information, creat ve
        // cin >> G->vexs[i];
        G->vexs[i] = VexChr;
    for (i = 0; i < G->numVertexes; i++)
        for (j = 0; j < G->numVertexes; j++)
            G->arc[i][j] = INFINITE; // the initialization of adjacency matrix

    // initilaize adjacency matrix
    //  whichMatrixYouWantCall(G, 1);

    whichMatrixYouWantCall(G, 2); // used for attemp Shortest Path

    for (int i = 0; i < G->numVertexes; i++)
    {
        for (int j = 0; j < G->numVertexes; j++)
        {
            G->arc[j][i] = G->arc[i][j];
            if (i == j)
                G->arc[i][j] = 0;
        }
    }
}
void outputMGraphMatrix(mGraph &G)
{
    cout << "THE ADJACENCY MATRIX: " << endl;
    cout << "  ";
    for (int i = 0; i < G.numVertexes; i++)
        cout << G.vexs[i] << i << '\t';
    cout << endl
         << "--------------------------------------------------------------------------" << endl;
    for (int i = 0; i < G.numVertexes; i++)
    {
        cout << G.vexs[i] << i << " |";
        for (int j = 0; j < G.numVertexes; j++)
        {
            if (G.arc[i][j] == INFINITE)
                cout << "◯" << '\t';
            else
                cout << G.arc[i][j] << '\t';
        }
        cout << endl;
    }
}

//  depth first search of mGraph
void mDFS(mGraph &G, int order)
{
    int j;
    visited[order] = TRUE;
    cout << "the accessed node is : " << G.vexs[order] << order << endl;
    for (j = 0; j < G.numVertexes; j++)
        if (G.arc[order][j] != INFINITE && G.arc[order][j] != 0 && !visited[j])
            mDFS(G, j); // recursive call adjacency nodes of unvisited nodes
}
void mTraverseDFS(mGraph &G)
{
    int i;
    for (i = 0; i < G.numVertexes; i++)
        visited[i] = FALSE; // initialize all nodes states to unvisited state
    for (i = 0; i < G.numVertexes; i++)
        if (!visited[i]) // call DFS to unvistied nodes, if connected graph, will only be executed once
            mDFS(G, i);
}
// breadth first search of mGraph
void mTraverseBFS(mGraph &G)
{
    int i, j;
    queue<int> Q;
    for (i = 0; i < G.numVertexes; i++)
        visited[i] = FALSE;

    for (i = 0; i < G.numVertexes; i++) // loop over each vertexes
    {
        if (!visited[i])
        {
            visited[i] = TRUE;
            cout << "the accessed vertex is : " << G.vexs[i] << i << endl;
            Q.push(i);

            while (!Q.empty())
            {
                i = Q.front(); // return index of accessed node
                Q.pop();
                for (j = 0; j < G.numVertexes; j++)
                {
                    // Determine other vertexes, if there is an edge with the current vertex and have not been visited
                    if (G.arc[i][j] != INFINITE && !visited[j])
                    {
                        visited[j] = TRUE;
                        cout << "the accessed vertex is : " << G.vexs[j] << j << endl;
                        Q.push(j);
                    }
                }
            }
        }
    }
}

// Focus and difficulty!
// minimum spanning tree 最小生成树

//普里姆(Prim)算法

void MiniSpanTree_Prim(mGraph &G)
{
    int min, i, j, k, mincost = 0;
    int adjvex[MAXVEX];  // a array to record corresponding path minimum weight between two vertexes
    int lowcost[MAXVEX]; // a array to record lowcost(minimum weight value)
    lowcost[0] = 0;
    adjvex[0] = 0;
    // initialization
    for (i = 1; i < G.numVertexes; i++)
    {
        lowcost[i] = G.arc[0][i];
        adjvex[i] = 0;
    }
    // search index number of vertex of minimum weight value path
    for (i = 1; i < G.numVertexes; i++)
    {
        min = INFINITE; // Set maximum weight value
        j = 1;
        k = 0;
        while (j < G.numVertexes)
        {
            if (lowcost[j] != 0 && lowcost[j] < min)
            {
                min = lowcost[j]; // min is minimum weight value
                k = j;            // assign to k
            }
            j++;
        }
        cout << "the weight value minimum  of edge in current nodes is : (" << adjvex[k] << "," << k << ")" << endl;
        mincost += min;
        lowcost[k] = 0; // Set the weight of current vertex be 0, to record the vertex had finished mession
        for (j = 1; j < G.numVertexes; j++)
        {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
            {
                // if each edge weight of G.arc[k][j] is lower than current these vertexes that not been add to span tree weight
                lowcost[j] = G.arc[k][j]; // make lower weight value store to lowcost[]
                adjvex[j] = k;            // store vertexes that index is k to adjvex[]
            }
        }
    }
    cout << "the minimum cost of minimum spanning tree is: " << mincost << endl;
}

//克鲁斯卡尔(Kruskal)算法
// Edge Set array
typedef struct
{
    int begin;
    int end;
    int weight;
} Edge;

int Find(int *parent, int f);

bool cmp(Edge e1, Edge e2)
{
    return e1.weight < e2.weight;
}

Edge *initialEdgeSetArray(mGraph &G)
{
    Edge *e = new Edge[G.numEdges];
    int i, j, k = 0;
    for (i = 0; i < G.numVertexes; i++)
        for (j = 0; j < G.numVertexes; j++)
        {
            if (G.arc[i][j] != 0 && G.arc[i][j] != INFINITE)
            {
                G.arc[j][i] = 0; // change original value, and then restore
                e[k].begin = i;
                e[k].end = j;
                e[k].weight = G.arc[i][j];
                k++;
            }
        }

    // restore G.arc[][]
    for (i = 0; i < G.numVertexes; i++)
        for (j = 0; j < G.numVertexes; j++)
            G.arc[j][i] = G.arc[i][j];

    // Sort
    sort(e, e + G.numEdges, cmp);

    cout << endl
         << "FIRST IS EDGE SET ARRAY:   " << endl
         << "the edge set array is : " << endl;
    for (i = 0; i < G.numEdges; i++)
        cout << "Edges[" << i << "] → (" << e[i].begin << "," << e[i].end << "," << e[i].weight << ")" << endl;
    cout << endl;
    return e;
}

void MiniSpanTree_Kruskal(mGraph &G)
{
    int i, n, m;
    int sum = 0;
    Edge *edges = initialEdgeSetArray(G);

    int parent[MAXVEX];
    //
    for (i = 0; i < G.numVertexes; i++)
        parent[i] = INFINITE;

    for (i = 0; i < G.numEdges; i++) // loop over each edge
    {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);
        if (n != m) // if n!=m, it shows that this side does not form a loop with the previous spanning tree
        {
            parent[n] = m; // Put the end vertex of this edge into the parent whose index is the starting point
                           //  indicates that this vertex is already in the spanning tree
            cout << "the selected path is : (" << edges[i].begin << "," << edges[i].end << "," << edges[i].weight << ")" << endl;
            sum += edges[i].weight;
        }
    }

    // OUTPUT
    cout << endl;
    cout << "Current parent[]:\n";
    for (i = 0; i < G.numVertexes; i++)
        cout << "parent[" << i << "] = " << parent[i] << endl;

    cout << endl
         << "the minimum weight value is : " << sum << endl;
    delete[] edges;
}
// find root
int Find(int *parent, int f)
{
    while (parent[f] != INFINITE) // if accessed the vertex
        f = parent[f];            // assign f to parent[f], loop over until find root
    return f;
}
/*
//Another idea to solve Find Root
int parent[MAXVEX];//define a global variable
for (i = 0; i < G.numVertexes; i++)
parent[i] = INFINITE;

int FindFather(int f)//recursion
{
    if (parent[f] != INFINITE)
        return FindFather(parent[f]);
    else
        return f;
}
*/

//最短路径
//迪杰斯特拉(Dijkstra)算法
//和普利姆算法、广度优先遍历相似
typedef std::string Patharc[MAXVEX]; // used to store array that index number of shortest path
typedef int ShortPathTable[MAXVEX];  // used to store the weight sum of the shortest path to each vertex

// Dijkstra algorithm 求有向网G的v0顶点到其余顶点v最短路径F[v]及带权长度D[v]
// P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径长度和
void ShortestPath_Dijkstra(mGraph &G, int v0, Patharc *P, ShortPathTable *D)
{
    int v, w, k, min;
    int final[MAXVEX]; // final[w]=1 record get shortest path between v0 to vw
    for (v = 0; v < G.numVertexes; v++)
    {
        final[v] = 0;
        (*D)[v] = G.arc[v0][v];
        (*P)[v] = "V" + to_string(v0);
    }
    (*D)[v0] = 0;
    final[v0] = 1;

    for (v = 1; v < G.numVertexes; v++)
    {
        min = INFINITE;

        for (w = 0; w < G.numVertexes; w++)
        {
            if (!final[w] && (*D)[w] < min) // final[w]==0 must be established, because final[w]==0 means this path have not been measured
                                            // pay attention to here knowledge about 贪心算法 principle
            {
                min = (*D)[w];
                k = w;
            }
        }
        final[k] = 1; // mark final[k] (at the same time k is index of minimum in D)
        for (w = 0; w < G.numVertexes; w++)
        {
            if (!final[w] && (*D)[k] + G.arc[k][w] < (*D)[w] && G.arc[k][w] != INFINITE)
            {
                (*D)[w] = (*D)[k] + G.arc[k][w];
                (*P)[w] = (*P)[k] + "-->V" + to_string(w);
            }
        }
    }

    // OUTPUT
    cout << "         ";
    for (v = 0; v < G.numVertexes; v++)
        cout << VexChr << v << '\t';
    cout << "\nThe ShortPathTable[] is :\n"
            "         ";
    for (v = 0; v < G.numVertexes; v++)
        cout << (*D)[v] << '\t';
    cout << "\nThe Patharc[] is :" << endl;
    for (v = 0; v < G.numVertexes; v++)
        cout << (*P)[v] << "=" << (*D)[v] << endl;
    cout << endl;
}

//弗洛伊德(Floyd)算法

typedef int **PathMatrix;
typedef int **ShortestPathTable;
static PathMatrix P;
static ShortestPathTable D;
void ShortestPath_Floyd(mGraph &G, PathMatrix &P, ShortestPathTable &D)
{
    int v, w, k;
    // APPLY FOR MEMORY
    P = new int *[G.numVertexes];
    for (v = 0; v < G.numVertexes; v++)
        P[v] = new int[G.numVertexes];
    D = new int *[G.numVertexes];
    for (v = 0; v < G.numVertexes; v++)
        D[v] = new int[G.numVertexes];

    // initialize P && D
    for (v = 0; v < G.numVertexes; v++)
    {
        for (w = 0; w < G.numVertexes; w++)
        {
            D[v][w] = G.arc[v][w]; // assign weight to D
            P[v][w] = w;
        }
    }

    // Three levels of loop nesting, k stands for the index of the transit vertex, v stands for the starting vertex,
    // and w stands for the ending vertex
    for (k = 0; k < G.numVertexes; ++k)
    {
        for (v = 0; v < G.numVertexes; ++v)
        {
            for (w = 0; w < G.numVertexes; ++w)
            {
                // Core judgement: D⁰[v][w]=min{D[v][w] , D[v][k]+D[k][w]}
                if (D[v][w] > D[v][k] + D[k][w])
                {
                    /*
                    If the path through the index k vertex is shorter than the original path between two points,
                    set the weight of the distance between the current two points to a smaller one
                    */
                    D[v][w] = D[v][k] + D[k][w];
                    P[v][w] = P[v][k];
                }
                        }
        }
    }
}
void DisplayFloyd(mGraph &G, PathMatrix *P, ShortestPathTable *D)
{
    int v, w, k;
    for (v = 0; v < G.numVertexes; ++v)
    {
        for (w = v + 1; w < G.numVertexes; w++)
        {
            cout << "V" << v << "-->V" << w << "  weight: " << (*D)[v][w];
            k = (*P)[v][w];
            cout << "   Path: " << v;
            while (k != w)
            {
                cout << " -->" << k;
                k = (*P)[k][w];
            }
            cout << "-->" << w << endl;
        }
        cout << endl;
    }
}

int main()

{
    SetConsoleOutputCP(65001);
    mGraph *G = new mGraph;
    creatMGraph(G);
    outputMGraphMatrix(*G);
    cout << endl
         << "--------------------------------------------------------------------------" << endl;
    cout << "Breadth First Traverse:\n";
    mTraverseBFS(*G);
    cout << endl
         << "--------------------------------------------------------------------------" << endl;
    cout << "Depth First Traverse:\n";
    mTraverseDFS(*G);
    cout << endl
         << "--------------------------------------------------------------------------" << endl;
    cout << "Minimum Spanning Tree_ Prim Algorithm:\n";
    MiniSpanTree_Prim(*G);
    cout << endl
         << "--------------------------------------------------------------------------" << endl;
    cout << "Minimum Spanning Tree_Kruskal Algorithm:\n";
    MiniSpanTree_Kruskal(*G);
    cout << endl
         << "--------------------------------------------------------------------------" << endl;
    cout << "Shortest Path Dijkstra Algorithm:\n";
    Patharc p;
    ShortPathTable d;
    ShortestPath_Dijkstra(*G, 0, &p, &d);
    cout << endl
         << "--------------------------------------------------------------------------" << endl;
    cout << "Shortest Path Floyd Algorithm:\n";
    ShortestPath_Floyd(*G, P, D);
    DisplayFloyd(*G, &P, &D);
    cout << endl
         << "--------------------------------------------------------------------------" << endl;
    delete G;
    G = NULL;
    system("pause");
    return 0;
}
