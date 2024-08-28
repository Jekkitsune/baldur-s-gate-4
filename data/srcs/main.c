/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2024/08/28 21:09:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(void *param)
{
	t_data *data;

	data = (t_data *)param;
	move(data);
	mlx_clear_window(data->mlx, data->win);
	update_chunk(data);
	show_screen(data);
	show_minimap(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
	{
		ft_putstr_fd("Not enough maps!\n", 2);
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	data.test_key = 0;
	data.win_size.x = 1600;
	data.win_size.y = 800;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.win_size.x, data.win_size.y, "Baldur's Gate 4");
	data.scale = 10;
	data.render_distance = 500;

	data.test_length = 0;
	
	data.current_map = create_map(argv[1]);
	print_map(data.current_map);
	printf("\n\n\n\n\n\n\n");
	
	init_player(&data);

	create_minimap(&data, 300, 50);

	mlx_set_fps_goal(data.mlx, 60);
	mlx_on_event(data.mlx, data.win, MLX_KEYDOWN, key_down_manager, &data);
	mlx_on_event(data.mlx, data.win, MLX_KEYUP, key_up_manager, &data);
	
	update_chunk(&data);
	print_chunk(&data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);


	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
