/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:22:11 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/08 10:12:05 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_malloc(void)
{
	printf("Fatal: error in malloc\n");
	exit(1);
}

void	error_fork(t_data *data)
{
	data->chk_dolla = 1;
	ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
}

void	error_pipe(t_data *data, char *msg)
{
	data->chk_dolla = 1;
	printf("%s\n", msg);
}
