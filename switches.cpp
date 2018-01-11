#include <iostream>
#include <cstdlib>
#include <bitset>
#include <ctime>
using namespace std;

char box[3][3002];
bitset<26> letter;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	srand(time(NULL));
	int T;
	char buf;
	cin >> T;
	while(T--){
		letter.reset();
		int M;
		int Tpass=0,bestImp,bestBit;
		bool isPass = false;
		unsigned long init = 0, ansDig = 0;
		cin >> M;
		for(int i=0;i<3;++i) cin >> box[i];
		for(int i=0;i<3*M+1;++i){
			if(i%3==0) continue;
			for(int j=0;j<3;++j){
				buf = box[j][i];
				//int u = (int) box[j][i];
				if(buf<=90){
					//u-=65;
					letter.set((int)buf-65);
				}
				else if(buf>=97){
				   	//u-=97;
					letter.set((int)buf-97);
				}
				// cout << u << endl;
			}
		}
		bitset<26> ans(init);
		int itr = 0;
		while(itr<75){
			bestImp = 0;
			bestBit = -1;
			for(int i=0;i<26;++i){
				bitset<26>attempt(ans);
				if(letter[i]){
					attempt.flip(i);
					int stat = 0;
					for(int j=0;j<M;++j){
						for(int k=0;k<3;++k){
							buf = box[k][3*j+1];
							if((buf<=90 && attempt[(int)buf-65])||(buf>=97 && !attempt[(int)buf-97])){
								buf = box[k][3*j+2];
							}
							else continue;
							if((buf<=90 && attempt[(int)buf-65])||(buf>=97 && !attempt[(int)buf-97])){
								++stat;
								break;
							}
						}
					}
					if(stat>bestImp){
						bestImp = stat;
						bestBit = i;
					}
				}
			}
			// if best improvement is better than the global
			if(bestImp>Tpass){
				Tpass = bestImp;
				ans.flip(bestBit);
				ansDig = ans.to_ulong();
				if(Tpass==M){ 
					isPass = true;
					break;
				}
			}
			else{
				++itr;
				Tpass = 0;
				// jump
				for(int i=0;i<26;++i) if(letter[i]) ans[i] = rand()%2;
			}
		}
		bitset<26> print(ansDig);
		print &= letter;
		if(isPass){
			cout << letter.count() - print.count() << " ";
			for(int i=0;i<26;++i) if(letter[i]&&!print[i]) cout << (char)(i+65) << " ";
			cout << "\n";
		}
		else cout << "-1\n";
	}
	return 0;
}
