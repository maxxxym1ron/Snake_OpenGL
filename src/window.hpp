#include <GLFW/glfw3.h>

class Window {
    GLFWwindow* m_handle = nullptr;

    /* monitor info */
    int mWidth;
    int mHeight;
    int mRefreshRate;

    /* window info */
    int wWidth;
    int wHeight;
    bool fullscreen;

    bool terminated;

    // 348 = GLFW_KEY_LAST = GLFW_KEY_MENU
    inline static bool m_keys[GLFW_KEY_LAST + 1]{};

    void terminateWindow();

public:
    Window(int width_, int height_, bool fullscreen_);

    ~Window() { terminateWindow(); }
    void terminate() { terminateWindow(); }

    void close() const;
    bool shouldClose();
    
    void pollEvents();
    void swapBuffers();

    void setTitle(const int& fps, const int& length);

    bool isKeyPressed(const int& keyID) const { return m_keys[keyID]; }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};