/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:55:34 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 11:07:55 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_o_redirection(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != '<')
		return (0);
	while (n_line[i] == '<')
	{
		if (n_line[1] != '<')
		{
			i++;
			ft_init_tokenizer(data, &n_line[i], i, I_TRNC);
			return (1);
		}
		i++;
	}
	if (n_line[i] != '<')
	{
		ft_init_tokenizer(data, &n_line[i], i, I_APEND);
		data->chk_hrdoc = 1;
	}
	return (1);
}

int	is_i_redirection(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != '>')
		return (0);
	while (n_line[i] == '>')
	{
		if (n_line[1] != '>')
		{
			i++;
			ft_init_tokenizer(data, &n_line[i], i, O_TRNC);
			return (1);
		}
		i++;
	}
	if (n_line[i] != '>')
		ft_init_tokenizer(data, &n_line[i], i, O_APEND);
	return (1);
}

int	is_dolla(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != '$')
		return (0);
	if (n_line[i] == '$')
	{
		i++;
		while (n_line[i] != ' ' && !(n_line[i] >= 9 && n_line[i] <= 13) \
				&& n_line[i] != '|' && n_line[i] != '>' && n_line[i] != '<' \
				&& n_line[i])
			i++;
	}
	ft_init_tokenizer(data, &n_line[i], i, DOLLA);
	return (1);
}
