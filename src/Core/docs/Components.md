# Creating a Component

- Request the current ID from the `ComponentManager`
- Set the ID in the Component's constructor
- Add the component via `addComponent` to the `ComponentManager`
  - The `ComponentManager` increases the current ID when adding a component

## Planned Improvements

- Introduce a global manager system for all managers
  - Components ask the `ComponentManager` directly in their constructor
  - The `ComponentManager` assigns IDs automatically
  - Components are added to the `ComponentManager` automatically upon creation
