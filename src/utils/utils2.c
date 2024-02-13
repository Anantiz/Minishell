/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:24:09 by aurban            #+#    #+#             */
/*   Updated: 2024/02/12 20:31:57 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_data	*get_shell_data_ptr(t_shell_data *shell_data_unused)
{
	static t_shell_data	*shell_data = NULL;

	if (shell_data_unused)
		shell_data = shell_data_unused;
	return (shell_data);
}
