#include "stdafx.h"
#include "CHttpUrl.h" 
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <math.h>
#include <boost/math/special_functions/fpclassify.hpp>

using boost::string_ref;
using boost::lexical_cast;

CHttpUrl::CHttpUrl(std::string const & url)
{
	tie(m_protocol, m_domain, m_port, m_document) = ParseUrl(url);
};

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port) :
	m_domain(ValidateDomainName(domain)),
	m_port(port),
	m_document(ValidateDocument(document)),
	m_protocol(protocol)
{
	if (port == HTTP_PORT && m_protocol == Protocol::HTTPS)
	{
		m_port = HTTPS_PORT;
	}
}

std::string CHttpUrl::GetUrl()const
{
	return ToStringProtocol() + "://" + m_domain + (((m_port == HTTP_PORT) || (m_port == HTTPS_PORT)) ? "" : ":" + std::to_string(m_port)) + m_document;
}

std::string CHttpUrl::GetDomain()const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument()const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol()const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort()const
{
	return m_port;
}

Protocol CHttpUrl::ToProtocolType(std::string const & protocol)
{
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		return Protocol::HTTPS;
	}

	throw std::invalid_argument("Invalid protocol.");
}

CHttpUrl::UrlComponents CHttpUrl::ParseUrl(std::string const & url)
{
	string_ref urlRef(url);

	auto protocol = ParseProtocol(urlRef);
	urlRef = urlRef.substr(protocol.size() + 3, urlRef.size() - 1);
	auto foundProtocol = ToProtocolType(protocol);

	auto domain = ValidateDomainName(ParseDomain(urlRef));//here
	urlRef = urlRef.substr(domain.size(), urlRef.size() - 1); 
	unsigned short port = HTTP_PORT;
	if (foundProtocol == HTTP)
	{
		 port = HTTP_PORT;
	}
	else if (foundProtocol == HTTPS)
	{
		port = HTTPS_PORT;
	} 
	if (urlRef[0] == ':')
	{
		auto portStr = ParsePort(urlRef);
		urlRef = urlRef.substr(portStr.size() + 1, urlRef.size() - 1);
		port = lexical_cast<unsigned short>(portStr);
	}

	auto document = urlRef.to_string();

	return make_tuple(foundProtocol, ValidateDomainName(domain), port, ValidateDocument(document));
}

bool isValidDomainName(const std::string  & domain)
{
	auto space = domain.find(' ');
	auto slash = domain.find('/');
	auto reverseSlash = domain.find('\'');
	return (space == std::string::npos && slash == std::string::npos && reverseSlash == std::string::npos);
}

std::string const& CHttpUrl::ValidateDomainName(std::string const & domain)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain name is empty.");
	}
	else if(!isValidDomainName(domain))
	{
		throw std::invalid_argument("Domain name can't contains any slashes, spaces or tabulations.");
	}  
	return domain;
}

bool isValidDocumentName(std::string const & documentName)
{ 
	auto space = documentName.find(' ');
	auto tab = documentName.find('\t');
	return (space == std::string::npos && tab == std::string::npos);
}

std::string CHttpUrl::ValidateDocument(std::string const & document)
{
	if(!isValidDocumentName(document))
	/*if (std::find_if(document.begin(), document.end(), [&](char ch)
														{
															return (isspace(ch));
														}
	) != document.end())*/
	{
		throw std::invalid_argument("Document can't contain any spaces or tabulation.");
	}

	if (document[0] != '/')
	{
		return '/' + document;
	}

	return document;
}

std::string CHttpUrl::ToStringProtocol()const
{
	switch (m_protocol)
	{
	case Protocol::HTTP:
		return "http";

	case Protocol::HTTPS:
		return "https";
	}

	return std::string();
}

std::string CHttpUrl::ParseDomain(string_ref &url)
{
	auto domainEnd = url.find(':');
	if (domainEnd == string_ref::npos)
	{
		domainEnd = url.find("/");
	}

	return url.substr(0, domainEnd).to_string();
}

std::string CHttpUrl::ParseProtocol(string_ref &url)
{
	const std::string protocolDelimiter = "://";
	auto schemeEnd = url.find(protocolDelimiter);

	if (schemeEnd == string_ref::npos)
	{
		throw CUrlParsingError("Protocol parsing error.");
	}

	return url.substr(0, schemeEnd).to_string();
}

std::string CHttpUrl::ParsePort(string_ref & str)
{
	auto portEnd = str.find('/');
	auto portStr = str.substr(1, portEnd - 1).to_string();

	return portStr.empty() ? throw CUrlParsingError("Port parsing error.") : portStr;
}
 