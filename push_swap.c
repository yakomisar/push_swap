/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:12:12 by jmacmill          #+#    #+#             */
/*   Updated: 2021/10/10 20:11:55 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	free_all(my_list);
}

int	main(int argc, char **argv)
{
	if (argc > 2)
		push_swap(argc, argv);
	return (0);
}
