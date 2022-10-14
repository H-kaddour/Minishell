/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/13 15:33:11 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	tokenizer_init(t_data *data)
{
	free_implementation(data, data->line);
	data->beg_line = ft_strtrim(data->line, "\t\v\r\f ");
	free_implementation(data, data->beg_line);
	if (!data->beg_line[0])
	{
		data->error_lexer = 1;
		return (1);
	}
	init_var_tokenizer(data);
	return (0);
}

void	tokenizer(t_data *data)
{
	if (tokenizer_init(data))
		return ;
	while (*data->beg_line)
	{
		if (is_word(data, data->n_line) || is_s_quote(data, data->n_line) || \
				is_d_quote(data, data->n_line) || is_space(data, data->n_line) \
				|| is_dolla(data, data->n_line) || is_pipe(data, data->n_line) \
				|| is_i_redirection(data, data->n_line) || \
				is_o_redirection(data, data->n_line))
		{
			if (add_node(data, data->typ))
			{
				data->chk_dolla = 258;
				data->error_lexer = 1;
				return ;
			}
		}
	}
	parser_phase(data);
}
