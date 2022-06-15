#include<iostream>
#include"int-tree.cpp"
#include"rect.cpp"
using namespace std;
void sortKey(double* key, int* record, int n);
int main() {
    int n;
    cout<<"# Rectangles ? ";
    cin>>n;
    Rect* rect = new Rect[n];
    interval = new Interval[n];
    //allocating adj
    adj = new bool*[n];
    for(int i=0;i<n;i++)
        adj[i]=new bool[n];
    //adj=0
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            adj[i][j]=false;

    cout<<"Input the Rectangles\n";
    for(int i=0;i<n;i++) {
        cout<<"Rectangle #"<<i+1<<endl;
        rect[i].input();
        interval[i].a1 = rect[i].y1;
        interval[i].a2 = rect[i].y2;
    }

    double* arr = new double[2*n];
    double* arrx = new double[2*n];
    int* eventQueue = new int[2*n];
    
    for(int i=0;i<n;i++) {
        arr[2*i] = interval[i].a1;
        arr[2*i+1] = interval[i].a2;
        arrx[2*i] = rect[i].x1;
        arrx[2*i+1] = rect[i].x2;
        eventQueue[2*i] = i;
        eventQueue[2*i+1] = -i;
    }
//display arr contents
    cout<<"Intervals:\n";
    for(int i=0;i<2*n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
//sort arr
    sort(arr,2*n);
    sortKey(arrx,eventQueue,2*n);
    cout<<"Sorted Intervals:\n";
    for(int i=0;i<2*n;i++) {
        cout<<arr[i]<<", "<<arrx[i]<<", "<<eventQueue[i]<<endl;
    }
    cout<<endl;

    head = createNodes(arr,0,(2*n)-1);

    //special care for 0 since, +0 = -0
    bool zerothIntervalInserted = false;
    for(int i=0;i<2*n;i++) {
        if(eventQueue[i]==0)
            if(!zerothIntervalInserted) {
                insertInterval(0);
                zerothIntervalInserted = true;
            }
            else {
                deleteInterval(0);
                zerothIntervalInserted = false;//not required
            }
        else
            if(eventQueue[i]>0)
                insertInterval(eventQueue[i]);
            else
                deleteInterval(-eventQueue[i]);
     //visitNodesAndList(head);cout<<".............\n";
    }

   //visitNodesAndList(head);

   cout<<"\nAdjacency Matrix:\n";
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

}

void sortKey(double* key, int* record, int n) {
    for(int i=n-1;i>=1;i--)
        for(int j=0;j<i;j++)
            if(key[j]>key[j+1]) {
                swap(key[j],key[j+1]);
                swap(record[j],record[j+1]);
            }
}