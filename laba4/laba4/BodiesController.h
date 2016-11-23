#pragma once 
#include "stdafx.h"
#include <boost/noncopyable.hpp>
#include "CBody.h"
#include "CSphere.h"
#include "CParallelepiped.h"
#include "CCone.h"
#include "CCylinder.h"

class CBody;

using namespace std;

class CController : boost::noncopyable
{
public:
	CController(vector<shared_ptr<CBody>> &bodies, istream &input, ostream &output);
	bool HandleCommand();
private:
	bool ShowCommands();
	bool FindBodyWithMaxMass();
	bool FindBodyWithSmallestWeight();
	bool PrintAllBodies();
	bool CreateSphere(istream &rgs);
	bool CreateParallelepiped(istream &args);
	bool CreateCone(istream &args);
	bool CreateCylinder(istream &args);
	double GetWeight(shared_ptr<CBody> &body);

	typedef map<string, function<bool(istream & args)>> ActionMap;

	vector<shared_ptr<CBody>> &m_bodies;
	istream &m_input;
	ostream &m_output;

	const ActionMap m_actionMap;
};