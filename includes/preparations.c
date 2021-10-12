#include "push_swap.h"

void	quick_sort(int *arr, int len)
{
	long	tmp;
	int		i;

	i = 0;
	while (i < len - 1)
	{
		if (arr[i] <= arr[i + 1])
			i++;
		else
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			i = 0;
		}
	}
}

void	assign_order(int argc, int *arr, t_list *my_list)
{
	int		i;
	t_stack	*a;

	i = 0;
	a = my_list->a;
	while (a->next != my_list->a)
	{
		while (i < (argc - 1))
		{
			if (arr[i] == a->value)
			{
				a->order = i;
				i = 0;
				break ;
			}
			i++;
		}
		a = a->next;
	}
	i = 0;
	if (a->next == my_list->a)
	{
		while (argc - 1)
		{
			if (arr[i] == a->value)
			{
				a->order = i;
				i = 0;
				return ;
			}
			i++;
		}
	}
}

void	get_position(int argc, t_list *my_list)
{
	int		*arr;
	int		i;
	t_stack	*p;

	i = 0;
	p = my_list->a;
	arr = (int *)malloc((argc - 1) * sizeof(int));
	while (p->next != my_list->a)
	{
		arr[i] = p->value;
		p = p->next;
		i++;
	}
	if (p->next == my_list->a)
		arr[i] = p->value;
	quick_sort(arr, (argc - 1));
	assign_order(argc, arr, my_list);
	free(arr);
}

t_support	*init_support(int max)
{
	t_support	*tmp;

	tmp = (t_support *)malloc(sizeof(t_support));
	tmp->flag = 0;
	tmp->max = max;
	tmp->next = 0;
	tmp->mid = (max / 2) + tmp->next;
	return (tmp);
}
