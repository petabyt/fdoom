#include <stdio.h>
#include <doomkeys.h>
#include <m_argv.h>
#include <doomgeneric.h>

#include <buttons.h>

void D_DoomMain (void);
void M_FindResponseFile(void);
void dg_Create();

extern int myargc;
extern char **myargv;

int last_key = 0;
int key_queue = 0;

void DG_Init() {
	printf("Init bmp\n");
	sys_init_bmp();
}

void check_keys() {
	int key = 0;
	if (sys_check_key(SYS_BUTTON_DOWN)) {
		key = KEY_DOWNARROW;
	} else if (sys_check_key(SYS_BUTTON_UP)) {
		key = KEY_UPARROW;
	} else if (sys_check_key(SYS_BUTTON_RIGHT)) {
		key = KEY_RIGHTARROW;
	} else if (sys_check_key(SYS_BUTTON_LEFT)) {
		key = KEY_LEFTARROW;
	} else if (sys_check_key(SYS_BUTTON_QUIT)) {
		key = KEY_ESCAPE;
	} else if (sys_check_key(SYS_BUTTON_OK)) {
		key = KEY_ENTER;
	}

	if (key == 0) {
		if (last_key != 0) {
			key_queue = last_key;
			last_key = 0;
		}
	}

	last_key = key;
}

void DG_DrawFrame() {
	check_keys();
	puts("rendering");
	for (int x = 0; x < DOOMGENERIC_RESX * DOOMGENERIC_RESY; x++) {
		uint32_t col = DG_ScreenBuffer[x];
		//col &= 0x000000ff;
		//printf("%dx%d\n", (x % DOOMGENERIC_RESX), (x / DOOMGENERIC_RESX));
		bmp_pixel((x % DOOMGENERIC_RESX), (x / DOOMGENERIC_RESX), col);
	}
	puts("Done");

	bmp_apply();
}

void DG_SleepMs(uint32_t ms) {
	msleep(ms);
}

uint32_t DG_GetTicksMs() {
	return sys_get_ticks();
}

void DG_SetWindowTitle(const char * title) {
	puts("Window title");
}

int DG_GetKey(int* pressed, unsigned char* key) {
	*key = key_queue;
	if (key_queue == 0) {
		*pressed = 0;
		return 0;
	} else {
		key_queue = 0;
		*pressed = 1;
		return 1;
	}
}

int main() {
	printf("Init\n");
	sys_init_bmp();
	myargc = 3;

	char *args[] = {"doom", "-iwad", "doom1.wad"};
	myargv = args;

	printf("M_FindResponseFile()\n");
	M_FindResponseFile();

	printf("Creating doom context...\n");
	dg_Create();

	printf("Running doom...");
	D_DoomMain();

	return 0;
}
