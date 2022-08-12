#include "minishell.h"

static void	ft_close_descriptors(void)
{
	int	i;

	i = 0;
	while (i < g_data.cmd_count)
	{
		if (g_data.commands[i].in != 0)
			close(g_data.commands[i].in);
		if (g_data.commands[i].out != 1)
			close(g_data.commands[i].out);
		i++;
	}
}

static int	ft_exec_builtin(t_command *cmd)
{
	int	ret;

	ret = ft_convert_builtin(cmd->args[0]);
	// if (ret == _ECHO)
	// 	g_data.status = ft_echo(cmd);
	// else if (ret == _CD)
	// 	g_data.status = ft_cd(cmd);
	// else if (ret == _PWD)
	// 	g_data.status = ft_pwd(cmd);
	// else if (ret == _EXPORT)
	// 	g_data.status = ft_export(cmd);
	// else if (ret == _UNSET)
	// 	g_data.status = ft_unset(cmd);
	// else if (ret == _ENV)
	// 	g_data.status = ft_env(cmd);
	if (ret == _EXIT)
		ft_exit(cmd);
	if (ret)
		return (0);
	return (-1);
}


static void	ft_traverse_binaries(t_command *cmd)
{
	char	**paths;
	char	*temp;
	int		i;

	if (ft_exec_builtin(cmd) == -1)
	{
		execve(cmd->args[0], cmd->args, ft_env_to_array(g_data.env));
		if (ft_getenv("PATH"))
		{
			paths = ft_split(ft_getenv("PATH"), ':');
			i = 0;
			while (paths[i])
			{
				temp = ft_strjoin3(paths[i], "/", cmd->args[0]);
				execve(temp, cmd->args, ft_env_to_array(g_data.env));
				free(temp);
				i++;
			}
			ft_free_matrix(paths);
			ft_minishell_error(ft_strjoin(cmd->args[0], ": command not found"));
		}
		else
			ft_minishell_error(ft_strjoin(cmd->args[0], ": No such file or directory"));
	}
}


void	ft_exec(t_command *cmd)
{
	if (!ft_convert_builtin(cmd->args[0]) || g_data.cmd_count != 1)
	{
		if (dup2(cmd->out, STDOUT) == -1 || dup2(cmd->in, STDIN) == -1)
		{
			perror("minishell: failed dup2");
			exit(1);
		}
		ft_close_descriptors();
		cmd->out = 1;
	}
	if (cmd->args[0][0] == '/')
	{
		execve(cmd->args[0], cmd->args, ft_env_to_array(g_data.env));
		ft_minishell_error(ft_strjoin(cmd->args[0], ": No such file or directory"));
	}
	else
		ft_traverse_binaries(cmd);
	if (g_data.cmd_count != 1 || !ft_convert_builtin(cmd->args[0]))
	{
		if (ft_convert_builtin(cmd->args[0]))
			exit(g_data.status);
		exit(UNKNOWN_COMMAND);
	}
}

