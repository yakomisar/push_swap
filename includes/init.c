#include "push_swap.h"

t_stack	*init_stack_a(t_list *my_list, int num)
{
	t_stack	*tmp;
	void	*p;

	if (my_list->a == NULL)
	{
		my_list->a = (t_stack *)malloc(sizeof(t_stack));
		my_list->a->value = num;
		my_list->a->order = 0;
		my_list->a->flag = 0;
		my_list->a->next = my_list->a;
		return (my_list->a);
	}
	else
	{
		tmp = (t_stack *)malloc(sizeof(t_stack));
		p = my_list->a->next;
		my_list->a->next = tmp;
		tmp->value = num;
		tmp->order = 0;
		tmp->flag = 0;
		tmp->next = p;
	}
	return (my_list->a);
}

t_stack	*init_stack_b(t_list *my_list)
{
	t_stack	*tmp;
	void	*p;

	if (my_list->b == NULL)
	{
		my_list->b = (t_stack *)malloc(sizeof(t_stack));
		my_list->b->value = my_list->a->value;
		my_list->b->order = my_list->a->order;
		my_list->b->flag = my_list->a->flag;
		my_list->b->next = my_list->b;
		return (my_list->b);
	}
	else
	{
		tmp = (t_stack *)malloc(sizeof(t_stack));
		p = my_list->b->next;
		my_list->b->next = tmp;
		tmp->value = my_list->a->value;
		tmp->order = my_list->a->order;
		tmp->flag = my_list->a->flag;
		tmp->next = p;
		ft_swap_b(my_list);
	}
	return (my_list->b);
}

void	list_init(t_list *mylist)
{
	mylist->a = NULL;
	mylist->b = NULL;
}

t_stack	*init_stack_a_for_pa(t_list *my_list, int num)
{
	t_stack	*temp;
	t_stack	*p;

	num = 0;
	temp = (t_stack *)malloc(sizeof(t_stack));
	p = my_list->a->next;
	my_list->a->next = temp;
	temp->value = my_list->b->value;
	temp->order = my_list->b->order;
	temp->flag = my_list->b->flag;
	temp->next = p;
	ft_swap_a(my_list);
	return (my_list->a);
}

void	*deletelem(t_stack *lst)
{
	t_stack	*temp;

	temp = lst;
	if (temp->next == lst)
	{
		free(lst);
		return (NULL);
	}
	while (temp->next != lst)
		temp = temp->next;
	temp->next = lst->next;
	free(lst);
	return (temp);
}
