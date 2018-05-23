#include<iostream>  
#include<queue>  
#include<cstdio>  
#include<cmath>  
#include<cstdlib>  
#include<cstring>  
using namespace std;  
  
struct knight  
{  
    int x,y,step;  
    int g,h,f;  
    bool operator < (const knight &k) const  
    {  
        return f > k.f;  
    }  
}k;  
  
bool visited[8][8];  
int x2,y2,ans; //起点(x1,y1),终点(x2,y2),最少移动次数ans  
int dir[8][2] = {{-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2}};  
priority_queue<knight> que; //最小优先队列(开启列表)  
  
bool in(const knight &a) //判断knight是否在棋盘内  
{  
    if(a.x < 0|| a.y <0 || a.x >= 8 || a.y >= 8)  
    {  
        return false;  
    }  
    return true;  
}  
  
int Heuristic(const knight &a) //曼哈顿估价函数  
{  
    return (abs(a.x - x2) + abs(a.y - y2)) * 10;  
}  
  
void Astar() //A*算法  
{  
    knight t,s;  
    while(!que.empty()) //如果开启列表不为空  
    {  
        t = que.top();  
        que.pop();  
        visited[t.x][t.y] = true;  
        if(t.x == x2 && t.y == y2) //如果到达目的地  
        {  
            ans = t.step;  
            break;  
        }  
        for(int i=0;i<8;i++)  
        {  
            s.x = t.x + dir[i][0];  
            s.y = t.y + dir[i][1];  
            if(in(s) && !visited[s.x][s.y])  
            {  
                s.g = t.g + 23; //23表示根号5乘以10再取其ceil(向上取整)  
                s.h = Heuristic(s); //曼哈顿估价函数  
                s.f = s.g + s.h;  
                s.step = t.step + 1;  
                que.push(s);  
            }  
        }  
    }  
}  
  
int main()  
{  
    char line[5];  
    int x1,y1;  
    //freopen("111","r",stdin);  
    while(gets(line))  
    {  
        x1 = line[0] - 'a'; //起点  
        y1 = line[1] - '1';  
        x2 = line[3] - 'a';//终点  
        y2 = line[4] - '1';  
        memset(visited,false,sizeof(visited));  
        k.x = x1;  
        k.y = y1;  
        k.g = k.step = 0;  
        k.h = Heuristic(k);  
        k.f = k.g + k.h;  
        while(!que.empty()) que.pop();  
        que.push(k);  
        Astar();  
        printf("To get from %c%c to %c%c takes %d knight moves.\n",line[0],line[1],line[3],line[4],ans);  
    }  
    return 0;  
} 
