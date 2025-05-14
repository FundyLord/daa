#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>
#include<stdbool.h>

#define MAX_QUEUE_SIZE 100
typedef struct{
    int profit;
    int weight;
    double ratio;
}Item;

typedef struct node{
    double bound;
    int level;
    int profit;
    int weight;
}Node;


Node * initNode()
{
    Node * node =(Node*)malloc(sizeof(Node));
    node->level=-1;
    node->profit=0;
    node->weight=0;
    node->bound=0;
    return node;
}
// Queue structure definition  
typedef struct Queue {  
    Node *nodes[MAX_QUEUE_SIZE]; // Array to hold nodes  
    int front; // Index of the front node  
    int rear;  // Index to the next node to enqueue  
} Queue;  

// Function to create a new queue  
Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = -1; // Initially, the front is set to -1 (indicating empty)  
    q->rear = -1; 
    return q; // Initially, the rear is set to -1 (indicating empty)  
}  

// Function to check if the queue is empty  
bool isEmpty(Queue* q) {  
    return (q->front == -1);  
}  

// Function to check if the queue is full  
bool isFull(Queue* q) {  
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;  
}  

// Function to enqueue a new node to the queue  
void enqueue(Queue* q, Node x) {  
    if (isFull(q)) {  
        printf("Queue is full! Cannot enqueue.\n");  
        return;  
    }  

    if (isEmpty(q)) {  
        q->front = 0; // If the queue is empty, set front to 0  
    }  

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; 
    q->nodes[q->rear] = initNode();  // Circular increment for rear  
    q->nodes[q->rear]->level = x.level; 
    q->nodes[q->rear]->profit = x.profit;  
    q->nodes[q->rear]->weight = x.weight;  
    q->nodes[q->rear]->bound = x.bound;  
}  

// Function to dequeue a node from the queue  
Node* dequeue(Queue* q) {  
    if (isEmpty(q)) {  
        printf("Queue is empty! Cannot dequeue.\n");  
        return NULL; // Queue is empty, nothing to dequeue  
    }  

    Node* temp = q->nodes[q->front]; // Get the front node  
    if (q->front == q->rear) {  
        // If there's only one element left after dequeuing  
        q->front = -1;  
        q->rear = -1; // Queue is now empty  
    } else {  
        q->front = (q->front + 1) % MAX_QUEUE_SIZE; // Circular increment for front  
    }  

    return temp; // Return the dequeued node  
}  

// Function to peek at the front node of the queue without dequeuing it  
Node* peek(Queue* q) {  
    return (isEmpty(q)) ? NULL : q->nodes[q->front];  
} 

void sortItemsByRatio(Item *items,int n)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-1-i; j++)
        {
            if(items[j].ratio<items[j+1].ratio)
            {
                Item temp = items[j];
                items[j] = items[j+1];
                items[j+1] = temp;

            }
        }
        
    }
    
}
void setRatio(Item * items,int n)
{
    for (int i = 0; i < n; i++)
    {
        items[i].ratio = ((double)items[i].profit)/items[i].weight;
    }
}

double bound(Node u,int W,int n,Item * items)
{   
    if(u.weight >= W)
        return 0;

    int totalWeight = u.weight;
    double profit_bound = u.profit;
    int j = u.level+1;

    while(j<n && totalWeight + items[j].weight <=W)
    {
        totalWeight+=items[j].weight;
        profit_bound+=items[j].profit;
        j++;
    }

    if(j<n)
        profit_bound += (W - totalWeight)*items[j].ratio;

    return profit_bound;
    
}
int knapsack_BB(Item *items,int W,int n)
{
    Queue *queue = createQueue();
    sortItemsByRatio(items,n);

    Node *u = initNode();
    Node *v = initNode();

    u->bound = bound(*u,W,n,items);
    
    enqueue(queue,*u);

    int maxProfit = 0;
    while(!isEmpty(queue))
    {
        u = dequeue(queue);
        if(u->level==n-1)
            continue;

        v->level = u->level+1;

        v->weight = u->weight + items[v->level].weight;
        v->profit = u->profit + items[v->level].profit;

        if(v->weight<=W && v->profit>maxProfit)
        {
            printf("Taken Item : p: %d , w: %d\n",v->profit,v->weight);
            maxProfit = v->profit;
        }
        v->bound = bound(*v,W,n,items);
        if(v->bound > maxProfit)
        {
            enqueue(queue,*v);
        }


        v->weight = u->weight;
        v->profit = u->profit;
        v->bound = bound(*v,W,n,items);
        if(v->bound>maxProfit)
        {
            enqueue(queue,*v);
        }
    }

    return maxProfit;
}

int main() {  
    // Hardcoded values for items (weights and profits)  
    int n = 6; // Number of items  
    Item items[] = {  
        {60, 10},  // Item 1  
        {100, 20}, // Item 2  
        {120, 30}, // Item 3  
        {80, 15},  // Item 4  
        {150, 25}, // Item 5  
        {50, 5}    // Item 6  
    };   
    
    // Hardcoded maximum weight capacity of the knapsack  
    int W = 50;  

    // Calculate the ratio before sorting  
    setRatio(items, n);  
    
    // Solve the 0/1 Knapsack problem  
    int maxProfit = knapsack_BB(items, W, n);  

    printf("Max profit : %d\n",maxProfit);
    return 0;  
}