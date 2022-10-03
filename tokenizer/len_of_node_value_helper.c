/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_of_node_value_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 06:11:06 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/02 12:17:23 by hkaddour         ###   ########.fr       */
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
	data->tok_len += ft_strlen(dolla);
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
	if (data->beg_line[data->i + 1] == '?')
	{
		data->i += 2;
		//mabye here i should free too
		data->tok_len += ft_strlen(ft_itoa(data->chk_dolla));
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
