#include "atm.h"

void ATM::readCard(){
    cardInfo=cardReader.fetchCardDetails();
}
void ATM::checkPassword(){
    access=bankService.isValidUser(keypad.getInput(),cardInfo);
}

void ATM::selectAccount(AccountType accountType){
    if(access){
        this->accountType=accountType;
    }
}

void ATM::executeTransaction(TransactionType transactionType,int amount=0,string destAccunt=""){
    if (!access){
        return;
    }
    switch (transactionType){
        case WITHDRAW:{
            Withdraw withdraw;
            withdraw.amount=amount;
            bankService.executeTransaction(withdraw,bankService.getCustomerDetails(cardInfo),accountType);
            break;
        }
        case DEPOSIT:{
            Deposit deposit;
            deposit.amount=amount;
            bankService.executeTransaction(deposit,bankService.getCustomerDetails(cardInfo),accountType);
            break;
        }
        case TRANSFER:{
            Transfer transfer;
            transfer.amount=amount;
            transfer.destAccunt=destAccunt;
            bankService.executeTransaction(transfer,bankService.getCustomerDetails(cardInfo),accountType);
            break;
        }
        case BALANCE:{
            CheckBalance balance;
            bankService.executeTransaction(balance,bankService.getCustomerDetails(cardInfo),accountType);
            break;
        }
    }
}

//simple workflow demonstration
int main(){
    ATM atm;
    atm.readCard();
    atm.checkPassword();
    atm.selectAccount(CHECKING);
    atm.executeTransaction(WITHDRAW,10);

}
