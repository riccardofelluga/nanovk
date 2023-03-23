#include "nanovk/window.h"

namespace nanovk {
std::unique_ptr<Window> Window::Create(
    const std::string& window_title, uint32_t width, uint32_t height) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  auto window = glfwCreateWindow(1200, 800, "nanovk", nullptr, nullptr);

  return std::make_unique<Window>(window);
}

const std::vector<const char*> Window::GetWindowExtensions() const {
  uint32_t glfw_ext_count;
  const char** glfw_ext_ptr =
      glfwGetRequiredInstanceExtensions(&glfw_ext_count);
  std::vector<const char*> extensions(glfw_ext_ptr,
                                      glfw_ext_ptr + glfw_ext_count);
  return extensions;
}

VkExtent2D Window::GetVkWindowExtent() const {
  int width, height;
  glfwGetFramebufferSize(window_, &width, &height);
  return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
}

std::optional<WindowSurfaceInfo> Window::GetSurface(
    const VkInstance& instance) const {
  VkSurfaceKHR surface;
  VkResult error =
      glfwCreateWindowSurface(instance, window_, nullptr, &surface);
  if (error) return {};

  const VkExtent2D extent = GetVkWindowExtent();
  return {{surface, extent}};
}

void Window::OpenWindowAndLoop(std::function<void()> draw_fn) const {
  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();
    draw_fn();
  }
}

Window::~Window() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}
}  // namespace nanovk
