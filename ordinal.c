#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
float compare(int n,char s1[][n][20],char s2[][n][20],int pass,int j,int k,int m,FILE *fc)
{
	//FILE *fc;
	int i=0;
	char rank[m+1][20],s[20];
	float grade,g1,g2;
	while(fscanf(fc,"%s",s)!=EOF)
	{
		strcpy(rank[i],s);
		i++;
	}
	for(i=0;	i<m;	i++)
	{
		if(strcmp(s1[pass][j],rank[i])==0)
		{
			g1=i/(float)(m-1);
			break;
		
		}
	}
	for(i=0;	i<m;	i++)
	{
		if(strcmp(s2[pass][k],rank[i])==0)
		{
			g2=i/(float)(m-1);
			break;
		}
	}				
	grade=g1-g2;
	if(grade<0)
		grade=-grade;
	return grade;
}
int main()
{
	FILE *fp,*fc;
	int i=0,m;
	char ss[20];
	int s,l,n;
	printf("Enter the number of columns containing ordinal attributes:\n");
	scanf("%d",&n);
	char arr[n][32][20];
	float a[32][32][n];
	fp=fopen("ordinal.txt","r");
	fc=fopen("rank.txt","r");
	fscanf(fc,"%d",&m);
	while(fscanf(fp,"%s ",ss)!=EOF)
	{
		
		strcpy(arr[0][i],ss);
		for(int p=1;	p<n;	p++)
		{
			fscanf(fp,"%s ",ss);
			strcpy(arr[p][i],ss);
		}
		i++;
	}
	for(int b=0;	b<n;	b++)
	{
		for(int j=0;	j<32;	j++)
		{
			for(int k=0;	k<32;	k++)
			{
				a[j][k][b]=compare(32,arr,arr,b,j,k,m,fc);
			}
		}
		printf("Column %d\n",b+1);
		for(int j=0;	j<32;	j++)	
		{
			for(int k=0;	k<32;	k++)
			{
				printf("%.2f ",a[j][k][b]);
			}
			printf("\n");
		}
	printf("\n");
	}
	return 0;
}

