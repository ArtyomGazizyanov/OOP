// main.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "stdafx.h"
#include "BodiesController.h"

using namespace std;

int main()
{
	vector<shared_ptr<CBody>> bodies;
	CController controller(bodies, cin, cout);
	while (!cin.eof() && !cin.fail())
	{
		cout << ">> ";
		if (!controller.HandleCommand())
		{
			cout << "Unknown command\n";
		}
	}
	return 0;
}