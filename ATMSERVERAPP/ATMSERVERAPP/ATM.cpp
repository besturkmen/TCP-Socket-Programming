#include "ATM.h"
#include<iostream>
#include<chrono>
#include<iomanip>
#include<sstream>

#pragma warning(disable : 4996)

std::stringstream ATM::st;
ATM::ATM() :amount(0.0f), balance(500.0f), initialBalance(500.0f)
{
}

float ATM::getbalance() const
{
	return balance;
}

bool ATM::withdraw(float amount)
{
	char type = 'w';
	if (balance >= amount) {
		balance -= amount;
		transaction(type, amount);   // write this transaction to a string buffer
		return true;
	}

	return false;

}

std::string ATM::insuffientFund() const
{

	return std::string("Insufficient fund\nYou have: R" + std::to_string(getbalance()) + " left");
}

void ATM::deposite(float amount)
{
	char type = 'd';
	balance += amount;
	transaction(type, amount);      // write this transaction to a string buffer

}

std::string ATM::transaction(char type, float amount) const
{

	if (type == 'd')
	{
		st << "Deposit" << std::right << std::setw(20) << "R" << amount << '\n';
	}

	if (type == 'w') {
		st << "Withdraw" << std::right << std::setw(19) << "R" << amount << '\n';
	}
	return st.str();
}

std::string ATM::print() const
{
	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
	time_t tt = std::chrono::system_clock::to_time_t(today);
	std::tm tm = *std::localtime(&tt);
	std::stringstream dtbuffer;
	dtbuffer << "------------------------------------\n";
	dtbuffer << std::right << std::setw(20) << "IBANK\n";
	dtbuffer << "   Your number one banking Solutions\n";
	dtbuffer << "------------------------------------\n";
	dtbuffer << '\n';
	dtbuffer << "ATM ID: " << 101985 << '\n';
	dtbuffer << "Acc No: " << "*******" << 606 << '\n';
	dtbuffer << "Date  : " << std::put_time(&tm, "%A %d %b %Y") << '\n';
	dtbuffer << "Time  : " << std::put_time(&tm, "%H:%M:%S") << '\n' << '\n';
	dtbuffer << "Initial Balance: R" << initialBalance << '\n' << '\n';

	dtbuffer << "Transaction Type" << std::right << std::setw(15) << "Amount" << '\n' << '\n';


	dtbuffer << st.str();

	dtbuffer << "\nBalance: R" << getbalance() << '\n';

	dtbuffer << "------------------------------------\n";
	dtbuffer << "Thank you for using PITON Bank\n";
	dtbuffer << "For Queries call + 27 0000000010\n";
	dtbuffer << "------------------------------------\n";

	std::string info = dtbuffer.str();
	return std::string(info);
}

ATM::~ATM()
{
}