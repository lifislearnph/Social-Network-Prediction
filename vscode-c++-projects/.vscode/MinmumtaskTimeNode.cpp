#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace  std;


class Solution {
public:
    static bool cmp(const vector<int> &t1, const vector<int> &t2){
        return t1[1]<t2[1];
    }
    int findMinimumTime(vector<vector<int>>& tasks) {
        //在重合时间段塞入尽可能多的任务
        //在时间区间中安排得越靠后，就越可能发生重合
        int n = tasks.size();
        sort(tasks.begin(), tasks.end(), cmp);//按照结束时间升序排列
        
        int dura=0,end=0;
        int num=0;
        vector<bool>run(tasks[n-1][1]+1) ;//标记哪个时间点已经有任务运行
        for(int i=0;i<n;i++){
            if(tasks[i][2]>0){//任务未结束
            //划分出一个区间
                dura=tasks[i][2];//持续时间
                end=tasks[i][1];//结束
                num+=tasks[i][2];
               
                for(int j=i+1;j<n;j++){
                    if(tasks[j][0]<=end&&tasks[j][2]>0){//之后任务开始时间早于该任务结束时间，且仍未结束
                        int k=0,maxTask=0;
                        while(end-k>=tasks[j][0]&&maxTask<dura){
                            if(!run[end-k]){//只有未发生任务的节点才能安插任务
                                tasks[j][2]--;
                                maxTask++;
                            }
                            k++;
                       }
                    }
                }
                //更新任务安插情况：
                int k=0;
                while(tasks[i][2]!=0){
                    if(!run[tasks[i][1]-k]){//该点无任务运行，加入任务
                        run[tasks[i][1]-k]=true;
                        tasks[i][2]--;
                    }
                    k++;
                }
            }
        }
        return num;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> a={{2,13,2},{6,18,5},{2,13,3}};
    cout<<s.findMinimumTime(a);
    return 0;
}