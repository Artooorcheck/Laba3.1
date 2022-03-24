#include"Bank account.h"

tm BankAccount::SetOpenDate(std::string date)
{
	tm openDate;
	std::vector<std::string> data = Split(date, ".");
	if (data.size() != 3 || !TryParse(data[1], openDate.tm_mon) || !TryParse(data[2], openDate.tm_year) || !TryParse(data[0], openDate.tm_mday))
		throw std::exception("Uncorrect date");
	return openDate;
}

std::string BankAccount::GetOpenDate()
{
	return ToString(openDate.tm_mday) + '.' + ToString(openDate.tm_mon) + '.' + ToString(openDate.tm_year);
}

bool BankAccount::CheckField(std::string fieldName, std::string value)
{
	return GetField(fieldName) == value;
}

void BankAccount::Print(std::ostream& stream)
{
	std::cout << "Номер вклада: " << number;
	std::cout << "\nКод вклада: " << code;
	std::cout << "\nФамилия: " << lastName;
	std::cout << "\nДепозит: " << sum;
	std::cout << "\nТип вклада: " << (((int)dType) == 1 ? "Срочный" : ((int)dType) == 2 ? "Накопительный" : "Сберегательный");
	std::cout << "\nПроцент: " << percent << '%';
	std::cout << "\nДата открытия: " << GetOpenDate();
	std::cout << "\n------------------------------------------\n";
}

std::string BankAccount::GetString()
{
	return "{" + ToString(number) + "}" + "{" + ToString(code) + "}"
		+ "{" + lastName + "}" + "{" + ToString(sum) + "}"
		+ "{" + ToString(percent) + "}" + "{" + GetOpenDate() + "}"
		+ "{" + ToString((int)dType) + "}" + "{" + login + "}" + "{" + password + "}";
}

bool BankAccount::ParseString(std::string data)
{
	int t;
	std::vector<std::string> d = Split(data, "}");
	bool res = TryParse(Trim(d[0], "{"), number) &&
		TryParse(Trim(d[1], "{"), code) &&
		TryParse(Trim(d[3], "{"), sum) &&
		TryParse(Trim(d[4], "{"), percent) &&
		TryParse(Trim(d[6], "{"), t);
	dType = (DepositType)t;
	openDate = SetOpenDate(Trim(d[5], "{"));
	login = Trim(d[7], "{");
	password = Trim(d[8], "{");
	lastName = Trim(d[2], "{");
	return res;
}

bool BankAccount::SetField(std::string fieldName, std::string value)
{
	if (fieldName == "number")
	{
		return TryParse(value, number);
	}
	if (fieldName == "code")
	{
		return TryParse(value, code);
	}
	if (fieldName == "lastname")
	{
		lastName = value;
		return true;
	}
	if (fieldName == "sum")
	{
		return TryParse(value, sum);
	}
	if (fieldName == "percent")
	{
		return TryParse(value, percent);
	}
	if (fieldName == "opendate")
	{
		openDate = SetOpenDate(value);
		return true;
	}
	if (fieldName == "dtype")
	{
		int t;
		if (TryParse(value, t))
		{
			dType = DepositType(t);
		}
		else
		{
			return false;
		}
	}
	if (fieldName == "login")
	{
		login = value;
		return true;
	}
	if (fieldName == "password")
	{
		return TryParse(value, percent);
	}
	return false;
}

std::string BankAccount::GetField(std::string fieldName)
{
	if (fieldName == "number")
	{
		return ToString(number);
	}
	if (fieldName == "code")
	{
		return ToString(code);
	}
	if (fieldName == "lastname")
	{
		return lastName;
	}
	if (fieldName == "sum")
	{
		return ToString(sum);
	}
	if (fieldName == "percent")
	{
		return ToString(percent);
	}
	if (fieldName == "opendate")
	{
		return GetOpenDate();
	}
	if (fieldName == "dtype")
	{
		return ToString((int)dType);
	}
	if (fieldName == "login")
	{
		return login;
	}
	if (fieldName == "password")
	{
		return password;
	}
	return "";
}

bool BankAccount::ReadFromConsole()
{
	srand(time_t(NULL));
	number = rand();
	code = rand();

	std::cout << "Фамилия: ";
	std::cin >> lastName;
	std::cout << "Депозит: ";
	std::cin >> sum;
	if (!std::cin.good())
	{
		ConsoleClear();
		return false;
	}

	std::cout << "Логин: ";
	std::cin >> login;
	std::cout << "Пароль: ";
	std::cin >> password;

	std::time_t time = std::time(nullptr);

	openDate = *std::localtime(&time);

	openDate.tm_year += 1900;

	std::cout << "Выберите тип вклада:\n";
	std::cout << "1.Срочный\n";
	std::cout << "2.Накопительный\n";
	std::cout << "3.Сберегательный\n";
	int type;
	std::cin >> type;
	if (!std::cin.good())
	{
		ConsoleClear();
		return false;
	}
	if (type < 1 && type > 3)
	{
		return false;
	}
	dType = (DepositType)type;
	percent = 9 + type * type;

	return true;
}

std::string ToString(int n)
{
	std::stringstream stream;
	stream << n;
	std::string date;
	stream >> date;
	return date;
}

std::string ToString(double n)
{
	std::stringstream stream;
	stream << n;
	std::string date;
	stream >> date;
	return date;
}