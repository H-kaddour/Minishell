/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pt1_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:24:01 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 11:08:26 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	quote_lexer_helper(int s_c, int d, int s, int typ)
{
	if (s_c >= 2 && typ == WRD)
	{
		printf("minishell: syntax error near unexpected token ';;'\n");
		return (1);
	}
	if (d % 2 == 0 && s % 2 == 0)
		return (0);
	printf("minishell: unclosed quotes\n");
	return (1);
}
