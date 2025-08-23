#pragma once

#include <string>
#include <vector>

namespace Core::UiResources::Datastructures
{
	/**
	 * @class OffsetVector
	 * @brief A container for managing a sequence of text lines with an offset.
	 *
	 * The OffsetVector stores a contiguous collection of text lines (as strings)
	 * along with a starting offset that represents the logical index of the
	 * first element in the view. This allows the vector to be used as a
	 * "window" into a larger text buffer, while still providing direct
	 * access and modification of its lines.
	 *
	 * Typical use cases include:
	 * - Representing a viewport of text in an editor or UI.
	 * - Managing a subset of lines with their original indices preserved.
	 *
	 * The class provides functionality to:
	 * - Query size and current offset.
	 * - Retrieve all lines.
	 * - Add, erase, and replace individual lines by their logical ID.
	 */
	class OffsetVector
	{
		// the offset is the 0 pos in the vector
		size_t m_beginOffset;
		std::vector<std::string> m_viewPort;

		public:
			/**
			 * @brief Constructs an OffsetVector with a given set of lines and an offset.
			 *
			 * @param viewPort A vector of strings representing the initial lines.
			 * @param beginOffset The starting offset to associate with the first line.
			 */
			OffsetVector(std::vector<std::string>&& viewPort, size_t beginOffset);

			/**
			 * @brief Default destructor.
			 */
			~OffsetVector();

			/**
			 * @brief Gets the number of lines stored in the vector.
			 *
			 * @return The size of the underlying viewport vector.
			 */
			size_t getSize() const;
			
			/**
			 * @brief Gets the offset associated with the first line.
			 *
			 * @return The beginning offset.
			 */
			size_t getOffsetBegin() const;

			/**
			 * @brief Retrieves all stored lines.
			 *
			 * @return A constant reference to the underlying vector of strings.
			 */
			const std::vector<std::string>& getLines();

			/**
			 * @brief Adds a new line to the vector.
			 *
			 * @param line The line string to be added.
			 * @param lineId The line identifier.
			 */
			void addLine(const std::string& line, size_t lineId);

			/**
			 * @brief Erases a line at a given position.
			 *
			 * @param lineId The identifier of the line to erase, relative to the offset.
			 *
			 * @note The method calculates the position by subtracting @ref m_beginOffset from lineId.
			 */
			void eraseLine(size_t lineId);


			/**
			 * @brief Replaces a line at the given identifier with a new string.
			 *
			 * @param line The new line string to insert.
			 * @param lineId The identifier of the line to replace, relative to the offset.
			 */
			void replaceLine(const std::string& line, size_t lineId);

	};
}