#pragma once
#include <iostream>
#include <vector>
#include <optional>

#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

typedef enum vk_info
{
    MY_VK_SUCCESS = 0,
    MY_VK_ERROR = 1,
    MY_RUNTIME_ERROR = 2,
    MY_GET_PHYSICAL_ERROR = 3,
    MY_CREATE_DEVICE_ERROR = 4,
    MY_CREATE_SURFACE_ERROR = 5,
    MY_CREATE_SWAP_CHAIN_ERROR = 6,
    MY_CREATE_IMAGE_VIEWS_ERROR = 7,
    MY_OPEN_FILE_ERROR = 8,
    MY_CREATE_SHADER_MODULE_ERROR = 9,
    MY_CREATE_PIPELINE_LAYOUT_ERROR = 10,
    MY_CREATE_RENDER_PASS_ERROR = 11,
    MY_CREATE_GRAPHICS_PIPELINE_FAILED = 12,
    MY_CREATE_FRAME_BUFFER_ERROR = 13,
    MY_CREATE_COMMAND_POOL_ERROR = 14,
    MY_CREATE_COMMAND_BUFFERS_ERROR = 15,
    MY_BEGIN_RECORDING_COMMAND_BUFFER_ERROR = 16,
    MY_CREATE_SEMAPHORES_ERROR = 17,
    MY_SUBMIT_DRAW_COMMAND_BUFFER_ERROR = 18
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pCallback);
void DestroyDebugUtilsMessengerEXT(VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class HelloTriangleApplication
{
public:
    HelloTriangleApplication()
        :window(nullptr)
    {

    }
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }
private:
    void initWindow();
    vk_info initVulkan();
    void mainLoop();
    void cleanup();
    vk_info createInstance();
    //pyhsicalDevice
    vk_info pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    //logicalDevice
    vk_info createLogicalDevice();
    //createSurface
    vk_info createSurface();
    //swapChain
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    vk_info createSwapChain();
    //imageView
    vk_info createImageViews();
    //graphicsPipeline
    vk_info createGraphicsPipline();
    //shaderModule
    vk_info createShaderModule(const std::vector<char>& code, VkShaderModule& t_shaderModule);
    //createRender
    vk_info createRenderPass();
    //framebuffers
    vk_info createFramebuffers();
    //commandPool
    vk_info createCommandPool();
    vk_info createCommandBuffers();
    vk_info recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    //createSemaphore
    vk_info createSemaphores();
    //render&draw
    vk_info drawFrame();

    

    //DEBUG
    VkDebugUtilsMessengerEXT debugMessenger;
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
    {
        std::cerr << "validation_layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }
    vk_info setupDebugCallback();

    GLFWwindow* window;
    VkInstance instance;
    const int WIDTH = 800;
    const int HEIGHT = 600;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;

    VkSwapchainKHR swapChain;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkImage> swapChainImages;

    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    //std::vector<VkCommandBuffer> commandBuffers;
    VkCommandBuffer commandBuffer;

    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;

    VkPipeline graphicsPipeline;
    VkCommandPool commandPool;

    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
};