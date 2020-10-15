#include "atm.h"
//simple example workflow demonstration
int main(){
    ATM atm;
    atm.readCard();
    atm.checkPassword();
    atm.selectAccount(CHECKING);
    atm.executeTransaction(WITHDRAW,10);
}
