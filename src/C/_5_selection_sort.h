#ifndef _5_SELECTION_SORT_H
#define _5_SELECTION_SORT_H

int arr[] = {49, 26, 15, 2, 10,19};

#define Swap(a,b) (a) = (a) + (b); \
                  (b) = (a) - (b); \
                    (a) = (a) - (b)

int GetMax(int *p, int count, int *index)
{
    int i = 0;

    int maxi = 0;
    int max = p[0];

    while(i < count)
    {
        if(p[i] > max)
        {
            max = p[i];
            maxi = i;
        }
        ++i;
    }
    *index = maxi;
    return max;
}

int SelectionSort(int *arr, int count)
{
    for(int i = 0; i < count - 1; ++i)
    {
        for(int j = i + 1; j < count; ++j)
        {
            if(arr[i] > arr[j])
                Swap(arr[i],arr[j]);
        }
    }
}


#endif // _5_SELECTION_SORT_H

