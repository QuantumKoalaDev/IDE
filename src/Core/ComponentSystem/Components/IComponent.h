#pragma once

#include <Core/EventSystem/Events/Event.h>

#include <memory>

/**
 * @brief Interface for components that hold data to be displayed by the UI.
 * 
 * Provides a method to retrieve a unique identifier for the component.
 */
class IComponent
{
    public:
    /**
     * @brief Get the unique identifier of the component.
     * 
     * @return unsigned int The ID of the component.
     */
    virtual size_t getId() = 0;
    virtual void executeEvent(const Core::EventSystem::Events::Event& ev) = 0;

    virtual ~IComponent() = default;

};