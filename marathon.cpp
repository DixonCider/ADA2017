#include <iostream>
#include <vector>
#include <string.h>
#include <climits>
using namespace std;

bool lastStop[40] = {0};
vector< vector<int> >Alist(40);
int GLOBALMIN = INT_MAX, dest;
int c[40] = {0};

void tsp(int here, int cost, vector<bool> &past){
	vector<bool> visit = past;
	vector<int>::iterator itr;
	for(itr=Alist[here].begin();itr!=Alist[here].end();++itr){
		if(!past[*itr]){
			// visit now
			visit[*itr] = true;
			cost += c[*itr];
		}
	}
	if(cost>GLOBALMIN) return;
	if(dest == here){
		GLOBALMIN = cost;
		return;
	}
	if(lastStop[here]){
		// go to last stop!!!
		tsp(dest,cost,visit);
		return;
	}
	for(itr=Alist[here].begin();itr!=Alist[here].end();++itr){
		if(!past[*itr]) tsp(*itr,cost,visit);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	vector<bool> visit(40,0);
	int N,M,u,v;
	cin >> N >> M;
	dest = N-1;
	for(int i=0;i<N;++i) cin >> c[i];
	for(int i=0;i<M;++i){
		cin >> u >> v;
		--u;
		--v;
		Alist[u].push_back(v);
		Alist[v].push_back(u);
		if(u==dest) lastStop[v] = true;
		else if(v==dest) lastStop[u] = true;
	}
	visit[0] = true;
	tsp(0,c[0],visit);
	cout << GLOBALMIN;
}
