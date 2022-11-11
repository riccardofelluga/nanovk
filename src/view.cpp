#include "nanovk/view.h"
#include <optional>

nanovk::View::View(const std::string& window_name, int width, int height) {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window_ =
		glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);

	vk::ApplicationInfo app_info;
	app_info.setPApplicationName(window_name.c_str());
	app_info.setPEngineName("nanovk");
	app_info.setEngineVersion(VK_MAKE_VERSION(0, 1, 0));
	app_info.setApiVersion(VK_API_VERSION_1_3);

	uint32_t glfw_extensions_count = 0;
	const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extensions_count);
	std::vector validation_layers = { "VK_LAYER_KHRONOS_validation" };

	vk::InstanceCreateInfo app_instance_info({}, &app_info);
	app_instance_info.setEnabledLayerCount(validation_layers.size());
	app_instance_info.setPEnabledLayerNames(validation_layers);
	app_instance_info.setEnabledExtensionCount(glfw_extensions_count);
	app_instance_info.setPpEnabledExtensionNames(glfw_extensions);
	instance_ = vk::createInstanceUnique(app_instance_info);

	std::optional<vk::PhysicalDevice> available_device;
	for (const auto& device : instance_->enumeratePhysicalDevices()) {
		const auto& properties = device.getProperties();
		std::cout << "Found " << vk::to_string(properties.deviceType) << " with name " << properties.deviceName << "\n";
		if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu || properties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu) {
			available_device = device;
		}
	}

	if (!available_device) {
		throw std::runtime_error("No devices available");
	}
	
	properties_.base_device = available_device.value();

	VkSurfaceKHR raw_surface;
	if (glfwCreateWindowSurface(instance_.get(), window_, nullptr, &raw_surface)) {
		throw std::runtime_error("Unable to create surface");
	}

	vk::ObjectDestroy< vk::Instance, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE > destroyer{ instance_.get() };
	properties_.surface = vk::UniqueSurfaceKHR{ vk::SurfaceKHR( raw_surface ), destroyer };    

	int fb_width, fb_height;
	glfwGetFramebufferSize(window_, &fb_width, &fb_height);
	properties_.framebuffer_width = fb_width;
	properties_.framebuffer_height = fb_height;
}

const nanovk::ViewProperties& nanovk::View::getProperties() const{
	return properties_;
}


nanovk::View::~View() {
	glfwDestroyWindow(window_);
	glfwTerminate();
}

/*void nanovk::View::loop(const Device& device, const Pipeline& pipeline) const {
	while (!glfwWindowShouldClose(window_)) {
		glfwPollEvents();
	}
}*/
