#include<iostream>
#include<cstdlib>
#include<fstream>
#define Inf 999999
using namespace std;

class Point {
	public:
	double b1,b2,b3,b4;
	 short int cluster;
	Point() { b1=b2=b3=b4=0; cluster=-1; }
	int dist2(Point& p) {
		return (b1-p.b1)*(b1-p.b1) + (b2-p.b2)*(b2-p.b2) + (b3-p.b3)*(b3-p.b3) + (b4-p.b4)*(b4-p.b4);
	}
	bool operator==(Point& p) {
		if(b1==p.b1 && b2==p.b2 && b3==p.b3 && b4==p.b4)
			return true;
		else
			return false;
	}
	bool operator!=(Point& p) {
		if((*this)==p)
			return false;
		else
			return true;
	}
	void operator/=(int n) {
		b1/=n;
		b2/=n;
		b3/=n;
		b4/=n;
	}
	void operator+=(Point& p) {
		b1+=p.b1;
		b2+=p.b2;
		b3+=p.b3;
		b4+=p.b4;
	}
	void disp() {
		cerr<<"("<<b1<<","<<b2<<","<<b3<<","<<b4<<")\n";
	}
} pix[512][512];

void inputImage();
	
int main(int argc, char* argv[]) {
	//input 
	
	inputImage();
	
	if(argc<2) {
		cout<<"Too few parameters\n";
		return 0;
	}
	
	int K = atoi(argv[1]);
	Point* y = new Point[K];

	//initializing values of y
	for(int k=0;k<K;k++)
		y[k]=pix[511*k/(K-1)][511*k/(K-1)];
	
	cerr<<"y:\n";
	for(int k=0;k<K;k++)
		y[k].disp();
		
	for(int iter=0;1;iter++) {
		for(int i=0;i<512;i++)
			for(int j=0;j<512;j++) {
				int min = Inf;
				short int clus = -1;
				for(int k=0;k<K;k++)
					if(pix[i][j].dist2(y[k])<min) {
						min = pix[i][j].dist2(y[k]);
						if(min==0) cerr<<"dist:0, iter:"<<iter<<"\n"; //why is this condition not satisfied?
						clus = k;
					}
				pix[i][j].cluster=clus;
			}

		//Step iii.
		Point* z = new Point[K];

		int* cluSize = new int[K];
		for(int k=0;k<K;k++)
			cluSize[k]=0;
	
		for(int i=0;i<512;i++)
			for(int j=0;j<512;j++) {
				z[pix[i][j].cluster]+=pix[i][j];
				cluSize[pix[i][j].cluster]++;
			}

		for(int k=0;k<K;k++)
			cerr<<cluSize[k]<<" " ;
			
		for(int k=0;k<K;k++)
			if(cluSize[k])
				z[k]/=cluSize[k];	
			else	{
				cerr<<"Cluster size:0\n";
				z[k]=y[k];
			}

		bool converge=true;

		for(int k=0;k<K;k++) {
			if(z[k]!=y[k]) {
				converge=false;
				break;
			}
		}
	
		if(converge||iter>=100)
			break;//from while/for(1);
		else
			for(int k=0;k<K;k++)
				y[k]=z[k];

	}//end of while/for
	
	//print img
	cout<<"P2\n512 512\n256\n";
	for(int i=0;i<512;i++) {
    		for(int j=0;j<512;j++)
    			cout<<255*pix[i][j].cluster/(K-1)<<" ";
    		cout<<endl;
    	}

    	return 0;
}

void inputImage() {
	ifstream f1,f2,f3,f4;
	f1.open("band1.pgm");
	f2.open("band2.pgm");
	f3.open("band3.pgm");
	f4.open("band4.pgm");
	char a[4];
	f1>>a>>a>>a>>a;
	f2>>a>>a>>a>>a;
	f3>>a>>a>>a>>a;
	f4>>a>>a>>a>>a;
	//cout<<a<<" ~ ";
	//*****reading vector starts******//
	for(int i=0;i<512;i++)
		for(int j=0;j<512;j++) {
			f1>>pix[i][j].b1;
			f2>>pix[i][j].b2;
			f3>>pix[i][j].b3;
			f4>>pix[i][j].b4;
		}
	f1.close();
	f2.close();
	f3.close();
	f4.close();
//	cout<<"P2\n512 512\n256\n";
//	for(int i=0;i<512;i++)
//    		for(int j=0;j<512;j++)
//    			pix[0][0].b1;//cluster/(K-1)*255;

}
