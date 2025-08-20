#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;

class Solution {
    public:
        int minDistance(string word1, string word2) {
            int m=word1.size(),n=word2.size();
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));//设dp[i][j]为word1前i个字符和word2前j个字符的最小编辑距离
           
            for(int i=0;i<=n;i++)
                dp[0][i]=i;//word1为空串，word2前i个字符的编辑距离为i
            for(int i=0;i<=m;i++)
                dp[i][0]=i;//word2为空串，word1前i个字符的编辑距离为i

            for(int i=1;i<=m;i++){
                for(int j=1;j<=n;j++){
                    //针对word1的四种操作：删除；插入；替换；
                    if(word1[i-1]==word2[j-1])//相同字符不需要编辑，保持     
                        dp[i][j]=dp[i-1][j-1];
                    else
                        dp[i][j]=min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1]))+1;//删除，插入，替换               
            }
        }
        return dp[m][n];//返回word1和word2的最小编辑距离
    }
};
    int main()
{
    Solution s;
    string a="horse";
    string b="ros";
    cout<<s.minDistance(a,b);
    return 0;
}