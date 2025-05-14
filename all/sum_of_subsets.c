#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100 // Define the maximum size of the stack  

int SIZE=0;
typedef struct Stack {  
    int arr[MAX];  
    int top;  
    int count; // To keep track of the number of elements  
} Stack;  

// Function to create an empty stack  
Stack* createStack() {  
    Stack* stack = (Stack*)malloc(sizeof(Stack));  
    if (stack) {  
        stack->top = -1;  
        stack->count = 0; // Initialize count to 0  
    }  
    return stack;  
}  

// Function to check if the stack is full  
int isFull(Stack* stack) {  
    return stack->top == MAX - 1;  
}  

// Function to check if the stack is empty  
int isEmpty(Stack* stack) {  
    return stack->top == -1;  
}  

// Function to add an item to the stack  
void push(Stack* stack, int value) {  
    if (isFull(stack)) {  
        // printf("Stack Overflow: Unable to push %d\n", value);  
        return;  
    }  
    stack->arr[++stack->top] = value;  
    stack->count++; // Increment count  
    // printf("Pushed %d to stack\n", value);  
}  

// Function to remove an item from the stack  
int pop(Stack* stack) {  
    if (isEmpty(stack)) {  
        // printf("Stack Underflow: Unable to pop\n");  
        return INT_MIN; // Return a sentinel value to indicate underflow  
    }  
    stack->count--; // Decrement count  
    return stack->arr[stack->top--];  
}  

// Function to view the top item of the stack  
int peek(Stack* stack) {  
    if (isEmpty(stack)) {  
        // printf("Stack is empty: Unable to peek\n");  
        return INT_MIN; // Return a sentinel value to indicate empty  
    }  
    return stack->arr[stack->top];  
}  

// Function to get the current number of elements in the stack  
int getCount(Stack* stack) {  
    return stack->count;  
}  



void sumOfSubsets(int arr[],int index,int target,Stack * currentSubset,int currentSum)
{
    // printf("Hleo\n");
    if(currentSum==target)
    {
        printf("{");
        for (int i = 0; i < getCount(currentSubset); i++)
        {
           printf("%d ",currentSubset->arr[i]);
        }
        printf("}\n");
    }

    if(currentSum > target || index >=SIZE) 
        return;

    push(currentSubset,arr[index]);
    sumOfSubsets(arr,index+1,target,currentSubset,currentSum+arr[index]);

    
    pop(currentSubset);
    sumOfSubsets(arr,index+1,target,currentSubset,currentSum);
}


void findSumOfSubsets(int arr[],int target)
{
    Stack *s = createStack();
    sumOfSubsets(arr,0,target,s,0);
}
int main(int argc, char const *argv[])
{
    // int arr[]= {2,4,6,10};
    int arr[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50,  
        55, 60, 65, 70, 75, 80, 85, 90, 95, 100}; 
    int n = sizeof(arr)/sizeof(int);

    SIZE = n;
    int target = 150;

    findSumOfSubsets(arr,target);
    return 0;
}
