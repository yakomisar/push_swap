/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:12:12 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/05 19:25:41 by jmacmill         ###   ########.fr       */
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

t_stack	*init_stack(t_stack *a, int num)
{
	t_stack	*tmp;
	void	*p;

	if (a == NULL)
	{
		a = (t_stack *)malloc(sizeof(t_stack));
		a->value = num;
		a->order = 0;
		a->flag = 0;
		a->next = a;
		return (a);
	}
	else
	{
		tmp = (t_stack *)malloc(sizeof(t_stack));
		p = a->next;
		a->next = tmp;
		tmp->value = num;
		tmp->order = 0;
		tmp->flag = 0;
		tmp->next = p;
	}
	return (a);
}



int	ft_strchr_ps(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] >= 58 && str[i][j] <= 127)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
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

void	check_errors(int argc, char **argv, t_stack *a)
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
		a = init_stack(a, num);
		i--;
		if (i == 0)
			a = a->next;
	}
	print_list(a);
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

void	check_duplicates(t_stack *a)
{
	t_stack	*tmp;
	int		len;

	tmp = a;
	len = 0;
	while (tmp->next != a)
	{
		if (ft_check(a, tmp->value, len))
			get_error();
		tmp = tmp->next;
		len++;
	}
}

void	push_swap(int argc, char **argv, t_stack *a)
{
	check_errors(argc, argv, a);
	check_duplicates(a);
	// check_sort();
	// algos();
}

// int	main(int argc, char **argv)
int	main()
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	char *argv[4] = {"x", "1", "2", "3"};
	if (argc > 2)
		push_swap(argc, argv, a);
	return (0);
}