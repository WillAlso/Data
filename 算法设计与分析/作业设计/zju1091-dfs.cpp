#include <iostream>
#include <memory.h>
using namespace std;

int knight[8][8];
int x[] = {1,1,2,2,-1,-1,-2,-2};
int y[] = {2,-2,1,-1,2,-2,1,-1};

void DFS(int si,int sj,int moves)
{
	if(si < 0 || sj < 0 || si >= 8 || sj >= 8 || moves >= knight[si][sj])
	{
		return;
	}
	knight[si][sj] = moves;
	int i;
	for(i = 0;i < 8;i++)
	{
		DFS(si + x[i],sj + y[i],moves + 1);
	}
}

int main()
{
	char a[10],b[10];
	while(cin >> a >> b)
	{
		memset(knight,10,sizeof(knight));
		DFS(a[0] - 'a',a[1] - '1',0);
		cout << "To get from " << a << " to " << b << " takes " << knight[b[0] - 'a'][b[1] - '1'] << \
		" knight moves." << endl;
	}
	return 0;
}
