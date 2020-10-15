#include <string>
#include <vector>
using namespace std;


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


class Keypad {
    public:
	    string getInput();
};

class Bank {
    protected:
        string name;
        Address location;
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


class CardInfo {
    protected:
        CardType cardType;
        Bank bank;
        string cardNumber;
        Date expiryDate;
        int cvv;
        float withdrawLimit;

};

class CardReader {
    public:
        CardInfo fetchCardDetails();
};



class Customer {
	protected:
		string firstName;
		string lastName;
		string accountNumber;
		CardInfo cardInfo;
		Account account;

};
class BankService {
    public:
	    virtual bool isValidUser(string pin, CardInfo cardInfo);
	    virtual Customer getCustomerDetails(CardInfo cardInfo);
	    virtual TransactionDetail executeTransaction(Transaction transactionInfo, Customer customer,AccountType accountType); 
		virtual ~BankService(){ };

};


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
		void readCard(){
			cardInfo=cardReader.fetchCardDetails();
		}
		void checkPassword(){
			access=bankService.isValidUser(keypad.getInput(),cardInfo);
		}
		void selectAccount(AccountType accountType){
			if(access){
        		this->accountType=accountType;
			}
		}
		void executeTransaction(TransactionType transactionType,int amount=0,string destAccunt=""){
			if (!access){
				return;
			}
			switch (transactionType){
				case WITHDRAW:{
					Withdraw withdraw;
					withdraw.amount=amount;
					bankService.executeTransaction(withdraw,bankService.getCustomerDetails(this->cardInfo),accountType);
					break;
				}
				case DEPOSIT:{
					Deposit deposit;
					deposit.amount=amount;
					bankService.executeTransaction(deposit,bankService.getCustomerDetails(this->cardInfo),accountType);
					break;
				}
				case TRANSFER:{
					Transfer transfer;
					transfer.amount=amount;
					transfer.destAccunt=destAccunt;
					bankService.executeTransaction(transfer,bankService.getCustomerDetails(this->cardInfo),accountType);
					break;
				}
				case BALANCE:{
					CheckBalance balance;
					bankService.executeTransaction(balance,bankService.getCustomerDetails(this->cardInfo),accountType);
					break;
				}
			}
		}
	private:
		bool access=false;
};

