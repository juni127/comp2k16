#include<stdio.h>

int bmoore(char *a, int sa, char *b, int sb){
	int oc = 0, dic[256], x, k, ta, tb;
	//Cria o dicionario :V
	for(x = 0; x < 256; x++)dic[x] = 0;
	for(x = 0; x < sa; x++)dic[a[x]] = x;
	
	k = sa;
	while(k <= sb){
		ta = sa, tb = k;	
		while(a[ta] == b[tb] && ta >= 1){
			ta--, tb--;
		}
		if(ta < 1)oc++;
		if(k >= sb)break;
		k += ta - dic[b[k+1]] + 1; 
	}
	
	return oc;
}

int main(){

	return 0;
}
