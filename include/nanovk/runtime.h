#ifndef NANOVK_RUNTIME_
#define NANOVK_RUNTIME_

#include <optional>
#include <string>
#include <vector>

#include <vulkan/vulkan_raii.hpp>
#include <GLFW/glfw3.h>

#include "device.h"

namespace nanovk {
class Runtime {
 public:
  Runtime(const std::string& name, bool enable_validation = true);
  ~Runtime();

  std::optional<Device> GetDevice(DeviceType type);

  void Subscribe(Device device);

  void Loop();

private:
  GLFWwindow* window_;
 vk::raii::Context vk_context_;
 vk::raii::Instance vk_instance_;
 vk::raii::SurfaceKHR vk_surface_;
};

}  // namespace nanovk
#endif  // NANOVK_RUNTIME_
