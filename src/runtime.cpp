#include "nanovk/runtime.h"

namespace nanovk {
Runtime::Runtime(const std::string& name, bool enable_validation)
    : vk_instance_(nullptr), vk_surface_(nullptr) {
  vk_context_ = vk::raii::Context();

  vk::ApplicationInfo runtime_info;
  runtime_info.setPApplicationName(name.c_str());
  runtime_info.setPEngineName("nanovk");
  runtime_info.setEngineVersion(VK_MAKE_VERSION(0, 1, 0));
  runtime_info.setApiVersion(VK_API_VERSION_1_3);

  std::vector<const char*> layers;
  if (enable_validation) {
    layers.push_back("VK_LAYER_KHRONOS_validation");
  }

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window_ = glfwCreateWindow(1200, 800, name.c_str(), nullptr, nullptr);

  uint32_t glfw_ext_count;
  const char** glfw_ext_ptr =
      glfwGetRequiredInstanceExtensions(&glfw_ext_count);

  std::vector<const char*> extensions;
  extensions.reserve(glfw_ext_count);

  for (uint32_t i = 0; i < glfw_ext_count; i++) {
    extensions.push_back(glfw_ext_ptr[i]);
    std::cout << glfw_ext_ptr[i] << "\n";
  }

  vk::InstanceCreateInfo instance_info({}, &runtime_info);
  instance_info.setPEnabledLayerNames(layers);
  instance_info.setPEnabledExtensionNames(extensions);
  vk_instance_ = vk_context_.createInstance(instance_info);

  VkSurfaceKHR vk_raw_surface;
  if (glfwCreateWindowSurface(*vk_instance_, window_, nullptr,
                              &vk_raw_surface)) {
    throw std::runtime_error("Unable to create GLFW surface");
  }
  vk_surface_ = vk::raii::SurfaceKHR(vk_instance_, vk_raw_surface);
}

Runtime::~Runtime() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

std::optional<Device> Runtime::GetDevice(DeviceType type) {
  vk::raii::PhysicalDevices physical_devices(vk_instance_);
  for (auto& device : physical_devices) {
    if (device.getProperties().deviceType ==
        static_cast<vk::PhysicalDeviceType>(type)) {
      std::cout << "Found device " << device.getProperties().deviceName << "\n";
      return {std::move(device)};
    }
  }
  return {};
}

void Runtime::Loop() {
  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();
  }
}

}  // namespace nanovk
