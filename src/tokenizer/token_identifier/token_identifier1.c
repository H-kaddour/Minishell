/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:48:01 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 11:07:48 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_s_quote(t_data *data, char *n_line)
{
	data->i = 0;
	if (n_line[data->i] != '\'')
		return (0);
	else if (n_line[data->i] == '\'')
		is_quote_helper(data, '\'', n_line);
	return (1);
}

int	is_d_quote(t_data *data, char *n_line)
{
	data->i = 0;
	if (n_line[data->i] != '\"')
		return (0);
	else if (n_line[data->i] == '\"')
		is_quote_helper(data, '\"', n_line);
	return (1);
}

int	is_pipe(t_data *data, char *n_line)
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

int	is_space(t_data *data, char *n_line)
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

int	is_word(t_data *data, char *n_line)
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
