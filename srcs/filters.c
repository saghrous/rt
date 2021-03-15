/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <hastid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 00:18:45 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/11/09 01:04:12 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec	black_white(t_vec color)
{
	double avg;

	avg = ((color.x + color.y + color.z) / 3);
	color.x = avg;
	color.y = avg;
	color.z = avg;

	return (color);


}

void	negatif(t_vec color)
{
	color.x = 255. - color.x;
	color.y = 255. - color.y;
	color.z = 255. - color.z;
}

void	spia(t_vec color)
{
	double tr;
	double tg;
	double tb;

	tr = (0.393 * color.x + 0.769 * color.y + 0.189 * color.z);
	tg = (0.349 * color.x + 0.686 * color.y + 0.168 * color.z);
	tb = (0.272 * color.x + 0.534 * color.y + 0.131 * color.z);
	if (tr > 255)
		color.x = 255;
	else
		color.x = tr;
	if (tg > 255)
		color.y = 255;
	else
		color.y = tg;
	if (tb > 255)
		color.z = 255;
	else
		color.z = tb;
}

t_vec	filters(t_vec color, int filter)
{
	color = vec_pro_k(color, 255);
	color.x = fmin(255, fmax(0, pow(color.x, 1 / 2.2)));
	color.y = fmin(255, fmax(0, pow(color.y, 1 / 2.2)));
	color.z = fmin(255, fmax(0, pow(color.z, 1 / 2.2)));
	if (filter == 2)
		color = black_white(color);
	if (filter == 3)
		negatif(color);
	if (filter == 1)
		spia(color);
	color.x /=  255;
	color.y /= 255; 
	color.z /= 255; 
		return (color);
}
