//based on fukunaga Ch-10.5 Pg 507/616 in pdf

#include<iostream>
using namespace std;
#define row_size _m+1
#define col_size n+1
#define negInf -999999

//bool **list;
//int *z, *z_opt; 
bool list[51][51];
int z[51], z_opt[51],val[51];
int bound = negInf;
int n,m,_m;
int jfunc(int i, int k);
int jfunc_opt(int i);
void f(int i);

int main() {
	
	cout<<"n? ";
	cin>>n;
	cout<<"m? ";
	cin>>m;
	_m=n-m;//_m=complement(m)
	
/*	list = new bool*[row_size];
	for(int i=0;i<row_size;i++)
		list[i] = new bool[col_size];
		
	z = new int[_m];
	
	z_opt = new int[_m];
	cout<<"alloc completed\n";
*/	//init();//set z...s to 0
	
	for(int j = 0; j <= n-m+1; j++) {
		z[j]=0;
		z_opt[j]=0;
		//val[j+1]=m+1-j;////
	}
	for(int j=0;j<=n-m+1;j++)
		val[j+1]=n-m-j;
		
	for(int i=0;i<=row_size;i++)
		for(int j=0;j<=col_size;j++)
			list[i][j]=false;
//step 2 	
	for(int j = 1; j <= m+1; j++)
		list[1][j]=true;
	f(1);

	cout<<"Features excluded: \n";
	for(int j=1;j<=_m;j++) {
		cout<<z_opt[j]<<" ";
	}	
	cout<<endl<<"optimal J:"<<jfunc_opt(_m)<<endl;
	return 0;
}

//

int jfunc(int i, int k=0) {
	int sum = 0;
	for(int j=1;j<=i;j++)
		sum+=z[val[j]];////val added
	sum+=k;
	sum = n*(n+1)/2 - sum; //z values are discarded.
	return sum;
}

int jfunc_opt(int i) {
	int sum = 0;
	for(int j=1;j<=i;j++)
		sum+=z_opt[val[j]];
	
	sum = n*(n+1)/2 - sum; //z values are discarded.
	return sum;
}

void f(int i) {
	//scout<<"i:"<<i;
while(1) {
	int max = negInf, temp=0;
	for(int j=z[i-1]+1; j<=m+i; j++)
		if(list[i][j] && (temp=jfunc(i-1,j))>max) {
			max=temp;
			z[i]=j;
		}
	if(max == negInf) {
		i--;
		if(i==0)
			return;
		else {
			continue;//f(i)
			return;
		}
	}
	//else
	list[i][z[i]]=false;
	
	if(jfunc(i)<bound) {
		//cout<<"!";
		i--;
		if(i==0)
			return;
		else
			continue;//f(i)
	}
	else
		if(i== _m) {
			//cout<<"@";
			bound=jfunc(i);
			//cout<<bound<<endl;
			//z* <-- z
			for(int j=0;j<=_m;j++)
				z_opt[j]=z[j];
			i--;
			if(i==0)
				return;
			else
				continue;//f(i)
		}
		else {
			//cout<<"#";
			i++;
			for(int j = z[i-1]+1; j <= m+i; j++)
				list[i][j]=true;
			continue;//f(i)
		}
}
}

			
