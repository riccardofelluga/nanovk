#ifndef NANOVK_VIEW_
#define NANOVK_VIEW_

/* Takes care of the window, device, image and swapchain setup*/

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

namespace nanovk {

class View {
 private:
  GLFWwindow* window_;
  vk::Instance vk_instance_;
  vk::SurfaceKHR vk_surface_;

 public:
  View(const std::string& window_name, int width, int height);
  ~View();

  void render();
};

}  // namespace nanovk

#endif  // NANOVK_VIEW_
