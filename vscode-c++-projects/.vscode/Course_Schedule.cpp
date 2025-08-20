#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //并查集（Union-Find）数据结构
class UnionFind {
private:
	vector<int> parent;  //父节点数组
	vector<int> rank;    //秩数组
public:
    //构造并查集结构：
	UnionFind(int n) {
		parent.resize(n+1);
		rank.resize(n+1, 0);//初始秩都为0，表示以该节点为根的生成树高度为rank
		for (int i = 1; i <= n; ++i) {
			parent[i] = i;  //每个节点的父节点初始为自己
		}
	}
	//查找根节点，并进行路径压缩
	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]); //递归查找并压缩路径
		}
		return parent[x];
	}
	//合并两个集合
	void unionSets(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);

		if (rootX!=rootY) {
			//按秩合并，避免树的高度过高
			if (rank[rootX]>rank[rootY]) 
				parent[rootY]=rootX;
			else if (rank[rootX]<rank[rootY]) 
				parent[rootX]=rootY;
			else 
 				parent[rootY]=rootX;
				rank[rootX]++; //增加秩
		}
	}
};
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //深度优先+并查集
        UnionFind uf(numCourses);
        for(int i=0;i<numCourses;i++){
            int u=prerequisites[i][0];
            int v=prerequisites[i][1];
           
            if(v==uf.find(u)){//v是u的前置却在v后完成
                return false;
            }
            else if(uf.find(u)!=uf.find(v)){
                uf.unionSets(u,v);
            }

        }
        return true;
    }
    
};
int main()
{
    Solution s;
    int courseNUM=3;
    vector<vector<int>> prerequisites={{1,0},{2,0},{0,2}};
    cout<<s.canFinish(courseNUM,prerequisites);
    return 0;
}