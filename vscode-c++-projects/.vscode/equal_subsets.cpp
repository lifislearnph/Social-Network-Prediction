#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;


class Solution {
public:
    bool canPartition(vector<int>& nums) {
        if(nums.size() < 2)//元素个数小于2，不能分成两部分
            return false;
        else{
            int sum=0;
            for(int i=0;i<nums.size();++i)
                sum+=nums[i];//计算总和
            if(sum&1)//总和为奇数，不能分成相等两部分
                return false;
            else{
                int target=sum/2;//目标值为总和的一半
                int maxNum = *max_element(nums.begin(), nums.end());//找出数组中的最大值
                if(maxNum>target)//由于最大值为不可切分整数，所以如果最大值大于目标值，说明不可能分成两部分
                    return false;
                    
                //建立n行target+1列二维数组dp，n表示元素个数，target+1是因为目标值不会为0，从一开始，所以要加1
                //dp的值代表“在0-i个元素中，能否找到一个子集，使得它的和为target”这个命题是否为真
                vector<vector<bool>> dp(nums.size(),vector<bool>(target+1,false));
               
                for(int i=0;i<nums.size();++i)
                    dp[i][0]=true;//第0列都为true，和为0表示一个元素都不用

                dp[0][nums[0]]=true;//当讨论第一个元素时，它能使目标值为nums[0]时为true;

                //从第二个元素开始讨论 
                for(int i=1;i<nums.size();++i)
                    for(int j=1;j<=target;++j){//从1开始，将部分目标值每次加一，直到加到题目的目标值为止
                        if(nums[i]<=j)//元素小于等于目标值，能加入序列
                            dp[i][j]=dp[i-1][j]||dp[i-1][j-nums[i]];//选择加入或不加入
                            //如果选择加入，目标值减去当前元素的值，判断剩余的目标值是否能在前i-1个元素中找到,
                            //只要两项中有一项为真，这就意味着在当前元素组合中能达到当前目标值
                        else//元素大于目标值，不能加入序列
                            dp[i][j]=dp[i-1][j];//保持不变
                    }
                //最后一行的最后一列即为结果
                return dp[nums.size()-1][target];
                    
            }
        }
    }
};

int main()
{
    Solution s;
    vector<int> a={2,4,6};
    cout<<s.canPartition(a);
    return 0;
}