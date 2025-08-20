//最大长方体问题 --最大子段和变形
#include<iostream>
#include<vector>
using namespace std;
 
int max1(vector<int>a, int n){//一维情况下的最大字段和
    int sum=0,b=0;
    int i;
    for(i=0;i<n;i++){
        if(b>0) 
            b+=a[i];
        else
            b=a[i];
        if(b>sum) 
            sum=b;
    }
    return sum;
}
int max2(int m,int n,vector<vector<int>>a){//二维情况下，最大矩形和
    int max=0,sum;
    int i,j,k;
	for(i=0;i<m;i++){
        vector<int> b(n,0);//将矩形的某一行初始化为0
        for(k=i;k<m;k++){//将从第i行到第m行的每一列进行相加，存入b数组中
            for(j=0;j<n;j++)
                b[j]+=a[k][j];
           sum=max1(b,n);//获得行方向的最大字段和
            if(sum>max)
                max=sum;
        }
    }
    return max;
}
 
int max3(int m,int n,int p,vector<vector<vector<int>>>a){//三维情况下，最大立方体和
    int max=0,sum;
    int i,j,k,r;
    for(i=0;i<m;i++){
        vector<vector<int>> c(n,vector<int>(p,0));//将立方体的某一面初始化为0
        for(r=i;r<m;r++){
            for(j=0;j<n;j++)
                for(k=0;k<p;k++)
                    c[j][k]+=a[r][j][k];
            sum=max2(n,p,c);
            if(sum>max)
                max=sum;
       }
    }
    return max;
}

int main(){
    int m,n,p;
    cin>>m>>n>>p;
    vector<vector<vector<int>>> r(m,vector<vector<int>>(n,vector<int>(p)));
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<p;k++){
				cin>>r[i][j][k];
			}
		}
	}
	cout<<max3(m,n,p,r)<<endl;
	return 0; 
}