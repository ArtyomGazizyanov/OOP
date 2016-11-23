#include "stdafx.h"
#include "../laba4/BodiesController.h"

using namespace std;
using namespace std::placeholders;

const string ERROR_MESSAGE_OF_INVALID_ARGUMENTS = "Invalid arguments\nArguments must be >= 0!\n";

CController::CController(vector<shared_ptr<CBody>> &bodies, istream &input, ostream &output)
	: m_bodies(bodies)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "Sphere", bind(&CController::CreateSphere, this, _1) },
		{ "Parallelepiped", bind(&CController::CreateParallelepiped, this, _1) },
		{ "Cone", bind(&CController::CreateCone, this, _1) },
		{ "Cylinder", bind(&CController::CreateCylinder, this, _1) }
})
{
}

bool CController::HandleCommand()
{
	string commandLine;
	if (!getline(m_input, commandLine))
	{
		return true;
	}
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	return false;
}

bool CController::CreateSphere(istream &args)
{
	double density;
	double radius;

	if (!(args >> density) || !(args >> radius))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Sphere <density> <radius>\n";
	}
	else if (density >= 0 && radius >= 0)
	{
		shared_ptr<CBody> sphere(new CSphere(density, radius));
		m_bodies.push_back(sphere);
	}
	else
	{
		m_output << ERROR_MESSAGE_OF_INVALID_ARGUMENTS;
	}
	return true;
}

bool CController::CreateParallelepiped(istream &args)
{
	double width;
	double height;
	double depth;
	double density;

	if (!(args >> width) || !(args >> height) || !(args >> depth) || !(args >> density))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Parallelepiped <width> <height> <depth> <density>\n";
	}
	else if ((width >= 0) && (height >= 0) && (depth >= 0) && (density >= 0))
		{
			shared_ptr<CBody> parallelepiped(new CParallelepiped(width, height, depth, density));
			m_bodies.push_back(parallelepiped);
		}
		else
		{
			m_output << ERROR_MESSAGE_OF_INVALID_ARGUMENTS;
		}
	return true;
}

bool CController::CreateCone(istream &args)
{
	double density;
	double radius;
	double height;

	if (!(args >> density) || !(args >> radius) || !(args >> height))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Cone <density> <radius> <height>\n";
	}
	else if ((density >= 0) && (radius >= 0) && (height >= 0))
	{
		shared_ptr<CBody> cone(new CCone(density, radius, height));
		m_bodies.push_back(cone);
	}
	else
	{
		m_output << ERROR_MESSAGE_OF_INVALID_ARGUMENTS;
	}
	
	return true;
}

bool CController::CreateCylinder(istream &args)
{
	double density;
	double radius;
	double height;

	if (!(args >> density) || !(args >> radius) || !(args >> height))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Cylinder <density> <radius> <height>\n";
		return false;
	}
	else if ((density >= 0) && (radius >= 0) && (height >= 0))
	{
		shared_ptr<CBody> cylinder(new CCylinder(density, radius, height));
		m_bodies.push_back(cylinder);
	}
	else
	{
		m_output << ERROR_MESSAGE_OF_INVALID_ARGUMENTS;
	}
	return true;
}

void CController::PrintAllBodies(vector<shared_ptr<CBody>> &bodies, ostream &output)
{
	if (!bodies.empty())
	{
		for (auto &body : bodies)
		{
			output << body->ShowInfo();
		}
	}
	else
	{
		output << "You have not entered figures\n";
	}
}

void CController::FindBodyWithMaxMass(vector<shared_ptr<CBody>> &bodies)
{
	if (!bodies.empty())
	{
		shared_ptr<CBody> bodyWithMaxMass = bodies[0];
		double maxMass = bodies[0]->GetMass();
		for (auto &body : bodies)
		{
			if (maxMass < body->GetMass())
			{
				maxMass = body->GetMass();
				bodyWithMaxMass = body;
			}
		}
		cout << "Body with MAX mass is " << bodyWithMaxMass->ShowInfo();
	}
}

void CController::FindBodyWithSmallestWeight(vector<shared_ptr<CBody>> &bodies)
{
	if (!bodies.empty())
	{
		const double WATER_DENSITY = 1000;
		const double GRAVITY_CONST = 9.8f;
		shared_ptr<CBody> bodyWithSmallestWeight = bodies[0];
		double smallestWeight = GetWeight(bodies[0], WATER_DENSITY, GRAVITY_CONST);
		for (auto &body : bodies)
		{
			if (smallestWeight > GetWeight(body, WATER_DENSITY, GRAVITY_CONST))
			{
				smallestWeight = GetWeight(body, WATER_DENSITY, GRAVITY_CONST);
				bodyWithSmallestWeight = body;
			}
		}
		cout << "Body with SMALLEST weight is " << bodyWithSmallestWeight->ShowInfo();
	}
}

double CController::GetWeight(shared_ptr<CBody> &body, const double &WATER_DENSITY, const double &GRAVITY_CONST)
{
	return (body->GetDensity() - WATER_DENSITY) * GRAVITY_CONST * body->GetVolume();
}