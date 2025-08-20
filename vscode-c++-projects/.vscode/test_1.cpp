#include <iostream>
#include <vector>
#include<string>
using namespace std;

class Solution {
    vector<vector<int>> res;
    public:
        vector<vector<int>> permute(vector<int>& nums) {
            
        }
        void exe(vector<int>& output,vector<vector<int>> res,int first ,int len){
            if(first==len)
                res.push_back(output);//当“填满”一列组合后，就放入结果表中
            for(int i=first;i<len;i++){
                swap(output[i],output[first]);//每次交换一次首指针指到位置
                exe(output,res,first+1,len-1);
                swap(output[i],output[first]);//撤销操作
            }

        }
};

int main()
{
    Solution s;
    vector<int>a={1,2,3,4,5};
    cout<<s.maxProfit(a);
    return 0;
}