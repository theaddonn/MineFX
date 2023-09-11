#include <sdk/os/lcd.hpp>

static int MAP_SIZE_X = 10; // Map size in x coord
static int MAP_SIZE_Y = 32; // Map size in y coord
static int MAP_SIZE_Z = 10; // Map size in z coord

int BLOCK_WIDTH = 80; // Block width in pixel
int BLOCK_HEIGHT = 85; // Block height in pixel

static int BLOCK_TILES_X = 16; // Block Tiles in the x coord
static int BLOCK_TILES_Y = 17; // Block Tiles in the y coord

static int CAMERA_OFFSET_CHANGE = 20; // Amount off pixel the camera should be able to move

int BLOCK_TILES_AVR_WIDTH; // Pixel size of block in width
int BLOCK_TILES_AVR_HEIGHT; // Pixel size of block in height

int DISPLAY_WIDTH, DISPLAY_HEIGT;

int x_offset, y_offset;

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