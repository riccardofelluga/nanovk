#ifndef NANOVK_WINDOW_H_
#define NANOVK_WINDOW_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace nanovk {
struct WindowSurfaceInfo {
  VkSurfaceKHR handle;
  VkExtent2D extent;
};

class Window {
 public:
  static std::unique_ptr<Window> Create(const std::string& window_title,
                                               uint32_t width, uint32_t height);

  const std::vector<const char*> GetWindowExtensions() const;

  VkExtent2D GetVkWindowExtent() const;

  std::optional<WindowSurfaceInfo> GetSurface(const VkInstance& instance) const;

  void OpenWindowAndLoop(std::function<void()> draw_fn) const;

  explicit Window(GLFWwindow* window) : window_(window){};
  ~Window();

 private:
  GLFWwindow* window_;
};

}  // namespace nanovk
#endif  // NANOVK_WINDOW_H_
