#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <termios.h>
# include <readline/history.h>
# include "libft/libft.h"


# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define _EXIT 7


# define SUCCESS 0
# define ERROR 1
# define SYNTAX_ERROR 258
# define UNKNOWN_COMMAND 127


typedef struct s_command
{
	char	**args;
	int		in;
	int		out;
	char	*stop_word;
}	t_command;

typedef struct s_vector
{
	
	int		size;
	int		capacity;
	char	**content;
	int		*quoted;
	
}	t_vector;

typedef struct s_whole
{
	t_vector	*env;
	t_vector	*tokens;
	t_command	*commands;
	pid_t	*fam;
	int			status;
	int			cmd_count;
}	t_whole;


/* UTILS */
int	ft_count_commands(char **token_array);
int	ft_heredoc_size(char **token_array);
void	ft_free_commands(t_cmd *cmds);
void	ft_free_matrix(char **matrix);
int     ft_convert_builtin(char *builtin);
int	init(t_mini *mini, char **env);
char	**ft_array_copy(char **args);
int	ft_minishell_error(char *msg);
int	ft_matrixlen(char **matrix);
t_cmd	*ft_find_command(pid_t pid);
int	ft_token_num(char *line);
int	ft_args_size(int index);
void	ft_free_tokens(void);
int	ft_isnum(char *num);
int	ft_isspace(char c);
void	ft_free_fam(void);
int	ft_abs(int nb);


extern t_whole g_data;

void	init_env(char **environ);
void	ft_vector_reallocate(t_vector *vector);
int		get_num_env(char **environ);
void	ft_vector_add(char *str);
void	ft_vector_print(t_vector *vector);
char	*ft_identifier(char *str);
//int		ft_exists_ident(char *ident);
int		find_env_index(char	*ident);
char	*ft_get_env(char *ident);
void	change_env_value(char *str, int index);
void	remove_env(char *ident);
int		parse(char *line);
int		init_tokens(char *line);
int		ft_err(char *str);
void	add_token(int i, int j, char *line);
void	ft_token_add(char *str, t_vector *vector);
void	check_quotes();
void	check_quotes_token(int i);
int		expand_if_needed(int i, int j, int ind);
void	take_out_quotes(int i, int j, int ind);

void	ft_exit(t_command *cmd);


/* SIGNALS */
void	sig_init(void);
void	sig_default(void);
void	sig_ignore(void);
void	sig_heredoc(void);

/* PARSING */
void	parse_and_execute(char *line);
void	get_tokens(char *line);
int	extract_token(char *line, char **token, char **quote);
int	extract_argument(t_command *cmd, int *index);
void	ft_append_token(char **token, char *line, int len, int expand);
void	parse_commands(void);
int	check_pipe(char **args, int *index);
char	*ft_refine_line(char *line);


/* EXECUTING */
void	ft_exec(t_command *cmd);


#endif