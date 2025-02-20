//Until now is uses Keycodes per platform
//Later there should be functionality to convert keycodes

//---------GLFW MouseButton Codes-----------
#if CB_PLATFORM_WINDOWS

#define CB_MOUSE_BUTTON_1         0
#define CB_MOUSE_BUTTON_2         1
#define CB_MOUSE_BUTTON_3         2
#define CB_MOUSE_BUTTON_4         3
#define CB_MOUSE_BUTTON_5         4
#define CB_MOUSE_BUTTON_6         5
#define CB_MOUSE_BUTTON_7         6
#define CB_MOUSE_BUTTON_8         7
#define CB_MOUSE_BUTTON_LAST      CB_MOUSE_BUTTON_8
#define CB_MOUSE_BUTTON_LEFT      CB_MOUSE_BUTTON_1
#define CB_MOUSE_BUTTON_RIGHT     CB_MOUSE_BUTTON_2
#define CB_MOUSE_BUTTON_MIDDLE    CB_MOUSE_BUTTON_3

#endif // CB_PLATFORM_WINDOWS
