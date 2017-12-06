#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <list>
using namespace std;

int ary[100000] = {0};	// 1 odd, 2 even
int even=0,odd=0,edge=0;
vector< list<int> >Alist(100000); 

bool DFSvisit(int u, int color){
	bool isReturn = false;
	int nextColor;
	if(color==1){
		++odd;
		nextColor = 2;
	}
	else{
		++even;
		nextColor = 1;
	}
	ary[u] = color;
	list<int>::iterator itr = Alist[u].begin();

	// true -> all, false -> no odd-even
	while(itr!=Alist[u].end()){
		++edge;
		if(ary[*itr]==0 && DFSvisit(*itr,nextColor)==true) isReturn = true;
		else if(ary[*itr]==color) isReturn = true;
		++itr;
	}
	return isReturn;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		memset(ary,0,sizeof(ary));
		int N,M,TOTAL_ROAD=0,u,v;
		cin >> N >> M;
		while(M--){
			cin >> u >> v;
			--u;--v;
			Alist[u].push_back(v);
			Alist[v].push_back(u);
		}
		// traverse
		for(int i=0;i<N;++i){
			even = 0; odd = 0; edge = 0;
			if(ary[i]==0){
				// all connected
				if(DFSvisit(i,1)==true) TOTAL_ROAD += ((odd+even)*(odd+even-1)-edge)/2;
				// seperated
				else TOTAL_ROAD += odd*even-edge/2;
			}
		}
		cout << TOTAL_ROAD << "\n";
		for(int i=0;i<N;i++) Alist[i].clear();
	}
}
