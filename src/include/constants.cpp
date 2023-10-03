#include <sdk/os/lcd.hpp>

int MAP_SIZE_X = 10; // Map size in x coord
int MAP_SIZE_Y = 10; // Map size in y coord
int MAP_SIZE_Z = 10; // Map size in z coord

const int BLOCK_TILES_X = 16; // Block Tiles in the x coord
const int BLOCK_TILES_Y = 17; // Block Tiles in the y coord

const int CAMERA_OFFSET_CHANGE = 20; // Amount off pixel the camera should be able to move

int BLOCK_WIDTH = 80; // Block width in pixel
int BLOCK_HEIGHT = 85; // Block height in pixel

int BLOCK_TILES_AVR_WIDTH; // Pixel size of block in width
int BLOCK_TILES_AVR_HEIGHT; // Pixel size of block in height

int DISPLAY_WIDTH, DISPLAY_HEIGT;

int x_offset, y_offset;

int x, y, z;
int cursor_x, cursor_y, cursor_z = 0;
int cal_x, cal_y;
bool running = true;

void calcScaleConstants()
{
	BLOCK_TILES_AVR_WIDTH = BLOCK_WIDTH / BLOCK_TILES_X;
	BLOCK_TILES_AVR_HEIGHT = BLOCK_HEIGHT / BLOCK_TILES_Y;
	
	x_offset = DISPLAY_WIDTH / 2 - BLOCK_WIDTH / 2;
	y_offset = DISPLAY_HEIGT / 20;
}

void initConstants()
{
	LCD_GetSize(&DISPLAY_WIDTH, &DISPLAY_HEIGT);

	calcScaleConstants();
}

const uint8_t WORLD_FORMAT_HEADER[] = {0x4D, 0x49, 0x4E, 0x45, 0x46, 0x58, 0x57, 0x4F, 0x52, 0x4C, 0x44};
const uint8_t WORLD_FORMAT_VERSION[] = {0x31, 0x30, 0x30};
const uint8_t WORLD_FORMAT_WORLD_SIZE_X = 0x0a;
const uint8_t WORLD_FORMAT_WORLD_SIZE_Y = 0x0a;
const uint8_t WORLD_FORMAT_WORLD_SIZE_Z = 0x0a;


const uint8_t WORLD_FORMAT[] = {0x4D, 0x49, 0x4E, 0x45, 0x46, 0x58, 0x57, 0x4F, 0x52, 0x4C, 0x44, 0x31, 0x30, 0x30, 0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x00};

const int WORLD_FORMAT_SIZE = 20;

const int WORLD_FORMAT_WORLD_SIZE_X_INDEX = 14;
const int WORLD_FORMAT_WORLD_SIZE_Y_INDEX = 15;
const int WORLD_FORMAT_WORLD_SIZE_Z_INDEX = 16;
