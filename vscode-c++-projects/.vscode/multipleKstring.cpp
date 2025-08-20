#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;
class Solution {
public:
    int longestSubstring(string s, int k) {
        if(s.empty()||s.length()<k)
            return 0;
        int alphabet[26] = { 0 }, check[26] = { 0 };
        for (int i = 0; i < s.length(); ++i) {//便利得到数量
            ++alphabet[s[i] - 'a'];
        }
        for (int i = 0; i < 26; ++i) {
            if (alphabet[i] < k&& alphabet[i]!=0){
                alphabet[i] = 0;//标记在整个数列中数量就不够的数组
            }
        }
        int maxlen = 0, start = 0, tmp=0;
        bool forbid=false;
        int i = 0;
        for (; i < s.length(); ++i) {
            tmp=maxlen;//用于存放上一个最大值，方便倒退
            if(alphabet[s[i]-'a']==0){
                forbid=true;
                maxlen=maxlen>i-start?maxlen:i-start;
                int ttmp=longestSubstring(s.substr(start,i-start),k);//检查之前的最大串是否正确
                maxlen=tmp>ttmp?tmp:ttmp;//把子串的值与上一个maxlen值比较，选较大的一个为maxlen
                start=i+1;//更新下一段起点
            }
        }
        if(forbid==false)return s.length();//如果字符串每个字符都通过，则直接返回字符串长
        //对最后一位子串进行检查
        tmp=maxlen;
        maxlen=maxlen>i-start?maxlen:i-start;
        int ttmp=longestSubstring(s.substr(start,i-start),k);//检查之前的最大串是否正确
        maxlen=tmp>ttmp?tmp:ttmp;//把子串的值与上一个maxlen值比较，选较大的一个为maxlen

        if(maxlen<k)return 0;
        return maxlen;
    }
};
int main()
{
    Solution s;
    string a="bbaaacddcaabdbd";
    cout<<s.longestSubstring(a,3);
    return 0;
}