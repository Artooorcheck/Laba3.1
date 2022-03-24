#pragma once
#include <string>


struct Node
{
	virtual bool CheckField(std::string fieldName, std::string value) { return false; }
	virtual void Print(std::ostream& stream) {}
	virtual std::string GetString() { return ""; }
	virtual bool ParseString(std::string data) { return false; }
	virtual std::string GetField(std::string fieldName) { return ""; }
	virtual bool SetField(std::string fieldName, std::string value) { return false; }
};