#include "push_swap.h"

t_stack	*find_stop_a(t_list *my_list)
{
	t_stack	*tmp;

	tmp = my_list->a;
	while (tmp->next != my_list->a)
		tmp = tmp->next;
	return (tmp);
}

t_stack	*find_stop_b(t_list *my_list)
{
	t_stack	*tmp;

	tmp = my_list->b;
	while (tmp->next != my_list->b)
		tmp = tmp->next;
	return (tmp);
}

void	ft_sort_b(t_list *my_list, t_support *support)
{
	t_stack	*tmp;
	t_stack	*stop;

	tmp = my_list->b;
	if (!tmp)
		return ;	
	stop = find_stop_b(my_list);
	support->max = support->mid;
	support->mid = ((support->max - support->next) / 2) + support->next;
	support->flag++;
	while (tmp != stop)
	{
		tmp = my_list->b;
		if (!(tmp->order == support->next || tmp->order >= support->mid))
		{
			ft_rb(my_list);
		}
		else
		{
			send_values_to_a(my_list, support);
		}
	}
	if (my_list->b)
	{
		send_values_to_a(my_list, support);
	}
}

void	ft_sort_a(t_list *my_list, t_support *support)
{
	t_stack	*tmp;
	t_stack	*stop;
	int		flag;

	tmp = my_list->a;
	stop = find_stop_a(my_list);
	flag = tmp->flag;
	while (tmp != stop)
	{
		tmp = my_list->a;
		if (tmp->flag != flag)
			return ;
		send_values_to_b(my_list, support);
	}	
	tmp = my_list->a;
	send_values_to_b(my_list, support);
}
