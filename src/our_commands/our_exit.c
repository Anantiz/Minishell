/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:07:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 17:08:25 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	our_exit(t_shell_data *shell_data, t_s_token *token)
{
	(void)shell_data;
	(void)token;

	exit(0);
	return (0);
}
