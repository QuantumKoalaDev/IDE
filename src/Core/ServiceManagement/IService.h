#pragma once

/**
 * @interface IService
 * @brief Abstract base interface for all services.
 * 
 * Provides a virtual destructor to allow safe polymorphic deletion of derived service instances.
 */
class IService 
{
    public:
    /**
     * @brief Virtual destructor for interface.
     * 
     * Ensures derived classes are destructed properly through base class pointers.
     */
    virtual ~IService() = default;
};