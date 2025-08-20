#include <iostream>
#include <vector>
#include<string>
using namespace std;


class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            /*该问题可以分解为两个最佳卖出时机问题，假设第一次交易最迟在第k天卖出(2<=k<=n)，
            则第二次交易在第k+1天到第n天之间进行。
            而找出最佳交易时间为了优化时间复杂度，使用贪心算法*/
            int n = prices.size();
           
                //第一次交易的收益表：
                //dp1[i]:前i天完成一次交易的最大利润，从前往后更新
                vector<int> dp1(n, 0);
                int min_price = prices[0];//买入时的最小价格
                for (int i = 1; i < n; ++i) {//i从1开始，默认只有最开始1天的情况下无法交易dp[0]=0
                    dp1[i] = max(dp1[i - 1], prices[i] - min_price);//当天保持或买入
                    min_price = min(min_price, prices[i]);
                }

                //第二次交易的收益表：
                //dp2[i]:后i天完成一次交易的最大利润，从后往前跟新
                vector<int> dp2(n, 0);
                int max_price = prices[n - 1];//卖出时的最大价格
                for (int i = n - 2; i >= 0; --i) {//i从n-2开始，默认只有最后1天的情况下无法交易dp[n-1]=0
                    dp2[i] = max(dp2[i + 1], max_price - prices[i]);//当天保持或卖出
                    max_price = max(max_price, prices[i]);
                }
                //计算最大利润
                int maxprofit=0;
                for(int i=0;i<n;i++){
                    maxprofit=max(maxprofit,dp1[i]+dp2[i]);//前i天和后i天的最大利润之和
                }
            
            return maxprofit;
        }
    };
int main()
{
    Solution s;
    vector<int>a={1,2,3,4,5};
    cout<<s.maxProfit(a);
    return 0;
}