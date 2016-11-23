#pragma once
#include "CBody.h"

class CSphere final : public CBody
{
public:
	CSphere(double density, double radius);

	double GetRadius() const;
	double GetVolume() const override;
protected:
	void AppendInfoAboutShape(std::ostream & strm) const override;
private:
	double m_radius;
};