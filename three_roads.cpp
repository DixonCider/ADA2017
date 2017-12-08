#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <string.h>
using namespace std;

bool visited[100000] = {0};
bool cl[100000] = {0};	// color array
vector< list<int> >Alist(100000);
stack<int>dfs;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		// reset visited array
		memset(visited,0,sizeof visited);
		unsigned long long TOTAL_ROAD = 0;
		int N,M,u,v;
		// read data
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
				bool isOddCycle = false;	// if odd cycle exist -> true
				// push in source node
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
							// determine odd cycle
							else if(cl[*itr]==cl[u]) isOddCycle = true;
						}
					}
				}
				if(isOddCycle) TOTAL_ROAD += pnt*(pnt-1)/2-edge;
				else TOTAL_ROAD += (pnt/2)*(pnt/2+pnt%2)-edge;
				cout << " OddCycle->" << isOddCycle << " pnt " << pnt << " edge " << edge << endl;
			}
		}
		cout << TOTAL_ROAD << "\n";
		// reset adjacency list
		for(int i=0;i<N;i++) Alist[i].clear();
	}
}
