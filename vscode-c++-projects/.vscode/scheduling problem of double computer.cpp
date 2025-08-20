#include<iostream>
#include<vector>
using namespace std;
//独立任务最优调度问题-0-1背包问题思路

/*第k个任务在A完成或不在A完成；
F(k,x)示完成第k个任务时A耗费的时间为x的情况下，B所花费的最短时间；
则第k个任务在A上完成时，F(k,x)=F(k-1,x-a[k])；
第k个任务不在A上完成时，F(k,x)=F(k-1,x)+b[k]；
所以F(k,x) = min{F(k-1,x-a[k]),F(k-1,x)+b[k])}；
最终最优解为max(F(n,x),x)*/

int get_result(vector<int>a ,vector<int>b, int n){
	if(n==1)//只有一个任务的情况
        return min(a[0], b[0]);

    /*构造F(n,x)函数*/
	int sum=0,result=INT_MAX;//result初始化为无穷大
	for(int i = 0;i < n;i++)
        sum += a[i];
    vector<vector<int>> F(n, vector<int>(sum+1, 0));//初始化f的各个元素为0  
	
	//初始化完成第一个任务时的情况
	for(int x = 0;x < a[0];x++)
        F[0][x] = b[0];//第一个任务在B上完成时，B的时间为b[0]
	F[0][a[0]] = 0; //第一个任务在A上完成时，B的时间为0
	
	//进入动态规划的循环
    sum=a[0];//第一个任务完成后，A的时间为a[0]，讨论x的范围为[0,a[0]]时的最短时间
    for(int k = 1;k < n;k++){
        sum += a[k];//更新sum的值
        for(int x = 0;x <= sum;x++){
            if(x-a[k] < 0)//处理x<0时设为无穷大的情况 
                F[k][x] = F[k-1][x]+b[k];
            else
                F[k][x] = min(F[k-1][x-a[k]], F[k-1][x]+b[k]);
            
            if(k == n-1){//处理最后的结果
                int tmp=max(x, F[k][x]);
                if(tmp<result)
                    result =tmp;
            }
            
        }
    }
	return result; 
} 

int main()
{
	int n;
    vector<int> a, b;
    cin >> n;
    a.resize(n);
    b.resize(n);
    for(int i = 0; i < n; i++)  cin >> a[i];
    for(int i = 0; i < n; i++)   cin >> b[i];
    cout<<get_result(a,b,n)<<endl;
    return 0 ;
}
