#include <iostream>
#include <windows.h>
#include <queue>
using namespace std;
typedef char vertexType;
typedef int edgeType;
#define MAXVEX 100       //the maxium of vertex
boolean visited[MAXVEX]; //the mark of accessed array element
//Establish the adjacency matrix representation of the undirected network graph
typedef struct mGraph
{
   vertexType vexs[MAXVEX];
   edgeType arc[MAXVEX][MAXVEX];
   int numVertexes, numEdges;
} mGraph;

typedef struct edgeNode //edgeList node
{
   int adjvex; //adjacency point field, store the index that corresponding to the vertex
   edgeType weight;
   struct edgeNode *next; //list field, point to the next adjacenct point
} edgeNode;

typedef struct vertexNode //vertexList node
{
   vertexType data;     //vertex field, store information of vertex
   edgeNode *firstEdge; //edgeList head pointer
} vertexNode, adjList[MAXVEX];

typedef struct
{
   adjList adjlist;
   int numVertexes, numEdges;
} graphAdjList;

void creatMGraph(mGraph *G)
{
   int i, j, k, w;
   cout << "please input the number(<" << MAXVEX << ") of vertex and edge\n";
   cin >> G->numVertexes;
   cin >> G->numEdges;

   cout << "please input the number of vertexes\n";
   for (i = 0; i < G->numVertexes; i++) //Read the vertex information, creat ve
      cin >> G->vexs[i];
   for (i = 0; i < G->numVertexes; i++)
      for (j = 0; j < G->numVertexes; j++)
         G->arc[i][j] = INFINITE; //the initialization of adjacency matrix

   for (k = 0; k < G->numEdges; k++)
   {
      cout << "please input index i, index j and weight w in edge(Vi,Vj):\n";
      cin >> i >> j >> w;
      G->arc[i][j] = w;
      G->arc[j][i] = G->arc[i][j];
   }
}

// THE ADJACENCY TABLE OF UNDIRECRED GRAPH
void creatALGraph(graphAdjList *G)
{
   int i, j, k;
   edgeNode *e;
   cout << "input the number of vertex and edge:\n";
   cin >> G->numVertexes >> G->numEdges;

   cout << "please input the data of vertexes\n";
   for (i = 0; i < G->numVertexes; i++)
   {
      cin >> G->adjlist[i].data;
      G->adjlist[i].firstEdge = NULL;
   }

   for (k = 0; k < G->numEdges; k++)
   {

      cout << "please input vertex number in edge(Vi,Vj):\n";
      cin >> i >> j;

      //Head insertion (@linked list)
      e = new edgeNode;                  //apply for space for memory
                                         //generate edge table nodes
      e->adjvex = j;                     //adjacency number is j
      e->next = G->adjlist[i].firstEdge; //make e point to the node the current vertex points to
      G->adjlist[i].firstEdge = e;       //make the pointer of current vertex points to e

      e = new edgeNode;
      e->adjvex = i;
      e->next = G->adjlist[j].firstEdge;
      G->adjlist[j].firstEdge = e;
   }
}

//  depth first search of mGraph
void mDFS(mGraph &G, int order)
{
   int j;
   visited[order] = TRUE;
   cout << "the accessed nodes is : " << G.vexs[order] << endl;
   for (j = 0; j < G.numVertexes; j++)
      if (G.arc[order][j] != INFINITE && !visited[j])
         mDFS(G, j); //recursive call adjacency nodes of unvisited nodes
}
void mTraverseDFS(mGraph &G)
{
   int i;
   for (i = 0; i < G.numVertexes; i++)
      visited[i] = FALSE; //initialize all nodes states to unvisited state
   for (i = 0; i < G.numVertexes; i++)
      if (!visited[i]) //call DFS to unvistied nodes, if connected graph, will only be executed once
         mDFS(G, i);
}
// breadth first search of mGraph
void mTraverseBFS(mGraph &G)
{
   int i, j;
   queue<int> Q;
   for (i = 0; i < G.numVertexes; i++)
      visited[i] = FALSE;

   for (i = 0; i < G.numVertexes; i++) //loop over each vertexes
   {
      if (!visited[i])
      {
         visited[i] = TRUE;
         cout << "the accessed nodes is : " << G.vexs[i] << endl;
         Q.push(i);

         while (!Q.empty())
         {
            i = Q.front(); //return index of accessed node

            Q.pop();
            for (j = 0; j < G.numVertexes; j++)
            {
               //Determine other vertexes, if there is an edge with the current vertex and have not been visited
               if (G.arc[i][j] != INFINITE && !visited[j])
               {
                  visited[j] = TRUE;
                  cout << "the vertexes is : " << G.vexs[j] << endl;
                  Q.push(j);
               }
            }
         }
      }
   }
}
//depth first search of adjacency table
void ALDFS(graphAdjList &GL, int i)
{
   edgeNode *p;
   visited[i] = TRUE;
   cout << "the accessed nodes is : " << GL.adjlist[i].data << endl;
   p = GL.adjlist[i].firstEdge;
   while (p)
   {
      if (!visited[p->adjvex])
         ALDFS(GL, p->adjvex);
      p = p->next;
   }
}
void ALTraverseDFS(graphAdjList &GL)
{
   int i;
   for (i = 0; i < GL.numVertexes; i++)
      visited[i] = FALSE;
   for (i = 0; i < GL.numVertexes; i++)
      if (!visited[i])
         ALDFS(GL, i);
}
//breadth first search of adjacency table
void ALTraverseBFS(graphAdjList &GL)
{
   int i;
   edgeNode *p;
   queue<int> Q;
   for (i = 0; i < GL.numVertexes; i++)
      visited[i] = FALSE;

   for (i = 0; i < GL.numVertexes; i++)
   {
      if (!visited[i])
      {
         visited[i] = TRUE;
         cout << "the accessed node is : " << GL.adjlist[i].data << endl;
         Q.push(i);
         while (!Q.empty())
         {
            i = Q.front();
            Q.pop();
            p = GL.adjlist[i].firstEdge;
            while (p) //if there is an adjacent edge
            {
               if (!visited[p->adjvex])
               {
                  visited[p->adjvex] = TRUE;
                  cout << "the accessed node is : " << GL.adjlist[p->adjvex].data << endl;
                  Q.push(p->adjvex);
               }
               p = p->next;
            }
         }
      }
   }
}

//Focus and difficulty!
//minimum spanning tree 最小生成树

//普里姆(Prim)算法

void MiniSpanTree_Prim(mGraph &G)
{
   int min, i, j, k;
   int adjvex[MAXVEX];
   int lowcost[MAXVEX];
   lowcost[0] = 0;
   adjvex[0] = 0;

   for (i = 1; i < G.numVertexes; i++)
   {
      lowcost[i] = G.arc[0][i];
      adjvex[i] = 0;
   }
   for (i = 1; i < G.numVertexes; i++)
   {
      min = INFINITE;
      j = 1;
      k = 0;
      while (j < G.numVertexes)
      {
         if (lowcost[j] != 0 && lowcost[j] < min)
         {
            min = lowcost[j];
            k = j;
         }
         j++;
      }
      cout << "the weight value minimum  of edge in current nodes is : (" << adjvex[k] << "," << k << ")" << endl;
      lowcost[k] = 0;
      for (j = 1; j < G.numVertexes; j++)
      {
         if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
         {
            lowcost[j] = G.arc[k][j];
            adjvex[j] = k;
         }
      }
   }
}

//克鲁斯卡尔(Kruskal)算法
typedef struct
{
   int begin; 
   int end;
   int weight;
} Edge;
const int MAXEDGE = 100;
int Find(int *parent, int f);
void MiniSpanTree_Kruskal(mGraph &G)
{
   int i, n, m;
   Edge edges[MAXEDGE];
   int parent[MAXVEX];

   for (i = 0; i < G.numVertexes; i++)
      parent[i] = 0;
   for (i = 0; i < G.numVertexes; i++)
   {
      n = Find(parent, edges[i].begin);
      m = Find(parent, edges[i].end);
      if (n != m)
      {
         parent[n] = m;
         cout << "" << edges[i].begin << edges[i].end << edges[i].weight << endl;
      }
   }
}
int Find(int *parent, int f)
{
   while (parent[f] > 0)
      f = parent[f];
   return f;
}
int main()
{
   SetConsoleOutputCP(65001);
   mGraph *G = new mGraph;
   creatMGraph(G);
   delete G;
   G = NULL;
   system("pause");
   return 0;
}
