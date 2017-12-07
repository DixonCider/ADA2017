#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <string.h>
using namespace std;

bool visited[100000] = {0};	// 1 odd, 2 even
bool cl[100000] = {0};
vector< list<int> >Alist(100000); 
stack<int>dfs;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		memset(visited,0,sizeof visited);
		unsigned long long TOTAL_ROAD = 0;
		int N,M,u,v;
		cin >> N >> M;
		while(M--){
			cin >> u >> v;
			--u;--v;
			Alist[u].push_back(v);
			Alist[v].push_back(u);
		}
		// traverse
		for(int i=0;i<N;++i){
			if(visited[i]==0){
				unsigned long long pnt = 0,edge = 0;
				bool isAll = false;
				dfs.push(i);
				cl[i] = 0;
				while(!dfs.empty()){
					int u = dfs.top();
					dfs.pop();
					if(!visited[u]){
						visited[u] = true;
						++pnt;
						for(list<int>::iterator itr = Alist[u].begin(); itr!=Alist[u].end(); ++itr){
							if(visited[*itr]==0){
								++edge;
								dfs.push(*itr);
								cl[*itr] = !cl[u];
							}
							else if(isAll==false && cl[*itr]==cl[u]) isAll = true;
						}
					}
				}
				if(isAll) TOTAL_ROAD += pnt*(pnt-1)/2-edge;
				else TOTAL_ROAD += (pnt/2)*(pnt/2+pnt%2)-edge;
				//cout << " isAll " << isAll << " pnt " << pnt << " edge " << edge << endl;
			}
		}
		cout << TOTAL_ROAD << "\n";
		for(int i=0;i<N;i++) Alist[i].clear();
	}
}
