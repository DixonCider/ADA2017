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
	if(MAX_SIZE==2){
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
	if(MAX_SIZE==3){
		
	}
	cout << MAX_SIZE << endl;
}
