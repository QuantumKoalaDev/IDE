#include "OffsetVector.h"

#include <stdexcept>

using Core::UiResources::Datastructures::OffsetVector;

OffsetVector::OffsetVector(std::vector<std::string>&& viewPort, size_t beginOffset)
	: m_viewPort(std::move(viewPort)), m_beginOffset(beginOffset)
{}

OffsetVector::~OffsetVector() {}

size_t OffsetVector::getSize() const
{
	return m_viewPort.size();
}

size_t OffsetVector::getOffsetBegin() const
{
	return m_beginOffset;
}

const std::vector<std::string>& OffsetVector::getLines()
{
	return m_viewPort;
}

void OffsetVector::addLine(const std::string& line, size_t lineId)
{
	if (lineId > m_beginOffset + m_viewPort.size())
		throw new std::invalid_argument("OffsetVector: addLine, lineId was to large");

	if (lineId < m_beginOffset + m_viewPort.size() - 1)
	{
		size_t pos = lineId - m_beginOffset;
		m_viewPort.insert(m_viewPort.begin() + pos, line);
		return;
	}

	m_viewPort.push_back(line);
}

void OffsetVector::eraseLine(size_t lineId)
{
	size_t itPos = lineId - m_beginOffset;

	m_viewPort.erase(m_viewPort.begin() + itPos);
}

void OffsetVector::replaceLine(const std::string& line, size_t lineId)
{
	m_viewPort[lineId - m_beginOffset] = line;
}