#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;
class Solution {
public:
    int jump(vector<int>& nums) {
        int cur=0,cover=nums[0],n=nums.size();
        int count=0;
        while(cur+nums[cur]<n-1){//当能碰到最后一个点时跳出循环
            int nextpos=0,maxlen=0;
            for(int i=1;i<=cover&&cur+i<n-1;i++){//找到下一个起跳点
                if(cur+i+nums[cur+i]>=maxlen){
                    maxlen=cur+i+nums[cur+i];
                    nextpos=cur+i;
                }
            }
            cur=nextpos;
            nextpos=0;
            maxlen=0;
            cover=nums[cur];
            count++;
        }
        return count;
    }
};
int main()
{
    Solution s;
    vector<int> a={2,3,1,1,4};
    cout<<s.jump(a);
    return 0;
}