/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens_dolla.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 07:23:50 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/16 11:56:00 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_acceptable_char(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

static void	add_dolla_helper(t_data *data, int len)
{
	char	*dolla;
	t_env	*hold;
	t_env	*trav_env;

	trav_env = data->l_env;
	dolla = allocation(data, len + 1, sizeof(char), 1);
	data->i -= len;
	len = 0;
	while (ft_acceptable_char(data->beg_line[data->i]))
		dolla[len++] = data->beg_line[data->i++];
	hold = getenv_addr(data, dolla);
	if (hold)
	{
		len = 0;
		while (hold->value[len])
			data->node->value[data->j++] = hold->value[len++];
	}
}

void	add_dolla(t_data *data)
{
	int	len;

	if (data->beg_line[data->i] == '$' && \
			ft_acceptable_char(data->beg_line[data->i + 1]))
	{
		data->i++;
		len = 0;
		while (ft_acceptable_char(data->beg_line[data->i]))
		{
			data->i++;
			len++;
		}
		add_dolla_helper(data, len);
	}
	else if (data->beg_line[data->i] == '$' && \
			!ft_acceptable_char(data->beg_line[data->i + 1]))
	{
		data->node->value[data->j++] = data->beg_line[data->i++];
		while (data->beg_line[data->i] && data->beg_line[data->i] != '$' \
				&& !ft_acceptable_char(data->beg_line[data->i + 1]))
			data->node->value[data->j++] = data->beg_line[data->i++];
	}
}
