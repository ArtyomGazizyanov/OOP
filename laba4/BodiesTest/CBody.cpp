#include "../laba4/stdafx.h"
#include "../laba4/CBody.h"
  
CBody::CBody(const std::string & type, double density)
	: m_density(density)
	, m_type(type)
{
}

CBody::~CBody()
{
}

double CBody::GetDensity()const
{
	return m_density;
}

double CBody::GetMass()const
{
	return GetVolume() * GetDensity();
}

std::string CBody::ShowInfo()const
{
	std::ostringstream strm;
	strm << m_type << ":" << std::endl << std::setprecision(10)
		<< "\tdensity = " << GetDensity() << std::endl
		<< "\tvolume = " << GetVolume() << std::endl
		<< "\tmass = " << GetMass() << std::endl;
	AppendInfoAboutShape(strm);
	return strm.str();
}