/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:26:04 by aben-nei          #+#    #+#             */
/*   Updated: 2023/03/27 21:25:39 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_data *lst, void (*del)(void *))
{
	if (lst && del)
	{
		(*del)(lst->content);
		free(lst);
	}
}
