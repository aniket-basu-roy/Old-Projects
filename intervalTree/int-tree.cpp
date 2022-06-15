#include<iostream>
//#define swap(x,y) {x=x^y;y=x^y;x=x^y;}
using namespace std;

struct IntervalNode {
    int intervalIndex;
    IntervalNode* next;
};

struct IntervalTreeNode {
//public:
    double val;
    IntervalTreeNode *left, *right;
    IntervalNode *LeftListHead, *RightListHead;
}*head;

IntervalTreeNode* createNodes(double* arr, int l, int r);
void visitNodes(IntervalTreeNode* node);
void sort(double* a, int n);
void insertInterval(int index);
void visitNodesAndList(IntervalTreeNode* node);
void searchLeft(int index, IntervalTreeNode *p);
void searchRight(int index, IntervalTreeNode *p);
void reportAll(int index, IntervalTreeNode* node);
void deleteInterval(int index);

void swap(double& x, double& y) {
    double t=x;
    x=y;
    y=t;
}
void swap(int& x, int& y) {
    int t=x;
    x=y;
    y=t;
}
class Interval {
public:
    double a1,a2;
    void input() {
        cout<<"a1? ";
        cin>>a1;
        cout<<"a2? ";
        cin>>a2;
    }
}*interval;

bool** adj;
/*
int main() {
    int n;
    cout<<"# intervals? ";
    cin>>n;
    interval = new Interval[n];
    
    adj = new bool*[n];
    for(int i=0;i<n;i++)
        adj[i]=new bool[n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            adj[i][j]=false;

    for(int i=0;i<n;i++) {
        cout<<"Interval "<<i+1<<endl;
        interval[i].input();
    }

    double* arr = new double[2*n];
    for(int i=0;i<n;i++) {
        arr[2*i] = interval[i].a1;
        arr[2*i+1] = interval[i].a2;
    }
//display arr contents
    cout<<"Intervals:\n";
    for(int i=0;i<2*n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
//sort arr
    sort(arr,2*n);
    cout<<"Sorted Intervals:\n";
    for(int i=0;i<2*n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    head = createNodes(arr,0,(2*n)-1);

    cout<<"Displaying nodes\n";
    visitNodes(head);
    cout<<endl;
    for(int i=0;i<n;i++)
        insertInterval(i);
   visitNodesAndList(head);
   cout<<"\nAdjacency Matrix:\n";
   for(int i=0;i<n;i++) {
       for(int j=0;j<n;j++)
           cout<<adj[i][j]<<" ";
       cout<<endl;
   }
   int k;
   cout<<"Interval index to be deleted? ";
   cin>>k;
   deleteInterval(k);
   visitNodesAndList(head);
    return 0;
}
*/
void sort(double* a, int n) {
    for(int i=n-1;i>=1;i--)
        for(int j=0;j<i;j++)
            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
}

IntervalTreeNode* createNodes(double* arr, int l, int r) {
    IntervalTreeNode *a = new IntervalTreeNode;
    if(l<r)
        if((l+r)%2) {
            a->val = (arr[(l+r-1)/2] + arr[(l+r+1)/2])/2; //cout<<a->val<<" l:"<<l<<" r:"<<r<<"; "<<arr[(l+r-1)/2]<<","<<arr[(l+r+1)/2]<<"\n";
            a->left = createNodes(arr,l,(l+r-1)/2);
            a->right = createNodes(arr,(l+r+1)/2,r);
            a->LeftListHead = NULL;
            a->RightListHead = NULL;
        }
        else {
            a->val = arr[(l+r)/2]; //cout<<a->val<<" l:"<<l<<" r:"<<"; "<<arr[(l+r)/2]<<r<<"\n";
            a->left = createNodes(arr,l,(l+r)/2-1);
            a->right = createNodes(arr,(l+r)/2+1,r);
            a->LeftListHead = NULL;
            a->RightListHead = NULL;
        }
    else {//l==r
        a->val = arr[l]; //cout<<a->val<<" l:"<<l<<" r:"<<r<<"; "<<arr[l]<<"\n";
        a->left = NULL;
        a->right = NULL;
        a->LeftListHead = NULL;
        a->RightListHead = NULL;
    }
    return a;
}

void visitNodes(IntervalTreeNode* node) {
    if(!node)
        return;
    else {
        cout<<node->val<<" ";
        //cout<<"l: ";
        visitNodes(node->left);
        //cout<<"r: ";
        visitNodes(node->right);
    }
}

void insertInterval(int index) {
    IntervalTreeNode *p=head;
    IntervalNode *node, *t,*t_pre;//cout<<" *** ";
    for(; p!=NULL; ) {
        if(interval[index].a1 <= p->val && interval[index].a2 >= p->val) {

            //update adj[][]
            for(t=p->LeftListHead; t!=NULL; t=t->next) {
                adj[index][t->intervalIndex]=true;
                adj[t->intervalIndex][index]=true;
            }
            //cout<<" !!! ";
            //insert a1 in LeftList
            node = new IntervalNode;
            node->intervalIndex=index;
            for(t=p->LeftListHead, t_pre=NULL; t!=NULL && interval[index].a1 >= interval[t->intervalIndex].a1; t_pre=t, t=t->next);
            if(t_pre) {
                t_pre->next=node;
                node->next=t;
            }
            else {//getting inserted at the beginning
                node->next = p->LeftListHead;
                p->LeftListHead = node;
            }
            //cout<<" ### ";
            //insert a2 in RightList
            node = new IntervalNode;
            node->intervalIndex=index;
            for(t=p->RightListHead, t_pre=NULL; t!=NULL && interval[index].a2 <= interval[t->intervalIndex].a2; t_pre=t, t=t->next);
            if(t_pre) {
                t_pre->next=node;
                node->next=t;
            }
            else {//getting inserted at the beginning
                node->next = p->RightListHead;
                p->RightListHead = node;
            }
            searchLeft(index,p);
            searchRight(index,p);
            return;

        }
        else
            if(interval[index].a2 < p->val) {
                //update adj[][]
                for(t=p->LeftListHead; t!=NULL && interval[index].a2 >= interval[t->intervalIndex].a1; t=t->next) {
                    adj[index][t->intervalIndex]=true;
                    adj[t->intervalIndex][index]=true;
                }
                p=p->left;
            }
            else {
                //update adj[][]
                for(t=p->RightListHead; t!=NULL && interval[index].a1 <= interval[t->intervalIndex].a2; t=t->next) {
                    adj[index][t->intervalIndex]=true;
                    adj[t->intervalIndex][index]=true;
                }
                p=p->right;
            }
    }
}

void visitNodesAndList(IntervalTreeNode* node) {
    if(!node)
        return;
    else {
        cout<<node->val<<endl<<"Left List: ";
        for(IntervalNode* t=node->LeftListHead; t!=NULL; t=t->next) {
            cout<<interval[t->intervalIndex].a1<<" ";
        }
        cout<<"..."<<endl<<"Right List: ";
        for(IntervalNode* t=node->RightListHead; t!=NULL; t=t->next) {
            cout<<interval[t->intervalIndex].a2<<" ";
        }
        cout<<"---\n";
        visitNodesAndList(node->left);
        //cout<<"r: ";
        visitNodesAndList(node->right);
    }
}

void searchLeft(int index, IntervalTreeNode *p) {
    IntervalTreeNode *k;
    IntervalNode* t;
    for(k=p->left;k!=NULL;) {
        //update adj[][]
        for(t = k->RightListHead; t!=NULL && interval[t->intervalIndex].a2 >= interval[index].a1; t=t->next) {
                    adj[index][t->intervalIndex]=true;
                    adj[t->intervalIndex][index]=true;
        }

        if(k->val < interval[index].a1)//all whose a2 >= interval[index].a1
            k=k->right;
        else {
            for(; t!=NULL; t=t->next) { //and the rest in the list
                    adj[index][t->intervalIndex]=true;
                    adj[t->intervalIndex][index]=true;
            }
            if(k->val == interval[index].a1) {//all
                reportAll(index,k->right);
                return;
            }
            else {
                reportAll(index,k->right);//interval[index] intersects with every interval in k->right
                k=k->left;
            }
        }
    }
}

void reportAll(int index, IntervalTreeNode* node) {
    if(!node)
        return;
    else {
        //cout<<node->val<<endl;
        for(IntervalNode* t=node->LeftListHead; t!=NULL; t=t->next) {
            //cout<<interval[t->intervalIndex].a1<<" ";
            adj[index][t->intervalIndex]=true;
            adj[t->intervalIndex][index]=true;
        }
        //cout<<"..."<<endl;
        reportAll(index, node->left);
        //cout<<"r: ";
        reportAll(index, node->right);
    }
}
/*
void searchRight(int index, IntervalTreeNode *p) {
    IntervalTreeNode *k;
    for(k=p->right;k!=NULL;) {
        //update adj[][]
        for(IntervalNode* t = k->RightListHead; t!=NULL && interval[index].a2 >= interval[t->intervalIndex].a2; t=t->next) {
                    adj[index][t->intervalIndex]=true;
                    adj[t->intervalIndex][index]=true;
        }

        if(k->val == interval[index].a2)
            return;
        else
            if(k->val > interval[index].a2)
                k=k->left;
            else {
                reportAll(index,k->left);//interval[index] intersects with every interval in k->left
                k=k->right;
            }
    }
}
*/

void searchRight(int index, IntervalTreeNode *p) {
    IntervalTreeNode *k;
    IntervalNode* t;
    for(k=p->right;k!=NULL;) {
        //update adj[][]
        for(t = k->LeftListHead; t!=NULL && interval[t->intervalIndex].a1 <= interval[index].a2; t=t->next) {
                    adj[index][t->intervalIndex]=true;
                    adj[t->intervalIndex][index]=true;
        }

        if(k->val > interval[index].a2)//all whose a1 <= interval[index].a1
            k=k->left;
        else {
            for(; t!=NULL; t=t->next) { //and the rest in the list
                    adj[index][t->intervalIndex]=true;
                    adj[t->intervalIndex][index]=true;
            }
            if(k->val == interval[index].a2) {//all
                reportAll(index,k->left);
                return;
            }
            else {
                reportAll(index,k->left);//interval[index] intersects with every interval in k->left
                k=k->right;
            }
        }
    }
}

void deleteInterval(int index) {
IntervalTreeNode *p=head;
    IntervalNode *t,*t_pre;//cout<<" *** ";
    for(; p!=NULL; ) {
        if(interval[index].a1 <= p->val && interval[index].a2 >= p->val) {

            //cout<<" !!! ";
            //delete index from LeftList
           for(t=p->LeftListHead, t_pre=NULL; t!=NULL && index != t->intervalIndex; t_pre=t, t=t->next);
            if(!t)
                return;
            if(index == t->intervalIndex)
                if(!t_pre) {
                    p->LeftListHead = t->next;
                    delete t;
                }
                else {
                    t_pre->next=t->next;
                    delete t;//node->next=t;
                }

            //cout<<" ### ";
            //delete a2 in RightList
            for(t=p->RightListHead, t_pre=NULL; t!=NULL && index != t->intervalIndex; t_pre=t, t=t->next);
            if(index == t->intervalIndex) //check for t is not necessary as already done for LeftList
                if(!t_pre) {
                    p->RightListHead = t->next;
                    delete t;
                }
                else {
                    t_pre->next=t->next;
                    delete t;//node->next=t;
                }
            return;

        }
        else
            if(interval[index].a2 < p->val) {
                p=p->left;
            }
            else {
                p=p->right;
            }
    }
}

