#include "minishell.h"

t_whole	g_data;

int main(int argc, char **arvg, char **environ)
{
	// int i;
	// i = 0;
	// while (environ[i])
	// 	printf("%s\n", environ[i++]);
	char *env[] = {"we=are", "the=champions", "my=friend", "maybe=not", NULL};
	//printf("NUM: %d", get_num_env(env));
	// init_env(env);
	//char *ident = ft_identifier("we=esim");
	//printf("Exists? %d", find_env_index(ident));
	// ft_vector_add(g_data.env, "mine=notfriend");
	// ft_vector_add(g_data.env, "maybe=oyyy");
	// remove_env("maybe");
	// ft_vector_print(g_data.env);

	init_env(environ);
	//printf("%s", get_env());
	
	char *line;
	while (1)
	{
		line = readline("\001\033[1;35m\002Minishell> \001\033[1;0m\002");
		if (!parse(line))
			ft_err("Parsing failed");
		ft_vector_print(g_data.tokens);
		//printf("%s\n", line);
		free(g_data.tokens);
		free(line);
	};
}