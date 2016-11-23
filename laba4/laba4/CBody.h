#pragma once
#include <string>

class CBody
{
public:
	CBody(std::string const &type, double density);

	double GetDensity() const;
	virtual double GetVolume() const = 0;
	double GetMass() const;
	std::string ShowInfo() const;

	virtual ~CBody();
protected:
	virtual void AppendInfoAboutShape(std::ostream & strm) const = 0;
private:
	double m_density;
	std::string m_type;
}; 
