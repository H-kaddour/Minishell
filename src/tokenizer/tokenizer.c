/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 12:08:24 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	*spaces_first(char *str)
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

static int	loop_reversely(char *str, int len)
{
	while (str[len] == ' ' || (str[len] >= 9 && str[len] <= 13))
		len--;
	return (len);
}

static char	*spaces_takeoff(t_data *data, char *str)
{
	int		len;
	char	*ptr;
	int		i;

	str = spaces_first(str);
	if (!str)
		return (0);
	len = ft_strlen(str) - 1;
	if (str[len] == ' ' || (str[len] >= 9 && str[len] <= 13))
		len = loop_reversely(str, len);
	else
		return (str);
	ptr = malloc(sizeof(char) * len + 2);
	if (!ptr)
		error_malloc();
	i = 0;
	while (i <= len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

static int	tokenizer_init(t_data *data)
{
	data->beg_line = spaces_takeoff(data, data->line);
	if (!data->beg_line)
	{
		data->error_lexer = 1;
		return (1);
	}
	init_var_tokenizer(data);
	return (0);
}

void	tokenizer(t_data *data)
{
	if (tokenizer_init(data))
		return ;
	while (*data->beg_line)
	{
		if (is_word(data, data->n_line) || is_s_quote(data, data->n_line) || \
				is_d_quote(data, data->n_line) || is_space(data, data->n_line) \
				|| is_dolla(data, data->n_line) || is_pipe(data, data->n_line) \
				|| is_i_redirection(data, data->n_line) || \
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
	parser_phase(data);
}
