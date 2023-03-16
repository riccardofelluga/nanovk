#ifndef NANOVK_DEVICE_
#define NANOVK_DEVICE_

#include <optional>
#include "nanovk/view.h"
#include <vulkan/vulkan_raii.hpp>

#include "stream.h"

namespace nanovk {

enum class DeviceType {
  GPU = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,
  IntegratedGraphics = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU
};

class Device {
 public:
  Device();
  Device(vk::raii::PhysicalDevice&& vk_physical_device);

  const Stream& CreateStream(StreamType type);

 private:
  vk::raii::PhysicalDevice vk_phy_device_;
  std::vector<std::unique_ptr<Stream>> streams_;
};
}  // namespace nanovk

#endif  // NANOVK_DEVICE_
