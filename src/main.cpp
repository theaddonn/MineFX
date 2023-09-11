#include <appdef.hpp>
#include <sdk/calc/calc.hpp>
#include <sdk/os/lcd.hpp>
#include <sdk/os/debug.hpp>
#include <sdk/os/input.hpp>

#include "include/utils.cpp"
#include "include/constants.cpp"
#include "include/square.cpp"
#include "include/utils.cpp"

#include "include/blocks/instances/airBlock.cpp"
#include "include/blocks/instances/dirtBlock.cpp"
#include "include/blocks/instances/grassBlock.cpp"
#include "include/blocks/instances/stoneBlock.cpp"
#include "include/blocks/instances/leaveBlock.cpp"
#include "include/blocks/instances/logBlock.cpp"
#include "include/blocks/instances/pathBlock.cpp"
#include "include/blocks/baseBlock.cpp"

APP_NAME("A simple isometric Renderer");
APP_DESCRIPTION("nothing more than a simple isometric renderer..");
APP_AUTHOR("Adrian");
APP_VERSION("0.1.2");

int x, y, z;
int cal_x, cal_y;
bool running = true;

extern "C"

Coordinate2D coordinateToGrid(int ca_x, int ca_y, int ca_z, int ca_offset_x, int ca_offset_y)
{
	cal_x = (ca_x * 0.5 * BLOCK_WIDTH) + (ca_z * -0.5 * BLOCK_WIDTH) + ca_offset_x;
	cal_y = (ca_x * 0.25 * BLOCK_HEIGHT) + (ca_z * 0.25 * BLOCK_HEIGHT - ca_z) + (ca_y * 0.5 * BLOCK_HEIGHT) + ca_offset_y;

	return Coordinate2D(cal_x, cal_y);
}

void drawBlockWithTemplate(int bl_x, int bl_y, TemplatePatternMap bl_pattern, KeyColorPairMap bl_keys)
{
	for (int cu_px = 0; cu_px < BLOCK_TILES_X; cu_px++) {
	    for (int cu_py = 0; cu_py < BLOCK_TILES_Y; cu_py++) {
			auto bl_symbol = bl_pattern.textureTemplatePattern[cu_py][cu_px];

			if (bl_symbol != '#')
			{
				uint16_t bl_color = bl_keys.get(bl_symbol);

				square(bl_x + cu_px*BLOCK_TILES_AVR_WIDTH, bl_y + cu_py*BLOCK_TILES_AVR_HEIGHT, BLOCK_TILES_AVR_WIDTH, BLOCK_TILES_AVR_HEIGHT, bl_color);
			}
	    }
	}
}

void renderEntireScreen(BaseBlock* rn_MAP[32][10][10])
{
    for (int y = MAP_SIZE_Y - 1; y >= 0; --y)
    {
        for (int x = 0; x < MAP_SIZE_X; ++x)  // Adjusted loop boundary
        {
            for (int z = 0; z < MAP_SIZE_Z; ++z)  // Adjusted loop boundary
            {
                BaseBlockType* cu_blockType = rn_MAP[y][x][z]->type;

                if (cu_blockType->isVisable() &&
                    ((y == 0 || !rn_MAP[y - 1][x][z]->type->isVisable()) ||
                     (x == MAP_SIZE_X - 1 || !rn_MAP[y][x + 1][z]->type->isVisable()) ||
                     (z == MAP_SIZE_Z - 1 || !rn_MAP[y][x][z + 1]->type->isVisable())))
                {
                    Coordinate2D grid_pos = coordinateToGrid(x, y, z, x_offset, y_offset);

					int calculated_x = grid_pos.xVal;
					int calculated_y = grid_pos.yVal;
					if (( DISPLAY_WIDTH <= calculated_x || DISPLAY_HEIGT <= calculated_y || 0 - BLOCK_WIDTH > calculated_x || 0 - BLOCK_HEIGHT > calculated_y) != true)

                    drawBlockWithTemplate(calculated_x, calculated_y, cu_blockType->getTextureTemplatePattern(), cu_blockType->getTextureTemplateKeys());
                }
            }
        }
    }
}

void clearEntireScreen()
{
	fillScreen(color(110, 114, 127));
}

void main() {
	calcInit(); //backup screen and init some variables
	
	initConstants();

	BaseBlock* MAP[32][10][10] = {
		{
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()}
	    },
		{
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LogBlock(), new LeaveBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()}
	    },
		{
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LogBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()}
	    },
		{
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LogBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LeaveBlock(), new LeaveBlock(), new LeaveBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()}
	    },
		{
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LogBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()}
	    },
		{
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LogBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()}
	    },
	    {
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new LogBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()},
	        {new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock(), new AirBlock()}
	    },
		{
	        {new GrassBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock()},
	        {new GrassBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock()},
	        {new GrassBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock()},
	        {new GrassBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock()},
	        {new GrassBlock(), new PathBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new LogBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock()},
	        {new GrassBlock(), new GrassBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock()},
	        {new GrassBlock(), new GrassBlock(), new PathBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new AirBlock()},
	        {new GrassBlock(), new GrassBlock(), new GrassBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new AirBlock()},
	        {new GrassBlock(), new GrassBlock(), new GrassBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new GrassBlock(), new AirBlock(), new AirBlock()},
	        {new GrassBlock(), new GrassBlock(), new GrassBlock(), new PathBlock(), new PathBlock(), new GrassBlock(), new GrassBlock(), new AirBlock(), new AirBlock(), new AirBlock()}
	    },
	    {
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock()},
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock()},
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock()},
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock()},
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock()},
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock()},
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock()},
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new AirBlock()},
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new AirBlock()},
	        {new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new DirtBlock(), new AirBlock(), new AirBlock(), new AirBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock(), new AirBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new AirBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    },
	    {
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()},
	        {new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock(), new StoneBlock()}
	    }
	};
	clearEntireScreen();
	
	renderEntireScreen(MAP);

	LCD_Refresh();

	while (running) {

		if (Input_IsAnyKeyDown())
		{
			uint32_t key1, key2;    //First create variables
			getKey(&key1, &key2);    //then read the keys

    		if(testKey(key1, key2, KEY_CLEAR)){ //Use testKey() to test if a specific key is pressed
    		    running = false;
				clearEntireScreen();
				break;
    		}
    		else if(testKey(key1, key2, KEY_UP)){
				y_offset += CAMERA_OFFSET_CHANGE;
				clearEntireScreen();
				renderEntireScreen(MAP);
    		}
    		else if(testKey(key1, key2, KEY_DOWN)){
				y_offset -= CAMERA_OFFSET_CHANGE;
				clearEntireScreen();
				renderEntireScreen(MAP);
    		}
    		else if(testKey(key1, key2, KEY_LEFT)){
				x_offset += CAMERA_OFFSET_CHANGE;
				clearEntireScreen();
				renderEntireScreen(MAP);
    		}
    		else if(testKey(key1, key2, KEY_RIGHT)){
				x_offset -= CAMERA_OFFSET_CHANGE;
				clearEntireScreen();
				renderEntireScreen(MAP);
    		}
			else if(testKey(key1, key2, KEY_ADD)){
				BLOCK_WIDTH += 16;
				BLOCK_HEIGHT += 17;
				calcScaleConstants();

				clearEntireScreen();
				renderEntireScreen(MAP);
    		}
			else if(testKey(key1, key2, KEY_SUBTRACT)){
				BLOCK_WIDTH -= 16;
				BLOCK_HEIGHT -= 17;
				calcScaleConstants();

				clearEntireScreen();
				renderEntireScreen(MAP);
    		}
	
			LCD_Refresh();
		}

	}

	LCD_ClearScreen();

	LCD_Refresh();

	calcEnd(); //restore screen and do stuff

	LCD_Refresh();

	calcEnd(); //restore screen and do stuff
}
