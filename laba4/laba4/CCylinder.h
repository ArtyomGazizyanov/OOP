#pragma once
#include "CBody.h"

class CCylinder final :	public CBody
{
public:
	CCylinder(double density, double radius, double height);

	double GetRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
protected:
	void AppendInfoAboutShape(std::ostream & strm) const override;
private:
	double m_radius;
	double m_height;
}; 
