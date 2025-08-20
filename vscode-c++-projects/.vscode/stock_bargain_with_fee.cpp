#include <iostream>
#include <vector>
#include<string>
using namespace std;


class Solution {
    public:
        int maxProfit(int k,vector<int>& prices) {
            vector<vector<int>>hold(prices.size()+1,vector<int>(k+1));//hold[i][j]表示在第i天的时候，进行了j笔交易时持有股票的最大利润
            vector<vector<int>>unhold(prices.size()+1,vector<int>(k+1));//unhold[i][j]表示在第i天的时候，进行了j笔交易时不持有股票的最大利润
            
            //设第零天时候没有股票，利润为0
            unhold[0][0]=0;
            hold[0][0]=-prices[0];//初始化：第一天就买入股票，利润为负数，第零天第一笔交易尚未开始
            //对于于第零天的其他交易，由于不可能完成，所以都设为非法状态
            for (int i = 1; i <= k; ++i) {
                hold[0][i] = INT_MIN / 2;
                unhold[0][i] = INT_MIN / 2;
            }
    

               
            for(int i=1;i<=prices.size();i++){
                //在一笔交易都没有完成时，决定在第i天不买入股票，或买入股票，进行初始化
                hold[i][0] = max(hold[i - 1][0], unhold[i - 1][0] - prices[i]);
                for(int j=1;j<=k;j++){
                    //第i天售出股票，则利润为前一天持有股票的利润加上今天的价格，并且由于进行了一次交易，这次unhold的j要比hold的j多1
                    unhold[i][j]=max(unhold[i-1][j],hold[i-1][j-1]+prices[i-1]);
                    //第i天买入股票，则利润为前一天不持有股票的利润减去今天的价格，由于新开始的这次交易没有完成，所以j不变
                    hold[i][j]=max(hold[i-1][j],unhold[i-1][j]-prices[i-1]);
                }
            }
            int max_choice=0;
            for(int j=1;j<=k;j++){
                max_choice=max(max_choice,unhold[prices.size()][j]);//在第n天完成j笔交易可获得最大利润(k笔交易不一定每一笔都完成)
            }
            return max_choice;
            
        }
    };
int main()
{
    Solution s;
    vector<int>a={3,2,6,5,0,3};
    cout<<s.maxProfit(4,a);
    return 0;
}