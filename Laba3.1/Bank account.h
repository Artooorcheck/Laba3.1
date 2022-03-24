#pragma once
#include <string>
#include <list>
#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include "StringMethods.h"
#include "Node.h"
#include<cmath>

std::string ToString(int n);
std::string ToString(double n);


enum class DepositType
{
	express = 1,
	accumulative = 2,
	saving = 3
};

struct BankAccount: Node
{
private:
	int number;
	int code;
	std::string lastName;
	double sum;
	double percent;
	DepositType dType;
	std::string login;
	std::string password;
	tm openDate;

	tm SetOpenDate(std::string date);
	std::string GetOpenDate();

public:
	bool ReadFromConsole();
	virtual bool CheckField(std::string fieldName, std::string value) override;
	virtual void Print(std::ostream& stream = std::cout) override;
	virtual std::string GetString() override;
	virtual bool ParseString(std::string data) override;
	virtual bool SetField(std::string fieldName, std::string value) override;
	virtual std::string GetField(std::string fieldName) override;
};