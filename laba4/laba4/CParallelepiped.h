#pragma once 
#include "CBody.h"

class CParallelepiped final : public CBody
{
public:
	CParallelepiped(double width, double height, double depth, double density);

	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	double GetVolume() const override;
protected:
	void AppendInfoAboutShape(std::ostream & strm) const override;
private:
	double m_width;
	double m_height;
	double m_depth;
};