#include <iostream>
#include<fstream>

#define UDEF -1000
using namespace std;

int main(int argc, char* argv[])
{
	ifstream in;
	int n,k,x,w,i=0,last=0;
	int j,a=1,max=0,l=0,maxp=0;
	//cout<<"argv["<<1<<"]= "<<argv[1];
	in.open (argv[1]);
	in>>n>>k;
	int A[n+1],W[n+1];
	int LMS[n+1], P[n+1];
	LMS[0]=0;
	P[0]=0;
	
	for(int p=0;p<n+1;p++)
	{
		W[p]=0; A[p]=0; //cout<<"\tA["<<p<<"]= "<<A[p];
	}
	
	int array[n];
	
	for(;a<=n;a++)
	{
		in>>x>>w;
		A[a]=x;
		W[a]=w;
	}

	for(i=1;i<=n;i++)
	{
		max=0;
		for(j=0;j<i;j++)
		{
			if(A[j]<A[i])
			{
				if(LMS[j]>max)
				{
					max=LMS[j];		
					P[i]=j;
				}
			}		
		}
		LMS[i]=max+W[i];		
		if(max==0)
			P[i]=0;
	}	
	
	for(i=1;i<=n;i++)
	{
		if(LMS[i]>maxp)
		{	maxp=LMS[i];
			last=i;
		}
	}
	cout<<"Output of part a:\n"<<maxp;
	cout<<"\n";//index printing:";	
	
	int q=0;
	array[0]=last;
	l=last;
	while(P[l]!=0)
	{
		array[++q]=P[l];
		l=P[l];
	}
	int length=q;
	
	for(;q>=0;q--)
		cout<<array[q]<<"\t";	

	cout<<"\n";//number printing";
	for(i=length;i>=0;i--)
		cout<<A[array[i]]<<"\t";
	cout<<"\n";
//*************************************************************end of part a***********************************************//

	int Ab[n+1],Wb[n+1];
	int LMSb[n+1][k+1], Pb[n+1][k+1], Pc[n+1][k+1];
	LMSb[0][0]=0; 
	Pb[0][0]=0;
	Pc[0][0]=0;
	
	int maxb;
	for(int p=1;p<k+1;p++)                  	// initialize LMSb
	{
		LMSb[0][p]=UDEF;
		Pb[0][p]=-10;			// initialize PB
		Pc[0][p]=-10;			// initialize Pc
	}
	
	for(int y=0;y<=n;y++)			// putting values in Ab and Wb
	{
		Ab[y]=A[y];
		Wb[y]=W[y];
	}
	
	for(int y=1;y<=n;y++)			// putting values in LMSb[i][0]
	{
		LMSb[y][0]=LMS[y];
		Pb[y][0]=P[y];
		Pc[y][0]=0;
	}

	for(int v=1; v<=k; v++)
	{	
		for(i=1;i<=n;i++)
		{
			maxb=0;
			for(j=1;j<i;j++)
			{		
			  	if(Ab[j]>=Ab[i]) 
				{
					if(LMSb[j][v-1]==UDEF)
						continue;
					else
					{
						int pen=(Ab[j]-Ab[i])*Wb[i];
						if(LMSb[j][v-1]-pen>maxb)
						{
							maxb=LMSb[j][v-1]-pen;	
							Pb[i][v]=j;
							Pc[i][v]=v-1;
						}
					}
				}
				else if(Ab[j]<Ab[i])
				{
					if(LMSb[j][v]==UDEF)
						continue;
					else
					{
						if(LMSb[j][v]>maxb)
						{
							maxb=LMSb[j][v];		
							Pb[i][v]=j;
							Pc[i][v]=v;
						}
					}
				}
			}
			if(maxb==0)
			{	LMSb[i][v]=UDEF;
				Pb[i][v]=UDEF;
				Pc[i][v]=UDEF;
			}
 			else if(maxb>=W[i])
				LMSb[i][v]=maxb+W[i];
			else
				LMSb[i][v]=W[i];		
			if(LMSb[i][v]==W[i])
			{	Pb[i][v]=0;
				Pc[i][v]=0;
			}
		}	
	}	

	int arrayb[n+1];

	int mw=0, row, col;
	for(int x=0;x<=n;x++)
	{
		for(int y=0;y<=k;y++)
		{	
			if(LMSb[x][y]>mw)
			{
				mw=LMSb[x][y];	
				row=x;
				col=y;
			}
		}	
	}

	cout<<"Output of part b:\n"<<mw;

	cout<<"\n";//index printing:";	
	q=0;
	arrayb[0]=row;
	l=row;
	int c=col;
	while(Pb[l][c]!=0)
	{
		arrayb[++q]=Pb[l][c];
		int temp=l;
		l=Pb[l][c];
		c=Pc[temp][c];
	}
	length=q;

	for(;q>=0;q--)
		cout<<arrayb[q]<<"\t";	
	cout<<"\n";

	for(i=length;i>=0;i--)
		cout<<Ab[arrayb[i]]<<"\t"; 
	cout<<"\n";

		return 0;
}