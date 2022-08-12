#include "minishell.h"

int	ft_err(char *str)
{
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	return (1);
}