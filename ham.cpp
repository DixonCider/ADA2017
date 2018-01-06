#include<iostream>
#include<vector>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<cstdio>
using namespace std;

int sol[100000] = {0};
int degI[100000] = {0};
int degO[100000] = {0};
bool visit[100000] = {0};
bool skip[100000] = {0};
vector< vector<int> >Alist(100000);
int N;
bool myfunction (int i,int j) { 
	// return min(degI[i],degO[i])>min(degI[j],degO[j]);
	return degI[i]-degO[i]>degI[j]-degO[j];
	// return degO[i]<degO[j];
	//return degI[i]>degI[j];
}
void bk(int n){
	int now = sol[n-1];
	vector<int>::iterator itr;
	if(n==N){
		for(itr = Alist[now].begin(); itr!=Alist[now].end(); ++itr){
			if(*itr == sol[0]){
				int head;
				for(int i=0; i<N; ++i){
					if(sol[i]==0) head = i;
				}
				int r = head;
				for(int i=0; i<N; ++i){
					cout << sol[r]+1 << " ";
					++r;
					r%=N;
				}
				cout << sol[head]+1;
				exit(0);
			}
		}
		return;
	}
	
	for(itr = Alist[now].begin(); itr!=Alist[now].end(); ++itr){
		if(degO[now]!=1 && skip[*itr]) continue;
		if(!visit[*itr]){
			visit[*itr] = true;
			sol[n] = *itr;
			bk(n+1);
			visit[*itr] = false;
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	// srand(time(NULL));
	// srand(1126);
	int M,u,v;
	vector<int>::iterator itr;
	cin >> N >> M;
	while(M--){
		cin >> u >> v;
		--u;
		--v;
		Alist[u].push_back(v);
		++degO[u];
		++degI[v];
	}
	for(int i=0;i<N;++i){
		for(itr=Alist[i].begin(); itr!=Alist[i].end(); ++itr){
			if(degI[*itr]==1){
				int tmp = *itr;
				Alist[i].clear();
				Alist[i].push_back(tmp);
				degO[i] = 1;
				break;
			}
		}
	}
	for(int i=0;i<N;++i){
		if(degI[i]==0 || degO[i]==0){
			cout << -1;
			exit(0);
		}
		if(degO[i]==1){
			skip[Alist[i][0]] = true;
		}
		// random_shuffle(Alist[i].begin(),Alist[i].end());
	}
	queue<int>bfs;
	bool enc[100000] = {0};
	bfs.push(0);
	enc[0] = true;
	
	while(!bfs.empty()){
		int k = bfs.front();
		bfs.pop();
		for(itr=Alist[k].begin(); itr!=Alist[k].end(); ++itr){
			if(!enc[*itr]){
				bfs.push(*itr);
				enc[*itr] = true;
			}
		}
	}
	int init = 0;
	for(int i=0;i<N;++i){
		if(!enc[i]){
			cout << -1;
			exit(0);
		}
		// if(min(degI[i],degO[i])>min(degI[init],degO[init])) init = i;
		if(degI[i]-degO[i]>degI[init]-degO[init]) init = i;
		sort(Alist[i].begin(),Alist[i].end(),myfunction);
	}
	// int init = rand()%N;
	// int init = 2%N;
	visit[init] = true;
	sol[0] = init;
	bk(1);
	cout << -1;
}
