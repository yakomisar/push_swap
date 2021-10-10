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

#endif