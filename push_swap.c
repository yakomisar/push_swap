/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:12:12 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/07 19:33:26 by jmacmill         ###   ########.fr       */
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
		printf("value: %d\n", head->order);
		head = head->next;
	}
	printf("value: %d\n", head->order);
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

void	quick_sort(int *arr, int first, int last)
{
	int	left;
	int	right;
	int	middle;
	int tmp;

	if (first < last)
	{
		left = first;
		right = last;
		middle = arr[(left + right) / 2];
		while (left < right)
		{
			while (arr[left] < middle)
				left++;
			while (arr[right] > middle)
				right--;
			if (left <= right)
			{
				tmp = arr[left];
				arr[left] = arr[right];
				arr[right] = tmp;
				left++;
				right--;
			}
		}
		quick_sort(arr, first, right);
		quick_sort(arr, left, last);
	}
	return ;
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

void	assign_order(int *arr, t_list *my_list)
{
	int	i;
	t_stack	*a;

	i = 0;
	a = my_list->a;
	while (a->next != my_list->a)
	{
		while (arr[i])
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
	if (a->next == my_list->a)
	{
		i = 0;
		while (arr[i])
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
	int	array[argc - 1];
	int	i;
	t_stack	*p;

	i = 0;
	p = my_list->a;
	while (p->next != my_list->a)
	{
		array[i] = p->value;
		p = p->next;
		i++;
	}
	if (p->next == my_list->a)
		array[i] = p->value;
	i++;
	quick_sort(array, 0, argc - 1);
	assign_order(array, my_list);
	print_list_order(my_list->a);
}

void	ft_sa(t_list *my_list)
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
	my_list->a->next->value = tmp_value;
	my_list->a->next->order = tmp_value;
	my_list->a->next->flag = tmp_value;
	write(1, "sa\n", 3);
}

void	micro_algorithm(t_list *my_list)
{
	if (my_list->a->value > my_list->a->next->value)
		ft_sa(my_list);	
}

void	algorithm(int argc, t_list *my_list)
{
	int	i;

	i = argc - 1;
	if (i == 2  )
		micro_algorithm(my_list);
	// else if (i == 3)
	// 	mini_algorithm(my_list);
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
	// char *argv[4] = {"x", "1", "2", "2"};
	if (argc > 2)
		push_swap(argc, argv);
	return (0);
}