#include "push_swap.h"

void	mini_algorithm(t_list *my_list)
{
	t_stack	*a;

	a = my_list->a;
	if (a->value < a->next->value
		&& a->value < a->next->next->value)
	{
		ft_sa(my_list), ft_ra(my_list);
	}
	else if (a->value > a->next->value
		&& a->value > a->next->next->value)
	{
		if (a->next->value < a->next->next->value)
			ft_ra(my_list);
		else
			ft_sa(my_list), ft_rra(my_list);
	}
	else
	{
		if (a->next->value < a->next->next->value)
			ft_sa(my_list);
		else
			ft_rra(my_list);
	}
}