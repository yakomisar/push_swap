#include "push_swap.h"

void	send_values_to_a(t_list *my_list, t_support *support)
{
	t_stack	*tmp;

	tmp = my_list->b;
	if (tmp->order == support->next)
	{
		support->next++;
		tmp->flag = support->flag;
		ft_pa(my_list);
		ft_ra(my_list);
		return ;
	}
	else if (tmp->order >= support->mid)
	{
		tmp->flag = support->flag;
		ft_pa(my_list);
	}
}

void	ft_pa(t_list *my_list)
{
	my_list->a = init_stack_a_for_pa(my_list, my_list->b->value);
	my_list->b = deletelem(my_list->b);
	if (my_list->b != NULL)
		my_list->b = my_list->b->next;
	write(1, "pa\n", 3);
}

void	ft_swap_b(t_list *my_list)
{
	int	swap_v;
	int	swap_p;
	int	swap_f;

	swap_v = my_list->b->next->value;
	my_list->b->next->value = my_list->b->value;
	my_list->b->value = swap_v;
	swap_p = my_list->b->next->order;
	my_list->b->next->order = my_list->b->order;
	my_list->b->order = swap_p;
	swap_f = my_list->b->next->flag;
	my_list->b->next->flag = my_list->b->flag;
	my_list->b->flag = swap_f;
}

void	ft_rr(t_list *my_list)
{
	ft_ra(my_list);
	ft_rb(my_list);
	write(1, "rr\n", 3);
}

void	ft_rrr(t_list *my_list)
{
	ft_rra(my_list);
	ft_rrb(my_list);
	write(1, "rrr\n", 4);
}
