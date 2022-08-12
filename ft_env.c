#include "minishell.h"

void	init_env(char **environ)
{
	int	temp;

	g_data.env = (t_vector *)malloc(sizeof(t_vector));
	g_data.env->capacity = get_num_env(environ) + 1;
	temp = g_data.env->capacity;
	printf("Number of env variables: %d\n", g_data.env->capacity);
	g_data.env->content = (char **)malloc(g_data.env->capacity * sizeof(char*));
	g_data.env->size = 0;
	while (g_data.env->size < temp - 1)
	{
		ft_vector_add(environ[g_data.env->size]);
	}
	g_data.env->content[g_data.env->size] = NULL;
	//g_data.env->size++;
	ft_vector_print(g_data.env);
	// ft_vector_add(g_data.env, "Let's see");
	// ft_vector_print(g_data.env);
}

void	ft_vector_print(t_vector *vector)
{
	int	i;

	i = 0;
	// ft_putstr_fd("Vector size: ", 1);
	// ft_putnbr_fd(vector->size, 1);
	// ft_putchar_fd('\n', 1);
	//printf("%s\n", vector->content[0]);
	while (i < vector->size)
		printf("%s ", vector->content[i++]);
	printf("\nSIZE: %d\n", vector->size);
	printf("CAPACITY: %d\n", vector->capacity);

}

// int	ft_exists_ident(char *ident)
// {

// 	if (find_env_index(ident) >= 0)
// 		return (1);
// 	return (0);

// }

int	find_env_index(char	*ident)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(ident);
	while (i < g_data.env->size)
	{
		if (!ft_strncmp(g_data.env->content[i], ident, len))
		{
			if (g_data.env->content[i][len + 1] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

void change_env_value(char *str, int index)
{
	free(g_data.env->content[index]);
	g_data.env->content[index] = (char *)malloc(ft_strlen(str));
	ft_memcpy(g_data.env->content[index], str, ft_strlen(str));
}

void	remove_env(char *ident)
{
	int	index;

	index = find_env_index(ident);
	if (index >= 0)
	{
		free(g_data.env->content[index]);
		g_data.env->size--;
		while (index < g_data.env->size)
		{
			g_data.env->content[index] = g_data.env->content[index + 1];
			index++;
		}
		g_data.env->content[index] = NULL;
	}
}

char	*ft_get_env(char *ident)
{
	int	index;

	index = find_env_index(ident);
	if (index >= 0)
		return ft_substr(g_data.env->content[index], ft_strlen(ident) + 1, ft_strlen(g_data.env->content[index]));
	return (NULL);
}

char	*ft_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i != ft_strlen(str))
		return (ft_substr(str, 0, i));
	return (NULL);
}

void	ft_vector_reallocate(t_vector *vector)
{
	int		i;
	char	**copy;
	//int		size;

	i = 0;
	//size = vector->size;
	copy = (char **)malloc(2 * vector->capacity * sizeof(char*));
	while (i < vector->size)
	{
		//ft_putstr_fd("OOOf\n", 1);
		copy[i] = vector->content[i];
		//free(vector->content[i]);
		i++;
	}
	vector->capacity = 2 * vector->capacity;
	free(vector->content);
	vector->content = copy;
	//vector->content = (char **)malloc(vector->capacity * sizeof(char*));
	//i = 0;
	//vector->size = 0;
	//ft_putstr_fd("before while", 1);
	// while (i < size)
	// {
	// 	ft_putstr_fd("The copy: ", 1);
	// 	ft_putstr_fd(copy[i], 1);
	// 	ft_putchar_fd('\n', 1);
	// 	ft_token_add(copy[i], vector);
	// 	i++;
	// }
	//ft_putstr_fd("after while", 1);
	while (i < vector->capacity)
	{
		vector->content[i] = NULL;
		i++;
	}
	//free(copy);
}

void	ft_token_add(char *str, t_vector *vector)
{
	int i;

	i = 0;
	// ft_putstr_fd("Size: ", 1);
	// ft_putnbr_fd(vector->size, 1);
	// ft_putchar_fd('\n', 1);
	// ft_putstr_fd("The string right before malloc: ", 1);
	// ft_putstr_fd(str, 1);
	// ft_putchar_fd('\n', 1);
	if (vector->size == vector->capacity - 1)
	{
		// while (i < vector->size)
		// 	ft_putstr_fd(vector->content[i++], 1);
		ft_vector_reallocate(vector);
	}
	//ft_putstr_fd("Passed reallocation part\n", 1);
	// vector->content[vector->size] = (char *)malloc(ft_strlen(str));
	// ft_memcpy(vector->content[vector->size], str, ft_strlen(str));
	vector->content[vector->size] = ft_strdup(str);
		// ft_putstr_fd(g_data.env->content[g_data.env->size], 1);
		// ft_putchar_fd('\n', 1);
	ft_putstr_fd("Vector size: ", 1);
	ft_putnbr_fd(vector->size, 1);
	ft_putchar_fd('\n', 1);
	//printf("ADDRESS: %d\n", &vector);
	vector->size++;
}

void	ft_vector_add(char *str)
{
	char	*ident;
	int		index;

	ident = ft_identifier(str);
	index = find_env_index(ident);
	if (index >= 0)
	{
		ft_putstr_fd("OOOOOOPS", 1);
		change_env_value(str, index);
	}
	else{
		ft_token_add(str, g_data.env);
		// if (g_data.env->size == g_data.env->capacity)
		// 	ft_vector_reallocate(g_data.env);
		// g_data.env->content[g_data.env->size] = (char *)malloc(ft_strlen(str));
		// ft_memcpy(g_data.env->content[g_data.env->size], str, ft_strlen(str));
		// // ft_putstr_fd(g_data.env->content[g_data.env->size], 1);
		// // ft_putchar_fd('\n', 1);
		// g_data.env->size++;
	}
	free(ident);
}


int	get_num_env(char **environ)
{
	int i;

	i = 0;
	while (environ[i])
		i++;
	return (i);
}