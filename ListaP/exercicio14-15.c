#include<stdio.h>
#include"str.h"

void intercala(char *str1, char *str2, char *str3){
	int sl1 = slen(str1), sl2 = slen(str2), x, t1=0, t2=0;
	for(x = 0; x < sl1 + sl2; x++){
		if(t1 < sl1 && !(x%2)){
			str3[x] = str1[t1];
			t1++;
		}else if(t2 < sl2){
			str3[x] = str2[t2];
			t2++;
		}
	}
	x++;
	str3[x] = '\0';
}

void desintercalar(char *str1, char *str2, char *str3){
	int x, sl2 = slen(str2), sl3 = slen(str3), t1 = 0, t2 = 0;
	for(x = 0; x < sl3; x++){
		if((!(x%2) || t2 == sl2) && t1 < sl3 - sl2){
			str1[t1] = str3[x];
			t1++;
		}else t2++;
	}
}

int main(){
	char str1[50], str2[50], str3[99];
	printf("Digite a palavra intercalada:");
	scanf("%s", str3);
	printf("Digite a segunda palavra:");
	scanf("%s", str2);
	desintercalar(str1, str2, str3);
	printf("%s\n", str1); 
	return 0;
}
