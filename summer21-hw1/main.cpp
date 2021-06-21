#include "BankingSystem.h"
using namespace std;

int main() {
    BankingSystem B;
    B. addBranch ( 1451 , " Bilkent " );
    B. addBranch ( 2435 , " Kizilay " );
    //B. addBranch ( 1672 , " Bahcelievler " );
    B. addBranch ( 3216 , " Ulus " );
    B. addBranch ( 2435 , " Kizilay " );
    B. deleteBranch ( 1672 );
    B. deleteBranch ( 1723 );
    B. addBranch ( 9876 , " Umitkoy " );

    cout << endl;

    B. addCustomer ( 1234 , " John Smith " );
    B. addCustomer ( 4567 , " Aynur Dayanik " );
    B. addCustomer ( 891234 , " Batuhan Kaynak " );
    B. addCustomer ( 891234 , " Hakan Karaca " );
    B. addCustomer ( 5678 , " Mustafa Gundogan " );
    B. addCustomer ( 8901 , "Can Kara " );
    B. deleteCustomer ( 5678 );
    B. deleteCustomer ( 1267 );

    cout << endl;

    int account1 = B. addAccount ( 1451 , 4567 , 100.00 );
    int account2 = B. addAccount ( 1451 , 1234 , 200.00 );
    int account3 = B. addAccount ( 3216 , 4567 , 300.00 );
    int account4 = B. addAccount ( 1451 , 4567 , 1000.00 );
    int account5 = B. addAccount ( 1672 , 8901 , 100.00 );
    int account6 = B. addAccount ( 2435 , 5678 , 100.00 );
    int account7 = B. addAccount ( 3216 , 1234 , 500.00 );
    B. deleteAccount ( account2 );
    B. deleteAccount ( account5 );
    B. deleteAccount ( account7 );
    int account8 = B. addAccount ( 2435 , 891234 , 500.00 );

    cout << endl;
    B. showAllAccounts ();

    cout << endl;
    B.showBranch(1451);
    B.showBranch(1672);
    B.showBranch(9876);

    return 0;
}