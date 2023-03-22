#ifndef NANOVK_WINDOW_H_
#define NANOVK_WINDOW_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <memory>
#include <optional>
#include <vector>

namespace nanovk {
class WindowSurface {
 public:
  static std::unique_ptr<WindowSurface> Create(const std::string& window_title,
                                               uint32_t width, uint32_t height);

  const std::vector<const char*> GetWindowExtensions() const;

  std::optional<VkSurfaceKHR> CreateVkSurface(const VkInstance& instance) const;

  void OpenWindowAndLoop(std::function<void()> draw_fn) const;

  explicit WindowSurface(GLFWwindow* window) : window_(window){};
  ~WindowSurface();

 private:
  GLFWwindow* window_;
};

}  // namespace nanovk
#endif  // NANOVK_WINDOW_H_
