/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_tokens_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:30:14 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/29 11:32:32 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_dolla_helper(t_data *data, int len)
{
	char	*dolla;
	char	*hold;
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
	hold = dolla;
	dolla = myown_getenv(data, dolla, 0);
	if (!dolla)
		dolla = ft_strdup("");
	free(hold);
	len = 0;
	while (dolla[len])
		data->node->value[data->j++] = dolla[len++];
	//free(dolla);
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

int	dolla_begin_pt1(t_data *data)
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

int	dolla_begin_pt2(t_data *data)
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

int	dolla_begin_pt3(t_data *data)
{
	int	i;
	char	*ptr;

	if (data->beg_line[data->i + 1] == '?')
	{
		data->i += 2;
		//mabye here i should free too
		ptr = ft_itoa(data->chk_dolla);
		i = 0;
		while (ptr[i])
			data->node->value[data->j++] = ptr[i++];
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
