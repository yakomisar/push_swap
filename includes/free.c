#include "push_swap.h"

int	stack_counter(t_stack *stack)
{
	t_stack	*p;
	int		i;

	i = 1;
	p = stack;
	while (p->next != stack)
	{
		p = p->next;
		i++;
	}
	return (i);
}

void	fresh_stack_a(t_list *my_list)
{
	t_stack	*p;

	p = my_list->a;
	if (stack_counter(p) > 1)
	{
		while (my_list->a)
		{
			while (p->next != my_list->a)
				p = p->next;
			p->next = (my_list->a)->next;
			free(my_list->a);
			my_list->a = p;
			if (p->next == my_list->a)
			{
				free(p);
				break ;
			}
		}
	}
	else
		free(p);
	my_list->a = NULL;
}

void	fresh_stack_b(t_list *my_list)
{
	t_stack	*p;

	p = my_list->b;
	if (stack_counter(p) > 1)
	{
		while (my_list->b)
		{
			while (p->next != my_list->b)
				p = p->next;
			p->next = (my_list->b)->next;
			free(my_list->b);
			my_list->b = p;
			if (p->next == my_list->b)
			{
				free(p);
				break ;
			}
		}
	}
	else
		free(p);
	my_list->b = NULL;
}

void	free_all(t_list *my_list)
{
	if (my_list->a)
		fresh_stack_a(my_list);
	if (my_list->b)
		fresh_stack_b(my_list);
	if (my_list)
		free(my_list);
}