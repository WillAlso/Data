#include <iostream>
#include <queue>
using namespace std;
 
 struct point{
 	int x,y;
 	int c;
 }from,to;
 
 int main()
 {
 	queue<point> q;
 	char src[3],dist[3];
 	int dx[] = {1,1,2,2,-1,-1,-2,-2};
 	int dy[] = {2,-2,1,-1,2,-2,1,-1};
 	while(cin >> src >> dist)
 	{
 		cout << "To get from " << src << " to " << dist;
 		while(!q.empty())
 		{
 			q.pop();
		}
		from.x = src[0] - 'a';
		from.y = src[1] - '1';
		from.c = 0;
		to.x = dist[0] - 'a';
		to.y = dist[1] - '1';
		q.push(from);
		point temp;
		while(true)
		{
			from = q.front();
			q.pop();
			if(from.x == to.x && from.y == to.y)
			{
				break;
			}
			for(int i = 0;i < 8;i++)
			{
				temp.x = from.x + dx[i];
				temp.y = from.y + dy[i];
				temp.c = from.c + 1;
				if(temp.x < 0|| temp.x > 7 || temp.y < 0 || temp.y > 7)
				{
					continue;
				}
				q.push(temp);
			}
		}
		cout <<" takes " << from.c << " knight moves." << endl;
	}
 	return 0;
 }
