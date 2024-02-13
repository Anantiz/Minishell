/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:45:11 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/13 10:51:19 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	ft_is_o_parenthesis(char *token)
{
	if (!token || !(*token))
		return (false);
	if (*token == '(')
		return (true);
	return (false);
}

bool	ft_is_c_parenthesis(char *token)
{
	if (!token || !(*token))
		return (false);
	if (*token == ')')
		return (true);
	return (false);
}