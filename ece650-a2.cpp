#include <stdlib.h>
#include<iostream>
#include "stdio.h"
#define MAX 100
#define MAXQ 100
#include <cstdlib>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <string.h>


using namespace std;

int edgelist[MAX];
struct edgeNode
{
    int no;
    int info;
    struct edgeNode * next;
};
struct vexNode
{
    int info;
    struct edgeNode *link;
};


vexNode adjlist[MAX];

int queue[MAXQ];
bool visited[MAX];
int parent[MAX];
int n;
int v1,v;
vector<int> nums;
int j = v;


int createGraph(vexNode *adjlist)
{
    
    
    string str;
    str="\n";
    getline(cin,str);
    
    string m = str.substr(3, str.size()-4);
    char *s_input = (char *)m.c_str();
    const char * split = ",<>";
    
    char *p = strtok(s_input, split);
    
    int a;
    while(p != NULL)
    {
        // char * -> int
        sscanf(p, "%d", &a);
        nums.push_back(a);    // num = tuple (only numbers)
        p=strtok(NULL, split);
    }
    
    

    
    for (int x=0; x <=int(nums.size())-1;x++){
        if (nums[x]>=n){
            
            fprintf(stderr,"Error: There are some edges do not exist and plz re-type.\n");
            
            getline(cin,str);
            string m = str.substr(3, str.size()-4);
            char *s_input = (char *)m.c_str();
            const char * split = ",<>";
            char *p = strtok(s_input, split);
            int a;
            while(p != NULL)
            {
                
                sscanf(p, "%d", &a);
                nums.push_back(a);
                p=strtok(NULL, split);
            }
        
        }
    }
    
    
    
    
    
    
    
    
    
    
    int i;
    for(i=1;i<=n;i++)
    {
        
        
        adjlist[i].info=i-1;
        
        adjlist[i].link = NULL;
        
    }
    
    edgeNode *p1,*p2;
    
    for(i=0;i<=int(nums.size())-1;i=i+2)
    {
        
        
        
        p1 = (edgeNode*)malloc(sizeof(edgeNode));
        p2 = (edgeNode*)malloc(sizeof(edgeNode));

        p1->no = nums[i]+1;
        p1->info = adjlist[nums[i]+1].info;
        p1->next = adjlist[nums[i+1]+1].link;
        adjlist[nums[i+1]+1].link = p1;

        p2->no = nums[i+1]+1;
        p2->info = adjlist[nums[i+1]+1].info;
        p2->next = adjlist[nums[i]+1].link;
        adjlist[nums[i]+1].link = p2;
        
    }
    return n;
}



void createV(vexNode *adjlist, int n)

{
    
    
    
    
    for(int i=0;i<n;i++)
        
    {
        
        adjlist[i].link = NULL;
        
        
    }
}

void createE(vexNode *adjlist,  int *edgelist,int e)

{
    
    int v1,v2,k;
    
    for(k=0;k<e;k++){
        
        v1 = edgelist[2*k];
        
        v2 = edgelist[2*k+1];
        
        
        
        
        edgeNode *p1,*p2;
        
        
        p1 = (edgeNode*)malloc(sizeof(edgeNode));
        
        p2 = (edgeNode*)malloc(sizeof(edgeNode));
        
        p1->no = v1;
        
        p1->next = adjlist[v2].link;
        
        adjlist[v2].link = p1;
        
        p2->no = v2;
        
        p2->next = adjlist[v1].link;
        
        adjlist[v1].link = p2;
        
    }
    
}


int BFS(vexNode *adjlist,int *queue,bool *visited,int *parent, int N1)
{
    
    int front,rear,v1;
    v1 = N1;
    front = 0;
    rear = 1;
    queue[rear] = v1;
    int i;
    
    
    for(i=0;i<MAX;i++){
        
        visited[i] = false;
        parent[i] = 1000;
    }
    
    
    visited[v1] = true;
    parent[v1] = 500;
    
    int vx;
    edgeNode *p;
    while(front != rear)
    {
        front = (front + 1)%MAXQ;
        vx = queue[front];
        p = adjlist[vx].link;
        while(p!=NULL)
        {
            if(!visited[p->no])
            {
                visited[p->no] = true;
                
                rear = (rear + 1)%MAXQ;
                queue[rear] = p->no;
                parent[p->no] = vx;
            }
            p=p->next;
        }
    }
    return v1;
    
}


int Maxi0(int *a, int size) {
    
    int valofmax = a[0];
    for (int i=1; i<size; i++) {
        if (a[i] > valofmax) {
            valofmax = a[i];
        }
    }
    return valofmax;
}

void print_line(vexNode *adjlist,int *parent,int target)

{
    if(parent[target]==500){
        cout<<target;
    }
    
    
    else{
        print_line(adjlist,parent,parent[target]);
        cout<<'-'<<target;
    }
    
    
    
}





int main(int argc, char** argv) {
    
    unsigned num;
    unsigned N0;
    unsigned N1;
    unsigned N2;
    char ch;
    
    
    
    
    
    while (!std::cin.eof()) {
        

        std::string line;
        std::getline(std::cin, line);
        

        std::istringstream input(line);
        

        std::vector<unsigned> nums;
        std::vector<char> chars;
        
        
        
        
        
        
        

        input>>ch;
        
        if(ch == 'V'){
            input>>N0;
            int n = N0;
            createV(adjlist,n);
            
        }
        
        
        
        
        
        
        
        
        else if(ch == 'E'){
            int numofEdge=0;
            
            
            if(line == "E { }"){
                continue;

            }

            input>>ch;
            

            
            while(ch != '}'){

                input>>ch;

                input>>num;
                nums.push_back(num);
                

                input>>ch;
                

                input>>num;
                nums.push_back(num);
                

                input>>ch;
                

                input>>ch;

                numofEdge++;
                
            }
            

            int m;
            for(m=0;m<nums.size();m++){
                edgelist[m] = nums[m];
                
            }
            
            
            //check
            int maxedgenode;
            maxedgenode = Maxi0(edgelist,2*numofEdge);
            if(maxedgenode> (N0 - 1)){
                std::cerr << "Error: there is no edge between them.\n";
                
            }
            //everything fine, create E
            else
                createE(adjlist,edgelist,numofEdge);
            
            
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        else if(ch == 's'){

            input>>N1;
            

            input>>N2;
            

            int v1 = BFS(adjlist,queue,visited,parent,N1);
            int v = N2;
            
            

            int maxofpath = (N1>N2)?N1:N2;
            
            if(maxofpath > (N0 - 1)){
                std::cerr << "Error: you typed some nodes do not exist.\n";
                
            }
            

            else{
                

                
                if(v1 != v){
                    if(parent[v]==1000){
                        cout<<"Error: there is no edge between them.\n";
                    }

                    else{
                        print_line(adjlist,parent,v);
                        cout<<endl;
                    }
                    
                    
                    
                    
                    
                }
                
  
                else
                    cout<<v1<<endl;
                
                
            }
            
            ch = '0';
            
            
        }
        
        
        
        else
            std::cerr << "Error: you typed something wrong.\n";
        
        
        
        
        
    }
}

