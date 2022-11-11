#ifndef NANOVK_VIEW_
#define NANOVK_VIEW_

/* Takes care of the window, device, image and swapchain setup*/

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <string>
#include <vector>

namespace nanovk {

	struct ViewProperties
	{
		vk::PhysicalDevice base_device;
		vk::UniqueSurfaceKHR surface;
		unsigned int framebuffer_width;
		unsigned int framebuffer_height;
	};

	class View {

		GLFWwindow* window_;

		vk::UniqueInstance instance_;
		vk::PhysicalDevice phy_device_;
		vk::Semaphore next_image_available_signal_;
		ViewProperties properties_;

	public:
		View(const std::string& window_name, int width, int height);
		~View();
		//void loop(const Device& device, const Pipeline& pipeline) const; TODO
		const ViewProperties& getProperties() const;
		//void windowResizeCallback(void* callback) const; TODO
	};

}  // namespace nanovk

#endif  // NANOVK_VIEW_
