#include "push_swap.h"

void	ft_sa_hidden(t_list *my_list)
{
	int	tmp_value;
	int	tmp_order;
	int	tmp_flag;

	tmp_value = my_list->a->value;
	tmp_order = my_list->a->order;
	tmp_flag = my_list->a->flag;
	my_list->a->value = my_list->a->next->value;
	my_list->a->order = my_list->a->next->order;
	my_list->a->flag = my_list->a->next->flag;
	my_list->a->next = my_list->a->next->next;
	my_list->a->next->value = tmp_value;
	my_list->a->next->order = tmp_value;
	my_list->a->next->flag = tmp_value;
}

void	ft_sa(t_list *my_list)
{
	int		tmp_value;
	int		tmp_order;
	int		tmp_flag;
	t_stack	*tmp;

	tmp_value = my_list->a->value;
	tmp_order = my_list->a->order;
	tmp_flag = my_list->a->flag;
	my_list->a->value = my_list->a->next->value;
	my_list->a->order = my_list->a->next->order;
	my_list->a->flag = my_list->a->next->flag;
	my_list->a->next->value = tmp_value;
	my_list->a->next->order = tmp_order;
	my_list->a->next->flag = tmp_flag;
	tmp = my_list->a->next;
	my_list->a->next = my_list->a;
	my_list->a->next->next = tmp;
	write(1, "sa\n", 3);
}

void	ft_ra(t_list *my_list)
{
	my_list->a = my_list->a->next;
	write(1, "ra\n", 3);
}

void	ft_rra(t_list *my_list)
{
	int		j;
	int		i;
	t_stack	*p;

	j = 0;
	i = 0;
	p = my_list->a;
	while (p->next != my_list->a)
	{
		p = p->next;
		j++;
	}
	while (i < j)
	{
		my_list->a = my_list->a->next;
		i++;
	}
	write(1, "rra\n", 4);
}

void	ft_swap_a(t_list *my_list)
{
	int	swap_v;
	int	swap_p;
	int	swap_f;

	swap_v = my_list->a->next->value;
	my_list->a->next->value = my_list->a->value;
	my_list->a->value = swap_v;
	swap_p = my_list->a->next->order;
	my_list->a->next->order = my_list->a->order;
	my_list->a->order = swap_p;
	swap_f = my_list->a->next->flag;
	my_list->a->next->flag = my_list->a->flag;
	my_list->a->flag = swap_f;
}