#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_stack
{
	int				value;
	int				order;
	int				flag;
	struct s_stack	*next;

}	t_stack;

typedef struct s_list
{
	t_stack	*a;
	t_stack	*b;
}				t_list;

typedef struct s_support
{
	int	next;
	int	mid;
	int	max;
	int	flag;
}	t_support;

void		micro_algorithm(t_list *my_list);
void		mini_algorithm(t_list *my_list);
void		medium_algorithm(t_list *my_list);
void		above_algorithm(t_list *my_list);
void		big_deal(int i,t_list *my_list);
void		free_all(t_list *my_list);
void		push_swap(int argc, char **argv);
void		list_init(t_list *mylist);
void		check_errors(int argc, char **argv, t_list *my_list);
void		check_duplicates(t_list *my_list);
void		check_sort(t_list *my_list);
void		get_position(int argc, t_list *my_list);
int			ft_check(t_stack *a, int value, int len);
int			is_sort(t_list *my_list);
void		send_values_to_a(t_list *my_list, t_support *support);
void		ft_pa(t_list *my_list);
void		ft_swap_b(t_list *my_list);
void		ft_rr(t_list *my_list);
void		ft_rrr(t_list *my_list);
void		ft_start(t_list *my_list, t_support *support);
int			ft_finish(t_list *my_list);
int			ft_max_b(t_list *my_list);
void		send_values_to_b(t_list *my_list, t_support *support);
void		big_deal(int max, t_list *my_list);
t_stack		*init_stack_a(t_list *my_list, int num);
t_stack		*init_stack_b(t_list *my_list);
void		list_init(t_list *mylist);
t_stack		*init_stack_a_for_pa(t_list *my_list, int num);
void		*deletelem(t_stack *lst);
int			stack_counter(t_stack *stack);
void		fresh_stack_a(t_list *my_list);
void		fresh_stack_b(t_list *my_list);
t_stack		*find_stop_a(t_list *my_list);
t_stack		*find_stop_b(t_list *my_list);
void		ft_sort_b(t_list *my_list, t_support *support);
void		ft_sort_a(t_list *my_list, t_support *support);
void		ft_rb(t_list *my_list);
void		ft_sb(t_list *my_list);
void		ft_rrb(t_list *my_list);
void		ft_pb(t_list *my_list);
int			ft_atoi(const char *str);
void		get_error_wo(t_list *my_list);
void		get_error(t_list *my_list);
int			ft_isdigit(int c);
int			ft_ischar(char *str);
void		finish_five(t_list *my_list);
void		above_algorithm(t_list *my_list);
void		ft_sa_hidden(t_list *my_list);
void		ft_sa(t_list *my_list);
void		ft_ra(t_list *my_list);
void		ft_rra(t_list *my_list);
void		ft_swap_a(t_list *my_list);
t_support	*init_support(int max);

#endif