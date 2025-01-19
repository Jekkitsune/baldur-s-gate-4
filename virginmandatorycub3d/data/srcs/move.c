#include "cub3d.h"

void	correct_pos(t_data *data, t_vector *pos, t_vectorf *offset)
{
	while (offset->x >= data->scale)
	{
		pos->x++;
		offset->x = (double)-data->scale + (fabs(offset->x)
				- fabs((double)data->scale));
	}
	while (offset->x < -data->scale)
	{
		pos->x--;
		offset->x = (double)data->scale - (fabs(offset->x)
				- fabs((double)data->scale));
	}
	while (offset->y >= data->scale)
	{
		pos->y++;
		offset->y = (double)-data->scale + (fabs(offset->y)
				- fabs((double)data->scale));
	}
	while (offset->y < -data->scale)
	{
		pos->y--;
		offset->y = (double)data->scale - (fabs(offset->y)
				- fabs((double)data->scale));
	}
}

void	change_pos(t_data *data, t_vectorf *offset, float angle)
{
	t_vectorf	direc;

	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	direc.x = cosf(angle);
	direc.y = sinf(angle);
	offset->x += direc.x * data->player.speed;
	offset->y += direc.y * data->player.speed;
}

void	move(t_data *data)
{
	t_player	*p;

	p = &data->player;
	if (p->movement[0])
		change_pos(data, &data->player.offset, p->angle);
	if (p->movement[1])
		change_pos(data, &data->player.offset, p->angle - (M_PI / 2));
	if (p->movement[2])
		change_pos(data, &data->player.offset, p->angle + M_PI);
	if (p->movement[3])
		change_pos(data, &data->player.offset, p->angle + (M_PI / 2));
	correct_pos(data, &data->player.pos, &data->player.offset);
	if (p->rotation[0])
		p->angle -= 0.1;
	if (p->rotation[1])
		p->angle += 0.1;
	data->player.camera_plane.x = cosf(angle_add(data->player.angle, M_PI / 2));
	data->player.camera_plane.y = sinf(angle_add(data->player.angle, M_PI / 2));
	data->player.direction.x = cosf(data->player.angle);
	data->player.direction.y = sinf(data->player.angle);
}
