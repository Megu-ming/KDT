#pragma once
#include <iostream>

enum EMenuEvent : uint8_t
{
	ETerminated = 0,
	ECreateAccount = 1,
	EDeleteAccount = 2,
	EPrintAccount = 3,
};