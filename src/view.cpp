#include "nanovk/view.h"

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
	vk_instance_ = vk::createInstance(app_instance_info);

	VkSurfaceKHR raw_surface;
	if (glfwCreateWindowSurface(vk_instance_, window_, nullptr, &raw_surface)) {
		throw std::runtime_error("Unable to create surface");
	}
	vk_surface_ = raw_surface;
}

nanovk::View::~View() {
	vk_instance_.destroySurfaceKHR(vk_surface_);
	vk_instance_.destroy();

	glfwDestroyWindow(window_);
	glfwTerminate();
}

void nanovk::View::render() const {
	while (!glfwWindowShouldClose(window_)) {
		glfwPollEvents();
	}
}
  }
}