#include<iostream>
#include<cmath>
#include <fstream>
using namespace std;
const double PI = 3.14;
int graph_tex(char* graph_f, int n, bool** adj);

void print_header(ofstream& fout, int x1, int y1, int x2, int y2);
void print_trailer(ofstream& fout);

class Rect {
public:
    double x1,x2,y1,y2;//where x1<x2 & y1<y2
    void input() {
        cout<<"x1? ";
        cin>>x1;
        cout<<"x2? ";
        cin>>x2;
        cout<<"y1? ";
        cin>>y1;
        cout<<"y2? ";
        cin>>y2;
        cout<<endl;
    }
    bool intersect(Rect& r) {
        if( (r.x1>=x1 && r.x1<=x2) || (x1>r.x1 && x1<=r.x2) )
            if( (r.y1>=y1 && r.y1<=y2) || (y1>r.y1 && y1<=r.y2) )
                return true;
        return false;
    }
};
int rect_tex(char* rect_f, int n, Rect* rect);
/*
int main() {
    int n;
    cout<<"# Rectangles ? ";
    cin>>n;
    Rect* rect = new Rect[n];
    //allocating adj
    bool** adj = new bool*[n];
    for(int i=0;i<n;i++)
        adj[i]=new bool[n];

    cout<<"Input the Rectangles\n";
    for(int i=0;i<n;i++) {
        cout<<"Rectangle #"<<i+1<<endl;
        rect[i].input();
        for(int j=0;j<i;j++) {
            if(rect[i].intersect(rect[j]))
                adj[i][j]=true;
            else
                adj[i][j]=false;
            adj[j][i]=adj[i][j];
        }
    }

    cout<<"Adjacency Matrix of the Intersection graph\n";
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++)
            cout<<adj[i][j]<<" ";
        cout<<endl;
    }
    char tex_f[20];//assuming graph_f name is <=20 chars
    cout<<"Name of the graph tex file? ";
    cin>>tex_f;
    graph_tex(tex_f, n, adj);

    cout<<"Name of the rect tex file? ";
    cin>>tex_f;
    rect_tex(tex_f, n, rect);
    return 0;
}
*/
int graph_tex(char* graph_f, int n, bool** adj) {
    ofstream fout;
    fout.open(graph_f,ios::out);
    if(!fout) {
        cout<<"Cannot open "<<graph_f<<endl;
        return 1;
    }
    double theta=2*PI/n;
    double *x= new double[n];
    double *y= new double[n];

    print_header(fout,-1,-1,1,1);
    for(int i=0;i<n;i++) {
            x[i]=cos(i*theta);
            y[i]=sin(i*theta);
            fout<<"\\psdots[dotsize=0.2]("<<x[i]<<","<<y[i]<<")\n";
            fout<<"\\rput("<<1.25*x[i]<<","<<1.25*y[i]<<"){\\footnotesize "<<i+1<<"}\n";
    }
       
    //drawing the edges
    for(int i=0;i<n;i++)
            for(int j=0;j<i;j++)
                    if(adj[i][j])
                            fout<<"\\psline[linewidth=.1pt]("<<x[i]<<","<<y[i]<<")("<<x[j]<<","<<y[j]<<")\n";

    print_trailer(fout);
    fout.close();
    return 0;
}

void print_header(ofstream& fout, int x1, int y1, int x2, int y2) {

    fout<<
"\\documentclass{beamer}\
\\mode<presentation>\
\\usepackage[usenames,dvipsnames]{pstricks}\
\\usepackage{epsfig}\
\\usepackage{pst-grad}\
\\usepackage{pst-plot}\
\\begin{document}\
\\begin{frame}\
\\scalebox{1}{\
\\begin{pspicture}("<<x1<<","<<y1<<")("<<x2<<","<<y2<<")\n";

}

void print_trailer(ofstream& fout) {
    fout<<
"\\end{pspicture}}\
\\end{frame}\
\\end{document}\n";
}

int rect_tex(char* rect_f, int n, Rect* rect) {
    ofstream fout;
    fout.open(rect_f,ios::out);
    if(!fout) {
        cout<<"Cannot open "<<rect_f<<endl;
        return 1;
    }
    print_header(fout,0,0,10,10);

    for(int i=0;i<n;i++) {
        fout<<"\\psframe[linewidth=0.04,dimen=outer]("<<rect[i].x1<<","<<rect[i].y1<<")("<<rect[i].x2<<","<<rect[i].y2<<")\n";
        fout<<"\\rput("<<double(rect[i].x1)+0.25<<","<<double(rect[i].y1)+0.25<<"){\\footnotesize "<<i+1<<"}\n";
    }
    print_trailer(fout);
    fout.close();
    return 0;
}