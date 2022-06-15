#include<iostream>
#include<fstream>
using namespace std;

class Point {
	public:
	short int b1,b2,b3,b4, cluster;
	//Point() { b1=b2=b3=b4=0; cluster=-1; }
} pix[512][512];
int main() {
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
	//*****reading vector starts******
	for(int i=0;i<512;i++)
		for(int j=0;j<512;j++) {
			f1>>pix[i][j].b1;
			f2>>pix[i][j].b2;
			f3>>pix[i][j].b3;
			f4>>pix[i][j].b4;
		}
/*		
	char a[5];
	f1>>a;
	cout<<a<<" ";
	f1>>a;
	cout<<a<<" ";
	f1>>a;
	cout<<a<<" ";	
	f1>>a;
	cout<<a<<" ";
	f1>>pix[0][0].b1;
*/	cout<<pix[0][0].b1<<endl;
/*	*/
	cout<<"P2\n512 512\n256\n";
	for(int i=0;i<512;i++)
    		for(int j=0;j<512;j++)
  //  			pix[i][j].b1;//cluster/(K-1)*255;
	return 0;
}
