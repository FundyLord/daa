#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<limits.h>
#include<unistd.h>
#include<stdbool.h>
#define MAX 100

typedef struct item{
    int id;
    int profit;
    int weight;
    float ratio;
}Item;

int compareByRatioAsc(const void *a, const void *b) {
    float r1 = ((Item *)a)->ratio;
    float r2 = ((Item *)b)->ratio;

    if (r1 < r2) return 1;
    else if (r1 > r2) return -1;
    else return 0;
}

float FRACTIONAL_KNAPSACK(Item * items,int n,int max_weight)
{
    qsort(items,n,sizeof(Item),compareByRatioAsc);
    float profit = 0;
    int remainingWeight = max_weight;

    for (int i = 0; i < n; i++)
    {
        if(remainingWeight==0)
            break;
        else if(remainingWeight < items[i].weight)
        {
            printf("Frac part of Item %d added : contri = %f\n",items[i].id, remainingWeight * items[i].ratio);

            profit = profit + remainingWeight * items[i].ratio;
            break;
        }else
        {
                //add that item in sack
                printf("Item %d added\n",items[i].id);
                profit += items[i].profit;
                remainingWeight-=items[i].weight;
        }
    }

    return profit;
    
}
int main() {  
    int n,W;
    Item  * items;
    printf("Number of items : ");
    scanf("%d",&n);

    items = (Item*)malloc(sizeof(Item)*n);

    for (int i = 0; i < n; i++)
    {
        printf("Profit and Weight of Item %d (space between format) : ",i+1);
        scanf("%d %d", &items[i].profit,&items[i].weight);
        items[i].id = i+1;
        items[i].ratio = ((float)items[i].profit)/ items[i].weight;
    }
    
    for (int i = 0; i < n; i++)
    {
        printf("Item %d : Profit = %d , Weight : %d , Ratio : %.2f\n",i+1,items[i].profit,items[i].weight,items[i].ratio);
    }
    
    printf("Enter Max Capacity of Sack : ");
    scanf("%d",&W);
    float maxProfit = FRACTIONAL_KNAPSACK(items,n,W);
    printf("Max Profit : %f\n",maxProfit);

    return 0;
}

