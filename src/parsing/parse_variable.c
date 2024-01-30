/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:28:55 by lkary-po          #+#    #+#             */
/*   Updated: 2024/01/29 13:26:40 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool    add_var(char *str)
{
    char    *ret;

    if (ft_strncmp(str, "ARG=", 4) == 0)
    {
        ret = str + 4;
        //add to linked list
        return (true);
    }
    return(false);
}
