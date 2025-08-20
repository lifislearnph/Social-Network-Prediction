#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
#include<numeric>
using namespace std;
class Solution {
    public:
        int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
            //先得出耗时矩阵T
            vector<vector<int>>T =make_Tree(edges,values.size());
            //进行回溯法寻找最长路径
            int cValue=values[0];
            values[0]=0;//加入序列后该节点值被标为0
            vector<int> in_T(values.size(),0);//记录该点被加入次数
            in_T[0]=1;
            return backtrack(0,values,T,in_T,maxTime,cValue);
        }
        //n为最长路径经历的节点，最长路径为遍历所有通路两遍？
        int backtrack(int t,vector<int>& values, vector<vector<int>>& T, vector<int>& in_T,int maxTime,int cValue){//回溯法找到最佳路径
            
                int bValue=cValue;
                bool T_end=true;//是叶子节点
                for(int i=0;i<T[t].size();++i)
                    if(T[t][i]!=-1&&T[t][i]<maxTime&&cValue+values[i]>=bValue){//两点间有连线；加入两点耗时后不超过总耗时；加入该点后value值大于bestValue值
                        int vtmp=values[i];
                        cValue+=values[i];
                        values[i]=0;//已加入的节点值不再计入
                        in_T[i]++;
                        int tmp=backtrack(i,values,T,in_T,maxTime-T[t][i],cValue);
                        
                        if(tmp!=-1){
                            bValue=tmp;//更新最大值
                            T_end=false;//当前节点有可通往起点的子节点
                        }
                        //进入下一个子树分支前，还原该节点
                        in_T[i]--;
                        if(in_T[i]==0){
                            values[i]=vtmp;
                            cValue-=values[i];
                        }
                        
                    }
                if(T_end){//已经是叶子节点的情况下，必须能够返回开始节点该路径值才有效
                    if(t==0){
                        return bValue;
                    }
                    else 
                        return -1;
                }
                else {
                   
                    return bValue;
                }
        }
    
        vector<vector<int>> make_Tree(vector<vector<int>>& edges,int n){//构造子集树所需限制条件
            vector<vector<int>> T(n,(vector<int>(n)));//n为节点数,T的值为经过两点的耗时
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    T[i][j]=-1;//初始化为-1
                
            for(int i=0;i<edges.size();i++){
                T[edges[i][0]][edges[i][1]]=edges[i][2];
                T[edges[i][1]][edges[i][0]]=edges[i][2];
            }
            return T;
        }
    };
    
    int main()
    {
        vector<vector<int>> e ={{0,3,45},{0,2,16},{0,1,36},{3,4,38},{2,3,29}};
        vector<int>v={61,11,18,43,81};
        int m=88;
        Solution S;
        int res =S.maximalPathQuality(v,e,m);
        cout<<"res"<<res<<endl;
    }