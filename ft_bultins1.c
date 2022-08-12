#include "minishell.h"


static void	terminate(int exit_code)
{
	if(g_data.cmd_count == 1)
	{
		if (!g_data.status)
			exit(exit_code);
	}
	else
	{
		if (!exit_code)
			exit(g_data.status);
		exit(exit_code);
	}
}

void	ft_exit(t_command *cmd)
{
	int	exit_code;

	g_data.status = 0;
	exit_code = 0;
	if (g_data.cmd_count == 1)
		ft_putstr_fd("exit\n", STDERR);
	if (ft_matrixlen(cmd->args) == 1)
		exit(0);
	if (!ft_isnum(cmd->args[1]))
	{
		exit_code = 255;
		ft_minishell_error("minisell: exit: numeric argument required");
	}
	else
	{
		if (ft_matrixlen(cmd->args) == 2)
			exit_code = ft_atoi(cmd->args[1]);
		else
			g_data.status = ft_minishell_error("minishell: exit: too many arguments");
	}
	terminate(exit_code);
}