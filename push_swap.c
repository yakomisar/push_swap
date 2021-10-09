/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:12:12 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/09 17:42:26 by jmacmill         ###   ########.fr       */
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
		tmp->value = my_list->a->value;;
		tmp->order = my_list->a->order;
		tmp->flag = my_list->a->flag;
		tmp->next = p;
	}
	return (my_list->b);
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

void	ft_sa(t_list *my_list)
{
	int	tmp_value;
	int	tmp_order;
	int	tmp_flag;
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
	int	tmp_value;
	int	tmp_order;
	int	tmp_flag;
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
		my_list->a= my_list->a->next;
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
		//printf("1\n");
		ft_sa(my_list), ft_ra(my_list);
	}
	else if (a->value > a->next->value
		&& a->value > a->next->next->value)
	{
		if (a->next->value < a->next->next->value)
		{
			//printf("2\n");
			ft_ra(my_list);
		}
		else
		{
			//printf("3\n");
			ft_sa(my_list), ft_rra(my_list);
		}
	}
	else
	{
		if (a->next->value < a->next->next->value)
		{
			//printf("4\n");
			// print_list(my_list->a);
			ft_sa(my_list);
		}
		else
		{
			//printf("5\n");
			ft_rra(my_list);
		}
	}
}

void	*deletelem(t_stack *lst)
{
	t_stack *temp;

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
	return(temp);
}

void	ft_pb(t_list *my_list)
{
	my_list->b = init_stack_b(my_list);
	my_list->a = deletelem(my_list->a);
	if (my_list->a != NULL)
		my_list->a = my_list->a->next;
	write(1, "pb\n", 3);
}

t_stack	*init_stack_a_for_pa(t_list *my_list, int num)
{
	t_stack	*tmp;
	void	*p;
	int	tmp_value;

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
		tmp_value = my_list->a->value;
		my_list->a->value = my_list->a->next->value;
		my_list->a->next->value = tmp_value;
	}
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
	// printf("sorting out\n");
	// print_list(my_list->a);
	// printf("\nsorted\n");
	// print_list(my_list->b);
	mini_algorithm(my_list);
	// print_list(my_list->a);
	ft_pa(my_list);
	// print_list(my_list->a);
	//print_list_order(my_list->b);
}

void	finish_five(t_list *my_list)
{
	printf("List 0 b:\n");
	print_list_order(my_list->b);
	if (my_list->b->value < my_list->b->next->value)
	{
		ft_sb(my_list);
		printf("List 1 b:\n");
		print_list_order(my_list->b);
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
			printf("List init 0 b:\n");
			print_list_order(my_list->b);
			ft_pb(my_list);
			printf("List init 1 b:\n");
			print_list_order(my_list->b);
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
	printf("List a:\n");
	print_list_order(my_list->a);
	printf("List b:\n");
	print_list_order(my_list->b);
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