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
    MY_GET_PHYSICAL_ERROR = 3
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

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    bool isComplete()
    {
        return graphicsFamily.has_value();
    }
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
    //pyhsical
    vk_info pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

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
};