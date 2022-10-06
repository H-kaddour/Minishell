/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_of_node_value_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 06:11:06 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/05 22:35:40 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_dolla_helper(t_data *data, int len)
{
	char	*dolla;
	t_env	*hold;
	t_env	*trav_env;

	trav_env = data->l_env;
	dolla = malloc(sizeof(char) * len + 1);
	if (!dolla)
		return ;
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

int	count_dolla_begin_pt1(t_data *data)
{
	if (data->beg_line[data->i + 1] == ' ')
	{
		data->i++;
		data->tok_len++;
		return (1);
	}
	else if (data->beg_line[data->i + 1] == '\"'\
			|| data->beg_line[data->i + 1] == '\'')
	{
		if (data->d_q_chk == 0)
			data->i++;
		else
		{
			data->i++;
			data->tok_len++;
		}
		return (1);
	}
	else if (data->beg_line[data->i + 1] == 0)
	{
		data->i++;
		data->tok_len++;
		return (1);
	}
	return (0);
}

int	count_dolla_begin_pt2(t_data *data)
{
	int	i;

	if (data->beg_line[data->i + 1] == '0')
	{
		i = 2;
		while (data->args[0][i])
		{
			i++;
			data->tok_len++;
		}
		data->i += 2;
		return (1);
	}
	else if (data->beg_line[data->i + 1] >= '1' &&\
			data->beg_line[data->i + 1] <= '9')
	{
		data->i += 2;
		return (1);
	}
	return (0);
}

int	count_dolla_begin_pt3(t_data *data)
{
	char	*hold;

	if (data->beg_line[data->i + 1] == '?')
	{
		data->i += 2;
		hold = ft_itoa(data->chk_dolla);
		data->tok_len += ft_strlen(hold);
		free(hold);
		return (1);
	}
	else if (data->beg_line[data->i + 1] == '$')
	{
		while (data->beg_line[data->i] == '$')
		{
			if (data->beg_line[data->i + 1] == '$')
				data->i += 2;
			else
				break ;
		}
		return (1);
	}
	return (0);
}

//void	add_dolla_begin(t_data *data)
int	count_dolla_begin(t_data *data)
{
	if (count_dolla_begin_pt1(data))
		return (1);
	if (count_dolla_begin_pt2(data))
		return (1);
	if (count_dolla_begin_pt3(data))
		return (1);
	return (0);
}
