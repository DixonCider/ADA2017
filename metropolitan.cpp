#include <iostream>
#include <list>
#include <vector>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,M,u,v,MAX_SIZE=1,MAX_CARD=0;
	vector< list<int> >Alist(200000);
	int card[200000] = {0};
	cin >> N >> M;
	// check N = 2
	if(M>0) MAX_SIZE = 2;
	while(M--){
		cin >> u >> v;
		Alist[u].push_back(v);
		Alist[v].push_back(u);
		++card[u]; ++card[v];
	}
	int cnt_sort[200000] = {0};
	for(int i=0;i<N;++i){
		++cnt_sort[card[i]];
		MAX_CARD = max(MAX_CARD,card[i]);
	}
	int sorted[200000] = {0};
	int sorted1[200000] = {0};
	for(int i=1;i<=MAX_CARD;++i) cnt_sort[i]+=cnt_sort[i-1];
	for(int i=0;i<N;++i){
		sorted[N-1-(cnt_sort[card[i]]-1)] = i;
		--cnt_sort[card[i]];
	}
	// check N = 3
	if(MAX_SIZE==2 && MAX_CARD>=2){
		for(int ii=0;ii<N;++ii){
			int i = sorted[ii];
			//cout << "card" << card[i] << endl;
			if(card[i]>=2){
				bool bitmask[200000] = {0};
				list<int>::iterator itr,itr1;
				for(itr = Alist[i].begin(); itr!=Alist[i].end(); ++itr){
					bitmask[*itr] = true;
				}
				for(itr = Alist[i].begin(); itr!=Alist[i].end(); ++itr){
					if(card[*itr]>=2){
						for(itr1 = Alist[*itr].begin(); itr1!=Alist[*itr].end(); ++itr1){
							if(bitmask[*itr1]==true && *itr1!=i){
								MAX_SIZE = 3;
								break;
							}
						}
					}
					if(MAX_SIZE==3) break;
				}
			}
			if(MAX_SIZE==3) break;
		}
	}
	// check N = 4
	if(MAX_SIZE==3 && MAX_CARD>=3){
		for(int node=0;node<N;++node){
			int i = sorted[node];
			if(card[i]>=3){
				bool neighbor[200000] = {0};	// neighbor with p1
				list<int>::iterator itr, itr1, itr2;
				for(itr = Alist[i].begin(); itr!=Alist[i].end(); ++itr) neighbor[*itr] = true;
				// find k3 in neighbor
				for(int j=0; j<200000; ++j){
					if(neighbor[j]==false) continue;
					bool neighbor_1[200000] = {0};	// neighbor with p1(i) & p2(j)
					for(itr1 = Alist[j].begin(); itr1!=Alist[j].end(); ++itr1){
						if(neighbor[*itr1]==true) neighbor_1[*itr1] = true;
					}
					// itr1 is neighbor of p2
					for(itr1 = Alist[j].begin(); itr1!=Alist[j].end(); ++itr1){
						if(neighbor_1[*itr1]==false) continue;	// p3(*itr1)
						// itr2 is neighbor of p3
						for(itr2 = Alist[*itr1].begin(); itr2!=Alist[*itr1].end(); ++itr2){
							if(neighbor_1[*itr2]==true){
								MAX_SIZE = 4;
								break;
							}
						}
						if(MAX_SIZE==4) break;
					}
					if(MAX_SIZE==4) break;
				}
			}
			if(MAX_SIZE==4) break;
		}
	}
	cout << MAX_SIZE << endl;
}
