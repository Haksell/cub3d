/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:09:03 by axbrisse          #+#    #+#             */
/*   Updated: 2023/05/07 09:09:03 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->infos.floor = -1;
	data->infos.ceil = -1;
	data->player.pos.x = -1;
	data->player.pos.y = -1;
}
