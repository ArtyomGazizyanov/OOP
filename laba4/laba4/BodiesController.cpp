#include "stdafx.h"
#include "BodiesController.h"

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
		{ "Cylinder", bind(&CController::CreateCylinder, this, _1) },
		{ "ShowAll", bind(&CController::PrintAllBodies, this) },
		{ "ShowBodyWithMaxMass", bind(&CController::FindBodyWithMaxMass, this) },
		{ "ShowBodyWithSmallestWeight", bind(&CController::FindBodyWithSmallestWeight, this) },
		{ "Info", bind(&CController::ShowCommands, this) }
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

bool CController::PrintAllBodies()
{
	if (!m_bodies.empty())
	{
		for (auto &body : m_bodies)
		{
			m_output << body->ShowInfo();
		}
		return true;
	}
	else
	{
		m_output << "You have not entered figures\n";
		return false;
	}
}

bool CController::FindBodyWithMaxMass()
{
	if (!m_bodies.empty())
	{
		shared_ptr<CBody> bodyWithMaxMass = m_bodies[0];
		double maxMass = m_bodies[0]->GetMass();
		for (auto &body : m_bodies)
		{
			if (maxMass < body->GetMass())
			{
				maxMass = body->GetMass();
				bodyWithMaxMass = body;
			}
		}
		m_output << "Body with MAX mass is " << bodyWithMaxMass->ShowInfo();
		return true;
	}
	return false;
}

bool CController::FindBodyWithSmallestWeight()
{
	if (!m_bodies.empty())
	{		
		shared_ptr<CBody> bodyWithSmallestWeight = m_bodies[0];
		double smallestWeight = GetWeight(m_bodies[0]);
		for (auto &body : m_bodies)
		{
			if (smallestWeight > GetWeight(body))
			{
				smallestWeight = GetWeight(body);
				bodyWithSmallestWeight = body;
			}
		}
		m_output << "Body with SMALLEST weight is " << bodyWithSmallestWeight->ShowInfo();
		return true;
	}
	return false;
}

bool CController::ShowCommands()
{
	m_output << "\tSphere <density> <radius>"<<endl
		<<"\tParallelepiped <width> <height> <depth> <density>" << endl
		<<"\tCone <density> <radius> <height>" << endl
		<<"\tCylinder <density> <radius> <height>" << endl
		<<"\tShowAll -- Show all entered figures" << endl
		<< "\tShowBodyWithMaxMass -- Show all bodies with max mass" << endl
		<< "\tShowBodyWithSmallestWeight -- Show all bodies with smallest weight" << endl; 
	return true;
}

double CController::GetWeight(shared_ptr<CBody> &body)
{
	const double WATER_DENSITY = 1000;
	const double GRAVITY_CONST = 9.8f;
	return (body->GetDensity() - WATER_DENSITY) * GRAVITY_CONST * body->GetVolume();
}