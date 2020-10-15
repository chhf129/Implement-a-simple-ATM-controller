#include <string>
#include <vector>
using namespace std;

class ATM {
    public:
        int atmId;
        Address location;

        CardReader cardReader;
        Keypad keypad;
        Deposit deposit;
		CardInfo cardInfo;
        BankService bankService;
		AccountType accountType;
		void readCard();
		void checkPassword();
		void selectAccount(AccountType accountType);
		void executeTransaction(TransactionType transactionType,int amount,string destAccunt);
	private:
		bool access=false;
};

class CardReader {
    public:
        CardInfo fetchCardDetails();
};

class Address {
	protected:
		int zipCode; 
		string street;
		string city;
		string state;
		string country;
};

class Date{
	protected:
		int month,day,year;
};

class CardInfo {
    protected:
        CardType cardType;
        Bank bank;
        string cardNumber;
        Date expiryDate;
        int cvv;
        float withdrawLimit;

};



class Keypad {
    public:
	    string getInput();
};

class Bank {
    protected:
        string name;
        Address location;

        vector<ATM> atmList;
};

class BankService {
    public:
	    virtual bool isValidUser(string pin, CardInfo cardInfo);
	    virtual Customer getCustomerDetails(CardInfo cardInfo);
	    virtual TransactionDetail executeTransaction(Transaction transactionInfo, Customer customer,AccountType accountType); 
};






class Customer {
	protected:
		string firstName;
		string lastName;
		string accountNumber;
		CardInfo cardInfo;
		Account account;

		BankService bankServiceObj;


};


class Account {
	protected:
		string accountNumber;
		float availableBalance;

};

class checking:public Account{
};
class saving:public Account{

};

class Transaction {
	protected:
		int transactionId;
		string sourceAccount;
		Date transactionDate;

};

class Deposit:public Transaction {
	public:
		int amount;

};


class Withdraw :public Transaction {
	public:
		int amount;

};

class Transfer:public Transaction {
	public:	
		string destAccunt;
		float amount;

};

class CheckBalance:public Transaction {

};

class TransactionDetail {
	TransactionStatus transactionStatus;
	string sourceAccountNumber;
	Date transactionDate;
	TransactionType transactionType;
	int transactionId;
};

enum TransactionStatus {

	PENDING, CANCELLED, SUCCESS, ERROR
};

enum TransactionType {

	WITHDRAW, DEPOSIT, TRANSFER,BALANCE
};

enum CardType {
	DEBIT,CREDIT
};

enum AccountType {
	SAVING,CHECKING
};

