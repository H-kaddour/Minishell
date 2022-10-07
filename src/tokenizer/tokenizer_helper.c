/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 07:59:26 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 11:10:22 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_var_tokenizer(t_data *data)
{
	data->index = 0;
	data->check = 1;
	data->error_lexer = 0;
	data->chk_hrdoc = 0;
	ft_init_tokenizer(data, data->beg_line, 0, 0);
}

void	parser_phase(t_data *data)
{
	if (lexer_pt2(data))
	{
		data->chk_dolla = 258;
		data->error_lexer = 1;
		return ;
	}
	parser(data);
	return ;
}
