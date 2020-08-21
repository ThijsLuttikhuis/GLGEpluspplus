//
// Created by thijs on 12-08-20.
//

#ifndef GLGEPLUSPLUS_MOUSEINPUT_H
#define GLGEPLUSPLUS_MOUSEINPUT_H



#define GLGE_MOUSE_FPS          0x0001
#define GLGE_MOUSE_CURSOR_FPS   0x0002
#define GLGE_MOUSE_3__          0x0004
#define GLGE_MOUSE_4__          0x0008

class Window;

class MouseInput {
private:
    int mode;
    float mouseSpeed = 0.005f;
public:
    MouseInput(Window* handle, int mode);


    void update(Window* handle);
};


#endif //GLGEPLUSPLUS_MOUSEINPUT_H
