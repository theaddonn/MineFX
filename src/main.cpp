#include <appdef.hpp>
#include <sdk/calc/calc.hpp>
#include <sdk/os/lcd.hpp>
#include <sdk/os/debug.hpp>
#include <sdk/os/input.hpp>
#include <sdk/os/file.hpp>

#include "include/blocks/instances/airBlock.cpp"
#include "include/blocks/instances/dirtBlock.cpp"
#include "include/blocks/instances/grassBlock.cpp"
#include "include/blocks/instances/stoneBlock.cpp"
#include "include/blocks/instances/leaveBlock.cpp"
#include "include/blocks/instances/logBlock.cpp"
#include "include/blocks/instances/pathBlock.cpp"
#include "include/blocks/instances/cursorBlock.cpp"
#include "include/blocks/baseBlock.cpp"

#include "include/utils.cpp"
#include "include/constants.cpp"
#include "include/square.cpp"
#include "include/utils.cpp"

APP_NAME("MineFX");
APP_DESCRIPTION("Nothing more than a simple isometric renderer in a Minecraft style..");
APP_AUTHOR("Adrian");
APP_VERSION("0.2.2");

extern "C"

BaseBlock* getBlockTypeFromID(uint8_t id)
{
	switch (id)
    {
        case 0x01:
            return new AirBlock();
        case 0x02:
            return new DirtBlock();
        case 0x03:
            return new GrassBlock();
        case 0x04:
            return new LeaveBlock();
        case 0x05:
            return new LogBlock();
        case 0x06:
            return new PathBlock();
        case 0x07:
            return new StoneBlock();
        default:
            return new DirtBlock(); // Return AirBlock for unknown IDs
    }
}

void saveWorldToDisk(BaseBlock**** MAP)
{
    mkdir("\\fls0\\MineFx");

	int world_file = open("\\fls0\\MineFx\\world_1.mfxw", OPEN_WRITE | OPEN_CREATE);

	if (world_file < 0)
	{
		Debug_Printf(0, 1, true, 0, "Couldn't create file: %d", world_file);
		LCD_Refresh();
		while (true)
		{
		}
		
	}

	uint8_t world_data_buf[WORLD_FORMAT_SIZE + MAP_SIZE_X*MAP_SIZE_Y*MAP_SIZE_Z];

	for (int i = 0; i < sizeof(world_data_buf); i++)
	{
		world_data_buf[i] = 0x00;
	}
	 

	for (int i = 0; i < WORLD_FORMAT_SIZE; i++)
	{
		world_data_buf[i] = WORLD_FORMAT[i];
	}
	

	int index = WORLD_FORMAT_SIZE; // Start after the WORLD_FORMAT data

	for (int dy = MAP_SIZE_Y - 1; dy >= 0; --dy)
	{
	    for (int dx = 0; dx < MAP_SIZE_X; ++dx)
	    {
	        for (int dz = 0; dz < MAP_SIZE_Z; ++dz)
	        {
	            // Calculate the index based on the current dx, dy, and dz values
	            int current_index = index + (dx + MAP_SIZE_X * (dy + MAP_SIZE_Y * dz));
	
	            // Populate the data at the calculated index
	            world_data_buf[current_index] = MAP[dy][dx][dz]->type->id();
	        }
	    }
	} 

	int world_file_write = write(world_file, world_data_buf, sizeof(world_data_buf));
	if (world_file_write < 0)
	{
		Debug_Printf(0, 2, true, 0, "Couldn't write file: %d", world_file_write);
		LCD_Refresh();
		while (true)
		{
		}
		
	}
	int world_file_close = close(world_file);
	if (world_file_close < 0)
	{
		Debug_Printf(0, 3, true, 0, "Couldn't close file: %d", world_file_close);
		LCD_Refresh();
		while (true)
		{
		}
		
	}
}

void loadWorldFromDisk(BaseBlock**** MAP)
{
    int findHandle;
	struct findInfo findInfoBuf;

	uint32_t fileSize = 0;

	int world_file_info = findFirst(L"\\fls0\\MineFx\\world_1.mfxw", &findHandle, nullptr, &findInfoBuf);

	if (world_file_info == 0) {
        fileSize = findInfoBuf.size;
		//saveWorldToDisk(MAP);
		//loadWorldFromDisk(MAP);
    } else {
        Debug_Printf(0, 1, true, 0, "Error while finding info to file: %d", world_file_info);
		LCD_Refresh();
		while (true)
		{
		}
    }
	findClose(findHandle);

	int world_file = open("\\fls0\\MineFx\\world_1.mfxw", OPEN_READ);

	if (world_file < 0)
	{
		Debug_Printf(0, 1, true, 0, "Couldn't open file: %d", world_file);
		LCD_Refresh();
		while (true)
		{
		}
	}
	
	Debug_Printf(0, 10, true, 0, "Filesize %d", world_file);
	LCD_Refresh();

	uint8_t world_data_buf[fileSize];

	int world_file_read = read(world_file, world_data_buf, fileSize);

	if (world_file_read < 0)
	{
		Debug_Printf(0, 1, true, 0, "Couldn't read file: %d", world_file);
		LCD_Refresh();
		while (true)
		{
		}
	}

	MAP_SIZE_X = int(world_data_buf[WORLD_FORMAT_WORLD_SIZE_X_INDEX]);
	MAP_SIZE_Y = int(world_data_buf[WORLD_FORMAT_WORLD_SIZE_Y_INDEX]);
	MAP_SIZE_Z = int(world_data_buf[WORLD_FORMAT_WORLD_SIZE_Z_INDEX]);

	Debug_Printf(0, 11, true, 0, "X: %d | Y: %d | Z: %d", MAP_SIZE_X, MAP_SIZE_Y, MAP_SIZE_Z);
	LCD_Refresh();
	
	int index = WORLD_FORMAT_SIZE; // Start after the WORLD_FORMAT data

	for (int dy = MAP_SIZE_Y - 1; dy >= 0; --dy)
	{
	    for (int dx = 0; dx < MAP_SIZE_X; ++dx)
	    {
	        for (int dz = 0; dz < MAP_SIZE_Z; ++dz)
	        {
	            // Calculate the index based on the current dx, dy, and dz values
	            int current_index = index + (dx + MAP_SIZE_X * (dy + MAP_SIZE_Y * dz));

				switch (world_data_buf[current_index])
				{
					case 0x01:
						MAP[dy][dx][dz] = new AirBlock();
						break;

					case 0x02:
						MAP[dy][dx][dz] = new DirtBlock();
						break;

					case 0x03:
						MAP[dy][dx][dz] = new GrassBlock();
						break;

					case 0x04:
						MAP[dy][dx][dz] = new LeaveBlock();
						break;

					case 0x05:
						MAP[dy][dx][dz] = new LogBlock();
						break;

					case 0x06:
						MAP[dy][dx][dz] = new PathBlock();
						break;

					case 0x07:
						MAP[dy][dx][dz] = new StoneBlock();
						break;

					default:
						MAP[dy][dx][dz] = new AirBlock();
						break;
				}
	        }
	    }
	} 

	int world_file_close = close(world_file);
	if (world_file_close < 0)
	{
		Debug_Printf(0, 3, true, 0, "Couldn't close file: %d", world_file_close);
		LCD_Refresh();
		while (true)
		{
		}
		
	}
}

void drawLoadingScreen()
{
	fillScreen(color(0, 0, 0));
	Debug_Printf(0, 0, true, 0, "Loading...");
	LCD_Refresh();
}

void drawSavingScreen()
{
	fillScreen(color(0, 0, 0));
	Debug_Printf(0, 0, true, 0, "Saving...");
	LCD_Refresh();
}

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

void renderEntireScreen(BaseBlock**** rn_MAP)
{
    for (int y = MAP_SIZE_Y - 1; y >= 0; --y)
    {
        for (int x = 0; x < MAP_SIZE_X; ++x)
        {
            for (int z = 0; z < MAP_SIZE_Z; ++z)
            {
                BaseBlockType* cu_block_type = rn_MAP[y][x][z]->type;

				Coordinate2D grid_pos = coordinateToGrid(x, y, z, x_offset, y_offset);

				int calculated_x = grid_pos.xVal;
				int calculated_y = grid_pos.yVal;
				if (( DISPLAY_WIDTH <= calculated_x || DISPLAY_HEIGT <= calculated_y || -BLOCK_WIDTH > calculated_x || -BLOCK_HEIGHT > calculated_y) != true)
				{
					if (cu_block_type->isVisable() &&
                    ((y == 0 || !rn_MAP[y - 1][x][z]->type->isVisable()) ||
                     (x == MAP_SIZE_X - 1 || !rn_MAP[y][x + 1][z]->type->isVisable()) ||
                     (z == MAP_SIZE_Z - 1 || !rn_MAP[y][x][z + 1]->type->isVisable()))
					)
                	{
						drawBlockWithTemplate(calculated_x, calculated_y, cu_block_type->getTextureTemplatePattern(), cu_block_type->getTextureTemplateKeys());
                	}

					if (y == cursor_y && x == cursor_x && z == cursor_z)
					{
						drawBlockWithTemplate(calculated_x, calculated_y, CursorBlockType().getTextureTemplatePattern(), CursorBlockType().getTextureTemplateKeys());
					}
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

	drawLoadingScreen();

	BaseBlock**** MAP = new BaseBlock***[MAP_SIZE_Y];

	for (int i = 0; i < MAP_SIZE_Y; ++i) {
	    MAP[i] = new BaseBlock**[MAP_SIZE_X];
	    for (int j = 0; j < MAP_SIZE_X; ++j) {
	        MAP[i][j] = new BaseBlock*[MAP_SIZE_Z];
			for (int n = 0; n < MAP_SIZE_Z; n++)
			{
				MAP[i][j][n] = new StoneBlock();
			}
	    }
	}

	loadWorldFromDisk(MAP);
	
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
				break;
    		}
    		else if(testKey(key1, key2, KEY_UP)){
				y_offset += CAMERA_OFFSET_CHANGE;
    		}
    		else if(testKey(key1, key2, KEY_DOWN)){
				y_offset -= CAMERA_OFFSET_CHANGE;
    		}
    		else if(testKey(key1, key2, KEY_LEFT)){
				x_offset += CAMERA_OFFSET_CHANGE;
    		}
    		else if(testKey(key1, key2, KEY_RIGHT)){
				x_offset -= CAMERA_OFFSET_CHANGE;
    		}
			else if(testKey(key1, key2, KEY_ADD)){
				BLOCK_WIDTH += 16;
				BLOCK_HEIGHT += 17;
				calcScaleConstants();
    		}
			else if(testKey(key1, key2, KEY_SUBTRACT)){
				BLOCK_WIDTH -= 16;
				BLOCK_HEIGHT -= 17;
				calcScaleConstants();
    		}
			else if(testKey(key1, key2, KEY_3)){
				if (cursor_x < MAP_SIZE_X)
				{
					cursor_x++;
				}
    		}
			else if(testKey(key1, key2, KEY_7)){
				if (cursor_x > 0)
				{
					cursor_x--;
				}
    		}
			else if(testKey(key1, key2, KEY_1)){
				if (cursor_z < MAP_SIZE_Z)
				{
					cursor_z++;
				}
    		}
			else if(testKey(key1, key2, KEY_9)){
				if (cursor_z > 0)
				{
					cursor_z--;
				}
    		}
			else if(testKey(key1, key2, KEY_Y)){
				if (cursor_y < MAP_SIZE_Y)
				{
					cursor_y++;
				}
    		}
			else if(testKey(key1, key2, KEY_X)){
				if (cursor_y > 0)
				{
					cursor_y--;
				}
    		}
			else if(testKey(key1, key2, KEY_BACKSPACE)){
    			if (cursor_x >= 0 && cursor_x < MAP_SIZE_X &&
				    cursor_y >= 0 && cursor_y < MAP_SIZE_Y &&
				    cursor_z >= 0 && cursor_z < MAP_SIZE_Z
				)
				{
				    delete MAP[cursor_y][cursor_x][cursor_z];
				    MAP[cursor_y][cursor_x][cursor_z] = new AirBlock();
				}
    		}
			
			clearEntireScreen();
			renderEntireScreen(MAP);
			LCD_Refresh();
		}
	}

	drawSavingScreen();
	saveWorldToDisk(MAP);

    for (int i = 0; i < MAP_SIZE_Y; ++i) {
        for (int j = 0; j < MAP_SIZE_X; ++j) {
            for (int n = 0; n < MAP_SIZE_Z; n++) {
                delete MAP[i][j][n];  // Delete individual objects
            }
            delete[] MAP[i][j];      // Delete second-level pointers
        }
        delete[] MAP[i];              // Delete first-level pointers
    }
    delete[] MAP;                      // Delete the top-level pointer

	LCD_ClearScreen();
	LCD_Refresh();
	calcEnd(); //restore screen and do stuff
}
