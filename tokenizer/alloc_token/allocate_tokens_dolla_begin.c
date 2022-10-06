/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens_dolla_begin.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 07:20:58 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/06 11:45:08 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"


static int	dolla_begin_pt1(t_data *data)
{
	if (data->beg_line[data->i + 1] == ' ')
	{
		data->node->value[data->j++] = data->beg_line[data->i++];
		return (1);
	}
	else if (data->beg_line[data->i + 1] == '\"'\
			|| data->beg_line[data->i + 1] == '\'')
	{
		if (data->d_q_chk == 0)
			data->i++;
		else
			data->node->value[data->j++] = data->beg_line[data->i++];
		return (1);
	}
	else if (data->beg_line[data->i + 1] == 0)
	{
		data->node->value[data->j++] = data->beg_line[data->i++];
		return (1);
	}
	return (0);
}

static int	dolla_begin_pt2(t_data *data)
{
	int	i;

	if (data->beg_line[data->i + 1] == '0')
	{
		i = 2;
		while (data->args[0][i])
			data->node->value[data->j++] = data->args[0][i++];
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

static int	dolla_begin_pt3(t_data *data)
{
	int	i;
	char	*ptr;

	if (data->beg_line[data->i + 1] == '?')
	{
		data->i += 2;
		ptr = ft_itoa(data->chk_dolla);
		i = 0;
		while (ptr[i])
			data->node->value[data->j++] = ptr[i++];
		free(ptr);
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

int	add_dolla_begin(t_data *data)
{
	if (dolla_begin_pt1(data))
		return (1);
	if (dolla_begin_pt2(data))
		return (1);
	if (dolla_begin_pt3(data))
		return (1);
	return (0);
}
