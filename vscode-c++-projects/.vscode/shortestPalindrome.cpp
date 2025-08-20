#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;

class Solution {
    public:
        string shortestPalindrome(string s) {
             if(s.empty())//空串返回本身
                 return "";
            string add=get_add_reverse(s);//得到反转的加入串
            if(add.empty())//如果加入串为空，则返回本身
                return s;
            else{//如果加入串不为空，则将其反转并与原串拼接
                reverse(add.begin(),add.end());//反转得到加入串
                return add+s;
            }
        }

    string get_add_reverse(string &s) {
        //要找到包含最左边元素的最长回文子串，减去这个回文子串得到的剩余，再翻转即为所求加入串
        string rev_s=s;
        reverse(rev_s.begin(), rev_s.end());
        string new_s=s+"#"+rev_s; //防止原串和反转串混淆
        //若s有包含最左边元素的最长回文子串，找回文子串问题可转换为找s#rev_s的组合最长相同前后缀问题，可以采用KMP算法

        //KMP通过预处理子串生成一个next 数组（部分匹配表），记录子串的最长相同前后缀长度。匹配失败时，利用next数组跳过不必要的比较。
        //跳过的原理：相同前后缀，即如果ABDCABDE为子串，已经比较了ABDCABD这部分与主串相同，则可以后移三位不用比较，因为已经比较过的部分最大相同前后缀(ABC)长度为3
        vector<int> next(new_s.size(), 0);//计算KMP的next数组
        //递归计算next[i]的长度：
        for (int i = 1, j = 0; i < new_s.size();)//从长度为2的子串开始，计算前后缀
            if (new_s[i] == new_s[j]) {//相同，则最长前后缀的长度加一，同时指针整体后移
                next[i] = j + 1;
                i++;
                j++;
            } else{ //不同,则j回退到前缀的最长前缀位置，即可继续讨论新元素加入是否形成相同后缀
                if (j == 0) {
                    next[i] = 0;
                    i++;
                } else 
                    j = next[j - 1]; //回退
            }
        return s.substr(next.back());//如果存在回文子串，那么长度即为最大前后缀长度
    }

        
};

    int main()
{
    Solution s;
    string a="aacecaaa";
    cout<<s.shortestPalindrome(a);
    return 0;
}