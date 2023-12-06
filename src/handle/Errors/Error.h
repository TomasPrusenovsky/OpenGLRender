#pragma once
#include <iostream>

class Error
{
public:
	Error(const Error&) = delete;
	Error(Error&) = delete;
};