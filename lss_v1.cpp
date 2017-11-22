//TLE version
#include <stdio.h>
#include <iostream>
using namespace std;

int seq1[2001] = {0};
int seq2[2001] = {0};
int lss[2001][2001][21] = {0};

int main(int argc, char const *argv[])
{
	int N,M,K,i=0,j=0,k=0;
	scanf("%d %d %d", &N, &M, &K);
	// scanf("%d %d", &N, &M);
	for(i=1;i<=N;i++) scanf("%d",&seq1[i]);
	for(i=1;i<=M;i++) scanf("%d",&seq2[i]);

	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++){
			if(seq1[i]==seq2[j]) lss[i][j][k] = lss[i-1][j-1][k] + 1;
			else lss[i][j][k] = max(lss[i-1][j][k],lss[i][j-1][k]);
		}
	}

	for(k=1;k<=K;k++){
		for(i=1;i<=N;i++){
			for(j=1;j<=M;j++){
				if(seq1[i]==seq2[j]) lss[i][j][k] = lss[i-1][j-1][k] + 1;
				else lss[i][j][k] = max(lss[i][j][k-1]+1,max(lss[i-1][j][k],lss[i][j-1][k]));
			}
		}
	}
	printf("%d\n", lss[N][M][K]);
	return 0;
}