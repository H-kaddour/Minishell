/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:48:57 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 11:08:09 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_init_tokenizer(t_data *data, char *n_line, int i, t_types typ)
{
	data->typ = typ;
	data->n_line = n_line;
	data->i_line = i;
	data->index += i;
}

void	is_quote_helper(t_data *data, int c, char *n_line)
{
	data->i++;
	while (n_line[data->i])
	{
		if (n_line[data->i] == c)
		{
			data->i++;
			while (n_line[data->i])
			{
				if (n_line[data->i] == ' ' || \
						(n_line[data->i] >= 9 && n_line[data->i] <= 13) \
						|| n_line[data->i] == '|' || n_line[data->i] == '>' \
						|| n_line[data->i] == '<')
				{
					ft_init_tokenizer(data, &n_line[data->i], data->i, S_QUOT);
					return ;
				}
				data->i++;
				if (n_line[data->i] == c)
					break ;
			}
		}
		data->i++;
	}
	ft_init_tokenizer(data, &n_line[data->i], data->i, D_QUOT);
}

static char	is_word_typ_changer(t_data *data, char *n_line, int *typ)
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
			if ((n_line[data->i] == ' ' || (n_line[data->i] >= 9 && \
							n_line[data->i] <= 13) || n_line[data->i] == '|' || \
						n_line[data->i] == '>' || n_line[data->i] == '<') \
					&& quote % 2 == 0)
				break ;
			data->i++;
		}
		if (n_line[data->i] == c)
			data->i++;
	}
}
