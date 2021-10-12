#include "push_swap.h"

void	ft_start(t_list *my_list, t_support *support)
{
	t_stack	*tmp;
	t_stack	*stop;

	tmp = my_list->a;
	stop = find_stop_a(my_list);
	while (tmp != stop)
	{
		tmp = my_list->a;
		if (tmp->order <= support->mid)
			ft_pb(my_list);
		else
			ft_ra(my_list);
	}
}

int	ft_finish(t_list *my_list)
{
	t_stack	*tmp;
	t_stack *b_tmp;

	b_tmp = my_list->b;
	if (my_list->b)
	{
		return (0);
	}
	tmp = my_list->a;
	while (tmp->next != my_list->a)
	{
		if (tmp->order > tmp->next->order)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_max_b(t_list *my_list)
{
	t_stack	*tmp;
	int		max;

	max = 0;
	tmp = my_list->b;
	if (my_list->b != NULL)
	{
		while (tmp->next != my_list->b)
		{
			if (tmp->order > max)
				max = tmp->order;
			tmp = tmp->next;
		}
		if (tmp->order > max)
			max = tmp->order;
	}
	return (max);
}

void	send_values_to_b(t_list *my_list, t_support *support)
{
	t_stack	*tmp;
	int		flag;

	tmp = my_list->a;
	flag = tmp->flag;
	if (tmp->order == support->next)
	{
		support->next++;
		ft_ra(my_list);
	}
	else if (tmp->flag == flag)
	{
		ft_pb(my_list);
	}
}

void	big_deal(int max, t_list *my_list)
{
	t_support	*support;
	int			i;

	i = 0;
	support = init_support(max);
	ft_start(my_list, support);
	while (!ft_finish(my_list))
	{
		support->mid = ft_max_b(my_list);
		while (my_list->b != NULL)
		{
			ft_sort_b(my_list, support);
		}
		if (!is_sort(my_list))
		{
			ft_sort_a(my_list, support);
		}
	}
	free(support);
}
