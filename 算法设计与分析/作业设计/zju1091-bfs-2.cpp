#include<iostream>  
#include<cstdio>  
#include<queue>  
#include<cstring>  
#define qq 330  
using namespace std;  
int vis1[qq][qq];      //既标记路径 也统计步数  
int vis2[qq][qq];  
int fx1[8]={2,2,-2,-2,1,1,-1,-1};  
int fx2[8]={1,-1,1,-1,2,-2,2,-2};  
struct node {  
 int x,y;  
}start,end;               //双向BFS的两端起点        
int sx,sy,ex,ey;  
int m;  
bool inside(int xx,int yy)           //判断越界  
{  
    if(xx>=0&&yy>=0&&xx<m&&yy<m)  
        return true;  
    else  
        return false;  
}  
void dbfs()  
{  
    int i,tq,tw;  
    queue<node>q,w;            //两个队列  
    start.x=sx;start.y=sy;  
    end.x=ex;end.y=ey;  
    q.push(start);  
    w.push(end);                
    vis1[sx][sy]=0;         //后面的步数是从0开始加的  
    vis2[ex][ey]=0;  
    while(!q.empty()&&!w.empty())  
    {  
        node now,next;  
        tq=q.size();      //为了先将一个队列的全部判断完   
        while(tq--)  
        {  
          now=q.front();  
          q.pop();  
          if(inside(now.x,now.y)&&vis2[now.x][now.y]!=-1)    //两端开始的都经过这一点。。  
          {  
              printf("%d\n",vis1[now.x][now.y]+vis2[now.x][now.y]);  
              return;  
          }  
          for(i=0;i<8;i++)  
          {  
              next.x=now.x+fx1[i];  
              next.y=now.y+fx2[i];  
              if(inside(next.x,next.y)&&vis2[next.x][next.y]!=-1)    //重要，，因为奇数步时。。。  
              {  
                  printf("%d\n",vis1[now.x][now.y]+1+vis2[next.x][next.y]);  
                  return;  
              }  
              if(inside(next.x,next.y)&&vis1[next.x][next.y]==-1)  
              {  
                  vis1[next.x][next.y]=vis1[now.x][now.y]+1;  
                  q.push(next);  
              }  
          }  
        }  
        tw=w.size();  
        while(tw--)        //同上  
        {  
          now=w.front();  
          w.pop();  
          if(inside(now.x,now.y)&&vis1[now.x][now.y]!=-1)  
          {  
              printf("%d\n",vis1[now.x][now.y]+vis2[now.x][now.y]);  
              return;  
          }  
          for(i=0;i<8;i++)  
          {  
              next.x=now.x+fx1[i];  
              next.y=now.y+fx2[i];  
              if(inside(next.x,next.y)&&vis1[next.x][next.y]!=-1)  
              {  
                  printf("%d\n",vis2[now.x][now.y]+1+vis1[next.x][next.y]);  
                  return;  
              }  
              if(inside(next.x,next.y)&&vis2[next.x][next.y]==-1)  
              {  
                  vis2[next.x][next.y]=vis2[now.x][now.y]+1;  
                  w.push(next);  
              }  
          }  
        }  
    }  
}  
int main()  
{  
    int t;  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%d",&m);  
        scanf("%d%d%d%d",&sx,&sy,&ex,&ey);  
        memset(vis1,-1,sizeof(vis1));      //标记为未走过  
        memset(vis2,-1,sizeof(vis2));  
        dbfs();  
    }  
        return 0;  
}  
