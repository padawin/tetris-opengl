#ifndef __RENDERER__
#define __RENDERER__

bool renderer_init(int window_width, int window_height, const char* title, bool fullscreen);
void renderer_main_loop();
void renderer_cleanup();

#endif
