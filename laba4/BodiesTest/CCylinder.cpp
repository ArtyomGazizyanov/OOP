#include "../laba4/stdafx.h"
#include "../laba4/CCylinder.h"

CCylinder::CCylinder(double density, double radius, double height)
	: CBody("Cylinder", density)
	, m_radius(radius)
	, m_height(height)
{
}

double CCylinder::GetRadius() const
{
	return m_radius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return pow(m_radius, 2) * M_PI * m_height;
}

void CCylinder::AppendInfoAboutShape(std::ostream & strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl
		<< "\theight = " << GetHeight() << std::endl;
}