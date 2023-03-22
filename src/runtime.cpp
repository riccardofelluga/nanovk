#include "nanovk/runtime.h"

namespace nanovk {

std::unique_ptr<Runtime> Runtime::CreateWithExtensions(const std::string& name, std::vector<const char*> instance_extensions,
                                         bool with_validation) {
  vk::raii::Context context;

  vk::ApplicationInfo runtime_info;
  runtime_info.setPApplicationName(name.c_str());
  runtime_info.setPEngineName("nanoVk");
  runtime_info.setEngineVersion(VK_MAKE_VERSION(0, 1, 0));
  runtime_info.setApiVersion(VK_API_VERSION_1_3);

  std::vector<const char*> layers;
  if (with_validation) {
    layers.push_back("VK_LAYER_KHRONOS_validation");
  }

  vk::InstanceCreateFlags instance_flags;

#ifdef __APPLE__
  instance_flags |= vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
  instance_extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

  vk::InstanceCreateInfo instance_info(instance_flags, &runtime_info);
  instance_info.setPEnabledLayerNames(layers);
  instance_info.setPEnabledExtensionNames(instance_extensions);
  auto instance = context.createInstance(instance_info);

  return std::make_unique<Runtime>(context.createInstance(instance_info));
}

// std::optional<Device> Runtime::GetDevice(DeviceType type) {
//   vk::raii::PhysicalDevices physical_devices(instance_);
//   for (auto& device : physical_devices) {
//     if (device.getProperties().deviceType ==
//         static_cast<vk::PhysicalDeviceType>(type)) {
//       std::cout << "Found device " << device.getProperties().deviceName << "\n";
//       return {std::move(device)};
//     }
//   }
//   return {};
// }

}  // namespace nanovk
