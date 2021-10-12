#include "push_swap.h"

void	ft_rb(t_list *my_list)
{
	my_list->b = my_list->b->next;
	write(1, "rb\n", 3);
}

void	ft_sb(t_list *my_list)
{
	int		tmp_value;
	int		tmp_order;
	int		tmp_flag;
	t_stack	*tmp;

	tmp_value = my_list->b->value;
	tmp_order = my_list->b->order;
	tmp_flag = my_list->b->flag;
	my_list->b->value = my_list->b->next->value;
	my_list->b->order = my_list->b->next->order;
	my_list->b->flag = my_list->b->next->flag;
	my_list->b->next->value = tmp_value;
	my_list->b->next->order = tmp_order;
	my_list->b->next->flag = tmp_flag;
	tmp = my_list->b->next;
	my_list->b->next = my_list->b;
	my_list->b->next->next = tmp;
	write(1, "sb\n", 3);
}

void	ft_rrb(t_list *my_list)
{
	while (my_list->b->next != my_list->b)
		my_list->b = my_list->b->next;
	my_list->b = my_list->b->next;
	write(1, "rrb\n", 4);
}

void	ft_pb(t_list *my_list)
{
	my_list->b = init_stack_b(my_list);
	my_list->a = deletelem(my_list->a);
	if (my_list->a != NULL)
		my_list->a = my_list->a->next;
	write(1, "pb\n", 3);
}
