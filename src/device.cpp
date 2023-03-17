#include "nanovk/device.h"

namespace nanovk {
Device::Device(vk::raii::PhysicalDevice&& phy_device)
    : vk_phy_device_(phy_device) {}

const Stream& Device::CreateStream(StreamType type) { return {}; }

}  // namespace nanovk

/*
nanovk::Device::Device(const nanovk::ViewProperties& view) {

        std::optional<QueueProperties> graphics_q;
        unsigned int current_idx = 0;
        for (const auto& avail_q : view.base_device.getQueueFamilyProperties())
{ bool surface_support = view.base_device.getSurfaceSupportKHR(current_idx,
view.surface.get()); if (!graphics_q && avail_q.queueFlags &
vk::QueueFlagBits::eGraphics && surface_support) { graphics_q = {
                                {},
                                avail_q.queueFlags,
                                current_idx,
                                surface_support
                        };
                }
                current_idx++;
        }

        if (!graphics_q) {
                throw std::runtime_error("Unable to find suitable queue with
presentation and graphics");
        }

        graphics_queue_ = graphics_q.value();

        const std::vector queue_priority = { 1.f };
        const vk::DeviceQueueCreateInfo info(
                {},
                graphics_queue_.index,
                queue_priority
        );
        std::vector queue_info_list = { info };

        std::vector enabled_extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
        unsigned int missing_extensions = enabled_extensions.size();

        for (const auto& avail_extension :
view.base_device.enumerateDeviceExtensionProperties()) { std::cout <<
avail_extension.extensionName << "\n"; for (const auto& enabled :
enabled_extensions) { if
(std::string_view(avail_extension.extensionName).compare(enabled) == 0) {
                                missing_extensions--;
                        }
                }
        }

        if (missing_extensions > 0) {
                throw std::runtime_error("Not all extensions to enable are
supported");
        }

        vk::PhysicalDeviceFeatures enabled_features;
        vk::DeviceCreateInfo device_info;
        device_info.setQueueCreateInfos(queue_info_list);
        device_info.setPEnabledExtensionNames(enabled_extensions);
        device_info.setPEnabledFeatures(&enabled_features);
        device_ = view.base_device.createDeviceUnique(device_info);
        surface_properties_ = {
                view.surface.get(),
                view.base_device.getSurfaceCapabilitiesKHR(view.surface.get()),
                view.base_device.getSurfaceFormatsKHR(view.surface.get()),
                view.base_device.getSurfacePresentModesKHR(view.surface.get())
        };

        createSwapchain({ view.framebuffer_width, view.framebuffer_height });
}

void nanovk::Device::createSwapchain(const vk::Extent2D& extent) {
        std::optional<vk::SurfaceFormatKHR> format;
        for (auto const& avail_format : surface_properties_.formats) {
                if (avail_format.format == vk::Format::eB8G8R8A8Srgb &&
                        avail_format.colorSpace ==
vk::ColorSpaceKHR::eSrgbNonlinear) { format = avail_format;
                }
        }

        if (!format) {
                throw std::runtime_error("8-bit SRGB non linear not available");
        }

        std::optional<vk::PresentModeKHR> present_mode;
        for (auto const& avail_mode : surface_properties_.present_modes) {
                if (avail_mode == vk::PresentModeKHR::eMailbox) {
                        present_mode = avail_mode;
                }
        }

        if (!present_mode) {
                present_mode = vk::PresentModeKHR::eFifo;
                std::cout << "MAILBOX 'triple buffer' not available, using FIFO
\n";
        }

        vk::Extent2D actual_extent;
        if (surface_properties_.capabilities.currentExtent.width !=
                std::numeric_limits<uint32_t>::max()) {
                actual_extent = surface_properties_.capabilities.currentExtent;
        } else {
                const unsigned int actual_width = std::clamp(
                        extent.width,
                        surface_properties_.capabilities.minImageExtent.width,
                        surface_properties_.capabilities.maxImageExtent.width
                );
                const unsigned int actual_height = std::clamp(
                        extent.height,
                        surface_properties_.capabilities.minImageExtent.height,
                        surface_properties_.capabilities.maxImageExtent.height
                );
                actual_extent.setWidth(actual_width);
                actual_extent.setHeight(actual_height);
        }

        unsigned int swap_chain_size =
surface_properties_.capabilities.minImageCount + 1; if
(surface_properties_.capabilities.maxImageCount > 0 && swap_chain_size >
surface_properties_.capabilities.maxImageCount) { swap_chain_size =
surface_properties_.capabilities.maxImageCount;
        }

        vk::SwapchainCreateInfoKHR swap_chain_create_info(
                {},
                surface_properties_.surface,
                swap_chain_size,
                format.value().format,
                format.value().colorSpace,
                actual_extent,
                1,
                vk::ImageUsageFlagBits::eColorAttachment
        );

        swap_chain_create_info.setImageSharingMode(vk::SharingMode::eExclusive);

        swap_chain_create_info.setPreTransform(surface_properties_.capabilities.currentTransform);
        swap_chain_create_info.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
        swap_chain_create_info.setPresentMode(present_mode.value());
        swap_chain_create_info.setClipped(VK_TRUE);
        swap_chain_create_info.setOldSwapchain(VK_NULL_HANDLE);

        swapchain_.instance =
device_->createSwapchainKHRUnique(swap_chain_create_info); swapchain_.images =
device_->getSwapchainImagesKHR(swapchain_.instance.get()); swapchain_.format =
format.value().format; swapchain_.extent = actual_extent;
}
*/