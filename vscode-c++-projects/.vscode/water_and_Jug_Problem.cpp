#include <iostream>
#include <vector>
#include<queue>
using namespace std;

class Solution {
public:
    bool canMeasureWater(int x, int y, int target) {
        if(target==x||target==y)
            return true;
        if(x+y<target)//超过最大值，无法达到
            return false;
        if(x==y)//x与y相等的情况
            if(target==x||target==x+y)
                return true;
            else 
                return false;

        return bfs(x,y,target);
    }
    bool bfs(int &x,int &y,int&target){
        queue <pair<int,int>> bfsQ;
        bfsQ.push({0,0});//初始化为（0，0），表示不倒入水
        bfsQ.push({x,0});//往x加水
        bfsQ.push({0,y});//往y加水
        vector<vector<bool>>visited(x+1,vector<bool>(y+1,false));//用于标记已经访问的对
        visited[0][0]=true;
        visited[x][0]=true;
        visited[0][y]=true;
        while(!bfsQ.empty()){
        //对于两个瓶子依次进行加入水、倒出水、转移水的操作
        pair<int,int>cur=bfsQ.front();
        int a=cur.first;
        int b=cur.second;
        bfsQ.pop();
        if(a!=x&&!visited[x][b]){//x未满，加水
            visited[x][b]=true;
            bfsQ.push({x,b});
        }
        if(b!=y&&!visited[a][y]){//y未满，加水
            visited[a][y]=true;
            bfsQ.push({a,y});
        }
        if(a!=0&&!visited[0][b]){//x不为空，倒出
            visited[0][b]=true;
            bfsQ.push({0,b});
        }
        if(b!=0&&!visited[a][0]){//y不为空，倒出
            visited[a][0]=true;
            bfsQ.push({a,0});
        }
        if(a!=0&&b!=y){//x不为空且y未满，x倒入y
            int poured=a<y-b?a:y-b;
            if(!visited[a-poured][b+poured]){
                visited[a-poured][b+poured]=true;
                bfsQ.push({a-poured,b+poured});
            }
        }
        if(a!=x&&b!=0){//y不为空且x未满，y倒入x
            int poured=b<x-a?b:x-a;
            if(!visited[a+poured][b-poured]){
                visited[a+poured][b-poured]=true;
                bfsQ.push({a+poured,b-poured});
            }
        }
        }

        for(int i=0;i<x+1;i++)
            for(int j=0;j<y+1;j++)
                if(i+j==target&&visited[i][j])
                    return true;
        return false;
    }
};
int main()
{
    Solution s;
    cout<<s.canMeasureWater(3,5,4);
    return 0;
}