#include<iostream>
#include<stack>
using namespace std;

int main(){
	stack <int> bk;
	visit[100001] = {0};
	int pos = 0,N;
	bool isFound = false;
	while(!bk.empty()){
		int u = bk.top();
		bk.pop();
		++pos;
		visit[u] = true;
		bool isDead = true;
		for(vector<int>::iterator itr = Alist[u].begin(); itr!=Alist[u].end(); ++itr){
			if(visit[*itr]==false){
				bk.push(*itr);
				isDead = false;
			}else if(pos==N && *itr==0){	// if a ham is found
				isFound = true;
				break;
			}
		}
		if(isFound==true) break;
		if(isDead==true){
			visit[u] = false;
			--pos;
		}
	}
}

