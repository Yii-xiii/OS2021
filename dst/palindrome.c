#include<stdio.h>
#include<string.h>
int main()
{
	char s[10];
	scanf("%s",s);
	int i,j;

	for (i=0,j=strlen(s)-1;i<j;i++,j--){
		if (s[i] != s[j]){
			break;
		}
	}

	if(i>=j){
		printf("Y");
	}else{
		printf("N");
	}
	return 0;
}
