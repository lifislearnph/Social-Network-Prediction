#include <iostream>
#include <vector>
using namespace std;

long long  f(long long x){
    return x*x+1;
}
int gcd(int a, int b) {
while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}            
long long Pollard(long long n,long long x1,int &times){
    long long x=x1,x_=f(x)%n,p=gcd(abs(x-x_),n);
    times=0;//计数
    while(p==1){
        x=f(x)%n;
        x_=f(x_)%n;
        x_=f(x_)%n;
        p=gcd(abs(x-x_),n);
        times++;
    }
    if(p==n)
        return -1;
    else 
        return p;
}
int main()
{
    long long n1=262063,n2=9420457,n3=181937053;
    int times=0;
    cout<<"当n=262063时,因子 = "<<Pollard(n1,2,times)<<",迭代次数为："<<times<<endl;
    cout<<"当n=9420457,因子 = "<<Pollard(n2,2,times)<<",迭代次数为："<<times<<endl;
    cout<<"当n=181937053,因子 = "<<Pollard(n3,2,times)<<",迭代次数为："<<times<<endl;
    return 0;
}