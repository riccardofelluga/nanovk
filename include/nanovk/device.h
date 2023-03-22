#ifndef NANOVK_DEVICE_H_
#define NANOVK_DEVICE_H_

#include <optional>
#include <vulkan/vulkan_raii.hpp>

namespace nanovk {

enum class DeviceType {
  GPU = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,
  IntegratedGraphics = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU
};

class Device {
 public:
  std::unique_ptr<Device> Create();

  void SubmitQueueAndWait();

 private:
  Device(vk::raii::PhysicalDevice&& phy_device);

  vk::raii::PhysicalDevice vk_phy_device_;
};
}  // namespace nanovk

#endif  // NANOVK_DEVICE_H_
