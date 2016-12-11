#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

int main()
{
	try
	{

		CHttpUrl("www.blabla.com/asdasf.h");
	}
	catch (CUrlParsingError & exc)
	{
		std::cout << "Invalid url" << exc.what() << "\n";
	}

	return 0;
}