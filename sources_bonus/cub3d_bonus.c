/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:49:45 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 15:49:46 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	init_map(&map);
	read_input(argc, argv, &map);
	start_game(&map);
	return (0);
}
