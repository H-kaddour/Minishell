/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:54 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/24 14:27:31 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_acceptable_char(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
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
				if (n_line[data->i] == ' ' || n_line[data->i] == '|' || \
						n_line[data->i] == '>' || n_line[data->i] == '<')
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
