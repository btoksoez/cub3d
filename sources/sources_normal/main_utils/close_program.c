/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btoksoez <btoksoez@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:45:59 by andre-da          #+#    #+#             */
/*   Updated: 2024/07/13 14:06:37 by btoksoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes_normal/cub3d.h"

void	error_message(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

int	close_window(t_game *game, int status, int exit)
{
	if (exit == WON)
		clean_up(game, "You Won!", status);
	else
		clean_up(game, "Game Over!", status);
	return (0);
}

void	clean_up(t_game *game, char *str, int status)
{
	free_textures(game, game->textures);
	free_map(game->map, NULL, 0);
	mlx_destroy_image(game->mlx, game->img.img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	#ifdef LINUX
	mlx_destroy_display(game->mlx);
	#endif
	free(game->mlx);
	if (status)
		error_message(str);
	else
	{
		ft_printf("%s\n", str);
		exit(0);
	}
}
