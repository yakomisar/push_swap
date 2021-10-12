#include "push_swap.h"

void	check_errors(int argc, char **argv, t_list *my_list)
{
	int			i;
	long int	num;

	i = argc - 1;
	while (i)
	{
		num = ft_atoi(argv[i]);
		if (num > 2147483647 || num < -2147483648)
			get_error(my_list);
		if (num < 0 || argv[i][0] == '+')
		{
			if (!ft_isdigit(argv[i][1]))
				get_error(my_list);
		}
		else if (!ft_isdigit(*argv[i]))
			get_error(my_list);
		if (!ft_ischar(argv[i]))
			get_error(my_list);
		my_list->a = init_stack_a(my_list, num);
		i--;
		if (i == 0)
			my_list->a = my_list->a->next;
	}
}

int	ft_check(t_stack *a, int value, int len)
{
	t_stack	*tmp;

	tmp = a;
	while (len)
	{
		if (tmp->value == value)
			return (1);
		tmp = tmp->next;
		len--;
	}
	return (0);
}

void	check_duplicates(t_list *my_list)
{
	t_stack	*tmp;
	int		len;

	tmp = my_list->a;
	len = 0;
	while (tmp->next != my_list->a)
	{
		if (ft_check(my_list->a, tmp->value, len))
			get_error(my_list);
		tmp = tmp->next;
		len++;
	}
	if (tmp->next == my_list->a)
	{
		if (ft_check(my_list->a, tmp->value, len))
			get_error(my_list);
	}
}

void	check_sort(t_list *my_list)
{
	t_stack	*tmp;
	int		is_sorted;

	tmp = my_list->a;
	is_sorted = 1;
	while (tmp->next != my_list->a)
	{
		if (tmp->value > tmp->next->value)
			is_sorted = 0;
		tmp = tmp->next;
	}
	if (is_sorted)
		get_error_wo(my_list);
}

int	is_sort(t_list *my_list)
{
	t_stack	*tmp;

	tmp = my_list->a;
	while (tmp->next->next != my_list->a)
	{
		if (tmp->order > tmp->next->order)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
