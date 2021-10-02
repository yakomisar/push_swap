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


#endif