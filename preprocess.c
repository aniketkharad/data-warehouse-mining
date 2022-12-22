#include<stdio.h>
#include<string.h>
#include<stdlib.h>
float largest(float a[] , int n)
{
	float lar=a[0];
	for(int i=1;	i<n;	i++)
	{
		if(a[i]>lar)
			lar=a[i];
	}
	return lar;
}
float smallest(float a[] , int n)
{
	float sma=a[0];
	for(int i=1;	i<n;	i++)
	{
		if(a[i]<sma)
			sma=a[i];
	}
	return sma;
}
void emptyScanner(FILE *fp)
{
	char s[10];
	for(int i=0;	i<12;	i++)
	{
		fscanf(fp,"%s",s);	
	}

}
float * median(float data[],int n)
{
	float a[n];
	for(int i=0;	i<n;	i++)
		a[i]=data[i];
	for(int i=0;	i<n-1;	i++)
	{
		for(int j=i;	j<n;	j++)
		{
			if(a[i]>a[j])
			{
				int t=a[j];
				a[j]=a[i];
				a[i]=t;
			}
		}
	}
	float q2,q1,q3;
	static float q[3];
	int n1;
	if(n%2==0)
		q2=(a[(n/2)-1]+a[(n/2)+1-1])/2.0;
	else
		q2=a[((n+1)/2)-1];
	if(n%4==0)
	{
		q1=(a[(n/4)-1]+a[(n/4)+1-1])/2.0;
		q3=(a[(n/2)+(n/4)-1]+a[(n/2)+(n/4)+1-1])/2.0;
	}
	else if(n%2==0)
	{
		n1=n/2;
		q1=a[((n1+1)/2)-1];
		q3=a[(n1+((n1+1)/2))-1];
	}
	else if(n%4==1)
	{
		n1=(n+1)/2;
		q1=a[((n1+1)/2)-1];
		q3=a[((n/2)+(n1+1)/2)-1];
	}
	else
	{
		n1=(n+1)/4;
		q1=(a[n1-1]+a[n1+1-1])/2.0;
		q3=(a[(n/2)+n1-1]+a[(n/2)+n1+1-1])/2.0;
	}
	printf("\nq1 = %.2f\nq2 = %.2f\nq3 = %.2f\n",q1,q2,q3);
	q[0]=q1;
	q[1]=q2;
	q[2]=q3;
	return q;
}
float* outlier(float q[],float data[],int n)
{
	static float a[1500];
	float outL,outH;
	outL=q[0]-(q[2]-q[0])*1.5;
	outH=q[2]+(q[2]-q[0])*1.5;
	printf("outlier L = %.2f \noutlier H = %.2f\n",outL,outH);
	for(int i=0;	i<n;	i++)
	{
		if(data[i]<outL || data[i]>outH)
		{
			a[i]=q[1];
		}
		else
			a[i]=data[i];
	}
	return a;
}
void dataCleaning(float a[],int n,int median)
{
	for(int i=0;	i<n;	i++)
	{
		if(a[i]==0.00)
			a[i]=median;
	}
}
float* normalize(float data[],int n)
{
	static float a[1500];
	float lar=largest(data,n);
	float sma=smallest(data,n);
	float range=lar-sma;
	printf("\nlargest = %.2f \nsmallest = %.2f \nrange = %.2f\n\n",lar,sma,range);
	for(int i=0;	i<n;	i++)
	{
		a[i]=(data[i]-sma)/range;
	}
	return a;
}
int main()
{
	FILE *fp,*fw,*fd;
	char date[1500][11],s[10];
	char dataset[20];
	int i=0,count=0;
	char ch[3];
	float *q;
	int r,from,to;
	float open[1500],high[1500],low[1500],close[1500],volume[1500],openint[1500];
	float NORopen[1500],NORhigh[1500],NORlow[1500],NORclose[1500],NORvolume[1500],NORopenint[1500];
	float *Popen,*Phigh,*Plow,*Pclose,*Pvolume,*Popenint;
	printf("Enter the dataset file name\n");
	scanf("%s",dataset);
	fp=fopen(dataset,"r");
	if(fp==NULL)
	{
		printf("Invalid file name\n");
		return 0;
	
	}
	fw=fopen("normalisedDataset.txt","w");
	printf("1.Perform analysis on entire dataset \n2.Perform random analysis on the dataset by extracting a percentage of data\n3.Choose the required interval of data\n");
	scanf("%s",ch);
	if(strcmp(ch,"1")==0)
	{
		while(fscanf(fp,"%s",s)!=EOF)
		{
			strcpy(date[i],s);
			fscanf(fp,"%s",s);
			fscanf(fp,"%f",&open[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%f",&high[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%f",&low[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%f",&close[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%f",&volume[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%f",&openint[i]);
			i++;
		}
	}
	else if(strcmp(ch,"2")==0)
	{
		printf("enter the percentage of data to extract(integer):");
		scanf("%d",&r);
		while(fscanf(fp,"%s",s)!=EOF)
		{
			if((rand()%100)<r)
			{
				strcpy(date[i],s);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&open[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&high[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&low[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&close[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&volume[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&openint[i]);
				i++;
			}
			else
			{
				emptyScanner(fp);
			}
		}	
	}
	else if(strcmp(ch,"3")==0)
	{
		printf("enter the serial numbers of tuples to be extracted ( from and to ):");
		scanf("%d",&from);
		scanf("%d",&to);
		while(fscanf(fp,"%s",s)!=EOF)
		{
			if(count>=from && count<=to)
			{
				strcpy(date[i],s);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&open[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&high[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&low[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&close[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&volume[i]);
				fscanf(fp,"%s",s);
				fscanf(fp,"%f",&openint[i]);
				i++;
			}
			else
			{
				emptyScanner(fp);
			}
			count++;
		}	
	}

	int n=i;
	printf("%d tuples found !\n",n);
	printf("####################################################################################");
	printf("\nAnalysis of 'open' field\n");
	printf("Medians and quartiles:");
	q=median(open,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Popen=outlier(q,open,n);
	printf("\nData cleaning and ");
	dataCleaning(Popen,n,q[1]);
	printf("Data normalization");
	Popen=normalize(Popen,n);
	for(int i=0;i<n;	i++)
	{
		NORopen[i]=Popen[i];	
	}
	printf("####################################################################################");
	printf("\nAnalysis of 'high' field\n");
	printf("Medians and quartiles:");
	q=median(high,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Phigh=outlier(q,high,n);
	printf("\nData cleaning and ");
	dataCleaning(Phigh,n,q[1]);
	printf("Data normalization");
	Phigh=normalize(Phigh,n);
	for(int i=0;i<n;	i++)
	{
		NORhigh[i]=Phigh[i];	
	}
	printf("####################################################################################");
	printf("\nAnalysis of 'low' field\n");
	printf("Medians and quartiles:");
	q=median(low,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Plow=outlier(q,low,n);
	printf("\nData cleaning and ");
	dataCleaning(Plow,n,q[1]);
	printf("Data normalization");
	Plow=normalize(Plow,n);
	for(int i=0;i<n;	i++)
	{
		NORlow[i]=Plow[i];	
	}
	printf("####################################################################################");
	printf("\nAnalysis of 'close' field\n");
	printf("Medians and quartiles:");
	q=median(close,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Pclose=outlier(q,close,n);
	printf("\nData cleaning and ");
	dataCleaning(Pclose,n,q[1]);
	printf("Data normalization");
	Pclose=normalize(Pclose,n);
	for(int i=0;i<n;	i++)
	{
		NORclose[i]=Pclose[i];	
	}
	printf("####################################################################################");
	printf("\nAnalysis of 'volume' field\n");
	printf("Medians and quartiles:");
	q=median(volume,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Pvolume=outlier(q,volume,n);
	printf("\nData cleaning and ");
	dataCleaning(Pvolume,n,q[1]);
	printf("Data normalization");
	Pvolume=normalize(Pvolume,n);
	for(int i=0;i<n;	i++)
	{
		NORvolume[i]=Pvolume[i];	
	}
	for(int i=0;i<n;	i++)
	{
		NORopenint[i]=openint[i];	
	}
	printf("####################################################################################\n");
	/*for(i=0;	i<n;	i++)
	{
		printf("%s %.2f %.2f %.2f %.2f %.2f %.2f",date[i],open[i],high[i],low[i],close[i],volume[i],openint[i]);
		printf("\n");
	}*/
	for(int i=0;	i<n;	i++)
	{
		fprintf(fw,"%s ",date[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f  ",NORopen[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f  ",NORhigh[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f ",NORlow[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f ",NORclose[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f ",NORvolume[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f ",NORopenint[i]);
		fprintf(fw,"\n");
	}
	return 0;
}



