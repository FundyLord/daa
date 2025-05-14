#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<limits.h>
#include<unistd.h>
#include<stdbool.h>
#include<math.h>

#define MAX 100

typedef struct point{
    int x;
    int y;
}Point;
// stack
typedef struct {  
    Point points[MAX];  
    int top; 
} Stack;  

Point anchor;
void initStack(Stack *stack) {  
    stack->top = -1; 
}  

int isFull(Stack *stack) {  
    return stack->top == MAX - 1;  
}  

int isEmpty(Stack *stack) {  
    return stack->top == -1;  
}  

int push(Stack *stack, Point point) {  
    if (isFull(stack)) {  
        printf("Stack overflow! Cannot push point (%d, %d)\n", point.x, point.y);  
        return -1;  
    }  
    stack->points[++stack->top] = point; 
    return 0; 
}  

Point pop(Stack *stack) {  
    if (isEmpty(stack)) {  
        printf("Stack underflow! Cannot pop from empty stack.\n");  
        Point invalid = {__INT16_MAX__, __INT16_MAX__};
        return invalid;  
    }  
    return stack->points[stack->top--]; 
}  


Point peek(Stack *stack) {  
    if (isEmpty(stack)) {  
        printf("Stack is empty! Cannot peek.\n");  
        Point invalid = {__INT16_MAX__, __INT16_MAX__}; // Return an invalid point  
        return invalid;  
    }  
    return stack->points[stack->top];  
}  


double calculateAngle(Point A)
{
    return atan2(A.y - anchor.y,A.x-anchor.x);
}

int comparePointsByAngle(const void* a,const void* b)
{
    Point *A = (Point*)a;
    Point *B = (Point*)b;

    double a1 = calculateAngle(*A);
    double a2 = calculateAngle(*B);

    if(a1<a2)
    {
        return -1;
    }else if(a1>a2)
    {
        return 1;
    }

    double d1 = sqrt(pow(A->x - anchor.x,2) + pow(A->y - anchor.y,2) );
    double d2 = sqrt(pow(B->x - anchor.x,2) + pow(B->y - anchor.y,2) );


    if(d1<d2)
        return -1;
    if(d1>d2)
        return 1;

    return 0;

}

Point  findLowestPoint(Point *p,int n)
{
    Point lowest = p[0];
    for (int i = 1; i < n; i++)
    {
        if(p[i].y < lowest.y || p[i].y == lowest.y && p[i].x < lowest.x)
            lowest = p[i];
    }
    return lowest;
    
}

void sortPoints(Point *p,int n)
{
    anchor = findLowestPoint(p,n);
    qsort(p,n,sizeof(Point),comparePointsByAngle);
}

int vectorProduct(Point A,Point B,Point C)
{
    return (B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x);
}



void grahamScan(Point *p,int n,Point *result,int *x)
{
    Stack *s  = (Stack*)malloc(sizeof(Stack));
    initStack(s);

    sortPoints(p,n);

    push(s, p[0]);
    push(s, p[1]);
    push(s, p[2]);

    for (int i = 3; i < n; i++)
    {
        while(s->top>1 && vectorProduct(s->points[s->top-1],peek(s),p[i])<0)
        {
            pop(s);
        }
        push(s,p[i]);
    }

    while(!isEmpty(s))
    {
        Point p = pop(s);
        result[*x] = p;
        (*x)++;
    }
    
    sortPoints(result,*x);

}


int main() {
    // Hardcoded points (instead of input from the user)
    Point points[MAX] = {
        {0, 0}, {1, 0}, {2, 2}, {1, 1}, {0, 2}, // Example points
        {3, 3}, {2, 1}, {1, 2}, {2, 0}, {3, 0}  // Additional points
    };
    
    int n = 10; // Number of points
    Point result[MAX];
    int numResult = 0;

    // Compute the convex hull using brute force method
    grahamScan(points, n, result, &numResult);
    

    // Display the points in the convex hull
    printf("\nConvex Hull Points:\n");
    for (int i = 0; i < numResult; i++) {
        printf("Point %d: (%d, %d)\n", i + 1, result[i].x, result[i].y);
    }

    return 0;
}