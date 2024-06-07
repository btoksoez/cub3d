#include "../../includes_bonus/cub3d.h"

void	get_player_coordinates(t_map *map, int rows, int coll)
{
	map->player.x = coll;
	map->player.y = rows;
	if (map->map[rows][coll] == 'N')
		map->player_dir = NORTH;
	if (map->map[rows][coll] == 'S')
		map->player_dir = SOUTH;
	if (map->map[rows][coll] == 'E')
		map->player_dir = EAST;
	if (map->map[rows][coll] == 'W')
		map->player_dir = WEST;
	map->map[rows][coll] = '0';
}
void	get_enemy_coordinates(t_map *map, int rows, int coll)
{
	t_enemy *enemy;

	enemy = malloc(sizeof(t_enemy));
	map->enemies = realloc(map->enemies, sizeof(t_enemy *) * map->enemy_count);
	map->enemies[map->enemy_count - 1] = enemy;
	enemy->pos.x = coll * SCALE + 3 * (PSIZE / 2);
	enemy->pos.y = rows * SCALE + 3 * (PSIZE / 2);
	enemy->left.x = 0;
	enemy->left.y = 0;
	enemy->right.x = 0;
	enemy->right.y = 0;
	enemy->shooting = 0;
	enemy->speed = 2;
	if (map->map[rows][coll] == 'O')
		enemy->type = OFFICER;
	else if (map->map[rows][coll] == 'B')
		enemy->type = BOSS;
	else if (map->map[rows][coll] == 'H')
		enemy->type = HITLER;
	map->map[rows][coll] = '0';
}

bool	invalid_characters(t_map *map)
{
	int		rows;
	int		coll;
	bool	player_found;

	rows = 0;
	player_found = false;
	while (rows < map->rows)
	{
		coll = 0;
		while (map->map[rows][coll])
		{
			if (ft_strchr(PLAYER, map->map[rows][coll]))
			{
				if (player_found)
					free_map(map, "There can only be 1 player", 1);
				get_player_coordinates(map, rows, coll);
				player_found = true;
			}
			if (strchr(ENEMY, map->map[rows][coll]))
			{
				map->enemy_count++;
				get_enemy_coordinates(map, rows, coll);
			}
			if (!ft_strchr(VALID_CHARS, map->map[rows][coll]))
				return (true);
			coll++;
		}
		if (map->cols < coll)
			map->cols = coll;
		rows++;
	}
	if (!player_found)
		free_map(map, "There is no player in this map", 1);
	fill_with_space(map);
	return (false);
}

bool	found_leaking_space(t_map *map, int row, int coll)
{
	if (row != 0)
	{
		if (map->map[row - 1][coll] != WALL && !ft_isspace(map->map[row - 1][coll]))
			return (true);
	}
	if (row != map->rows - 1)
	{
		if (map->map[row + 1][coll] != WALL && !ft_isspace(map->map[row + 1][coll]))
			return (true);
	}
	if (coll != 0)
	{
		if (map->map[row][coll - 1] != WALL && !ft_isspace(map->map[row][coll - 1]))
			return (true);
	}
	if (coll != map->cols - 1)
	{
		if (map->map[row][coll + 1] != WALL && !ft_isspace(map->map[row][coll + 1]))
			return (true);
	}
	return (false);
}

bool	leaking_empty_spaces(t_map *map)
{
	int	row;
	int	coll;

	row = 0;
	while (map->map[row])
	{
		coll = 0;
		while (map->map[row][coll])
		{
			if (ft_isspace(map->map[row][coll]))
				if (found_leaking_space(map, row, coll))
					return (false);
			coll++;
		}
		row++;
	}
	return (true);
}
