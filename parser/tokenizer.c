/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/24 14:26:49 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_tokenizer(t_data *data, char *n_line, int i, t_types typ)
{
	data->typ = typ;
	data->n_line = n_line;
	data->i_line = i;
	data->index += i;
}

static int	is_pipe(t_data *data, char *n_line)
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

static int	is_space(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != ' ')
		return (0);
	while (n_line[i] == ' ')
		i++;
	ft_init_tokenizer(data, &n_line[i], i, W_SPACE);
	return (1);
}

static int	is_word(t_data *data, char *beg_line)
{
	char	*sp;

	sp = "<|\">'$ ";
	data->i = 0;
	while (beg_line[data->i])
	{
		data->j = 0;
		while (sp[data->j])
		{
			if (beg_line[data->i] == sp[data->j])
				break ;
			data->j++;
		}
		if (beg_line[data->i] == sp[data->j])
			break ;
		data->i++;
	}
	if (data->i == 0)
		return (0);
	ft_init_tokenizer(data, &beg_line[data->i], data->i, WRD);
	return (1);
}

void	tokenizer(t_data *data)
{
	//here maybe i should check all whitespace also in is_space
	if (data->line[0] == ' ')
		data->beg_line = ft_strchr(data->line, ' ');
	else
		data->beg_line = data->line;
	data->index = 0;
	data->check = 1;
	ft_init_tokenizer(data, data->beg_line, 0, 0);
	while (data->line[data->index])
	{
		if (is_word(data, data->n_line) || is_space(data, data->n_line) || \
				is_d_quote(data, data->n_line) || is_dolla(data, data->n_line))
			add_node(data, data->typ);
		if (is_pipe(data, data->n_line) || is_s_quote(data, data->n_line) || \
				is_i_redirection(data, data->n_line) || \
				is_o_redirection(data, data->n_line))
			add_node(data, data->typ);
	}
	//here to write the arg that i entred in the nodes
	t_token	*trav;

	trav = data->t_token;
	while (trav)
	{
		printf("| %d |\n", trav->type);
		printf("| %s |\n", trav->value);
		printf("\n");
		trav = trav->next;
	}
}
