#include "../laba4/stdafx.h"
#include "../laba4/CParallelepiped.h"

CParallelepiped::CParallelepiped(double width, double height, double depth, double density)
	: CBody("Parallelepiped", density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::getDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return m_width * m_height * m_depth;
}

void CParallelepiped::AppendInfoAboutShape(std::ostream & strm) const
{
	strm << "\twidth = " << GetWidth() << std::endl
		<< "\theight = " << GetHeight() << std::endl
		<< "\tdepth = " << getDepth() << std::endl;
}