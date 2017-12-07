#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <list>
using namespace std;

bool ary[100000] = {0};	// 1 odd, 2 even
bool cl[100000] = {0};
unsigned long long pnt=0,edge=0;
vector< list<int> >Alist(100000); 

bool DFSvisit(int u, bool color){
	bool rn = false;
	++pnt;
	ary[u] = 1;
	cl[u] = color;
	list<int>::iterator itr = Alist[u].begin();
	// true -> all, false -> no odd-even
	// for(list<int>::iterator itr = Alist[u].begin(); itr!=Alist[u].end(); ++itr){
	while(itr!=Alist[u].end()){
		++edge;
		if(ary[*itr]==0){
			if(DFSvisit(*itr,!color)==true) rn = true;
		}
		else if(cl[*itr]==color) rn  = true;
		++itr;
	}
	return rn;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		memset(ary,0,sizeof ary);
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
			if(ary[i]==0){
				pnt = 0; edge = 0;
				// all connected
				if(DFSvisit(i,0)==true)	TOTAL_ROAD += (pnt*(pnt-1)-edge)/2;
				// seperated
				else TOTAL_ROAD += (pnt/2)*(pnt/2+pnt%2)-edge/2;
			}
		}
		cout << TOTAL_ROAD << "\n";
		for(int i=0;i<N;i++) Alist[i].clear();
	}
}

