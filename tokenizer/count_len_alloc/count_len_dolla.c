/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len_dolla.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:12:06 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/06 08:18:53 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

static void	add_dolla_helper(t_data *data, int len)
{
	char	*dolla;
	t_env	*hold;
	t_env	*trav_env;

	trav_env = data->l_env;
	dolla = malloc(sizeof(char) * len + 1);
	if (!dolla)
		error_malloc();
	data->i -= len;
	len = 0;
	while (ft_acceptable_char(data->beg_line[data->i]))
		dolla[len++] = data->beg_line[data->i++];
	dolla[len] = 0;
	hold = getenv_addr(data, dolla);
	free(dolla);
	if (hold)
		data->tok_len += ft_strlen(hold->value);
}

void	count_dolla(t_data *data)
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
		data->tok_len++;
		data->i++;
		while (data->beg_line[data->i] && data->beg_line[data->i] != '$' \
				&& !ft_acceptable_char(data->beg_line[data->i + 1]))
		{
			data->i++;
			data->tok_len++;
		}
	}
}
