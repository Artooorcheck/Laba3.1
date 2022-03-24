#pragma once
#include "Bank account.h"
#include "Collection.h"

enum class AccountType
{
	user,
	admin,
	logout
};

class Autorization
{
private:
	AccountType accType;
	Bank<BankAccount> bank;
	bool exit;

	void Autorizate(std::string login, std::string password);

	void AdminMenu();

	void SignUp();

	void AskLoginAndPassword();

	void ChangeBalance();

	void LogOutMenu();

	void LogInMenu();

	void Update();

	void Select();

	void Print();

public:
	Autorization();

	void Menu();

	bool Exit();
};