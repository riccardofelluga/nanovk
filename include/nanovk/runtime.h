#ifndef NANOVK_RUNTIME_H_
#define NANOVK_RUNTIME_H_

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <vulkan/vulkan_raii.hpp>

#include "device.h"
#include "window.h"

namespace nanovk {
class Runtime {
 public:
  static std::unique_ptr<Runtime> CreateWithExtensions(
      const std::string& name, std::vector<const char*> instance_extensions,
      bool with_validation = true);

  std::unique_ptr<Device> CreateDeviceWithSurface(
      const vk::PhysicalDeviceType& type, const WindowSurfaceInfo& surface) const;
  const vk::Instance& GetInstance() const;

  explicit Runtime(vk::raii::Instance&& instance)
      : instance_(std::move(instance)){};
  ~Runtime();

 private:
  vk::raii::Instance instance_;
};

}  // namespace nanovk
#endif  // NANOVK_RUNTIME_H_
