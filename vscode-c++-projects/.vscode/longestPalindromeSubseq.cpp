#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;
#define N 1000

class Solution {
    public:
        vector<vector<int>> dp;//定义一个二维数组dp，存储子问题的解
        int execute(string &s,int i,int j) {
            int len;
            if(dp[i][j]!=-1)//如果已经计算过，直接返回
                return dp[i][j];
            else{
                if(i<j){
                    if(s[i]==s[j])//如果首尾元素相等，则回文子序列长度加2
                        dp[i][j]=execute(s,i+1,j-1)+2;//将结果存入dp中
                    else
                        dp[i][j]= max(execute(s,i+1,j),execute(s,i,j-1));//否则取两者的最大值
                }
                else if(i==j)
                    dp[i][j]= 1;//如果i=j，返回1,表示只有一个元素
                else
                    dp[i][j]=0;//如果i>j，返回0,表示没有元素
                return dp[i][j];//返回结果
            }
        }
        int longestPalindromeSubseq(string s) {

            for(int i=0;i<s.size();i++){
                vector<int> temp(s.size(),-1);//初始化为-1
                dp.push_back(temp);//将temp添加到dp中
            }
           return execute(s,0,s.size()-1);//从0到n-1进行递归
        }
};
int main()
{
    Solution s;
    string a="euazbipzncptldueeuechubrcourfpftcebikrxhybkymimgvldiwqvkszfycvqyvtiwfckexmowcxztkfyzqovbtmzpxojfofbvwnncajvrvdbvjhcrameamcfmcoxryjukhpljwszknhiypvyskmsujkuggpztltpgoczafmfelahqwjbhxtjmebnymdyxoeodqmvkxittxjnlltmoobsgzdfhismogqfpfhvqnxeuosjqqalvwhsidgiavcatjjgeztrjuoixxxoznklcxolgpuktirmduxdywwlbikaqkqajzbsjvdgjcnbtfksqhquiwnwflkldgdrqrnwmshdpykicozfowmumzeuznolmgjlltypyufpzjpuvucmesnnrwppheizkapovoloneaxpfinaontwtdqsdvzmqlgkdxlbeguackbdkftzbnynmcejtwudocemcfnuzbttcoew";
    cout<<s.longestPalindromeSubseq(a);
    return 0;
}