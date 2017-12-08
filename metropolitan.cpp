#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,M,u,v;
	vector< list<int> >Alist(200000);
	int card[200000] = {0};
	cin >> N >> M;
	while(M--){
		cin >> u >> v;
		Alist[u].push_back(v);
		Alist[v].push_back(u);
		// count cardinality
		++card[u]; ++card[v];
	}
	for(int i=0;i<N;i++){
		
	}
}
