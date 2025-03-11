#include "cbpch.h"
#include <glad/glad.h>
#include "WindowsWindow.h"
#include "../OpenGL/OpenGLRenderContext.h"
#include "../../Core/Utility/Log.h"
#include "../../Core/Events/ApplicationEvent.h"
#include "../../Core/Events/KeyEvent.h"
#include "../../Core/Events/MouseEvent.h"


namespace Cubes {

    static void GLFWErrorCallback(int error, const char* description) {
        CB_CORE_ERROR("GLFW error has occured: {0}", error);
    }

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        _data.Width = props.Width;
        _data.Height = props.Height;
        _data.Title = props.Title;
        

        initGLFW();
        _window = glfwCreateWindow(_data.Width, _data.Height, _data.Title.c_str(), NULL, NULL);
        _context = new OpenGLRenderContext(_window);
        glfwSetWindowUserPointer(_window, &_data);
        SetVSync(true);


        //Set GLFW Callbacks
        glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent e(width, height);
            data.EventCallback(e);
        });

        glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent e;
            data.EventCallback(e);
            
        });

        glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            //TODO: Convert in Cubes Keycode
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent e(key, 0);
                    data.EventCallback(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent e(key);
                    data.EventCallback(e);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent e(key, 1);
                    data.EventCallback(e);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent e(button);
                    data.EventCallback(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent e(button);
                    data.EventCallback(e);
                    break;
                }
            }
        });

        glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent e((float)xoffset, (float)yoffset);
            data.EventCallback(e);
        });

        glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent e((float)xpos, (float)ypos);
            data.EventCallback(e);
        });
    }

    WindowsWindow::~WindowsWindow()
    {
        glfwDestroyWindow(_window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        _context->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        _data.VSync = enabled;
    }

    void WindowsWindow::initGLFW()
    {
        if (!GLFW_INITIALIZED) {
            if (!glfwInit()) {
                CB_CORE_ERROR("GLFW isn't initialized");
            }
            glfwSetErrorCallback(GLFWErrorCallback);
        }
    }

    void WindowsWindow::setupOpenGL()
    {
        glfwMakeContextCurrent(_window);
        int succes = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!succes)
            CB_CORE_ERROR("Isn't able to load OpenGL functions");
    }

}
