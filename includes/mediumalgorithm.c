#include "push_swap.h"

void	medium_algorithm(t_list *my_list)
{
	t_stack	*tmp;

	tmp = my_list->a;
	while (tmp->next != my_list->a)
	{
		if (tmp->order == 0)
		{
			ft_pb(my_list);
			tmp = my_list->a;
			break ;
		}
		else
		{
			ft_ra(my_list);
			tmp = my_list->a;
		}
	}
	mini_algorithm(my_list);
	ft_pa(my_list);
}