#pragma once

#include "IService.h"

#include <string>
#include <memory>
#include <mutex>
#include <optional>
#include <unordered_map>
#include <vector>


/**
 * @class ServiceManager
 * @brief A thread-safe singleton-style service registry to manage IService instances.
 * 
 * Allows registration and retrieval of services by their class name as a string.
 * Services are stored as shared pointers and accessed via std::optional<std::reference_wrapper<IService>>.
 */
class ServiceManager
{
    /**
     * @brief Returns the internal map storing services.
     * 
     * This map uses service class names as keys and shared pointers to IService as values.
     * 
     * @return Reference to the internal service registry map.
     */
    static std::unordered_map<std::string, std::shared_ptr<IService>>& services()
    {
        static std::unordered_map<std::string, std::shared_ptr<IService>> instance;
        return instance;
    }

    /**
     * @brief Returns the mutex used for thread-safe access to the service registry.
     * 
     * @return Reference to the mutex protecting the registry.
     */
    static std::mutex& registryMutex()
    {
        static std::mutex m;
        return m;
    }

    public:
    /**
     * @brief Retrieves a registered service by its class name.
     * 
     * Thread-safe. Returns an optional reference wrapper to the IService instance if found.
     * If no service is registered under the given class name, returns std::nullopt.
     * 
     * @param classname The class name (string) identifying the service.
     * @return std::optional<std::reference_wrapper<IService>> Reference to the IService if found, otherwise nullopt.
     */
    static std::optional<std::reference_wrapper<IService>> getService(const std::string& classname)
    {
        std::lock_guard<std::mutex> lock(registryMutex());

        auto& registry = services();
        auto it = registry.find(classname);

        if (it != registry.end()) return  std::ref(*(it->second));
        return std::nullopt;

    }

    /**
     * @brief Registers a new service instance under the specified class name.
     * 
     * Thread-safe. If a service is already registered under the given class name, it will be replaced.
     * 
     * @param classname The class name (string) under which to register the service.
     * @param service A shared pointer to the IService instance to register.
     */
    static void registerService(const std::string& classname, std::shared_ptr<IService> service)
    {
        std::lock_guard<std::mutex> lock(registryMutex());

        services()[classname] = std::move(service);
    }
};