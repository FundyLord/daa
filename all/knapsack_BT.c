#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 100

typedef struct item{
    int profit;
    int weight;
}Item;


int itemArray[MAX];

void knapsack_BT(Item * items,int n,int W,int index,int currProfit,int currWeight,int *maxProfit)
{
    if(index==n)
    {
        if(currWeight <= W && currProfit > maxProfit)
        {
            *maxProfit = currProfit;
        }
        return;
    }

    // Include Item
    if(currWeight + items[index].weight <=W)
        knapsack_BT(items,n,W,index+1,currProfit+items[index].profit,currWeight+items[index].weight,maxProfit);

    knapsack_BT(items,n,W,index+1,currProfit,currWeight,maxProfit);
}
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
