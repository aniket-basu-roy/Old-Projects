#include<iostream>
#include<cmath>
#include<cstdlib>
/*
Lenna	225 225
Taj Mahal  550 366
Victoria Memorial 500 357
Self Potrait 627 502
*/
//#define M 502
//#define N 627
//short int M,N;

using namespace std;

const double PI = 3.1415926f;
//short int I[M][N];
//void inputImage();

int main(int argc, char* argv[]) {
	if(argc<2) {
		cout<<"Too few parameters\n";
		return 0;
	}
	//Calculate T1, T2
    	int T1=10, T2=40, M, N;
    	T1=atoi(argv[1]);
    	T2=atoi(argv[2]);
   //int I[M][N]= {{11,29,7,98},{11,29,47,98},{11,29,47,98},{1,29,7,98}};
   //inputImage();
	char a[4];
	cin>>a;
	cin>>N>>M>>a;
	
	short int **I, **I1, **I2, **I3;
	double **Mag, **theta, **Gx, **Gy;
	
	I = new short int*[M];
	I1 = new short int*[M];
	I2 = new short int*[M];
	I3 = new short int*[M];
	Mag = new double*[M];
	theta = new double*[M];
	Gx = new double*[M];
	Gy = new double*[M];
	
	for(int i=0;i<M;i++) {
		I[i] = new short int[N];
		I1[i] = new short int[N];
		I2[i] = new short int[N];
		I3[i] = new short int[N];
		Mag[i]= new double[N];
		theta[i]= new double[N];
		Gx[i] = new double[N];
		Gy[i] = new double[N];
	}
	
	for(int i=0;i<M;i++)
    		for(int j=0;j<N;j++)
    			cin>>I[i][j];
    			
   //short int Gx[M][N], Gy[M][N], I1[M][N], I2[M][N], I3[M][N];//, I4[M][N];
   //double Mag[M][N], theta[M][N];

////////////////////////////////////GAUSSIAN SMOOTHING////////////////////////////////////////////////////////////////////    

    //Gaussian Smoothing
    double mask[6] = {1, 	0.60653066, 0.367879441, 0.135335283, 0.082084999, 0.018315639}; //e^{-k/2}
    	//k:		//0    //1		//2		//4	//5	//8
    
    double sigma = mask[0]+ 4*(mask[1]+mask[2]+mask[3]+mask[5]) + 8*mask[4]; //sigma means sum
    
    for(int i=0;i<6;i++)
    	mask[i]=mask[i]/sigma;			
	
    for(int i=2;i<M-2;i++)
    	for(int j=2;j<N-2;j++)
    		I1[i][j]=	mask[0]*I[i][j] + 
    				mask[1]*(I[i-1][j] + I[i][j-1] + I[i+1][j] + I[i][j+1]) +
    				mask[2]*(I[i-1][j-1] + I[i-1][j+1] + I[i+1][j-1] + I[i+1][j+1]) +
    				mask[3]*(I[i-2][j] + I[i][j-2] + I[i+2][j] + I[i][j+2]) +
    				mask[4]*(I[i-1][j-2] + I[i-2][j-1] + I[i-1][j+2] + I[i+2][j-1] + I[i+1][j-2] + I[i-2][j+1] + I[i+1][j+2] + I[i+2][j+1]) +
    				mask[5]*(I[i-2][j-2] + I[i-2][j+2] + I[i+2][j-2] + I[i+2][j+2]) ;
/*    cout<<"Mask: ";
    for(int i=0;i<6;i++)
    	cout<<mask[i]<<" ";
    cout<<endl;	
*/
    //Borders
    for(int i=2;i<M-2;i++) {
    	I1[i][0]=I1[i][1]=I1[i][2];
    	I1[i][N-1]=I1[i][N-2]=I1[i][N-3];
    }
    for(int j=2;j<N-2;j++) {
    	I1[0][j]=I1[1][j]=I1[2][j];
    	I1[M-1][j]=I1[M-2][j]=I1[M-3][j];
    }
    
    I1[0][0]=I1[0][1]=I1[1][0]=I1[1][1]=I1[2][2];
    I1[0][N-1]=I1[0][N-2]=I1[1][N-1]=I1[1][N-2]=I1[2][N-3];
    I1[M-1][0]=I1[M-2][0]=I1[M-1][1]=I1[M-2][1]=I1[M-3][2];
    I1[M-1][N-1]=I1[M-1][N-2]=I1[M-2][N-1]=I1[M-2][N-2]=I1[M-3][N-3];
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //Gx calculation
    for(int i=0;i<M;i++)
    	for(int j=0;j<N-1;j++)
    		Gx[i][j]=I1[i][j+1]-I1[i][j];
    for(int i=0;i<M;i++) //the last coloumn is reset
    	Gx[i][N-1]=0;
    
    //Gx calculation
    for(int j=0;j<N;j++)
    	for(int i=0;i<M-1;i++)
    		Gy[i][j]=I1[i+1][j]-I1[i][j];
    for(int j=0;j<N;j++) //the last row is reset
    	Gy[M-1][j]=0;
/*   	
    //display Gx
    cout<<"Gx:\n";
    for(int i=0;i<M;i++) {
    	for(int j=0;j<N;j++)
    		cout<<Gx[i][j]<<" ";
    	cout<<endl;
    }
    	
    //display Gy
    cout<<"Gy:\n";
    for(int i=0;i<M;i++) {
    	for(int j=0;j<N;j++)
    		cout<<Gy[i][j]<<" ";
    	cout<<endl;
    }
*/    
    //Magnitude calculation
    for(int i=0;i<M;i++)
    	for(int j=0;j<N;j++)
    		Mag[i][j]=sqrt(Gx[i][j]*Gx[i][j] + Gy[i][j]*Gy[i][j]);
    		
    //theta calculation
    for(int i=0;i<M;i++)
    	for(int j=0;j<N;j++) {
    		if(Gx[i][j]==0)
    			theta[i][j]=PI;
    		else
    			theta[i][j]=atan(Gy[i][j]/Gx[i][j]);
    	}
/*   		
    //display Mag
    cout<<"Mag:\n";
    for(int i=0;i<M;i++) {
    	for(int j=0;j<N;j++)
    		cout<<Mag[i][j]<<" ";
    	cout<<endl;
    }
    
    //display theta
    cout<<"theta:\n";
    for(int i=0;i<M;i++) {
    	for(int j=0;j<N;j++)
    		cout<<theta[i][j]<<" ";
    	cout<<endl;
    }
*/

    //non-maxima suppression
    int magP, magQ, alpha;
    //excluding the {1st,last}*{row,col}
    for(int i=1;i<M-1;i++)
    	for(int j=1;j<N-1;j++) {
    		if(theta[i][j]>=0) {//as atan ranges [-pi/2,pi/2]
    			if(theta[i][j] >= PI/4) {
    				alpha=PI/2-theta[i][j];
	    			magQ=(1-tan(alpha))*Mag[i+1][j] + tan(alpha)*Mag[i+1][j+1];
	    			magP=(1-tan(alpha))*Mag[i-1][j] + tan(alpha)*Mag[i-1][j-1];
	    		}
	    		else {
	    			alpha=theta[i][j];
	    			magQ=(1-tan(alpha))*Mag[i][j+1] + tan(alpha)*Mag[i+1][j+1];
	    			magP=(1-tan(alpha))*Mag[i][j-1] + tan(alpha)*Mag[i-1][j-1];
	    		}
    			
    		}
    		else {
    			if(theta[i][j] >= -PI/4) {
    				alpha=-theta[i][j];
	    			magQ=(1-tan(alpha))*Mag[i][j+1] + tan(alpha)*Mag[i-1][j+1];
	    			magP=(1-tan(alpha))*Mag[i][j-1] + tan(alpha)*Mag[i+1][j-1];
	    		}
	    		else {
	    			alpha=PI/2+theta[i][j];
	    			magQ=(1-tan(alpha))*Mag[i-1][j] + tan(alpha)*Mag[i-1][j+1];
	    			magP=(1-tan(alpha))*Mag[i+1][j] + tan(alpha)*Mag[i+1][j-1];
	    		}
	    	}
    		if(magP<Mag[i][j] && magQ<Mag[i][j])
			I2[i][j]=1;
		else
			I2[i][j]=0;
	
    	}
    	
    	//{1st,last}*{row,col}
    	for(int j=0;j<N;j++) {
    		I2[0][j]=0;
    		I2[M-1][j]=0;
    	}
    	//excluding {0,0}*{N-1,N-1}
    	for(int i=1;i<M-1;i++) {
    		I2[i][0]=0;
    		I2[i][N-1]=0;
    	}
    	
    	
    	
    	//step iV
    	for(int i=0;i<M;i++)
	    	for(int j=0;j<N;j++) {
			if(I2[i][j]==0) {
				I3[i][j]=0;
				continue;
			}
			if(Mag[i][j]<T1) {
				I3[i][j]=0;
				continue;
			}
			if(Mag[i][j]>T2) {
				I3[i][j]=1;
				continue;
			}
			else
				I3[i][j]=2;
	    	}
    	
    	//step v
    	bool change;
    	do {
    	change=false;
    	for(int i=1;i<M-1;i++)
		for(int j=1;j<N-1;j++)		
			if(I3[i][j]==2)
				if(I3[i-1][j-1]==1 || I3[i-1][j]==1|| I3[i-1][j+1]==1 ||  
				I3[i][j-1]==1 			|| I3[i][j+1]==1 ||
				I3[i+1][j-1]==1	|| I3[i+1][j]==1|| I3[i+1][j+1]==1) {
					change=true;
					I3[i][j]=1;
				}
/*	change=false;			
	for(int i=1;i<M-1;i++)
		for(int j=1;j<N-1;j++)		
			if(I3[i][j]!=I4[i][j]) {
				change=true;
				I3[i][j]=I4[i][j];
			}
*/	}while(change);
				
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)		
			if(I3[i][j]==2) {
				I3[i][j]=0;
				//cerr<<"#";
				}
/*
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)			
			if(I3[i][j]==1)
				//cerr<<"$";
			else if(I3[i][j]==2)
				//cerr<<"%";
*/
	//cout<<"Final:\n";
	cout<<"P2\n"<<N<<" "<<M<<"\n256\n";
	for(int i=0;i<M;i++) {
    		for(int j=0;j<N;j++)
    			cout<<255*I3[i][j]<<" ";//changed
    	cout<<endl;
    	}
/*
	//cout<<"Gauss: "<<I1[50][50]<<endl;
	for(int i=-2;i<=2;i++) {
		for(int j=-2;j<=2;j++)
			cout<<I[50+i][50+j]<<"\t";
		cout<<endl;
	}
//*/
    return 0;
}
/*
void inputImage() {
	char a[4];
	cin>>a;
	cin>>N>>M>>a;
	for(int i=0;i<M;i++)
    		for(int j=0;j<N;j++)
    			cin>>I[i][j];
}
*/

