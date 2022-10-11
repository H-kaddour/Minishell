/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len_dolla_begin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:09:06 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/11 12:08:51 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	count_dolla_begin_pt1(t_data *data)
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

static int	count_dolla_begin_pt2(t_data *data)
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
	else if (data->beg_line[data->i + 1] >= '1' && \
			data->beg_line[data->i + 1] <= '9')
	{
		data->i += 2;
		return (1);
	}
	return (0);
}

static int	count_dolla_begin_pt3(t_data *data)
{
	char	*hold;

	if (data->beg_line[data->i + 1] == '?')
	{
		data->i += 2;
		hold = ft_itoa(data->chk_dolla);
		free_implementation(data, hold);
		data->tok_len += ft_strlen(hold);
		//free(hold);
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
