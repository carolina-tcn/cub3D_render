#include "test.h"

char g_map[MAP_HEIGHT][MAP_WIDTH + 1] = {
	"111111",
	"100001",
	"100001",
	"1000N1",
	"111111"
};

int floor_color[3] = {120, 120, 120};
int ceiling_color[3] = {30, 30, 30};

float player_x = 4.5f;
float player_y = 3.5f;
char player_dir = 'N';