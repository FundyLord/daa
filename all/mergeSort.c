
void merge(int arr[],int p,int q,int r)
{   
    int n1 = q-p+1;
    int n2 = r-q;
    int i,j,k;
    int left[n1],right[n2];

    for (i = 0; i < n1; i++)
        left[i] = arr[p+i];
    
    for (j = 0; j < n2; j++)
        right[j] = arr[q+j+1];

    i=j=0;
    k=p;
    while(i<n1 && j<n2)
    {
        if(left[i]<right[j])
        {
            arr[k++] = left[i++];
        }else
        {
            arr[k++] = right[j++];
        }
    }
    while(i<n1)
        arr[k++] = left[i++];

    while(j<n2)
        arr[k++] = right[j++];

}
void mergeSort(int arr[],int p,int r)
{
    if(p<=r)
    {
        int q = (p+r)/2;
        mergeSort(arr,p,q);
        mergeSort(arr,q+1,r);
        merge(arr,p,q,r);
    }
}
