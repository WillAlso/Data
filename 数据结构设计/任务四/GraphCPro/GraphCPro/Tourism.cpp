#include "Tourism.h"
CGraph m_Graph;

void CreateGraph()
{
	
	m_Graph.Init();
	ifstream fin(INPUT_VEX);
	ifstream fin1(INPUT_EDGE);
	ifstream fin2(INPUT_TIME);
	int cnt;
	Vex vex;
	Edge edge;
	if(!fin)
	{
		cout << "No File!" << endl;
		return;
	}
	fin >> cnt;
	for(int i = 0;i < cnt;i++)
	{
		string read;
		fin >> vex.num;
		fin >> vex.name;
		fin >> vex.desc;
		fin2 >> vex.time;
		m_Graph.InsertVex(vex);
	}
	while(!fin1.eof())
	{
		fin1 >> edge.vex1;
		fin1 >> edge.vex2;
		fin1 >> edge.weight;
		m_Graph.InsertEdge(edge);
	}
	fin.close();
	fin1.close();
	cout << "-----顶点-----" << endl;
	int m = m_Graph.GetVexNum();
	Vex vext;
	for(int i = 0;i < m;i++)
	{
		vext = m_Graph.GetVex(i);
		cout << vext.num << "-" << vext.name << endl;
	}
	cout << "-----边-----" << endl;
	for(int i = 0;i < cnt;i++)
	{
		for(int j = i;j < cnt;j++)
		{
			Edge edge1 = m_Graph.GetEdge(i,j);
			if(edge1.weight != 0)
			{
				cout << "(V" << i << ",V" << j << ")" << " " << edge1.weight << endl;
			}
		}
	}
	cout << "-----热点-----" << endl;
	int c = m_Graph.GetVexNum();
	Vex *vex1 = new Vex[cnt];
	for(int i = 0;i < c;i++)
	{
		vex1[i] = m_Graph.GetVex(i);
	}
	int max = 0;
	int max_pos = -1;
	for(int i = 0;i < c;i++)
	{
		if(vex1[i].time > max)
		{
			max = vex1[i].time;
			max_pos = i;
		}
	}
	cout << m_Graph.GetVex(max_pos).name << " 访问次数:" << m_Graph.GetVex(max_pos).time << endl;
	cout << "--------------" << endl << endl;
}

void GetSpotInfo()
{
	ofstream fout(INPUT_TIME);
	cout << "-----顶点-----" << endl;
	int cnt = m_Graph.GetVexNum();
	Vex *vex = new Vex[cnt];
	for(int i = 0;i < cnt;i++)
	{
		vex[i] = m_Graph.GetVex(i);
		cout << vex[i].num << "-" << vex[i].name << endl;
	}
	int num;
	cout << "请输入想要查询的景点编号:";
	cin >> num;
	system("cls");
	Vex des_vex;
	for(int i = 0;i < cnt;i++)
	{
		if(vex[i].num == num)
		{
			des_vex = vex[i];\
			vex[i].time++;
		}
	}
	cout << des_vex.name << endl << des_vex.desc << endl;
	for(int i = 0;i < cnt;i++)
	{
		fout << vex[i].time << " ";
	}
	fout << endl;
	fout.close();
	cout << "-----周边景区-----" << endl;
	Edge *edge = new Edge[m_Graph.GetVexNum()];
	int t = m_Graph.FindEdge(num,edge);
	for(int i = 0;i < t;i++)
	{
		cout << m_Graph.GetVex(num).name << "->" <<  m_Graph.GetVex(edge[i].vex2).name << " " << edge[i].weight << "m" << endl;
	}
	cout << "--------------" << endl << endl;
}

void TravelPath()
{
	cout << "=====旅游景点导航=====" << endl;
	int nVexNum = m_Graph.GetVexNum();
	for(int i = 0;i < nVexNum;i++)
	{
		Vex sVex = m_Graph.GetVex(i);
		cout << sVex.num << "-" << sVex.name << endl;
	}
	cout << "请输入起始点编号:";
	int nVex;
	cin >> nVex;
	if(nVex < 0 || nVex >= nVexNum)
	{
		cerr << "输入错误" << endl;
		return;
	}
	PathList pList = new Path;
	PathList pHead = pList;
	m_Graph.DFSTraverse(nVex,pList);
	cout << "导游路线为:" << endl;
	int count = 1;
	pList = pHead;
	while(pList->next)
	{
		Vex sVex = m_Graph.GetVex(pList->vex[0]);
		cout << "路线" << count++ << ":" << sVex.name;
		for(int j = 1;j < nVexNum;j++)
		{
			sVex = m_Graph.GetVex(pList->vex[j]);
			cout << " -> " << sVex.name;
		}
		cout << endl;
		Path *temp = pList;
		pList = pList->next;
		delete temp;
	}
	delete pList;
	pList = NULL;
	pHead = NULL;
}

void FindShortPath()
{
	cout << "=====搜索最短路径=====" << endl;
	int nVexNum = m_Graph.GetVexNum();
	if(nVexNum <= 0)
	{
		cout << "无景点信息!" << endl;
		return;
	}
	for(int i = 0;i < nVexNum;i++)
	{
		Vex sVex = m_Graph.GetVex(i);
		cout << sVex.num << "-" << sVex.name << endl;
	}
	int nVexStart;
	cout << "输入景点起点:";
	cin >> nVexStart;
	int nVexEnd;
	cout << "输入景点终点:";
	cin >> nVexEnd;
	Edge aPath[20];
	m_Graph.FindShortPath(nVexStart,nVexEnd,aPath);
}