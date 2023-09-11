#include <sdk/os/lcd.hpp>

void square(int sq_x, int sq_y, int sq_x_size, int sq_y_size, uint16_t sq_color)
{
	if ((sq_x >= 0) && (sq_y >= 0))
	{
		int max_x_size = sq_x_size + sq_x;
		int max_y_size = sq_y_size + sq_y;

		if ((max_x_size <= DISPLAY_WIDTH) && (max_y_size <= DISPLAY_HEIGT))
		{
			for (int current_x = sq_x; current_x < max_x_size; ++current_x)
			{
				for (int current_y = sq_y; current_y < max_y_size; ++current_y)
				{
					LCD_SetPixel(current_x, current_y, sq_color);
				}
			}
		}
	}
}