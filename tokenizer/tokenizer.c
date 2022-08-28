/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/28 18:25:27 by hkaddour         ###   ########.fr       */
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

//here for example okay'ckj' should be in one arg
static int	is_word(t_data *data, char *n_line)
{
	char	c;
	char	*sp;
	int		quote;
	int		typ;

	///sp = "<|\">'$ ";
	sp = "<|>$ ";
	data->i = 0;
	quote = 0;
	typ = WRD;
	while (n_line[data->i])
	{
		data->j = 0;
		if (n_line[data->i] == '\"' || n_line[data->i] == '\'')
		{
			c = n_line[data->i];
			if (n_line[0] == c)
			{
				if (c == '\'')
					typ = S_QUOT;
				else if (c == '\"')
					typ = D_QUOT;
			}
			//else
			//	typ = WRD;
			quote++;
			data->i++;
			//while (beg_line[data->i] != ' ')
			while (n_line[data->i])
			{
				if (n_line[data->i] == '\'' || n_line[data->i] == '\"')
					quote++;
				if ((n_line[data->i] == ' ' || n_line[data->i] == '|' ||\
						n_line[data->i] == '>' || n_line[data->i] == '<') && quote % 2 == 0)
					break ;
				data->i++;
			}
			if (n_line[data->i] == c)
				data->i++;
		}
		while (sp[data->j])
		{
			//if (beg_line[data->i] == sp[data->j] \
			//		&& (sp[data->j] == '\"' || sp[data->j] == '\''))
			if (n_line[data->i] == sp[data->j])
				break ;
			data->j++;
		}
		if (n_line[data->i] == sp[data->j])
			break ;
		data->i++;
	}
	if (data->i == 0)
		return (0);
	ft_init_tokenizer(data, &n_line[data->i], data->i, typ);
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
	//those two var should init in the main one time init
	data->chk_hrdoc = 0;
	data->chk_dolla = 0;
	ft_init_tokenizer(data, data->beg_line, 0, 0);
	//if (!lexer(data))
	//	return ;
	while (data->line[data->index])
	{
		if (is_word(data, data->n_line) || is_space(data, data->n_line) || \
				is_d_quote(data, data->n_line) || is_dolla(data, data->n_line) || \
				is_pipe(data, data->n_line) || is_s_quote(data, data->n_line) || \
				is_i_redirection(data, data->n_line) || \
				is_o_redirection(data, data->n_line))
		{
			if (add_node(data, data->typ))
			{
				//here free 
				return ;
			}
			//also '' "" now is entring in node of wrd
			//before u return u should free the token node and return an error msg with color and print newline prompt
		}
		//if (is_word(data, data->n_line) || is_space(data, data->n_line) || \
		//		is_d_quote(data, data->n_line) || is_dolla(data, data->n_line))
		//	add_node(data, data->typ);
		//if (is_pipe(data, data->n_line) || is_s_quote(data, data->n_line) || \
		//		is_i_redirection(data, data->n_line) || \
		//		is_o_redirection(data, data->n_line))
		//	add_node(data, data->typ);
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
