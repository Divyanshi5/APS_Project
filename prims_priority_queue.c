// STL implementation of Prim's algorithm for MST 
#include<bits/stdc++.h> 
using namespace std; 
# define INF 0x3f3f3f3f 

// iPair ==> Integer Pair 
typedef pair<int, int> iPair; 

// This class represents a directed graph using 
// adjacency list representation 
class Graph 
{ 
	int V; // No. of vertices 

	// In a weighted graph, we need to store vertex 
	// and weight pair for every edge 
	list< pair<int, int> > *adj; 

public: 
	Graph(int V); // Constructor 

	// function to add an edge to graph 
	void addEdge(int u, int v, int w); 

	// Print MST using Prim's algorithm 
	void primMST(); 
}; 

// Allocates memory for adjacency list 
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

// Prints shortest paths from src to all other vertices 
void Graph::primMST() 
{ 
	// Create a priority queue to store vertices that 
	// are being preinMST. This is weird syntax in C++. 
	// Refer below link for details of this syntax 
	// http://geeksquiz.com/implement-min-heap-using-stl/ 
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 

	int src = 0; // Taking vertex 0 as source 

	// Create a vector for keys and initialize all 
	// keys as infinite (INF) 
	vector<int> key(V, INF); 

	// To store parent array which in turn store MST 
	vector<int> parent(V, -1); 

	// To keep track of vertices included in MST 
	vector<bool> inMST(V, false); 

	// Insert source itself in priority queue and initialize 
	// its key as 0. 
	pq.push(make_pair(0, src)); 
	key[src] = 0; 

	/* Looping till priority queue becomes empty */
	while (!pq.empty()) 
	{ 
		// The first vertex in pair is the minimum key 
		// vertex, extract it from priority queue. 
		// vertex label is stored in second of pair (it 
		// has to be done this way to keep the vertices 
		// sorted key (key must be first item 
		// in pair) 
		int u = pq.top().second; 
		pq.pop(); 

		inMST[u] = true; // Include vertex in MST 

		// 'i' is used to get all adjacent vertices of a vertex 
		list< pair<int, int> >::iterator i; 
		for (i = adj[u].begin(); i != adj[u].end(); ++i) 
		{ 
			// Get vertex label and weight of current adjacent 
			// of u. 
			int v = (*i).first; 
			int weight = (*i).second; 

			// If v is not in MST and weight of (u,v) is smaller 
			// than current key of v 
			if (inMST[v] == false && key[v] > weight) 
			{ 
				// Updating key of v 
				key[v] = weight; 
				pq.push(make_pair(key[v], v)); 
				parent[v] = u; 
			} 
		} 
	} 

	// Print edges of MST using parent array 
	for (int i = 1; i < V; ++i) 
		printf("%d - %d\n", parent[i], i); 
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
    //cout<<"inside myfile"<<endl;
		myfile >> b;
		myfile >> c;	
		g.addEdge(a,b,c);
        
    } 
   // cout<<"outside while"<<endl;
   
     clock_t t;
    t = clock();
    cout<<"Calling prims"<<endl;
    g.primMST();
    cout<<"prims done "<<endl;
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
		cout<<"edge addition started"<<endl; 
		g.addEdge(a,b,c);
    cout<<"edge added"<<a<<" "<<b <<" "<<endl;  
       
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
    cout<<"edge added"<<endl;     
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



// Driver program to test methods of graph class 
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
