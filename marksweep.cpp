#include<iostream>
using namespace std;
struct node
{
    int data;
    bool mark;
    struct node* adj1;
    struct node* adj2;
    struct node* adj3;
    node(int num)
    {
        data = num;
        adj1=NULL;
        adj2=NULL;
        adj3=NULL;
        mark=false;
    }
}; //we know at most 3 connections are present
typedef struct root_tag
{
    node* pointer;
}root;

node* heap[8];
/*
root1->4 5 2
       |/|/|
root2->3 7 | 
       |\| |
       | |\|
       |\| |\
       8 1 9
*/
void start(root& root1,root& root2)
{                                                   
    node* temp = new node(4);
    heap[0]=temp;
    temp = new node(3);
    heap[1]=temp;
    temp = new node(8);
    heap[2]=temp;
    temp = new node(1);
    heap[3]=temp;
    temp = new node(9);
    heap[4]=temp;
    temp = new node(5);
    heap[5]=temp;
    temp = new node(7);
    heap[6]=temp;
    temp = new node(2);
    heap[7]=temp;
    temp = NULL;
    //now all nodes are in the 'heap',to create connections now
    root1.pointer=heap[0];//root1->5
    heap[0]->adj1=heap[1];//5->1
    root2.pointer=heap[1];//root2->1
    heap[1]->adj1=heap[2];//1->2
    heap[1]->adj2=heap[3];//1->9
    heap[1]->adj3=heap[4];//1->10
    heap[5]->adj1=heap[1];//7->1
    heap[5]->adj2=heap[6];//7->8
    heap[6]->adj1=heap[4];//8->10
    heap[7]->adj1=heap[6];//3->8
    heap[7]->adj2=heap[4];//3->10
    //connections done
}
void Display_node(const node* node)
{
    if(node==NULL)
    {
        return;
    }
    cout<<" "<<node->data;
    if (node->adj1!=NULL || node->adj2!=NULL || node->adj3!=NULL)
    {
        cout<<"-[";
        Display_node(node->adj1);
        Display_node(node->adj2);
        Display_node(node->adj3);
        cout<<" ]";
    }
}
void Display_heap(node** arr)
{
    for(int i=0;i<8;i++)
    {
        if(arr[i]!=NULL)
        {
            Display_node(arr[i]);
            cout<<endl;
        }
    }
}
void Display_used_heap(const root& value)
{
    cout<<"root->";
    Display_node(value.pointer);
    cout<<endl;
}

void mark_node(node* ptr)
{
    node* head=ptr;
    node* tail=NULL;
    node* middle=NULL;
    int flag=1;
    while(head !=NULL)
    {
        if(!head->mark) //if node we are on is unmarked, mark it
        {
            head->mark=true;
        }
        if(head->adj3!=NULL && !head->adj3->mark)
        {
            tail=middle;
            middle=head;
            head=head->adj3;   
        }
         else if(head->adj2!=NULL && !head->adj2->mark)//only move along one adjacent path every iteration
        {
            tail=middle;
            middle=head;
            head=head->adj2;   
        }
        else if(head->adj1!=NULL && !head->adj1->mark) //if adjacent node to this is unmarked, move to it
        {
            tail=middle;
            middle=head;
            head=head->adj1;
        }
       	else
        {
            head=middle;
            middle=tail;
            tail=NULL;
        }

    }
}
void mark(const root& value)
{
    mark_node(value.pointer);
}
void sweep(node** arr)
{
    for(int i=0;i<8;i++)
    {
        if(arr[i]!=NULL)
        {
            if(!arr[i]->mark)
            {
                //disconnect the node
                arr[i]->adj1=NULL;
                arr[i]->adj2=NULL;
                arr[i]->adj3=NULL;
                delete arr[i];
                arr[i]=NULL;
            }
        }
    }
}
void garbage_collector(const root& r1,const root& r2,node** hp)
{
    cout<<"Mark phase intialized"<<endl;
    mark(r1);
    mark(r2);
    cout<<"Marking done"<<endl;
    cout<<"Sweep phase intialized"<<endl;
    sweep(hp);
}
int main()
{
    root i,j;
    start(i,j);
    cout<<"Simulation for mark sweep garbage collector\n";
    cout<<"Key to navigate the printed table: '-'indicates connection and '[]' indicate all the elements connected to the element\n";
    cout<<"the full heap is: "<<endl;
    Display_heap(heap);
    cout<<"________________________"<<endl;
    cout<<"Heap connected to the roots is: "<<endl;
    Display_used_heap(i);
    Display_used_heap(j);
    cout<<"_________________________"<<endl;
    garbage_collector(i,j,heap);
    cout<<"the garbage collector was called,complete heap is:\n";
    Display_heap(heap);
    cout<<"checking out if it matches heap connected to roots printed below\n";
    Display_used_heap(i);
    Display_used_heap(j);
}
