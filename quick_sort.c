#include <stdio.h>

void	quick_sort(int *arr, int first, int last)
{
	int	left;
	int	right;
	int	middle;
	int tmp;

	if (first < last)
	{
		left = first;
		right = last;
		middle = arr[(left + right) / 2];
		while (left < right)
		{
			while (arr[left] < middle)
				left++;
			while (arr[right] > middle)
				right--;
			if (left <= right)
			{
				tmp = arr[left];
				arr[left] = arr[right];
				arr[right] = tmp;
				left++;
				right--;
			}
		}
		quick_sort(arr, first, right);
		quick_sort(arr, left, last);
	}
	return ;
}

int main()
{
    int arr[3] = {"6", "5", "4"};
    int i = 3;
    quick_sort(arr, 0, 3);
    for (i = 0; i < 3; i++)
    {

    }

    return (0);
}