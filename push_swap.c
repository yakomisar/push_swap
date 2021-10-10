/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:12:12 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/10 16:23:31 by jmacmill         ###   ########.fr       */
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

void	get_error(void)
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

void	print_list(t_stack *a)
{
	t_stack	*head;

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
	t_stack	*head;

	head = a;
	if (a != NULL)
	{
		while (head->next != a)
		{
			printf("value: %d  -  order: %d\n", head->value, head->order);
			head = head->next;
		}
		printf("value: %d  -  order: %d\n", head->value, head->order);
	}
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
	int		i;
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
	int		*arr;
	int		i;
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

void	ft_ra(t_list *my_list)
{
	my_list->a = my_list->a->next;
	write(1, "ra\n", 3);
}

void	ft_rb(t_list *my_list)
{
	my_list->b = my_list->b->next;
	write(1, "rb\n", 3);
}

void	ft_rr(t_list *my_list)
{
	ft_ra(my_list);
	ft_rb(my_list);
	write(1, "rr\n", 3);
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

void	ft_rrb(t_list *my_list)
{
	while (my_list->b->next != my_list->b)
		my_list->b = my_list->b->next;
	my_list->b = my_list->b->next;
	write(1, "rrb\n", 4);
}

void	ft_rrr(t_list *my_list)
{
	ft_rra(my_list);
	ft_rrb(my_list);
	write(1, "rrr\n", 4);
}

void	micro_algorithm(t_list *my_list)
{
	if (my_list->a->value > my_list->a->next->value)
		ft_sa(my_list);
}

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

void	ft_pb(t_list *my_list)
{
	my_list->b = init_stack_b(my_list);
	my_list->a = deletelem(my_list->a);
	if (my_list->a != NULL)
		my_list->a = my_list->a->next;
	write(1, "pb\n", 3);
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

t_stack	*init_stack_a_for_pa(t_list *my_list, int num)
{
	t_stack	*temp;
	t_stack	*p;
	// t_stack	*tmp;
	// void	*p;
	// int	tmp_value;

	// if (my_list->a == NULL)
	// {
	// 	my_list->a = (t_stack *)malloc(sizeof(t_stack));
	// 	my_list->a->value = num;
	// 	my_list->a->order = 0;
	// 	my_list->a->flag = 0;
	// 	my_list->a->next = my_list->a;
	// 	return (my_list->a);
	// }
	// else
	// {
	// 	tmp = (t_stack *)malloc(sizeof(t_stack));
	// 	p = my_list->a->next;
	// 	my_list->a->next = tmp;
	// 	tmp->value = num;
	// 	tmp->order = my_list->b->order;
	// 	tmp->flag = my_list->b->flag;
	// 	tmp->next = p;
	// 	tmp_value = my_list->a->value;
	// 	my_list->a->value = my_list->a->next->value;
	// 	my_list->a->next->value = tmp_value;
	// }
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

void	ft_pa(t_list *my_list)
{
	my_list->a = init_stack_a_for_pa(my_list, my_list->b->value);
	my_list->b = deletelem(my_list->b);
	if (my_list->b != NULL)
		my_list->b = my_list->b->next;
	write(1, "pa\n", 3);
}

void	medium_algorithm(t_list *my_list)
{
	t_stack	*tmp;

	tmp = my_list->a;
	while (tmp->next != my_list->a)
	{
		if (tmp->order == 0)
		{
			ft_pb(my_list);
			tmp = my_list->a;
			break ;
		}
		else
		{
			ft_ra(my_list);
			tmp = my_list->a;
		}
	}
	mini_algorithm(my_list);
	ft_pa(my_list);
}

void	finish_five(t_list *my_list)
{
	if (my_list->b->value < my_list->b->next->value)
	{
		ft_sb(my_list);
		ft_pa(my_list);
		ft_pa(my_list);
	}
	else
	{
		ft_pa(my_list);
		ft_pa(my_list);
	}
}

void	above_algorithm(t_list *my_list)
{
	t_stack	*tmp;
	int		counter;

	counter = 0;
	tmp = my_list->a;
	while (tmp->next != my_list->a)
	{
		if (tmp->order == 0 || tmp->order == 1)
		{
			ft_pb(my_list);
			tmp = my_list->a;
			counter++;
			if (counter == 2)
				break ;
		}
		else
		{
			ft_ra(my_list);
			tmp = my_list->a;
		}
	}
	mini_algorithm(my_list);
	finish_five(my_list);
}

t_support	*init_support(int max)
{
	t_support	*tmp;

	tmp = (t_support *)malloc(sizeof(t_support));
	tmp->flag = 0;
	tmp->max = max;
	tmp->next = 0;
	tmp->mid = (max / 2) + tmp->next;
	return (tmp);
}

t_stack	*find_stop_a(t_list *my_list)
{
	t_stack	*tmp;

	tmp = my_list->a;
	while (tmp->next != my_list->a)
		tmp = tmp->next;
	return (tmp);
}

t_stack	*find_stop_b(t_list *my_list)
{
	t_stack	*tmp;

	tmp = my_list->b;
	while (tmp->next != my_list->b)
		tmp = tmp->next;
	return (tmp);
}

void	ft_start(t_list *my_list, t_support *support)
{
	t_stack	*tmp;
	t_stack	*stop;

	tmp = my_list->a;
	stop = find_stop_a(my_list);
	while (tmp != stop)
	{
		tmp = my_list->a;
		if (tmp->order <= support->mid)
			ft_pb(my_list);
		else
			ft_ra(my_list);
	}
}

int	ft_finish(t_list *my_list)
{
	t_stack	*tmp;

	tmp = my_list->a;
	if (my_list->b != NULL)
		return (0);
	while (tmp->next != my_list->a)
	{
		if (tmp->order > tmp->next->order)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_max_b(t_list *my_list)
{
	t_stack	*tmp;
	int		max;

	max = 0;
	tmp = my_list->b;
	while (tmp->next != my_list->b)
	{
		if (tmp->order > max)
			max = tmp->order;
		tmp = tmp->next;
	}
	if (tmp->order > max)
		max = tmp->order;
	return (max);	
}

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

void	ft_sort_b(t_list *my_list, t_support *support)
{
	t_stack	*tmp;
	t_stack	*stop;

	tmp = my_list->b;
	if (!tmp)
		return ;	
	stop = find_stop_b(my_list);
	printf("stop for b: %d\n", stop->value);
	support->max = support->mid;
	printf("max b: %d\n", support->max);
	support->mid = ((support->max - support->next) / 2) + support->next;
	printf("mid for b: %d\n", support->mid);
	support->flag++;
	while (tmp != stop)
	{
		tmp = my_list->b;
		if (tmp->order == support->next || tmp->order >= support->mid)
			send_values_to_a(my_list, support);
		else
			ft_rb(my_list);
	}	
	if (my_list->b)
		send_values_to_a(my_list, support);
}

void	big_deal(int max, t_list *my_list)
{
	t_support	*support;

	support = init_support(max);
	ft_start(my_list, support);
	while (!ft_finish(my_list))
	{
		support->mid = ft_max_b(my_list);
		printf("current mid : %d\n", support->mid);
		while (my_list->b != NULL)
			ft_sort_b(my_list, support);
		printf("Stack A\n");
		print_list_order(my_list->a);
		printf("Stack B\n");
		print_list_order(my_list->b);
		exit(1);
	}
	printf("Stack A\n");
	print_list_order(my_list->a);
	printf("Stack B\n");
	print_list_order(my_list->b);
	free(support);
}

void	algorithm(int argc, t_list *my_list)
{
	int	i;

	i = argc - 1;
	if (i == 2)
		micro_algorithm(my_list);
	if (i == 3)
		mini_algorithm(my_list);
	else if (i == 4)
		medium_algorithm(my_list);
	else if (i == 5)
		above_algorithm(my_list);
	else if (i > 5)
		big_deal(i, my_list);
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
