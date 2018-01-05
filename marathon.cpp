#include <iostream>
#include <vector>
#include <string.h>
#include <stack>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N,M,tmp1,tmp2,MIN=-1;
	int c[40] = {0};
	bool visited[40] = {0};
	cin >> N >> M;
	vector< vector<int> >Alist(N);
	for(int i=0;i<N;++i) cin >> c[i];
	for(int i=0;i<M;++i){
		cin >> tmp1 >> tmp2;
		--tmp1;
		--tmp2;
		Alist[tmp2].push_back(tmp1);
		Alist[tmp1].push_back(tmp2);
	}
	stack <int> dfs;
	dfs.push(0);
	while(!dfs.empty()){
		int v = dfs.top();
		dfs.pop();
		for(vector<int>::iterator itr = Alist[v].begin(); itr!=Alist[v].end(); ++itr){
			if(visited[*itr]==false){
				dfs.push(*itr);
				visited[*itr] = true;
			}
		}

	}
}
