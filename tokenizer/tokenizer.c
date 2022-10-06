/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/05 23:57:40 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_tokenizer(t_data *data, char *n_line, int i, t_types typ)
{
	data->typ = typ;
	data->n_line = n_line;
	data->i_line = i;
	data->index += i;
}

static int	is_pipe(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != '|')
		return (0);
	while (n_line[i] == '|')
		i++;
	ft_init_tokenizer(data, &n_line[i], i, PIPE);
	return (1);
}

static int	is_space(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != ' ' && !(n_line[i] >= 9 && n_line[i] <= 13))
		return (0);
	while (n_line[i] == ' ' || (n_line[i] >= 9 && n_line[i] <= 13))
		i++;
	ft_init_tokenizer(data, &n_line[i], i, W_SPACE);
	return (1);
}

char	is_word_typ_changer(t_data *data, char *n_line, int *typ)
{
	char	c;

	c = n_line[data->i];
	if (n_line[0] == c)
	{
		if (c == '\'')
			*typ = S_QUOT;
		else if (c == '\"')
			*typ = D_QUOT;
	}
	return (c);
}

void	is_word_helper(t_data *data, char *n_line, int *typ)
{
	char	c;
	int		quote;

	quote = 0;
	if (n_line[data->i] == '\"' || n_line[data->i] == '\'')
	{
		c = is_word_typ_changer(data, n_line, typ);
		quote++;
		data->i++;
		while (n_line[data->i])
		{
			if (n_line[data->i] == c)
				quote++;
			if ((n_line[data->i] == ' ' || (n_line[data->i] >= 9 && n_line[data->i] <= 13) ||\
						n_line[data->i] == '|' || n_line[data->i] == '>' || n_line[data->i] == '<')\
					&& quote % 2 == 0)
				break ;
			data->i++;
		}
		if (n_line[data->i] == c)
			data->i++;
	}
}

static int	is_word(t_data *data, char *n_line)
{
	char	*sp;
	int		typ;

	sp = "<|>$\t\v\r\f ";
	data->i = 0;
	typ = WRD;
	while (n_line[data->i])
	{
		data->j = 0;
		is_word_helper(data, n_line, &typ);
		while (sp[data->j])
		{
			if (n_line[data->i] == sp[data->j])
				break ;
			data->j++;
		}
		if (n_line[data->i] == sp[data->j])
			break ;
		data->i++;
	}
	if (data->i == 0)
		return (0);
	ft_init_tokenizer(data, &n_line[data->i], data->i, typ);
	return (1);
}

void	*spaces_first(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 0)
		return (0);
	return (&str[i]);
}

char	*spaces_takeoff(t_data *data, char *str)
{
	int		len;
	char	*ptr;
	int		i;

	if (!str)
		return (0);
	str = spaces_first(str);
	if (!str)
		return (0);
	len = ft_strlen(str) - 1;
	if (str[len] == ' ' || (str[len] >= 9 && str[len] <= 13))
	{
		while (str[len] == ' ' || (str[len] >= 9 && str[len] <= 13))
			len--;
	}
	else
		return (str);
	ptr = malloc(sizeof(char) * len + 2);
	i = 0;
	while (i <= len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

void	init_var_tokenizer(t_data *data)
{
	data->index = 0;
	data->check = 1;
	data->error_lexer = 0;
	data->chk_hrdoc = 0;
	ft_init_tokenizer(data, data->beg_line, 0, 0);
}

void	tokenizer(t_data *data)
{
	data->beg_line = spaces_takeoff(data, data->line);
	if (!data->beg_line)
	{
		data->error_lexer = 1;
		return ;
	}
	init_var_tokenizer(data);
	while (*data->beg_line)
	{
		if (is_word(data, data->n_line) || is_space(data, data->n_line) || \
				is_d_quote(data, data->n_line) || is_dolla(data, data->n_line) || \
				is_pipe(data, data->n_line) || is_s_quote(data, data->n_line) || \
				is_i_redirection(data, data->n_line) || \
				is_o_redirection(data, data->n_line))
		{
			if (add_node(data, data->typ))
			{
				data->chk_dolla = 258;
				data->error_lexer = 1;
				return ;
			}
		}
	}
	if (lexer_pt2(data))
	{
		data->chk_dolla = 258;
		data->error_lexer = 1;
		return ;
	}
	parser(data);
}
