#include "minishell.h"


static int	ft_update_status(int terminated, int wstatus)
{
	int		signaled;
	t_command	*selected;

	signaled = 0;
	if (terminated == g_data.fam[g_data.cmd_count - 1])
	{
		if (!WTERMSIG(wstatus))
			g_data.status = WEXITSTATUS(wstatus);
		else
		{
			signaled = 1;
			g_data.status = WTERMSIG(wstatus) + 128;
		}
	}
	selected = ft_find_command(terminated);
	if (selected)
	{
		if (selected->out != 1)
			close(selected->out);
		if (selected->in != 0)
			close(selected->in);
	}
	return (signaled);
}

static void	block_main_process(void)
{
	int	i;
	int	wstatus;
	int	signaled;

	/* No signals at first */
	i = 0;
	signaled = 0;
	/* Wait for each command and update status accordingly */
	while (i < g_data.cmd_count)
	{
		signaled += ft_update_status(wait(&wstatus), wstatus);
		i++;
	}
	/* If a process signaled, check the status */
	if (signaled)
	{
		/* If the process status is not recoverable */
		if (g_data.status == 131)
			ft_putstr_fd("Quit", STDOUT);
		/* Else output a new line */
		ft_putstr_fd("\n", STDOUT);
	}
}

/**
 * The function launches the processes for commands and executes them. It 
 * also deals with waiting for processes and handles interprocess signals 
 * properly.
 **/

static void	launch_processes(void)
{
	int	i;

	if (g_data.cmd_count == 1 && g_data.commands[0].args 
			&& ft_convert_builtin(g_data.commands[0].args[0]))
		ft_exec(&g_data.commands[0]);
	else
	{
		i = 0;
		while (i < g_data.cmd_count)
		{
			g_data.fam[i] = fork();
			if (g_data.fam[i] == 0)
			{
				if (!g_data.commands[i].args)
					exit(0);
				sig_default();
				ft_exec(&g_data.commands[i]);
			}
			i++;
		}
		sig_ignore();
		block_main_process();
		sig_init();
	}
}


/**
 * The function is supposed to parse the input and execute the commands.
 **/

void	parse_and_execute(char *line)
{
	get_tokens(line);
	if (!g_data.tokens->content || !g_data.tokens->content[0])
	{
		ft_free_tokens();
		return ;
	}
	parse_commands();
	if (!g_data.commands || launch_heredoc())
	{
		ft_free_tokens();
		ft_free_commands(g_data.commands);
		return ;
	}
	g_data.fam = ft_calloc(g_data.cmd_count, sizeof(pid_t));
	launch_processes();
	ft_free_commands(g_data.commands);
	ft_free_fam();
	ft_free_tokens();
}
