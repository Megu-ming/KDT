#pragma once
#include <iostream>

enum EMenuEvent : uint8_t
{
	ETerminated = 0,
	ECreateAccount = 1,
	EDeleteAccount = 2,
	EPrintAccount = 3,

	ELogin = 4,
	ELogout = 5,
	EPrintLoginPlayer = 6,
	EPrintPlayerInfoTask = 7,
};