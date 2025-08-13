#pragma once


/**
 * @class Widget
 * @brief Base class for all UI widgets.
 *
 * Represents a generic widget in the UI system. Each widget is associated
 * with a component ID and can track its hover and focus states.
 */
class Widget
{
	unsigned int m_componentId;
	bool m_hoverd = false;
	bool m_focused = false;

	public:
		/**
		 * @brief Constructs a Widget with the given component ID.
		 *
		 * @param componentId The ID of the component to be displayed. This ID also serves as the widget ID.
		 */
		Widget(unsigned int componentId) : m_componentId(componentId) {};

		/*
		* @brief Default Destructor
		*/
		virtual ~Widget() = default;


		/**
		 * @brief Returns the ID of the widget/component.
		 * @return The component/widget ID.
		 */
		unsigned int getId() const { return m_componentId; }

		/**
		 * @brief Checks if the widget is currently hovered.
		 * @return True if hovered, false otherwise.
		 */
		bool isHoverd() const { return m_hoverd; }

		/**
		 * @brief Checks if the widget is currently focused.
		 * @return True if focused, false otherwise.
		 */
		bool isFocused() const { return m_focused; }


		/**
		 * @brief Sets the hovered state of the widget.
		 * @param hovered True if the widget should be marked as hovered.
		 */
		void setHoverd(bool hovered) { m_hoverd = hovered; }
		/**
		 * @brief Sets the focused state of the widget.
		 * @param focused True if the widget should be marked as focused.
		 */
		void setFocused(bool focused) { m_focused = focused; }
};