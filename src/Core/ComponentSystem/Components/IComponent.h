#pragma once

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
    virtual unsigned int getId() = 0;

    virtual ~IComponent() = default;

};