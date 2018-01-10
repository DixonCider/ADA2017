#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

struct set{int s[100]; int size;};

bool adjM[100][100] = {0};
int N;
int deg[100] = {0};
int Q=0, Qmax=0;

void colorSort(set* R, set* C){
	int max_no = 1;
	int kmin = Qmax - Q + 1;
	if(kmin <= 0) kmin = 1;
	int j = 0;
	vector<set>color(2);
	color[0].size = 0;
	color[1].size = 0;
	for(int i=0;i<R->size;++i){
		int p = R->s[i];
		int k = 1;
		// union
		bool isRepeat = true;
		while(isRepeat){
			isRepeat = false;
			for(int l=0;l<color[k].size;++l){
				if(adjM[p][color[k].s[l]]){
					++k;
					isRepeat = true;
					break;
				}
			}
		}
		if(k>max_no){
			max_no = k;

			set newK;
			newK.size = 0;
			color.push_back(newK);
		}
		color[k].s[color[k].size] = p;
		// cout << color[k].s[color[k].size] << endl;
		++color[k].size;
		if(k<kmin){
			R->s[j] = R->s[i];
			++j;
		}
	}
	C->s[j-1] = 0;
	// cout << kmin << max_no << color.size();
	for(int k=kmin;k<=max_no;++k){
		for(int i=0;i<color[k].size;++i){
			// cout << color[k].s[i];
			R->s[j] = color[k].s[i];
			C->s[j] = k;
			++j;
		}
	}
	// for(int i=0;i<N;++i) cout << R->s[i] << endl;
	// for(int kk=0;kk<C->size;++kk) cout << C->s[kk] << endl;
	// cout << endl;
}

void maxClq(set R, set C){
	while(R.size!=0){
		// choose a vertex p from set R (last)
		int p = R.s[R.size-1];
		// remove p from R
		--R.size;
		--C.size;
		// for(int JJ=0;JJ<C.size;++JJ) cout << C.s[JJ] << endl;
		if(Q + C.s[C.size] > Qmax){
			// add p to Q
			++Q;
			// find union of R and p.neighbor -> Randp
			bool isUnion = false;
			set Randp,Cnew;
			Randp.size = 0;
			Cnew.size = 0;
			for(int i=0;i<R.size;++i){
				// cout << adjM[p][R.s[i]] << "p " << p << "R.s " << R.s[i] << endl;
				if(adjM[p][R.s[i]]){
					isUnion = true;
					Randp.s[Randp.size] = R.s[i];
					Cnew.s[Cnew.size] = 0;
					++Randp.size;
					++Cnew.size;
				}
			}
			// backtrack if common neighbor exist
			if(isUnion){
				colorSort(&Randp,&Cnew);
				maxClq(Randp,Cnew);
			}
			// update Qmax
			Qmax = max(Q,Qmax);
			// delete p from Q
			--Q;
		}
		else return;
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int M,u,v;
	cin >> N >> M;
	for(int i=0;i<M;++i){
		cin >> u >> v;
		adjM[u][v] = true;
		adjM[v][u] = true;
		++deg[u];
		++deg[v];
	}
	// initialize set
	set R, C;
	C.size = N;
	R.size = N;
	// sort R by degree
	int cnt_sort[100] = {0};
	for(int i=0;i<N;++i) ++cnt_sort[deg[i]];
    for(int i=1;i<N;++i) cnt_sort[i]+=cnt_sort[i-1];
    for(int i=0;i<N;++i){
        R.s[N-cnt_sort[deg[i]]] = i;
        --cnt_sort[deg[i]];
    }
	
	// for(int i=0;i<N;++i) cout << R.s[i] << endl;
	// cout << R.size;
	// sort R by color, record in c
	colorSort(&R,&C);
	// driver
	maxClq(R,C);
	cout << Qmax;
}
