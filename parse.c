#include "minishell.h"

int	parse(char *line)
{
	g_data.tokens = (t_vector *)malloc(sizeof(t_vector));
	g_data.tokens->capacity = 2;
	g_data.tokens->content = (char **)malloc(g_data.tokens->capacity * sizeof(char*));

	g_data.tokens->content[0] = NULL;
	g_data.tokens->content[1] = NULL;
	g_data.tokens->size = 0;
	init_tokens(line); 
	g_data.tokens->quoted = ft_calloc(g_data.tokens->capacity, sizeof(int));
	check_quotes();
	//free(g_data.tokens);
	return (1);
}

void	check_quotes()
{
	int	i;

	i = 0;
	while (i < g_data.tokens->size)
	{
		check_quotes_token(i);
		i++;
	}
}

void	check_quotes_token(int ind)
{
	int	i;
	int j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(g_data.tokens->content[ind]);
	while (i < len && j < len)
	{
		if (g_data.tokens->content[ind][i] == '\'')
		{	
			j++;
			while (j < len && g_data.tokens->content[ind][j] != '\'')
				j++;
			if (j < len && g_data.tokens->content[ind][i] == g_data.tokens->content[ind][j])
			{
				g_data.tokens->quoted[ind] = 1;
				take_out_quotes(i, j, ind);
				j--;
				i = j;
			}
		}
		else if(g_data.tokens->content[ind][i] == '\"')
		{
			j++;
			while (j < len && g_data.tokens->content[ind][j] != '\"')
				j++;
			if (j < len && g_data.tokens->content[ind][i] == g_data.tokens->content[ind][j])
			{
				g_data.tokens->quoted[ind] = 1;
				j = expand_if_needed(i, j, ind);
				take_out_quotes(i, j, ind);
				j--;
				i = j;
			}
		}
		else
			i++;
		j++;
	}
}

int	expand_if_needed(int i, int j, int ind)
{
	// int		temp;
	// char	*prev;
	// char	*post;
	// char	*mid;

	// temp = i;
	// while (temp < j)
	// {
	// 	if (g_data.tokens->content[ind][temp] == '$')
	// 	{
	// 		mid = ft_substr(g_data.tokens->content[ind], temp + 1, j - temp);
	// 		mid = ft_get_env(mid);

	// 	}
	// 	else
	// 		i++;
	// }
	return (1);
}

void	take_out_quotes(int i, int j, int ind)
{
	int		len;
	char	*prev;
	char	*post;
	char	*mid;

	ft_putstr_fd("i: ", 1);
	ft_putnbr_fd(i, 1);
	ft_putchar_fd('\n', 1);

	ft_putstr_fd("j: ", 1);
	ft_putnbr_fd(j, 1);
	ft_putchar_fd('\n', 1);
	len = ft_strlen(g_data.tokens->content[ind]);
	
	prev = ft_substr(g_data.tokens->content[ind], 0, i);
	post = ft_substr(g_data.tokens->content[ind], j + 1, len - j - 1);
	mid = ft_substr(g_data.tokens->content[ind], i + 1, j - i - 1);
	ft_putstr_fd("PREV: ", 1);
	ft_putstr_fd(prev, 1);
	ft_putchar_fd('\n', 1);

	ft_putstr_fd("MID: ", 1);
	ft_putstr_fd(mid, 1);
	ft_putchar_fd('\n', 1);

	ft_putstr_fd("POST: ", 1);
	ft_putstr_fd(post, 1);
	ft_putchar_fd('\n', 1);
	free(g_data.tokens->content[ind]);
	g_data.tokens->content[ind] = ft_strjoin(prev, mid);
	g_data.tokens->content[ind] = ft_strjoin(g_data.tokens->content[ind], post);
	free(prev);
	free(post);
	free(mid);
}

void	add_token(int i, int j, char *line)
{
	char	*token;

	//printf("i: %d, j: %d\n", i, j);
	ft_putstr_fd("\nADDING TOKEN\n", 1);
	ft_putstr_fd("i: ", 1);
	ft_putnbr_fd(i, 1);
	ft_putstr_fd(", j: ", 1);
	ft_putnbr_fd(j, 1);
	ft_putchar_fd('\n', 1);

	// if (line[i] == '\"' && line[j] == '\"' && i != j)
	// {	
	// 	if (i != j)
	// 		j++;
	// 	//ft_putstr_fd("Expand if needed\n", 1);
	// }
	// else if (line[i] == '\'' && line[j] == '\'' && i != j)
	// {
	// 	j++;
	// }
	token = ft_substr(line, i, j - i + 1);
	ft_putstr_fd("Substring separated: ", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd("|\n", 1);
	// ft_putstr_fd("The string right before malloc: ", 1);
	// ft_putstr_fd(token, 1);
	// ft_putchar_fd('\n', 1);
	ft_token_add(token, g_data.tokens);
	// if (g_data.tokens->size == 1)
	// 	g_data.tokens->content[g_data.tokens->size] = NULL;
	ft_putstr_fd("\nADDED\n", 1);
	free(token);
}

int	init_tokens(char *line)
{
	int temp;
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	//g_data.tokens = (t_vector *)malloc(sizeof(t_vector));
	while (j < len)
	{
		if (line[j] == ' ' || line[j] == '\t' || j == len - 1)
		{
			if (j == len - 1)
			{
				ft_putnbr_fd(j, 1);
				add_token(i, j, line);
				return (1);
			}
			else if (i != j)
				add_token(i, j - 1, line);
			while (j < len && (line[j] == ' ' || line[j] == '\t'))
			{	
				ft_putstr_fd("First while: j = ", 1);
				ft_putnbr_fd(j, 1);
				ft_putchar_fd('\n', 1);
				j++;
			}
			i = j;
		}
		if (line[j] == '\'' || line[j] == '\"')
		{
			temp = j;
			j++;
			if (line[i] == '\'')
				while (line[j] != '\'' && j < len)
					j++;
			if (line[i] == '\"')
				while (line[j] != '\"' && j < len)
					j++;
			// if (j < len && line[j] == line[i])
			// {
			// 	add_token(i, j, line);
			// 	i = j + 1;
			// }
			if (j < len && line[j] != line[temp])
				j--;
		}
		else if (line[j] == '<' || line[j] == '>' || line[j] == '|')
		{
			add_token(i, j - 1, line);
			i = j;
			if ((j + 1 < len && line[j] == line[j + 1]) && (line[j] == '>' || line[j] == '<'))
				j++;
			add_token(i, j, line);
			i = j + 1;
			if (j + 1 < len && (line[j+1] == '<' || line[j+1] == '>' || line[j+1] == '|'))
			{
				ft_putstr_fd("WRONG", 1);
				return (0);
			}	
		}
		j++;
	}
	return (1);
}