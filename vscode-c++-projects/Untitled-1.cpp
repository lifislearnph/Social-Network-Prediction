#include <iostream>
#include <vector>
#include<string>
using namespace std;
#define N 1000

class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int n=prices.size();
            vector<vector<int>> dp(n+1, vector<int>(2,0));//初始化为零
            //规定第零天不持股,现金数为零
            dp[0][1]=-prices[0];
            
           
            for(int i=1;i<=n;++i){
                //今天结束时不持股的最大获益(保持昨天 或 今天卖出)
                dp[i][0]=max(dp[i-1][0],dp[i-1][1]+prices[i-1]);
                //今天结束时持股的最大获益（昨天或之前某一天买入 或 今天买入）
                dp[i][1]=max(dp[i-1][1],-prices[i-1]);
            }
            return dp[n][0];
        }
    };
int main()
{
    Solution s;
    vector<int> a={7,1,5,3,6,4};
    cout<<s.maxProfit(a);
    return 0;
}