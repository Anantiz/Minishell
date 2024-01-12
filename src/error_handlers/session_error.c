/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:25:35 by aurban            #+#    #+#             */
/*   Updated: 2024/01/12 12:26:08 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error(int error)
{
	if (error == PARSING_ERROR)
		ft_putstr_fd("Parsing error\n", 2);
	else if (error == EXECTION_ERROR)
		ft_putstr_fd("Execution error\n", 2);
	else if (error == 0)
		ft_putstr_fd("Session ended\n", 2);
}