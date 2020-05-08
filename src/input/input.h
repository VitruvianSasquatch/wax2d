#ifndef INPUT_H
#define INPUT_H


#define SDLK_LEFTCLICK (-1)
#define SDLK_MIDDLECLICK (-2)
#define SDLK_RIGHTCLICK (-3)


void input_init(void);


void input_update(void);


int input_getMouseX(void);


int input_getMouseY(void);


int input_isDown(int code);


int input_justPressed(int code);


int input_justReleased(int code);



#endif //INPUT_H