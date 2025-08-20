#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
#include<numeric>
using namespace std;

class Solution {
    public:
        static bool comparelastDay(const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        }
        static bool compareduration(const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        }
        int scheduleCourse(vector<vector<int>>& courses) {
            //从最迟结束时间倒序排列？
            sort(courses.begin(),courses.end(),comparelastDay);//结束日期最早的放最前，先进行一次排列
    
            int totaldays=0,cnum=0;
            for(int i=0;i<courses.size();i++){
                totaldays+=courses[i][0];
                if(courses[i][1]>=totaldays)
                    cnum++;
            }
            //再按最短持续时间暴力后推
            sort(courses.begin(),courses.end(),compareduration);//按最短持续时间升序排列
            int cnum2=0;
            totaldays=0;
            for(int i=0;i<courses.size();i++){
                totaldays+=courses[i][0];
                if(totaldays<=courses[i][1])//能加入
                    cnum2++;
                else//不能加入则不计入总天数
                    totaldays-=courses[i][0];
                    
            }
    
            return max(cnum,cnum2);
        }
    };

    int main()
    {
        vector<vector<int>> a ={{5,15},{3,19},{6,7},{2,10},{5,16},{8,14},{10,11},{2,19}};//{{1,2,3},{1,2,3},{1,2,3}};//{{11,38,83,84,84,85,88,89,89,92},{28,61,89},{52,77,79,80,81},{21,25,26,26,26,27},{9,83,85,90},{84,85,87},{26,68,70,71},{36,40,41,42,45},{-34,21},{-28,-28,-23,1,13,21,28,37,37,38},{-74,1,2,22,33,35,43,45},{54,96,98,98,99},{43,54,60,65,71,75},{43,46},{50,50,58,67,69},{7,14,15},{78,80,89,89,90},{35,47,63,69,77,92,94}};// //{{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};
        Solution S;
        int res =S.scheduleCourse(a);
        cout<<"res"<<res<<endl;
    }