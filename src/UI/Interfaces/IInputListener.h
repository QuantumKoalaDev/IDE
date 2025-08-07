#pragma once

/// @interface IInputListener
/// @brief Interaface for components that respond to input events.
/// 
/// This interface should be implemented by any widget or component
/// that wants to receive and handle input events such as key presses
/// or mouse actions.

class Event;

class IInputListener
{
public:
	/// @brief Handles an input event dispatched by the EventManager.
	/// This method is called when an event relevant to the listener is triggered.
	virtual void onEvent(Event& event) = 0;
};