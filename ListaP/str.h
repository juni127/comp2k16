int slen(char str[]){
	int size;
	for(size = 0; str[size] != '\0'; size++);
	return size+1;
}

int scmp(char str1[], char str2[]){
	int s1 = slen(str1), s2 = slen(str2), x, r = 0;
	for(x = 0; x < s1 || x < s2; x++){
		if(x > s1)r =- 1;
		else if(x > s2)r = 1;
		else{
			if((int)str1[x] > (int)str2[x])r = 1;
			else if((int)str1[x] < (int)str2[x])r = -1;
			else r = 0;
		}
		if(r != 0)break;
	}
	return r;
}

int slocate(char str1[], char str2[]){
	int i, j, r = -1, sl1 = slen(str1), sl2 = slen(str2);
	for(i = 0; i < sl1 - sl2; i++){
		for(j = 0; j < sl2; j++)if(!(str1[i+j] == str2[j]))break;
		if(j >= sl2-1){
			r = i;
			break;
		}
	}
	return r;	
}

void sremove(char str[], int i, int s){
	int sl = slen(str), x;
	for(x = i; x <= sl-s ; x++)str[x] = str[x+s];
}

void sinsert(char str1[], char str2[], int p){
	int sl1 = slen(str1), sl2 = slen(str2), x;
	for(x = sl1 + sl2; x > p + sl2; x--)str1[x] = str1[x - sl2];
	for(x = p; x < sl2 + p; x++)str1[x] = str2[x-p];
}
