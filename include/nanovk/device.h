#ifndef NANOVK_DEVICE_
#define NANOVK_DEVICE_

#include <vulkan/vulkan.hpp>
#include <optional>
#include "nanovk/view.h"

namespace nanovk {

	struct QueueProperties {
		vk::Queue queue_instance;
		vk::QueueFlags supported_type;
		unsigned int index;
		bool surface_support;
	};

	struct Swapchain {
		vk::UniqueSwapchainKHR instance;
		std::vector<vk::Image> images;
		vk::SurfaceFormatKHR format;
		vk::Extent2D extent;
	};

	struct SurfaceProperties
	{
		vk::SurfaceKHR surface;
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector<vk::PresentModeKHR> present_modes;
	};

	class Device {

		QueueProperties graphics_queue_;
		SurfaceProperties surface_properties_;
		vk::UniqueDevice device_;
		Swapchain swapchain_;

		void createSwapchain(const vk::Extent2D& extent);

	public:
		Device(const ViewProperties& view_properties);
		void setFramebuffer(unsigned int width, unsigned int height);
		void getNextImage(vk::Semaphore signal_available);
		void presentNextImage(vk::Semaphore render_done_signal);

		vk::UniqueSemaphore createSemaphore() const;
		vk::UniqueFence createSignaledFence() const;
	};

} // namespace nanovk

#endif // NANOVK_DEVICE_
