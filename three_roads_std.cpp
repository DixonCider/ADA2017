#include <iostream>
#include <vector>
#include <list>
#include <string.h>
#include <stack>
using namespace std;

vector< vector<int> >Alist(100000);
int visited[100000] = {0};
stack<int>dfs;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		unsigned long long TOTAL_ROAD = 0;
		int N,M,U,V;
		// read data
		cin >> N >> M;
		// reset visited array
		memset(visited,0,sizeof(int)*N);
		while(M--){
			cin >> U >> V;
			--U;--V;
			Alist[U].push_back(V);
			Alist[V].push_back(U);
		}
		// traverse
		for(int i=0;i<N;++i){
			if(visited[i]==0){
				unsigned long long even = 0,edge = 0,odd=0;
				bool isOddCycle = false;	// if odd cycle exist -> true
				// push in source node
				dfs.push(i);
				visited[i] = 1;
				while(!dfs.empty()){
					int u = dfs.top();
					dfs.pop();
					if(visited[u]==1) ++even;
					else ++odd;
					for(vector<int>::iterator itr = Alist[u].begin(); itr!=Alist[u].end(); ++itr){
						++edge;
						if(visited[*itr]==0){
							dfs.push(*itr);
							visited[*itr] = -visited[u];
						}
						// determine odd cycle
						else if(visited[*itr]==visited[u]) isOddCycle = true;
					}
				}
				if(isOddCycle) TOTAL_ROAD += ((even+odd)*(even+odd-1)-edge)/2;
				else TOTAL_ROAD += even*odd-edge/2;
				// cout << " OddCycle->" << isOddCycle << " pnt " << pnt << " edge " << edge << endl;
			}
		}
		cout << TOTAL_ROAD << "\n";
		// reset adjacency list
		for(int i=0;i<N;i++) Alist[i].clear();
	}
}
