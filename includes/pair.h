/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:03:56 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 15:04:53 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_H
# define PAIR_H

# include "libft.h"

typedef struct	s_pair_char
{
	char	*key;
	char	*val;
}t_pair_char;

void			pair_char_free(t_pair_char *pair);
t_pair_char		*pair_char_strtok(char *str, char sep);

#endif