#pragma once

#include <Core/ComponentSystem/Components/IComponent.h>
#include <Core/ComponentSystem/ComponentType.h>

#include <vector>

/**
 * @brief Manages the lifetime and storage of components in the system.
 * 
 * The ComponentManager is responsible for storing pointers to components,
 * assigning them unique IDs, and ensuring that allocated memory is freed
 * when the manager is destroyed.
 */
class ComponentManager
{
    unsigned int m_currentId = 0;
    std::vector<IComponent*> m_componentList;

    public:
    /**
     * @brief Constructs an empty ComponentManager.
     */
    ComponentManager() {};

    /**
     * @brief Destructor that cleans up all stored components.
     * 
     * Deletes all dynamically allocated components stored in the component list
     * and clears the container.
     */
    ~ComponentManager();

    /**
     * @brief Adds a new component to the manager.
     * 
     * The component is stored internally for lifetime management. 
     * Currently, the ComponentManager does not assign IDs directly;
     * instead, the component is expected to already have an ID 
     * (for example, set in its constructor).
     * 
     * @note In a future design with a global manager system, components 
     *       will obtain their unique IDs automatically during construction.
     * 
     * @param comp Pointer to the component to be added. Ownership is 
     *             transferred to the ComponentManager.
     * @param type The type of the component (for categorization or logic).
     * @return The ID of the component as returned by comp->getId().
     */
    int addComponent(IComponent* comp, ComponentType type);

    /**
     * @brief Deletes the component with the specified ID from the component list.
     * 
     * This function searches through the stored components and removes the one
     * whose ID matches the given parameter. The component is deleted from memory
     * to avoid leaks.
     * 
     * @param id The unique identifier of the component to delete.
     */
    void deleteComponent(unsigned int id);
};