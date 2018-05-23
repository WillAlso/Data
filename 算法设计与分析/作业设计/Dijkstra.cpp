#include<stdio.h>  
#include<stdlib.h>  
 typedef struct node {  
    int distance;  
    int tag;  
} chess;  
  
int position[8][2] = {  
    {-1,  2}, { 1,  2}, { 2, -1}, { 2,  1},  
    {-1, -2}, { 1, -2}, {-2, -1}, {-2,  1}  
};  
  
chess **chess1;  
chess **chess2;  
chess **chess3;  
  
void dijkstra(chess **map, int x, int y) {  
    map[x][y].distance = 0;  
    map[x][y].tag = 1;  
      
    int set[64][2];  
    set[0][0] = x;  
    set[0][1] = y;  
      
    int xi, yi, x_n, y_n;  
    int min_x, min_y;  
    int min;   
      
    min_x = x;  
    min_y = y;  
    for(int i = 0; i < 8; i++) {  
        x_n = min_x + position[i][0];  
        y_n = min_y + position[i][1];  
        if(x_n >= 0 && x_n < 8 && y_n >= 0 && y_n < 8) {  
            if(map[x_n][y_n].tag == 0) {  
                if(map[x_n][y_n].distance == -1 ||   
                    map[x_n][y_n].distance > map[min_x][min_y].distance + 1) {  
                    map[x_n][y_n].distance = map[min_x][min_y].distance + 1;  
                }  
            }  
        }     
    }  
      
    int count = 1;  
    while(count < 64) {  
        min = -1;  
          
        for(int i = 0; i < count; i++) {  
            xi = set[i][0];  
            yi = set[i][1];  
            for(int j = 0; j < 8; j++) {  
                x_n = xi + position[j][0];  
                y_n = yi + position[j][1];  
                if(x_n >= 0 && x_n < 8 && y_n >= 0 && y_n < 8) {  
                    if(map[x_n][y_n].tag == 0) {  
                        if(min == -1 || min > map[x_n][y_n].distance) {  
                            min = map[x_n][y_n].distance;  
                            min_x = x_n;  
                            min_y = y_n;  
                        }  
                    }  
                }  
            }  
        }  
          
        map[min_x][min_y].tag = 1;  
        set[count][0] = min_x;  
        set[count][1] = min_y;  
        count++;  
          
        for(int i = 0; i < 8; i++) {  
            x_n = min_x + position[i][0];  
            y_n = min_y + position[i][1];  
            if(x_n >= 0 && x_n < 8 && y_n >= 0 && y_n < 8) {  
                if(map[x_n][y_n].tag == 0) {  
                    if(map[x_n][y_n].distance == -1 ||   
                        map[x_n][y_n].distance > map[min_x][min_y].distance + 1) {  
                        map[x_n][y_n].distance = map[min_x][min_y].distance + 1;  
                    }  
                }  
            }     
        }  
    }  
}  
          
/* 
 * The main program. 
 */  
int main(void) {  
    chess1 = (chess**) malloc(sizeof(chess*) * 8);  
    for(int i = 0; i < 8; i++) {  
        chess1[i] = (chess*) malloc(sizeof(chess) * 8);  
    }  
      
    chess2 = (chess**) malloc(sizeof(chess*) * 8);  
    for(int i = 0; i < 8; i++) {  
        chess2[i] = (chess*) malloc(sizeof(chess) * 8);  
    }  
      
    chess3 = (chess**) malloc(sizeof(chess*) * 8);  
    for(int i = 0; i < 8; i++) {  
        chess3[i] = (chess*) malloc(sizeof(chess) * 8);  
    }  
    int t;  
      
    scanf("%d", &t);  
      
    for(; t > 0; t--) {  
        for(int i = 0; i < 8; i++) {  
            for(int j = 0; j < 8; j++) {  
                chess1[i][j].distance = chess2[i][j].distance   
                    = chess3[i][j].distance = -1;  
                chess1[i][j].tag = chess2[i][j].tag   
                    = chess3[i][j].tag = 0;  
            }  
        }  
          
        char location[3];  
          
        scanf("%s", location);  
        dijkstra(chess1, location[0] - 'A', location[1] - '1');  
          
        scanf("%s", location);  
        dijkstra(chess2, location[0] - 'A', location[1] - '1');  
          
        scanf("%s", location);  
        dijkstra(chess3, location[0] - 'A', location[1] - '1');   
          
        int min = -1;  
          
        for(int i = 0; i < 8; i++) {  
            for(int j = 0; j < 8; j++) {  
                int s = chess1[i][j].distance + chess2[i][j].distance   
                    + chess3[i][j].distance;  
                if(min == -1 || min > s) {  
                    min = s;  
                }  
            }  
        }  
          
        printf("%d\n", min);       
    }  
    return 0;  
}  