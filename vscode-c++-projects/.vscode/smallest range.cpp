#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
#include<numeric>
using namespace std;

class Solution {
    public:
        vector<int> smallestRange(vector<vector<int>>& nums) {
           vector<pair<int, int>> sorted;// 数字，组别
            for(int i=0;i<nums.size();i++)
                for(int k=0;k<nums[i].size();k++)
                    sorted.push_back({nums[i][k],i});
            sort(sorted.begin(),sorted.end());//按数字大小升序排列
    
            
            int j=0,i=0;
            vector<int> count(nums.size());//用于计数每组列表包含的值的个数
            //初始化count:
            for(int k=0;k<nums.size();k++)
                count[k]=0;
            
            
            //保证每一列都有值包含进来：
            int count_sum=0;
            while(count_sum!=nums.size()){
                if(count[sorted[i].second]==0)
                    count_sum++;
                count[sorted[i++].second]++;
            }
            vector<int> res={0,INT_MAX};//初始化结果区间
            count[sorted[--i].second]--;

            for(;i<sorted.size();++i){
                count[sorted[i].second]++;
                while(count[sorted[j].second]>1){//右移左边界
                    count[sorted[j].second]--;
                    j++;
                }
                if(sorted[i].first-sorted[j].first<res[1]-res[0]){//更新区间
                    res[1]=sorted[i].first;
                    res[0]=sorted[j].first;
                }
            }
            
            //约束右边界：
            i=sorted.size()-1;
            while(count[sorted[i].second]>1){
                count[sorted[i].second]--;
                i--;
            }
             if(sorted[i].first-sorted[j].first<res[1]-res[0])//更新右边界
                res[1]=sorted[i].first;
            return res;
        }
    };
    int main()
    {
        vector<vector<int>> a ={{1,5}};//{{1,2,3},{1,2,3},{1,2,3}};//{{11,38,83,84,84,85,88,89,89,92},{28,61,89},{52,77,79,80,81},{21,25,26,26,26,27},{9,83,85,90},{84,85,87},{26,68,70,71},{36,40,41,42,45},{-34,21},{-28,-28,-23,1,13,21,28,37,37,38},{-74,1,2,22,33,35,43,45},{54,96,98,98,99},{43,54,60,65,71,75},{43,46},{50,50,58,67,69},{7,14,15},{78,80,89,89,90},{35,47,63,69,77,92,94}};// //{{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};
        Solution S;
        vector<int>res=S.smallestRange(a);
        cout<<"["<<res[0]<<","<<res[1]<<"]"<<endl;
    }