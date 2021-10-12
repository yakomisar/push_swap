#include "push_swap.h"

void	finish_five(t_list *my_list)
{
	if (my_list->b->value < my_list->b->next->value)
	{
		ft_sb(my_list);
		ft_pa(my_list);
		ft_pa(my_list);
	}
	else
	{
		ft_pa(my_list);
		ft_pa(my_list);
	}
}

void	above_algorithm(t_list *my_list)
{
	t_stack	*tmp;
	int		counter;

	counter = 0;
	tmp = my_list->a;
	while (tmp->next != my_list->a)
	{
		if (tmp->order == 0 || tmp->order == 1)
		{
			ft_pb(my_list);
			tmp = my_list->a;
			counter++;
			if (counter == 2)
				break ;
		}
		else
		{
			ft_ra(my_list);
			tmp = my_list->a;
		}
	}
	mini_algorithm(my_list);
	finish_five(my_list);
}