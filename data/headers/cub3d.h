/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:26 by fparis            #+#    #+#             */
/*   Updated: 2024/09/04 20:06:09 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MacroLibX/includes/mlx.h"
# include "../libft/libft.h"

# define M_PI 0

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define GROUND '0'
# define WALL '1'

# define NB_RAYS 500
# define FOV 1.57

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_vectorf
{
	float	x;
	float	y;
}	t_vectorf;

typedef struct s_impact
{
	t_vector	wall_pos;
	t_vector	impact_pos;
	float		length;
	int			face;
	t_vectorf	direc;
}	t_impact;

typedef	struct s_map
{
	int			index;
	t_vector	size;
	char		**arr;
}	t_map;

typedef struct s_player
{
	t_vector	pos;
	t_vectorf	offset;
	float		angle;
	int			movement[4];
	int			rotation[2];
	int			speed;
	int			is_running;
	t_impact	vision[NB_RAYS];
}	t_player;

typedef struct minimap
{
	int			UI_size;
	int			fig_size;
	t_vector	pos;
	int			chunk_size;
	char		**chunk;
}	t_minimap;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_vector	win_size;
	t_map		*current_map;
	t_minimap	minimap;
	t_player	player;
	int			scale;
	int			render_distance;
	int			test_key;
	float		test_length;
} t_data;

void		print_map(t_map *map);
void		print_chunk(t_data *data);

t_map		*create_map(char *path);
int			in_bound(t_map map, t_vector vec);
t_vector	vec_sum(t_vector vec1, t_vector vec2);
int			create_minimap(t_data *data, int UI_size, int fig_size);
void		update_chunk(t_data *data);
void		show_minimap(t_data *data);
int			key_up_manager(int key, void *param);
int			key_down_manager(int key, void *param);
void		init_player(t_data *data);
void		move(t_data *data);
t_vector	vec(int x, int y);
void		draw_line(t_data *data, t_vector p1, t_vector p2, t_vector col_width);
t_vector	vec_add(t_vector vec, int add);
void		draw_square(t_data *data, t_vector pos, t_vector col_width);
t_impact	get_impact(t_vector start, t_vectorf direc, t_data *data);
t_vector	vec_mult(t_vector vec, int mult);
int			in_window(t_vector win_size, t_vector vec);
void		get_all_rays(t_data *data);
void		show_screen(t_data *data);

#endif
