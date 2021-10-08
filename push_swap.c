/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:12:12 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/08 22:30:20 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	char		*s;
	long int	result;
	int			i;
	short int	sign;

	i = 0;
	sign = 1;
	result = 0;
	s = (char *)str;
	while (s[i] == '\t' || s[i] == '\r' || s[i] == '\n'
		   || s[i] == ' ' || s[i] == '\f' || s[i] == '\v')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{	
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = (result * 10) + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

void	get_error()
{
	write(2, "Error\n", 6);
	exit(0);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_ischar(char *str)
{
	int	a;
	
	a = 0;
	while (str[a] != '\0')
	{
		if (!ft_isdigit(str[a]) || str[a] != '-' || str[a] != '+')
			return (1);
		a++;
	}
	return (0);
}

t_stack	*init_stack(t_list *my_list, int num)
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

void	print_list(t_stack *a)
{
	t_stack *head;

	head = a;
	while (head->next != a)
	{
		printf("value: %d\n", head->value);
		printf("next value: %d\n", head->next->value);
		head = head->next;
	}
	printf("value: %d\n", head->value);
		printf("next value: %d\n", head->next->value);
}

void	print_list_order(t_stack *a)
{
	t_stack *head;

	head = a;
	while (head->next != a)
	{
		printf("value: %d  -  order: %d\n", head->value, head->order);
		head = head->next;
	}
	printf("value: %d  -  order: %d\n", head->value, head->order);
}

void	check_errors(int argc, char **argv, t_list *my_list)
{
	int			i;
	long int	num;
	
	i = argc - 1;
	while (i)
	{
		num = ft_atoi(argv[i]);
		if (num > 2147483647 || num < -2147483648)
			get_error();
		if (num < 0 || argv[i][0] == '+')
		{
			if (!ft_isdigit(argv[i][1]))
				get_error();
		}
		else if (!ft_isdigit(*argv[i]))
			get_error();
		if (!ft_ischar(argv[i]))
			get_error();
		my_list->a = init_stack(my_list, num);
		i--;
		if (i == 0)
			my_list->a = my_list->a->next;
	}
	//print_list(a);
}

int		ft_check(t_stack *a, int value, int len)
{
	t_stack	*tmp;

	tmp = a;
	while(len)
	{
		if (tmp->value == value)
			return (1);
		tmp = tmp->next;
		len--;
	}
	return (0);
}

void	list_init(t_list *mylist)
{
	mylist->a = NULL;
	mylist->b = NULL;
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
			get_error();
		tmp = tmp->next;
		len++;
	}
	if (tmp->next == my_list->a)
	{
		if (ft_check(my_list->a, tmp->value, len))
			get_error();
	}
}

void	quick_sort(int *arr, int len)
{
	long	tmp;
	int		i;

	i = 0;
	while (i < len - 1)
	{
		if (arr[i] <= arr[i + 1])
			i++;
		else
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			i = 0;
		}
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
		printf("Заглушка список отсортирован.\n");
}

void	assign_order(int argc, int *arr, t_list *my_list)
{
	int	i;
	t_stack	*a;

	i = 0;
	a = my_list->a;
	while (a->next != my_list->a)
	{
		while (i < (argc - 1))
		{
			if (arr[i] == a->value)
			{
				a->order = i;
				i = 0;
				break ;
			}
			i++;
		}
		a = a->next;
	}
	i = 0;
	if (a->next == my_list->a)
	{
		while (argc - 1)
		{
			if (arr[i] == a->value)
			{
				a->order = i;
				i = 0;
				return ;
			}
			i++;
		}
	}
}

void	get_position(int argc, t_list *my_list)
{
	int	*arr;
	int	i;
	t_stack	*p;

	i = 0;
	p = my_list->a;
	arr = (int *)malloc((argc - 1) * sizeof(int));
	while (p->next != my_list->a)
	{
		arr[i] = p->value;
		p = p->next;
		i++;
	}
	if (p->next == my_list->a)
		arr[i] = p->value;
	quick_sort(arr, (argc - 1));
	assign_order(argc, arr, my_list);
	print_list_order(my_list->a);
	free(arr);
}

void	ft_sa(t_stack *a)
{
	int	tmp_value;
	int	tmp_order;
	int	tmp_flag;
	//t_stack	*tmp;
	
	tmp_value = a->value;
	tmp_order = a->order;
	tmp_flag = a->flag;
	//tmp = a->next;
	a->value = a->next->value;
	a->order = a->next->order;
	a->flag = a->next->flag;
	a->next = a->next->next;
	a->next->value = tmp_value;
	a->next->order = tmp_value;
	a->next->flag = tmp_value;
	//a->next->next = tmp;
	write(1, "sa\n", 3);
}

void	ft_ra(t_stack *a)
{
	a = a->next;
	write(1, "ra\n", 3);
}

void	ft_rb(t_stack *b)
{
	b = b->next;
	write(1, "rb\n", 3);
}

void	ft_rr(t_stack *a, t_stack *b)
{
	ft_ra(a);
	ft_rb(b);
	write(1, "rr\n", 3);
}

void	ft_rra(t_stack *a)
{
	int		j;
	int		i;
	t_stack	*p;

	j = 0;
	i = 0;
	p = a;
	while (p->next != a)
	{
		p = p->next;
		j++;
	}
	while (i < j)
	{
		a = a->next;
		i++;
	}
	write(1, "rra\n", 4);
}

void	ft_rrb(t_stack *b)
{
	while (b->next != b)
		b = b->next;
	b = b->next;
	write(1, "rrb\n", 4);
}

void	ft_rrr(t_stack *a, t_stack *b)
{
	ft_rra(a);
	ft_rrb(b);
	write(1, "rrr\n", 4);
}

void	micro_algorithm(t_stack *a)
{
	if (a->value > a->next->value)
		ft_sa(a);
}

void	mini_algorithm(t_stack *a)
{
	if (a->value < a->next->value
		&& a->value < a->next->next->value)
		ft_sa(a), ft_ra(a);
	else if (a->value > a->next->value
		&& a->value > a->next->next->value)
	{
		if (a->next->value < a->next->next->value)
			ft_ra(a);
		else
			ft_sa(a), ft_rra(a);
	}
	else
	{
		if (a->next->value < a->next->next->value)
			ft_sa(a);
		else
			ft_rra(a);
	}
}

void	algorithm(int argc, t_list *my_list)
{
	int	i;

	i = argc - 1;
	if (i == 2)
		micro_algorithm(my_list->a);
	if (i == 3)
		mini_algorithm(my_list->a);
		
	// else if (i == 4)
	// 	medium_algorithm(my_list);
	// else if (i == 5)
	// 	above_algorithm(my_list);
	// else if (i > 5)
	// 	big_deal(my_list);
}

void	push_swap(int argc, char **argv)
{
	t_list	*my_list;

	my_list = (t_list *)malloc(sizeof(t_list));
	list_init(my_list);
	check_errors(argc, argv, my_list);
	check_duplicates(my_list);
	check_sort(my_list);
	get_position(argc, my_list);
	algorithm(argc, my_list);
}

int	main(int argc, char **argv)
// int	main()
{
	//char *argv[4] = {"x", "6", "5", "4"};
	if (argc > 2)
		push_swap(argc, argv);
	return (0);
}