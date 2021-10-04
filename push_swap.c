/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:12:12 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/04 22:03:06 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	get_error(t_stack *a, t_stack *b)
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
		if (!ft_isdigit(str[a]))
			return (1);
		a++;
	}
	return (0);
}

void	init_stack(t_stack *a, int num)
{
	t_stack	*tmp;
	t_stack	*next;

	if (a == NULL)
	{
		a = (t_stack *)malloc(sizeof(t_stack));
		a->value = num;
		a->order = 0;
		a->flag = 0;
		a->next = a;
	}
	else
	{
		tmp = (t_stack *)malloc(sizeof(t_stack));
		next = a->next;
		a->next = tmp;
		tmp->value = num;
		tmp->order = 0;
		tmp->flag = 0;
		tmp->next = next;
	}
}

void	check_errors(int argc, char **argv, t_stack *a, t_stack *b)
{
	int			i;
	long int	num;
	
	i = 1;
	while (argv[i])
	{
		num = ft_atoi(argv[i]);
		if (num > 2147483647 || num < -2147483648)
			get_error(a, b);
		if (num < 0 || argv[i][0] == '+')
		{
			if (!ft_isdigit(argv[i][1]))
				get_error(a, b);
		}
		else if (!ft_isdigit(*argv[i]))
			get_error(a, b);
		if (!ft_ischar(argv[i]))
			get_error(a, b);
		init_stack(a, num);
		i++;
	}
}

void	push_swap(int argc, char **argv, t_stack *a, t_stack *b)
{
	check_errors(argc, argv, a, b);
	check_duplicates();
	check_sort();
	algos();
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	if (argc > 2)
		push_swap(argc, argv, a, b);
	return (0);
}