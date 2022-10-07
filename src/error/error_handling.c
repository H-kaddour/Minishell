/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:22:11 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/07 11:00:00 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_malloc(void)
{
	printf("Fatal: error in malloc\n");
	exit(1);
}

void	error_fork(t_data *data, char *msg)
{
	data->chk_dolla = 1;
	printf("%s\n", msg);
	exit(1);
}

void	error_pipe(t_data *data, char *msg)
{
	data->chk_dolla = 1;
	printf("%s\n", msg);
}
