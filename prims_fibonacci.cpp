#include<bits/stdc++.h>
#include <time.h>
# define INF 0x3f3f3f3f
using namespace std;

struct node
	    {
			int id;
			int data;
			int noofchilds;
			struct node* par;
			struct node* child;
			struct node* left;
			struct node* right;
			bool mark;
			char C;
	    };
int nodes;

struct node* minptr=NULL;

struct node* create_node(int k, int ide)
  {
    struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
    temp->data=k;
    temp->id=ide;
    temp->noofchilds=0;
    temp->par=NULL;
    temp->child=NULL;
    temp->left=temp;
    temp->right=temp;
    temp->mark=false;
    temp->C='N';
    return temp;
  }
  
void heap_insert(int key, int id)
  {
    struct node *x = create_node(key, id);
    if(minptr!=NULL)
      {
        minptr->left->right=x;
        x->right=minptr;
        x->left=minptr->left;
        minptr->left=x;
        if( x->data < minptr->data )
          minptr=x;
      }
    else
      {
	     minptr=x;
      }
    nodes=nodes+1; 
  }
  void fibHeapLink(struct node *H1,struct node* y,struct node* z)
  { 
    y->left->right = y->right;
    y->right->left = y->left;
    if(z->right == z)
      H1 = z;
    y->left = y;
    y->right = y;
    y->par = z;
    if(z->child == NULL)
      z->child = y;
    y->right = z->child;
    y->left = (z->child)->left;
    z->child->left->right=y;
    z->child->left=y;
    if( y->data < z->child->data )
      z->child = y;
    z->noofchilds++;
  }

struct node* heapUnion(struct node* H1,struct node* H2)
  {
    struct node* np;
    struct node* minptr = NULL;
    minptr = H1;
    minptr -> left->right = H2;
    H2 -> left->right = minptr;
    np = minptr->left;
    minptr->left = H2->left;
    H2->left = np;
    return minptr;
  }

  void consolidateHeap( struct node *minp)
  {
     int d;
    // float f = (log(nodes)) / (log(2));
    // int D = f;
    struct node* A[nodes];
    for(int i=0; i<=nodes; i++)
	    A[i] = NULL;
    struct node* x = minp;
    struct node* y;
    struct node* np;
    struct node* pt = x;
    do
      {
        pt = pt->right;
        d = x->noofchilds;
        while(A[d]!=NULL)
        {
            y = A[d];
            if(x->data > y->data)
            {
                np = x;
                x = y;
                y = np;
            }
            if( y == minp)
                minp = x;
            fibHeapLink(minp, y,x );  
            if( x->right == x)
              minp=x;
            A[d] = NULL;
            d = d + 1;   
	  }
	A[d] = x;
	x = x->right;
      }while( x != minp );
   minptr=NULL;
   for(int j=0; j<=nodes; j++)
    {
      if( A[j] != NULL)
	  {
        A[j]->left = A[j];
        A[j]->right = A[j];
        if(minptr != NULL)
          {
            minptr->left->right = A[j];
            A[j]->right = minptr;
            A[j]->left = minptr->left;
            minptr->left = A[j];
            if(A[j]->data < minptr->data)
            minptr=A[j];
          }
        else
            {
            minptr=A[j];
            }
	    if(minptr == NULL)
	      minptr=A[j];
	    else if(A[j]->data < minptr->data)
	      minptr=A[j];
	   }
    }
  }

    
struct node* findNode(struct node *x,int k)
  {
    x->C = 'Y';
    struct node* p=NULL;
    if(x->data == k)
      {
        p = x;
        x->C = 'N';
	    return p;
      }
    if( x->child != NULL && p == NULL )
      {
        p = findNode(x->child, k);
      }
    if( x->right->C!='Y' && p==NULL )
      {
        p = findNode(x->right,k);
      }
    x->C = 'N';  
    return p; 
  }

struct node* extractMin(struct node *temp)
  {
    struct node* p;
    struct node* ptr;
    struct node* ret=temp;
    p=ret;
    ptr=ret;
    if(ret == NULL)
    {	
     return ret;
	}
    struct node* x;
    struct node* np;
    x = NULL;
    if( ret->child != NULL )
	    x = ret->child;
    if( x != NULL ) 
      {
	    ptr=x;
	do
	  {
	    np = x->right;
        temp->left->right=x;
        x->right = temp;
        x->left = temp->left;
        temp->left=x;
        if( x->data < temp->data )
            temp = x;
        x->par = NULL;
        x = np;
       }while(np != ptr);
      }  
    ret->left->right = ret->right;
    ret->right->left = ret->left;
    temp = ret->right;
    if(ret == ret->right && ret->child == NULL)
    {
      minptr=NULL;
    }
    else
      {
	  //can change here
        temp = ret->right;
        consolidateHeap(temp );
      }
    nodes=nodes-1;
    return p;
  }
    //can change here
void cut(struct node* temp,struct node* x,struct node* y)
  {
    if(x == x->right)
      y->child = NULL;
    x->left->right = x->right;
    x->right->left = x->left;
    if(x == y->child)
      y->child = x->right;
    y->noofchilds = y->noofchilds-1;
    x->right = x;
    x->left = x;
    temp->left->right = x;
    x->right = temp;
    x->left = temp->left;
    temp->left = x;
    x->par = NULL;
    x->mark = false;
  }
  
  
void cascadeCut(struct node*temp,struct node* y)
  {
    struct node* z = y->par;
    if( z != NULL)
      {
	if( y->mark == false)
	    {
	      y->mark=true;
	    }
	else
	  {
	    cut(temp,y,z);
	    cascadeCut(temp,z);
	  }
      }
  }
  

  
  
void decreaseKey(struct node* temp,int x,int k)
  {
    struct node* y;
    if(temp == NULL)
      {
        cout<<"\nHeap Is Empty! Exiting!!";
        return;
      }
    struct node* ptr = findNode(temp,x);
    if(ptr==NULL)
      {
        cout<<"\nThe specified Node does not exist!!";
        return;
      }
    if(ptr->data < k)
      {
        cout<<"\nThe entered value is greater than the current value";
        return;
      }
    ptr->data = k;
    y = ptr->par;
    if( y != NULL && ptr->data < y->data )
      {
        cut(temp,ptr,y);
        cascadeCut(temp,y);
      }
    if( ptr->data < minptr->data )
      minptr=ptr;
   return;
  }



void deleteKey(struct node *delnode)
{
    int del_val;
    cout<<"Enter the value of the node to be deleted!"<<endl;
    cin>>del_val;
      decreaseKey(minptr,del_val, -INF);
      extractMin(minptr);
    
}


typedef pair<int, int> iPair;

class Graph
{
    int V;
    list< pair<int, int> > *adj;
 
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void primMST();
    
    void printlist();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
}
 
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
 void Graph::printlist(){
	 
	     list< pair<int, int> >::iterator i;
        {
            int v = (*i).first;
            int weight = (*i).second;
            printf("%d %d :: ",v,weight);
		}
 }
 
void Graph::primMST()
{
 
    int src = 0;
    vector<int> key(V, INF);
    vector<int> par(V, -1);
    vector<bool> inMST(V, false);
    
	heap_insert(0,src);
    cout<<"heap insert done "<<endl;
   
    
    key[src] = 0;
    
    node *q1=minptr;
    while(q1!=NULL)
    /// END
    {
     
       // cout<<"extracting min-------"<<endl;
        q1=extractMin(minptr);
        //cout<<"extracted-------"<<endl;
        if(q1==NULL)break;
        int u=q1->id;    
 
        inMST[u] = true;
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;
            if (inMST[v] == false && key[v] > weight)
            {

                key[v] = weight;
                ///ADDED
                heap_insert(key[v],v);
                ///END
                
                
                par[v] = u;
            }
        }
    }
 
    for (int i = 1; i < V; ++i)
        printf("%d - %d\n", par[i], i);
}

void selftest1()
{
	int V = 9;
    Graph g(V);
	printf("/////////////// TEST 1 : 10 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);
    cout<<"one edge added"<<endl;
	std::fstream myfile("testcase1.txt", std::ios_base::in);
    
    int a,b,c;
    while (myfile >> a)
    {
    //    cout<<"inside myfile"<<endl;
		myfile >> b;
		myfile >> c;	
		g.addEdge(a,b,c);
        
    } 
    //cout<<"outside while"<<endl;
   
     clock_t t;
    t = clock();
    //cout<<"Calling prims"<<endl;
    g.primMST();
    //cout<<"prims done "<<endl;
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
	}
	
	
	void selftest2()
{
	int V = 100;
    Graph g(V);
	printf("/////////////// TEST 2 : 100 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);
   
	std::fstream myfile("testcase2.txt", std::ios_base::in);
    
    int a,b,c;
    while (myfile >> a)
    {
		myfile >> b;
		myfile >> c;		
		g.addEdge(a,b,c);
        
    } 
     clock_t t;
    t = clock();
    
    g.primMST();
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
	}
	
	void selftest3()
{
	int V = 100;
    Graph g(V);
	printf("/////////////// TEST 3 : 500 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);
	std::fstream myfile("testcase3.txt", std::ios_base::in);
    
    int a,b,c;
    while (myfile >> a)
    {
		myfile >> b;
		myfile >> c;		
		g.addEdge(a,b,c);
        
    } 
     clock_t t;
    t = clock();
    
    g.primMST();
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
	}
	
	void selftest4()
{
	int V = 100;
    Graph g(V);
	printf("/////////////// TEST 4 : 1000 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);    
	std::fstream myfile("testcase4.txt", std::ios_base::in);
    
    int a,b,c;
    while (myfile >> a)
    {
		myfile >> b;
		myfile >> c;
		
		g.addEdge(a,b,c);
        
    }     
     clock_t t;
    t = clock();
    
    g.primMST();
    
    t = clock() ;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
	}
  	void selftest5()
{
	int V = 100;
    Graph g(V);
	printf("/////////////// TEST 5 : 1000 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);    
	std::fstream myfile("testcase5.txt", std::ios_base::in);
    
    int a,b,c;
     
    while (myfile >> a)
    {
		myfile >> b;
		myfile >> c;
		//cout<<"edge addition started"<<endl; 
		g.addEdge(a,b,c);
    //cout<<"edge added"<<a<<" "<<b <<" "<<endl;  
       
    } 
    cout<<"edge added"<<endl;     
     clock_t t;
    t = clock();
    
    g.primMST();
    
    t = clock() ;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
	}

void selftest6()
{
  int V = 100;
    Graph g(V);
  printf("/////////////// TEST 6 : 10000 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);    
  std::fstream myfile("testcase6.txt", std::ios_base::in);
    
    int a,b,c;
     
    while (myfile >> a)
    {
    myfile >> b;
    myfile >> c;
    //cout<<"edge addition started"<<endl; 
    g.addEdge(a,b,c);
    //cout<<"edge added"<<a<<" "<<b <<" "<<endl;  
       
    } 
   // cout<<"edge added"<<endl;     
     clock_t t;
    t = clock();
    
    g.primMST();
    
    t = clock() ;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
  }
 void selftest7()
{
  int V = 100;
    Graph g(V);
  printf("/////////////// TEST 7 : 20000 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);    
  std::fstream myfile("testcase7.txt", std::ios_base::in);
    
    int a,b,c;
     
    while (myfile >> a)
    {
    myfile >> b;
    myfile >> c;
    //cout<<"edge addition started"<<endl; 
    g.addEdge(a,b,c);
    //cout<<"edge added"<<a<<" "<<b <<" "<<endl;  
       
    } 
    cout<<"edge added"<<endl;     
     clock_t t;
    t = clock();
    
    g.primMST();
    
    t = clock() ;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
  }
void selftest8()
{
  int V = 100;
    Graph g(V);
  printf("/////////////// TEST 8 : 50000 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);    
  std::fstream myfile("testcase8.txt", std::ios_base::in);
    
    int a,b,c;
     
    while (myfile >> a)
    {
    myfile >> b;
    myfile >> c;
    //cout<<"edge addition started"<<endl; 
    g.addEdge(a,b,c);
    //cout<<"edge added"<<a<<" "<<b <<" "<<endl;  
       
    } 
    cout<<"edge added"<<endl;     
     clock_t t;
    t = clock();
    
    g.primMST();
    
    t = clock() ;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
  }
void selftest9()
{
  int V = 100;
    Graph g(V);
  printf("/////////////// TEST 9 : 70000 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);    
  std::fstream myfile("testcase9.txt", std::ios_base::in);
    
    int a,b,c;
     
    while (myfile >> a)
    {
    myfile >> b;
    myfile >> c;
    //cout<<"edge addition started"<<endl; 
    g.addEdge(a,b,c);
    //cout<<"edge added"<<a<<" "<<b <<" "<<endl;  
       
    } 
    cout<<"edge added"<<endl;     
     clock_t t;
    t = clock();
    
    g.primMST();
    
    t = clock() ;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
  } 
void selftest10()
{
  int V = 100;
    Graph g(V);
  printf("/////////////// TEST 10 : 100000 Edges ////////////////////////\n");
    g.addEdge(0,1,-1);    
  std::fstream myfile("testcase10.txt", std::ios_base::in);
    
    int a,b,c;
     
    while (myfile >> a)
    {
    myfile >> b;
    myfile >> c;
    //cout<<"edge addition started"<<endl; 
    g.addEdge(a,b,c);
    //cout<<"edge added"<<a<<" "<<b <<" "<<endl;  
       
    } 
    cout<<"edge added"<<endl;     
     clock_t t;
    t = clock();
    
    g.primMST();
    
    t = clock() ;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("TIME : %f\n",time_taken);
  }
int main()
{
      selftest1();
      selftest2();
      selftest3();
       selftest4();
       
       selftest6();
       selftest7();
       selftest8();
       selftest9();
        selftest10();
      
 
    return 0;
}
