#include <iostream>
#include <windows.h>

using namespace std;
typedef int vertexType;
typedef int edgeType;
typedef boolean status;
#define MAXVEX 100 //the maxium of vertex

typedef struct edgeNode //edgeList node
{
    int adjvex; //adjacency point field, store the index that corresponding to the vertex
    edgeType weight;
    struct edgeNode *next; //list field, point to the next adjacenct point
} edgeNode;

typedef struct vertexNode //vertexList node
{
    int in = 0;
    vertexType data;     //vertex field, store information of vertex
    edgeNode *firstEdge; //edgeList head pointer
} vertexNode, adjList[MAXVEX];

typedef struct
{
    adjList adjlist;
    int numVertexes, numEdges;
} graphAdjList, *GraphAdjList;

void creatALGraph(graphAdjList *G)
{
    int i, j, k, w;
    edgeNode *e;
    cout << "input the number of vertex and edge:\n";
    cin >> G->numVertexes >> G->numEdges;

    cout << "please input the data of vertexes\n";
    for (i = 0; i < G->numVertexes; i++)
    {
        cin >> G->adjlist[i].data;
        G->adjlist[i].firstEdge = NULL;
    }
    cout << "please input vertex number in edge(Vi,Vj) and their weight:\n";
    for (k = 0; k < G->numEdges; k++)
    {
        cin >> i >> j >> w;
        //Head insertion (@linked list)
        // e = new edgeNode;                  //apply for space for memory
        //                                    //generate edge table nodes
        // e->adjvex = i;                     //adjacency number is j
        // e->next = G->adjlist[j].firstEdge; //make e point to the node the current vertex points to
        // G->adjlist[j].firstEdge = e;       //make the pointer of current vertex points to e
        e = NULL;
        e = new edgeNode;
        e->adjvex = j;
        e->weight = w;
        e->next = G->adjlist[i].firstEdge;
        G->adjlist[i].firstEdge = e;
        ++G->adjlist[G->adjlist[i].firstEdge->adjvex].in;
    }
}

//拓扑排序
int *etv, *ltv; //etv(earliest time of vertex)   ltv(latest time of vertex)
int *stack2;
int top2;
status TopolgicalSort(GraphAdjList GL)
{
    edgeNode *e;
    int i, k, getTop;
    int top = 0;   //used to index of stack pointer
    int count = 0; //used to  count number of outputed vertexes
    int *stack;    //a stack to store vertex with zero indegree
    stack = new int[GL->numVertexes];
    for (i = 0; i < GL->numVertexes; i++)
        if (GL->adjlist[i].in == 0)
            stack[++top] = i; //push vertex with zero indegree

    //record topolgicallt sorted vertexes
    top2 = 0;
    etv = new int[GL->numVertexes];
    for (i = 0; i < GL->numVertexes; i++)
        etv[i] = 0;
    stack2 = new int[GL->numVertexes];

    while (top != 0)
    {
        getTop = stack[top--]; //pop vertex with zero indegree
        // cout << GL->adjlist[getTop].data << "-->";
        count++; //count outputed vertex

        stack2[++top2] = getTop;

        for (e = GL->adjlist[getTop].firstEdge; e; e = e->next)
        {
            k = e->adjvex;
            if (!(--GL->adjlist[k].in)) //Decrease the indegree of the adjacent point of the k vertex by one
                stack[++top] = k;       //if  k vertex's indegree is zero, push()

            if ((etv[getTop] + e->weight) > etv[k])
                etv[k] = etv[getTop] + e->weight;
        }
    }
    cout << endl
         << "      ";
    for (int i = 0; i < GL->numVertexes; i++)
    {
        cout << i << '\t';
    }
    cout << endl
         << "etv:  ";
    for (int i = 0; i < GL->numVertexes; i++)
        cout << etv[i] << '\t';
    cout << endl
         << "stk2: ";
    for (int i = GL->numVertexes; i != 0;)
        cout << stack2[i--] << '\t';
    cout << endl
         << "ltv:  ";
    if (count < GL->numVertexes)
        return false;
    else
        return true;
}

//关键路径
void CriticalPath(GraphAdjList GL)
{
    edgeNode *e;
    int i, getTop, k, j;
    int ete, lte; // ete(earliest time of edge)  lte(latest time of edge)
    TopolgicalSort(GL);
    ltv = new int[GL->numVertexes];
    for (i = 0; i < GL->numVertexes; i++)
        ltv[i] = etv[GL->numVertexes - 1]; //initialize ltv assigned to etv[last]
    for (i = 0; i < GL->numVertexes; i++)
        cout << ltv[i] << '\t';
    cout << endl;
    while (top2 != 0)
    {
        getTop = stack2[top2--];
        for (e = GL->adjlist[getTop].firstEdge; e; e = e->next)
        {
            k = e->adjvex;
            if (ltv[k] - e->weight < ltv[getTop])
                ltv[getTop] = ltv[k] - e->weight;
        }
    }
    for (j = 0; j < GL->numVertexes; j++)
    {
        for (e = GL->adjlist[j].firstEdge; e; e = e->next)
        {
            k = e->adjvex;
            ete = etv[j];
            lte = ltv[k] - e->weight;
            if (ete == lte)
                cout << "<v" << GL->adjlist[j].data << ",v" << GL->adjlist[k].data << ">——weight: " << e->weight << endl;
        }
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    GraphAdjList GL = new graphAdjList;
    creatALGraph(GL);
    CriticalPath(GL);
    delete GL;
    GL = NULL;
    system("pause");
    return 0;
}
