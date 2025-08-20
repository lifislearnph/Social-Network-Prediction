#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;
#define N 1000

class Solution {
    public:
        string longestPalindrome(string s) {
            vector<vector<bool>> P(s.size(),vector<bool>(s.size(), false));//初始化为false
            int maxlen=1;
            int max_start=0;
    
            //边界条件：
            for(int i=0;i<s.size();++i){
                P[i][i]=true;//对角线为true
                if(i<s.size()-1 && s[i]==s[i+1])//相邻的两个元素相等
                 {  
                     P[i][i+1]=true;
                    maxlen=2;
                    max_start=i;
                 }
            }
            //动态规划过程：
            if(s.size()>=3)//长度大于3才进入
            for(int r=2;r<s.size();r++)
            for(int i=0;i<s.size()-r;i++){
                     //for(int j=i+2;j<s.size();j++)
                        if(P[i+1][r+i-1]&&s[i]==s[r+i]){//如果i+1到j-1的子串是回文串，且i和j的元素相等
                             P[i][r+i]=true;
                            if(r+1>maxlen){//更新最大子串
                              maxlen=r+1;
                              max_start=i;
                            }
                        }
                
            }
            
            return s.substr(max_start,maxlen);//返回从max_start开始的长度为maxlen的子串
        }
};
int main()
{
    Solution s;
    string a={31,26,33,21,40};
    cout<<s.longestPalindrome(a);
    return 0;
}