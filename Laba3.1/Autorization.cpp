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
		std::cout << "Некорректный ввод!\n";
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
			std::cout << "Некорректный логин или пароль!";
		}
	}
}

void InterfaceAdmin()
{
	std::cout << "Выберите действие:\n";
	std::cout << "1.Выбрать по фильтру\n";
	std::cout << "2.Снять с счетов\n";
	std::cout << "3.Обновить информацию\n";
	std::cout << "4.Посмотреть список вкладчиков\n";
	std::cout << "5.Выйти\n";
	std::cout << "6.Закрыть программу\n";
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
		int count = bank.GetSelected().size();
		if (count == 1)
		{
			ChangeBalance();
		}
		else if (count > 1)
		{
			std::cout << "Уточните Фильтры!";
		}
		else
		{
			std::cout << "Вы не выбрали ни одного пользователя!";
		}
	}
	else if (command == 3)
	{
		if(bank.GetSelected().size()==0)
		{
			std::cout << "Вы не выбрали ни одного пользователя!";
		}
		else
		{
			Update();
		}
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
		std::cout << "Неизвестная комманда!\n";
	}
}

void Autorization::LogOutMenu()
{
	std::cout << "Выберите действие:\n";
	std::cout << "1.Войти\n";
	std::cout << "2.Сделать вклад\n";
	std::cout << "3.Закрыть программу\n";
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
		std::cout << "Неизвестная комманда!";
	}
	
}

void Autorization::LogInMenu()
{
	std::cout << "Выберите действие:\n";
	std::cout << "1.Посмотреть информацию\n";
	std::cout << "2.Закрыть счет\n";
	std::cout << "3.Снять средства\n";
	std::cout << "4.Выйти\n";
	std::cout << "5.Закрыть программу\n";
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
		std::cout << "Неизвестная комманда!";
	}
}

void Autorization::Update()

{
	int command = 0;
	std::string param = "";

	std::string value;

	while (command != 3)
	{
		std::cout << "1. Процент\n";
		std::cout << "2. Тип вклада\n";
		std::cout << "3. Выход\n";
		std::cin >> command;
		std::string value;

		switch (command)
		{
		case 1:
			param = "percent";
			std::cout << "Введите новую процентную ставку\n";
			std::cin >> value;
			break;
		case 2:
			param = "dtype";
			std::cout << "Выберите тип вклада:\n";
			std::cout << "1.Срочный\n";
			std::cout << "2.Накопительный\n";
			std::cout << "3.Сберегательный\n";
			std::cin >> value;
			break;
		case 3:
			return;
		default:
			std::cout << "Неизвестная комманда\n";
			return;
		}

		try
		{
			bank.Update(param + '=' + value);
		}
		catch (const std::exception& e)
		{
			std::cout << "Некорректное значение поля\n";
		}
	}
}

void Autorization::Select()
{
	int command;
	std::cout << "1. Фильтровать по номеру счета\n";
	std::cout << "2. Фильтровать по дате открытия\n";
	std::cout << "3. Фильтровать по владельцу\n";
	std::cout << "4. Фильтровать по типу вклада\n";
	std::cout << "5. Фильтровать по размеру вклада\n";
	std::cout << "6. Фильтровать по проценту\n";
	std::cout << "7. Фильтровать по коду\n";
	std::cin >> command;
	std::string param = "";
	std::string value = "";
	switch (command)
	{
	case 1:
		std::cout << "Введите номер счета: ";
		std::cin >> value;
		param = "number";
		break;
	case 2:
		std::cout << "Введите дату открытия счета: ";
		std::cin >> value;
		param = "opendate";
		break;
	case 3:
		std::cout << "Введите фамилию владельца счета: ";
		std::cin >> value;
		param = "lastname";
		break;
	case 4:
		std::cout << "Выберите тип вклада:\n";
		std::cout << "1.Срочный\n";
		std::cout << "2.Накопительный\n";
		std::cout << "3.Сберегательный\n";
		std::cin >> value;
		param = "dtype";
		break;
	case 5:
		std::cout << "Введите размер депозита: ";
		std::cin >> value;
		param = "sum";
		break;
	case 6:
		std::cout << "Введите годовой процент: ";
		std::cin >> value;
		param = "percent";
		break;
	case 7:
		std::cout << "Введите код счета: ";
		std::cin >> value;
		param = "code";
		break;
	default:
		std::cout << "Неизвестная комманда\n";
		break;
	}
	if (command > 0 && command < 8)
	{
		bank.Select(param + '=' + value);
	}
}

void Autorization::Print()
{
	int command;
	std::cout << "1. Печать всех элементов\n";
	std::cout << "2. Печать выбранных элементов\n";
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
		std::cout << "Неизвестная комманда\n";
	}

}

bool Autorization::Exit()
{
	return exit;
}

void Autorization::SignUp()
{
	BankAccount* acc = new BankAccount();
	if(acc->ReadFromConsole())
	{

		std::string login = acc->GetField("login");
		bank.Select("login=" + login);
		if (bank.GetSelected().size() > 0)
		{
			std::cout << "Пользователь уже существует";
		}
		else
		{
			bank.Add(acc);
		}
	}
	else
	{
		std::cout << "Некорректные данные";
	}
}

void Autorization::AskLoginAndPassword()
{
	std::string login, password;

	std::cout << "Логин:";
	std::cin >> login;

	std::cout << "Пароль:";
	std::cin >> password;

	Autorizate(login, password);

}

void Autorization::ChangeBalance()
{
	int sum, dSum, type;
	TryParse(bank.GetSelected().begin()->GetField("dtype"), type);
	if (type == 1)
	{
		std::cout << "Ведите сумму, которую хотите снять:";
		std::cin >> dSum;
		TryParse(bank.GetSelected().begin()->GetField("sum"), sum);
		if (sum > dSum)
		{
			bank.Update("sum=" + ToString(sum - dSum));
		}
		else if (sum == dSum)
		{
			bank.Remove();
			if (accType != AccountType::admin)
			{
				accType = AccountType::logout;
			}
		}
		else
		{
			std::cout << "Вы не можете снять сумму превышающую вклад!";
		}
	}
	else
	{
		std::cout << "Ваш тип вклада не позволяет снять средства!";
	}
}
