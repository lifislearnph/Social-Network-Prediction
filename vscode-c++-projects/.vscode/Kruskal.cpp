//用kruskal算法实现最小生成树
#include <iostream>
#include <vector>
#include<string>
#include<algorithm>
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
struct ArcNode {
	int nextVex;//一条弧的尾顶点的下标
    int weight;//权重
	ArcNode() { nextVex = 0;weight=0; }
};

struct VexNode {
	int No;//此处存储的是该顶点编号（初始化为0）
	vector<ArcNode> Arcs;//这个顶点依附的所有边
	VexNode() { No = 0;}
};

class ALGraph
{
private:
	VexNode* vertices;//顶点数组
	int vexnum, arcnum;
public:	
	/*构造函数用于建立邻接表*/
	ALGraph(int &v,int &a,vector<vector<int>> &arcs)
	{
        vexnum=v;
        arcnum=a;
		vector<VexNode>vertices(vexnum + 1);
		if (vertices.empty())
			exit(-1);
		/*初始化顶点data为下标值+1(舍去下标为0的顶点)*/
		for (int i = 1; i <= vexnum; i++)
			vertices[i].No = i;
       
		/*根据给出连通边建立无向图邻接表*/
		for (int i = 0; i < arcnum; i++){
            vector<VexNode>newV(2);
            newV[0].No=arcs[i][0];
            newV[1].No=arcs[i][1];
            for(int j=0;j<2;j++){
                ArcNode newA;
                newA.weight=arcs[i][2];
                newA.nextVex=newV[~j].No;
                newV[j].Arcs.push_back(newA);
            }
		}
	}
	friend int kruskal(ALGraph& G, vector<vector<int>>& arcs,vector<vector<int>>&res);
};
    friend int kruskal(ALGraph& G,vector<vector<int>>& arcs,vector<vector<int>>& res){
        UnionFind uf(G.vexnum);
        int min_total_weight=0,usedEdge=0;;
        for(int i=0;i<G.arcnum;i++){
            int u=arcs[i][0];
            int v=arcs[i][1];
            
             //如果u和v不在同一个集合中，加入这条边
            if(uf.find(u)!=uf.find(v)){
                uf.unionSets(u, v);
                usedEdge++;
                min_total_weight+=arcs[i][2];
                res.push_back(arcs[i]);
	            //如果已经选了n-1条边，生成树完成
	            if (usedEdge ==G.vexnum- 1) {
		            break;
	            }
            }   
        }
        return min_total_weight;
    }
    static bool cmp_arcs(vector<int> &a1,vector<int>& a2){
        return a1[2]<a2[2];//按权值排列
    } 
    void exe(){
        int v,a;
        vector<vector<int>> arcs,res;
        cout<<"请输入图的顶点数，边数:"<<endl;
		cin >> v;
		cin >> a;
        cout<<"请输入每条边的起点、终点和边的权值:"<<endl;
        int src,des,weight;
        for (int i = 0; i < a; i++){
            cin>>src>>des>>weight;
            arcs.push_back({src,des,weight});
        }
        sort(arcs.begin(),arcs.end(),cmp_arcs);//按权值升序排列
        ALGraph G(v,a,arcs);

       int min_weight= kruskal(G,arcs,res);
       cout<<"最小生成树边的权值之和为："<<min_weight<<endl;
       cout<<"组成最小生成树的顶点和边如下："<<endl;
       cout<<"起点 终点 边权值"<<endl;
       for(int i=0;i<res.size();i++){
            cout<<res[i][0]<<"     "<<res[i][1]<<"     "<<res[i][2]<<endl;
       } 
    }
    
};
int main()
{
    Solution s;
    s.exe();
    return 0;
}