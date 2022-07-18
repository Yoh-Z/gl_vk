#pragma once
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

typedef enum vk_info
{
    MY_VK_SUCCESS = 0,
    MY_VK_ERROR = 1,
    MY_RUNTIME_ERROR = 2
};

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef DEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pCallback);

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
};