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

Point anchor;

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

void bruteForce(Point * p,int n,Point *result,int *numResult)
{
    int i,j,k;
    
    int pos,neg;

    sortPoints(p,n);
    for ( i = 0; i < n-1; i++)
    {
        for ( j = i+1; j < n; j++)
        {
            pos = neg = 0;
            for ( k = 0; k < n; k++)
            {
                if(k!=i && k!=j)
                {
                    int vector = vectorProduct(p[i],p[j],p[k]);
                    if(vector > 0)
                        pos++;
                    if(vector < 0 )
                        neg++;

                    if(pos>0 && neg>0)
                        break;
                }
                
            }

            if(pos==0 || neg==0)
            {
                int foundI =0,foundJ = 0;

                for (int n = 0; n < *numResult; n++)
                {
                    if(result[n].x==p[i].x && result[n].y==p[i].y)
                    {    
                        foundI =1;
                    }
                    if(result[n].x==p[j].x && result[n].y==p[j].y)
                    {    
                        foundJ =1;
                        
                    }

                }
                
                if(!foundI)
                {
                    result[*numResult] = p[i];
                    (*numResult)++;
                }

                if(!foundJ)
                {
                    result[*numResult] = p[j];
                    (*numResult)++;
                }


                break;
            }
            
        }
        
    }
    
    sortPoints(result,*numResult);
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
    bruteForce(points, n, result, &numResult);

    // Display the points in the convex hull
    printf("\nConvex Hull Points:\n");
    for (int i = 0; i < numResult; i++) {
        printf("Point %d: (%d, %d)\n", i + 1, result[i].x, result[i].y);
    }

    return 0;
}