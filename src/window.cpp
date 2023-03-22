#include "nanovk/window.h"

namespace nanovk
{
    std::unique_ptr<WindowSurface> WindowSurface::Create(const std::string& window_title, uint32_t width, uint32_t height){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        auto window = glfwCreateWindow(1200, 800, "nanovk", nullptr, nullptr);
        return std::make_unique<WindowSurface>(window);
    }

    const std::vector<const char*> WindowSurface::GetWindowExtensions() const {
        uint32_t glfw_ext_count;
        const char** glfw_ext_ptr = glfwGetRequiredInstanceExtensions(&glfw_ext_count);
        std::vector<const char*> extensions(glfw_ext_ptr,  glfw_ext_ptr + glfw_ext_count);
        return extensions;
    }

    std::optional<VkSurfaceKHR> WindowSurface::CreateVkSurface(const VkInstance& instance) const {
        VkSurfaceKHR surface;
        VkResult error = glfwCreateWindowSurface(instance, window_, nullptr, &surface);
        if (error)
            return {};
        return surface;
    }

    void WindowSurface::OpenWindowAndLoop(std::function<void()> draw_fn) const {
        while(!glfwWindowShouldClose(window_)){
            glfwPollEvents();
            draw_fn();
        }
    }
    
    WindowSurface::~WindowSurface() {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }
} // namespace nanovk
