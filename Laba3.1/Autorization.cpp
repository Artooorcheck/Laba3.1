#include"Autorization.h"


Autorization::Autorization()
{

	accType = AccountType::logout;
	bank.Read();
	exit = false;
}

void Autorization::Menu()
{
	if (accType == AccountType::admin)
	{
		AdminMenu();
	}
	else if (accType == AccountType::user)
	{
		LogInMenu();
	}
	else
	{
		LogOutMenu();
	}
	if (!std::cin.good())
	{
		ConsoleClear();
		std::cout << "������������ ����!\n";
	}
}

void Autorization::Autorizate(std::string login, std::string password)
{
	if (bank.CheckRoot(login, password))
	{
		accType = AccountType::admin;
	}
	else
	{
		bank.Select("login=" + login + " AND password=" + password);
		accType = bank.GetSelected().size() > 0 ? AccountType::user : AccountType::logout;
		if (accType == AccountType::logout)
		{
			std::cout << "������������ ����� ��� ������!";
		}
	}
}

void InterfaceAdmin()
{
	std::cout << "�������� ��������:\n";
	std::cout << "1.������� �� �������\n";
	std::cout << "2.����� � ������\n";
	std::cout << "3.�������� ����������\n";
	std::cout << "4.���������� ������ ����������\n";
	std::cout << "5.�����\n";
	std::cout << "6.������� ���������\n";
}

void Autorization::AdminChangeBalance()
{
	int count = bank.GetSelected().size();
	if (count == 1)
	{
		ChangeBalance();
	}
	else if (count > 1)
	{
		std::cout << "�������� �������!";
	}
	else
	{
		std::cout << "�� �� ������� �� ������ ������������!";
	}

}

void Autorization::AdminUpdateInfo()
{
	if (bank.GetSelected().size() == 0)
	{
		std::cout << "�� �� ������� �� ������ ������������!";
	}
	else
	{
		Update();
	}
}

void Autorization::AdminMenu()
{
	InterfaceAdmin();
	int command = 0;
	std::cin >> command;
	if (command == 1)
	{
		Select();
	}
	else if (command == 2)
	{
		AdminChangeBalance();
	}
	else if (command == 3)
	{
		AdminUpdateInfo();
	}
	else if (command == 4)
	{
		Print();
	}
	else if (command == 5)
	{
		accType = AccountType::logout;
	}
	else if (command == 6)
	{
		exit = true;
	}
	else
	{
		std::cout << "����������� ��������!\n";
	}
}

void Autorization::LogOutMenu()
{
	std::cout << "�������� ��������:\n";
	std::cout << "1.�����\n";
	std::cout << "2.������� �����\n";
	std::cout << "3.������� ���������\n";
	int command = 0;
	std::cin >> command;
	if (command == 1)
	{
		AskLoginAndPassword();
	}
	else if (command == 2)
	{
		SignUp();
	}
	else if (command == 3)
	{
		exit = true;
	}
	else
	{
		std::cout << "����������� ��������!";
	}

}

void Autorization::LogInMenu()
{
	std::cout << "�������� ��������:\n";
	std::cout << "1.���������� ����������\n";
	std::cout << "2.������� ����\n";
	std::cout << "3.����� ��������\n";
	std::cout << "4.�����\n";
	std::cout << "5.������� ���������\n";
	int command = 0;
	std::cin >> command;
	if (command == 1)
	{
		bank.PrintSelected(std::cout);
	}
	else if (command == 2)
	{
		bank.Remove();
		accType = AccountType::logout;
	}
	else if (command == 3)
	{
		ChangeBalance();
	}
	else if (command == 4)
	{
		accType = AccountType::logout;
	}
	else if (command == 5)
	{
		exit = true;
	}
	else
	{
		std::cout << "����������� ��������!";
	}
}

void Autorization::Update()

{
	int command = 0;
	std::string param = "";

	std::string value;

	while (command != 3)
	{
		std::cout << "1. �������\n";
		std::cout << "2. ��� ������\n";
		std::cout << "3. �����\n";
		std::cin >> command;
		std::string value;

		switch (command)
		{
		case 1:
			param = "percent";
			std::cout << "������� ����� ���������� ������\n";
			std::cin >> value;
			break;
		case 2:
			param = "dtype";
			std::cout << "�������� ��� ������:\n";
			std::cout << "1.�������\n";
			std::cout << "2.�������������\n";
			std::cout << "3.��������������\n";
			std::cin >> value;
			break;
		case 3:
			return;
		default:
			std::cout << "����������� ��������\n";
			return;
		}

		try
		{
			bank.Update(param + '=' + value);
		}
		catch (const std::exception& e)
		{
			std::cout << "������������ �������� ����\n";
		}
	}
}

void ForkSelect(int command)
{
	switch (command)
	{
	case 1:
		std::cout << "������� ����� �����: ";
		break;
	case 2:
		std::cout << "������� ���� �������� �����: ";
		break;
	case 3:
		std::cout << "������� ������� ��������� �����: ";
		break;
	case 4:
		std::cout << "�������� ��� ������:\n";
		std::cout << "1.�������\n";
		std::cout << "2.�������������\n";
		std::cout << "3.��������������\n";
		break;
	case 5:
		std::cout << "������� ������ ��������: ";
		break;
	case 6:
		std::cout << "������� ������� �������: ";
		break;
	case 7:
		std::cout << "������� ��� �����: ";
		break;
	default:
		std::cout << "����������� ��������\n";
		break;
	}
}

void Autorization::Select()
{
	int command;
	std::string params[] = { "number", "opendate", "lastname", "dtype", "sum", "percent", "code" };
	std::cout << "1. ����������� �� ������ �����\n";
	std::cout << "2. ����������� �� ���� ��������\n";
	std::cout << "3. ����������� �� ���������\n";
	std::cout << "4. ����������� �� ���� ������\n";
	std::cout << "5. ����������� �� ������� ������\n";
	std::cout << "6. ����������� �� ��������\n";
	std::cout << "7. ����������� �� ����\n";
	std::cin >> command;
	std::string value = "";
	if (command > 0 && command < 8)
	{
		ForkSelect(command);
		std::cin >> value;
		bank.Select(params[command - 1] + "=" + value);
	}
}

void Autorization::Print()
{
	int command;
	std::cout << "1. ������ ���� ���������\n";
	std::cout << "2. ������ ��������� ���������\n";
	std::cin >> command;

	if (command == 1)
	{
		bank.Print(std::cout);
	}
	else if (command == 2)
	{
		bank.PrintSelected(std::cout);
	}
	else
	{
		std::cout << "����������� ��������\n";
	}

}

bool Autorization::Exit()
{
	return exit;
}

void Autorization::SignUp()
{
	BankAccount* acc = new BankAccount();
	if (acc->ReadFromConsole())
	{

		std::string login = acc->GetField("login");
		bank.Select("login=" + login);
		if (bank.GetSelected().size() > 0)
		{
			std::cout << "������������ ��� ����������";
		}
		else
		{
			bank.Add(acc);
		}
	}
	else
	{
		std::cout << "������������ ������";
	}
}

void Autorization::AskLoginAndPassword()
{
	std::string login, password;

	std::cout << "�����:";
	std::cin >> login;

	std::cout << "������:";
	std::cin >> password;

	Autorizate(login, password);

}

void Autorization::GetMoney()
{
	int sum, dSum;
	std::cout << "������ �����, ������� ������ �����:";
	std::cin >> dSum;
	TryParse(bank.GetSelected().begin()->GetField("sum"), sum);
	if (sum == dSum)
	{
		bank.Remove();
		if (accType != AccountType::admin)
		{
			accType = AccountType::logout;
		}
	}
	else if (sum > dSum)
	{
		bank.Update("sum=" + ToString(sum - dSum));
	}
	else
	{
		std::cout << "�� �� ������ ����� ����� ����������� �����!";
	}

}

void Autorization::ChangeBalance()
{
	int type;
	TryParse(bank.GetSelected().begin()->GetField("dtype"), type);
	if (type == 1)
	{
		GetMoney();
	}
	else
	{
		std::cout << "��� ��� ������ �� ��������� ����� ��������!";
	}
}
