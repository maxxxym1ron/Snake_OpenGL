#include <GLFW/glfw3.h>

class Window {
    GLFWwindow* m_handle = nullptr;

    /* monitor info */
    int m_mWidth;
    int m_mHeight;
    int m_mRefreshRate;

    /* window info */
    int m_width;
    int m_height;
    bool m_fullscreen;

    bool terminated;

    // 348 = GLFW_KEY_LAST = GLFW_KEY_MENU
    inline static bool m_keys[GLFW_KEY_LAST + 1]{};

public:
    Window(int width, int height, bool fullscreen);

    ~Window() { terminateWindow(); }
    void terminate() { terminateWindow(); }

    void close() const;
    bool shouldClose();
    
    void pollEvents();
    void swapBuffers();

    void setTitle(const int& fps, const int& length);

    bool isKeyPressed(const int& keyID) const { return m_keys[keyID]; }

private:
    void terminateWindow();

    static void errorCallback(const int error_code, const char *description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};