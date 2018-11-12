#include<bits/stdc++.h>
#define INF 999999
using namespace std;
int nodes = 0,nodes1=0;
struct node
{
	int data;
	int noofchilds;
	bool mark;
    char C;
	struct node *left;
	struct node *right;
	struct node *par;
	struct node *child;
	
};
struct node *minptr=NULL;
struct node *minptr1=NULL;
struct node *create_node(int key)
{
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->data=key;
	temp->noofchilds=0;
	temp->mark=false;
	temp->par=NULL;
	temp->child=NULL;
	temp->left=temp;
	temp->right=temp;
    temp->C = 'N';
	return temp;
}
void insert(int key)
{
	struct node *temp=create_node(key);
	if(minptr==NULL)
	{
		minptr=temp;
	}
	else
	{
		//cout<<"minptr value "<<minptr->data<<endl;
		minptr->left->right=temp;
		temp->right=minptr;
		temp->left=minptr->left;
		minptr->left=temp;
		int minkey=minptr->data;
		if(key<minkey)
			minptr=temp;
	}
   nodes++;
}

void insertinexisting(int key)
{
    struct node *temp=create_node(key);
    if(minptr1==NULL)
    {
        minptr1=temp;
    }
    else
    {
        //cout<<"minptr value "<<minptr->data<<endl;
        minptr1->left->right=temp;
        temp->right=minptr1;
        temp->left=minptr1->left;
        minptr1->left=temp;
        int minkey=minptr1->data;
        if(key<minkey)
            minptr1=temp;
    }
   nodes1++;
}

void display() 
{    
    if (minptr == NULL) 
        cout << "The Heap is Empty" << endl; 
  
    else
    { 
        cout << "The root nodes of Heap are: " << endl;         
        struct node *temp=minptr;
        temp=temp->right;
        if(temp==NULL)
        	cout<<minptr->data<<endl;
        else
        {
        	while(temp!=minptr)
        	{
        		cout<<temp->data<<"-->";
        		temp=temp->right;
        	}
        	cout<<minptr->data<<endl;
        }
        
    } 
} 

void fibHeapLink(struct node *x, struct node *y)
{
    if (x -> child == NULL)
    {
        x -> child = y;
        y -> left = y -> right = y;
    }
    else
    {
        //cout<<"p child not null"<<endl;
        struct node *last = x -> child -> left;
        last -> right = y;
        y -> left = last;
        x -> child -> left = y;
        y -> right = x -> child;
    }
}

void consolidateHeap()
{
    if (minptr != NULL)
    {
        //cout<<"in consolidate!"<<endl;
        struct node *degreeArray[nodes];
        //cout<<"current number of nodes: "<<nodes<<endl;
        for (int i=0;i<nodes;i++) 
          degreeArray[i] = NULL;
        int maxDegree = 0;
        //cout<<"After for loop"<<endl;
        struct node *curr = minptr;
        //cout<<minptr->data<<endl;
        do
        {
            struct node * next = curr -> right;
            int deg = curr -> noofchilds;
            struct node *x = curr;
            while (degreeArray[deg] != NULL)
            {
                struct node *y = degreeArray[deg];
                if (x -> data > y -> data)
                {
					//swapping P and Q based on data of node
                    struct node *tmp = x;
                    x = y;
                    y = tmp;
                }
                //setting P as parent of Q
                y -> par = x;
                //cout<<y->par->data<<" "<<y->data<<endl;
                fibHeapLink(x,y);
                degreeArray[deg] = NULL;
                deg++;
                x -> noofchilds = deg;
            }
            degreeArray[deg] = x;
            if (deg > maxDegree) maxDegree = deg;
            curr = next;
        } while (curr != minptr);
        // cout<<"After while"<<endl;
        // cout<<"max degree: "<<maxDegree<<endl;
        struct node *maxDegreeNode = degreeArray[maxDegree];
        minptr = maxDegreeNode;
        for (int i=0;i<=maxDegree;i++)
        {
            if (degreeArray[i] != NULL)
            {
                maxDegreeNode -> right = degreeArray[i];
                degreeArray[i] -> left = maxDegreeNode;
                if (degreeArray[i] -> data >= minptr -> data) 
                   {
                       minptr = minptr;
                   }
                else
                {
                    minptr = degreeArray[i];
                } 
                maxDegreeNode = degreeArray[i];
            }
        }
        
    }
}
struct node* extractMin()
{
    if(minptr==NULL)
        return NULL;
    struct node *ret = minptr;
    nodes --;
    //minptr->noofchilds = minptr->noofchilds - 1;
    if (ret -> right == ret)
    {
        minptr = NULL;
    }
    else
    {//removing min
        ret->left->right=ret->right;
        ret->right->left=ret->left; 
        minptr=minptr->right;
       
    }
    if(ret->child == NULL)
	{
		//cout<<"Childeren not present!"<<endl;
	}
    else
    {
        //make parents as null
       // cout<<"In else"<<endl;
        struct node *tchild = ret -> child;
        //cout<<tchild->data<<endl;
		tchild->par =  NULL;
		tchild = tchild -> right;
        //cout<<tchild->data<<" child's data"<<endl;
        while(ret -> child != tchild)
		{
			tchild -> par = NULL;
            //cout<<tchild->data<<" child's data"<<endl;
			tchild = tchild -> right;
		}
        tchild = ret -> child;
        if (minptr == NULL)
        {
            minptr = tchild;
        }
        else
        {
            struct node *last1 = minptr -> left;
            minptr->left->right=tchild;
            minptr->left=minptr->left->right->left;
            tchild->left->right=minptr;
            tchild->left=last1;
        }
    }
    consolidateHeap();
    return ret;
}

struct node* findMin()
{
    if (nodes == 0)
     return NULL;
	return minptr;
}
void Cut(struct node *x, struct node *y)
{
    //cout<<"Inside cut"<<endl;
    x -> mark = false;
    x->par=NULL;
    if (x -> right == x) 
        y -> child = NULL;
    else
    {
        x->left->right=x->right;
        x->right->left=x->left;
        if (y->child == x) 
            y->child =x->left;
    }
    y -> noofchilds = y -> noofchilds - 1;
    struct node *last = minptr -> left;
    last -> right = x;
    x -> left = last;
    minptr -> left = x;
    x -> right = minptr;
}

void decreaseKey(struct node *x, int newData)
{
    //cout<<newData<<" "<<x->data<<endl;     
    if(newData > x->data)
     {
         cout<<"New key is greater than the current key"<<endl;
         return;
     }
     // cout<<"x data before change-------->  "<<x->data<<endl;
    x -> data = newData;
    //cout<<"x key: "<<x->data<<endl;
    struct node *curr = x;
    struct node *y = x -> par;
    //cout<<"y is data-------->  "<<y->data<<endl;
    if ( y != NULL && x->data < y->data )
    {
            Cut(x, y);
            //cout<<"Parent's mark ============> "<<parent->mark<<endl;
            if (x -> data < minptr -> data) 
                minptr = x;
            // ................ cascading cut...........................
            while (y -> par != NULL && y -> mark)
            {
               // cout<<"Inside while"<<endl;
                x = y;
                y = x->par;
                //x -> mark = false;
                Cut(x,y);               
            }
            if (y -> par != NULL) 
              y -> mark = true;
    }
    else if (curr -> data < minptr -> data) 
      minptr = curr;
  //cout<<"Value decreased successfully"<<endl;
}


void deleteKey(struct node *delnode)
{
    decreaseKey(delnode, -INF);
    extractMin();
    cout<<"Node deleted successfully"<<endl;
   
}

void Displayheapexisting()
{
    node* p = minptr1;
    if (p == NULL)
    {
        cout<<"The Heap is Empty"<<endl;
        return ;
    }
    cout<<"The root nodes of Heap are: "<<endl;
    do
    {
        cout<<p->data;
        p = p->right;
        if (p != minptr1)
        {
            cout<<"-->";
        }
    }while (p != minptr1&& p->right != NULL);
    cout<<endl;
}
 
struct node* find(struct node *x, int k)
{
    //struct node* x = minptr;
    x->C = 'Y';
    //cout<<"x data: "<<x->data<<endl;
    struct node* p = NULL;
    if (x->data == k)
    {
        p = x;
        x->C = 'N';
        return p;
    }
    if (p == NULL)
    {
        if (x->child != NULL )
        {
            p =  find(x->child, k);
            if(p&&p->data==k)
                return p;
        }            
        if ((x->right)->C != 'Y' )
            p =  find(x->right, k);

    }
    x->C = 'N';
    return p;
}
void unionheap(struct node *x,struct node *y)
{
    nodes=nodes+nodes1;
    if (x==NULL &&y==NULL) 
        return;
    if (x==NULL)
    {
        minptr=minptr1;
        minptr1=NULL;
        //free(minptr1);
        return;
    }
    if(y==NULL)
        return;
    struct node *first1 = minptr;
    struct node *last1 = minptr->left;
    struct node *first2 =minptr1;
    struct node *last2 = minptr1->left;
    first1 -> left = last2;
    last1 -> right = first2;
    first2 -> left = last1;
    last2 -> right = first1;
    if (minptr1-> data < minptr-> data) 
       minptr = minptr1;
   minptr1=NULL;
}

int main()
{
    int choice, node_val, newval,flag; 
    struct node *address=NULL;   
    while (1)
    {
        flag=0;
        cout<<"----------------------------"<<endl;
        cout<<"Operations on Fibonacci Heap"<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"1)Insert Element in the heap"<<endl;
        cout<<"2)Extract Minimum key node"<<endl;
        cout<<"3)Decrease key of a node"<<endl;
        cout<<"4)Delete a node"<<endl;
        cout<<"5)Display Minimum"<<endl;
        cout<<"6)Display Root List"<<endl; 
        //cout<<"7)Display whole heap"<<endl;       
        cout<<"7)Union"<<endl;
        cout<<"8)Exit"<<endl;
        cout<<"Enter Your Choice as integer: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            cout<<"Enter the element to be inserted  "<<endl;
            cin>>node_val;
            insert(node_val);
            cout<<"Inserted successfully "<<endl;
            break;

            case 2:
            cout<<"Extracting Min----------"<<endl;
            if(minptr==NULL)
                cout<<"No element in heap to extract "<<endl;
            else
            {
                cout<<"current minimum "<<extractMin()->data<<endl;
                if(findMin())
                    cout<<"New minimum: "<<findMin()->data<<endl;
                else
                    cout<<"New minimum: "<<"Heap is empty"<<endl;                 

            }            
            break;

            case 3:
            cout<<"Enter the node value to decrease the key"<<endl;
            cin>>node_val;
            cout<<"Enter new value for node "<<endl;
            cin>>newval;
            if(minptr==NULL)
                cout<<"Value not found in heap "<<endl;
            else
            {
                address=find(minptr,node_val);
                if(address==NULL)
                    cout<<"Value not found in heap"<<endl;
                else
                {
                    decreaseKey(address,newval);
                    cout<<"Value decreased successfully"<<endl;
                }
            }
            
            break;

            case 4:
            if(minptr==NULL)
            {
                cout<<"Heap is empty...First insert elements"<<endl;
                break;
            }
            cout<<"Enter the node value to be deleted"<<endl;
            cin>>node_val;            
            address=find(minptr,node_val);
            if(address==NULL)
                cout<<"Value not found in heap"<<endl;
            else
            {
                deleteKey(address);
            }
            break;

            case 5:
            if(findMin())
                cout<<findMin()->data<<endl;
            else
                cout<<"Heap is empty"<<endl;
            break;

            case 6:
            display();
            break;

            case 7:
            // insertinexisting(5);
            // insertinexisting(10);
            // insertinexisting(15);
            // insertinexisting(4);
            // insertinexisting(3);
            // insertinexisting(50);
            // insertinexisting(30);
            // insertinexisting(1);
            cout<<"Please enter elements of new heap"<<endl;
            while(1)
            {
                cout<<"Enter element or enter -0 when no more elements to be added"<<endl;
                cin>>node_val;
                if(node_val==-0)
                    break;
                insertinexisting(node_val);
            }
            cout<<"Current heap will be merged with following heap"<<endl;
            Displayheapexisting(); 
            unionheap(minptr,minptr1);           
            break;            
            case 8:
            flag=1;
            break;

            default:
            cout<<"Enter correct choice"<<endl;
        }
        if(flag==1)
            break;
    }

	return 0;
}