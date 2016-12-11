#pragma once

#include "stdafx.h"
#include <string>
#include "CUrlParsingError.h"
#include <tuple>
#include <boost/utility/string_ref.hpp>

enum Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
	using UrlComponents = std::tuple<Protocol, std::string, unsigned short, std::string>;

public:
	CHttpUrl(std::string const &url);
	CHttpUrl
	(
		std::string const &domain,
		std::string const &document,
		Protocol protocol = Protocol::HTTP,
		unsigned short port = HTTP_PORT
	);

	std::string GetUrl()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

	std::string ToStringProtocol()const;
	static Protocol ToProtocolType(std::string const &protocol);

private:
	static std::string const& ValidateDomainName(std::string const &domain);
	static std::string ValidateDocument(std::string const &document);
	static std::string ParseDomain(boost::string_ref &str);
	static std::string ParseProtocol(boost::string_ref &str);
	static std::string ParsePort(boost::string_ref &str);
	static UrlComponents ParseUrl(std::string const &url);

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};
 