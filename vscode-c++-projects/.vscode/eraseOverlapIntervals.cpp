#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;


class Solution {
    public:
        int eraseOverlapIntervals(vector<vector<int>>& intervals) {
            //排序算法
            // for(int i=0;i<intervals.size()-1;i++)
            //     for(int j=0;j<intervals.size()-i-1;j++)
            //         if(intervals[j][1]>intervals[j+1][1])
            //             swap(intervals[j],intervals[j+1]);
            MergeSort(intervals,0,intervals.size()-1);
            int j=0,addnum=1;
            for(int i=1;i<intervals.size();i++){
                if(intervals[i][0]>=intervals[j][1]){
                    addnum++;
                    j=i;
                }
            }
            return intervals.size()-addnum;
        }
        void MergeSort(vector<vector<int>> &a, int left, int right) {
        if (left < right) {
            int i = (left+right) / 2;
            vector<int> b;
            MergeSort(a, left, i);
            MergeSort(a, i + 1, right);
            Merge(a,left, i, right);
        }
    }
    
    void Merge(vector<vector<int>> &src, int left, int mid, int right) {
        vector<vector<int>> tmp;//建立临时数组
    
        //建立指针，分别指向两部分的开头
       int fst = left;
       int snd = mid+1;//后半部分开头从mid后一位开始
    
        //比较，将较小元素加入新数组
        int i = 0;
       while( fst <= mid && snd <= right) {
            if (src[fst][1] < src[snd][1]) {
                tmp.push_back(src[fst]);
                fst++;
            }
            else {
                tmp.push_back(src[snd]);
                snd++;
            }
       }
    
        //将剩下的元素直接加入新数组中
        while (fst <= mid) {
            tmp.push_back(src[fst]);
            ++fst;
        }
        while (snd <= right) {
            tmp.push_back(src[snd]);
            ++snd;
        }
    
        // 将临时数组的内容复制回原数组
        for (int i = 0; i < tmp.size(); i++) {
            src[left + i] = tmp[i];
        }
    }
    };

    int main()
    {
        vector<vector<int>> a={{1,2},{2,3},{3,4},{1,3}};
        Solution S;
        cout<<S.eraseOverlapIntervals(a);
    }