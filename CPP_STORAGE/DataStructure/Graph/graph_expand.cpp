#include <iostream>
#include <windows.h>

using namespace std;
#define MAX_VEXTEX 20
typedef int infoType;
typedef int vertexType;
typedef int status;
//cross linked list
typedef struct arcBox
{
    int headVex, tailVex;
    struct arcBox *headlink, *taillink;
} arcBox;
typedef struct vexNode
{
    arcBox *firstin, *firstout;
    vertexType data;
} vexNode;
typedef struct
{
    vexNode cList[MAX_VEXTEX];
    int numVextexes, numEdges;
} OLGraph;
status creatDG(OLGraph &G, int vexNum, int edgeNum)
{
    G.numVextexes = vexNum;
    G.numVextexes = edgeNum;

    //initialization
    cout << "please input the data of vextexes:\n";
    for (int i = 0; i < G.numVextexes; i++)
    {
        cin >> G.cList[i].data;
        G.cList[i].firstin = G.cList[i].firstout = NULL;
    }

    for (int i = 0; i < G.numEdges; i++)
    {
        vexNode node1, node2;
        cout << "please input two nodes of " << i + 1 << "-th arc" << endl;
        cin >> node1.data >> node2.data;

        //insertArc(G,node1,node2);
    }
    return 1;
}

//MULTIPLE ADJACENCY LIST
typedef struct arcNode
{
    bool mark;
    int iVex, jvex;
    struct arcNode *ilink, *jlink;
} arcNode;
typedef struct VNode
{
    vertexType data;
    arcNode *firstedge;
} VNode;
typedef struct
{
    VNode adjMulList[MAX_VEXTEX];
    VNode adjMulList[MAX_VEXTEX];
    int vexNum, arcNum;
} AMLGraph;

int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
