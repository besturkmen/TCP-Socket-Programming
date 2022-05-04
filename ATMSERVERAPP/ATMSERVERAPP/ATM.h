#pragma once
#include<string>
#include<sstream>

class ATM
{
public:
	ATM();
	float getbalance()const;
	bool withdraw(float amount);
	std::string insuffientFund()const;
	void deposite(float amount);
	std::string transaction(char type, float amount)const;
	std::string print()const;

	~ATM();

private:
	float amount;
	float balance;
	float initialBalance;
	static std::stringstream st;


};