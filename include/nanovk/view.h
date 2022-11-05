#ifndef NANOVK_VIEW_
#define NANOVK_VIEW_

/* Takes care of the window, device, image and swapchain setup*/

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

namespace nanovk {

	class Device {
	};

	class View {

		GLFWwindow* window_;
		vk::Instance vk_instance_;
		vk::SurfaceKHR vk_surface_;
		Device vk_device_;

	public:
		View(const std::string& window_name, int width, int height);
		View(const View&) = delete;
		View(View&&) = delete;
		View& operator=(const View&) = delete;
		View& operator=(View&&) = delete;
		~View();

		void render(const Device& device) const;
		Device getDevice();
	};

}  // namespace nanovk

#endif  // NANOVK_VIEW_
