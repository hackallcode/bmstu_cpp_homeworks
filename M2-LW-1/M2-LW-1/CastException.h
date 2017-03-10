#pragma once

#include <exception>

class CastException
	: public std::exception
{};

class TooBigNumberException
	: public CastException
{};

class UnknownChar
	: public CastException
{};