#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;


class Solution {
public:
    int numTrees(int n){
        vector<int> dp(n+1,0);//dp[i]表示i个节点的二叉搜索树的数量
        dp[0]=1;//空树
        dp[1]=1;//只有一个节点的树
        for(int i=2;i<=n;++i){
            for(int j=1;j<=i;++j){
                dp[i]+=dp[j-1]*dp[i-j];//左子树和右子树的组合
            }
        }
        return dp[n];
    }
};

int main()
{
    Solution s;
    int a=9;
    cout<<s.numTrees(a);
    return 0;
}