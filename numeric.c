#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
int main()
{
	FILE *fp;
	int i=0;
	int s,l,n;
	printf("Enter the number of columns containing numeric attributes\n");
	scanf("%d",&n);
	int arr[32][n];
	float a[32][32][n];
	fp=fopen("numeric.txt","r");
	while(fscanf(fp,"%d ",&s)!=EOF)
	{
		arr[i][0]=s;
		for(int p=1;	p<n;	p++)
		{
			fscanf(fp,"%d ",&s);
			arr[i][p]=s;
		}
		i++;
	}
	for(int b=0;	b<n;	b++)
	{
		l=arr[0][b];
		s=arr[0][b];
		for(int j=0;	j<32;	j++)
		{
			if(arr[j][b]>l)
				l=arr[j][b];
			if(arr[j][b]<s)
				s=arr[j][b];	
		}
		printf("\n");
		printf("\nColumn %d\n",b+1);
		printf("minimum = %d\n",s);
		printf("maximum = %d\n",l);
		for(int j=0;	j<32;	j++)
		{
			for(int k=0;	k<32;	k++)
			{
				a[j][k][b]=(abs(arr[j][b]-arr[k][b]))/(float)(l-s);
			}
		}
		for(int j=0;	j<32;	j++)
		{
			for(int k=0;	k<32;	k++)
			{	
				printf("%.2f ",a[j][k][b]);
			}
			printf("\n");
		}
	}
	return 0;
}


