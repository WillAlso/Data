typedef struct Path
{
	int vex[20];
	Path *next;
}*PathList;

struct Vex
{
	int num;
	char name[20];
	char desc[1024];
	int time;
};

struct Edge
{
	int vex1;
	int vex2;
	int weight;
};

class CGraph
{
private:
	int m_aAdjMatrix[20][20];	//�ڽӾ���
	Vex m_aVexs[20];			//������Ϣ����
	int m_nVexNum;				//��ǰͼ�Ķ�����
public:
	void Init();
	bool InsertVex(Vex sVex);
	bool InsertEdge(Edge sEdge);
	Vex GetVex(int v);
	int FindEdge(int v,Edge aEdge[]);
	int GetVexNum();
	Edge GetEdge(int x1,int x2);
	void DFS(int nVex,bool bVisted[],int &nIndex,PathList &pList);
	void DFSTraverse(int nVex,PathList pList);
};

