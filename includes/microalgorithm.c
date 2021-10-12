#include "push_swap.h"

void	micro_algorithm(t_list *my_list)
{
	if (my_list->a->value > my_list->a->next->value)
		ft_sa(my_list);
}
