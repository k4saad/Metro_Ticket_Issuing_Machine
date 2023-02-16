#include <iostream>
#include<string>
#include"MTIM_DBAbstraction.h"
int main()
{
    MTIM_DBAbstraction Process_1("Metro_Ticket_Issuing_Machine.db");
   
   
    while (1)
    {
        system("CLS");
        int opt; 
        cout << "\n\n" << endl;
        Process_1.metroGraphic("graphics\\welcome_metro.txt");
        cout << "\t\t\t---------------------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t---------------------------------------------------------------------------------------------------------" << endl;
        cout << "\n\n" << endl;
        Process_1.metroGraphic("graphics\\main_menue.txt");
        cout << "\t\t\t\t\t------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\tChoose from the options below. \n";
        cout << "\t\t\t\t\tChoose a number corresponding to the option you want to Select. " << endl;
        cout << "\t\t\t\t\t------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\t  1. Book Tickit" << endl;
        cout << "\t\t\t\t\t  2. Admin Login" << endl;
        cout << "\t\t\t\t\t  3. Exit" << endl;

        cin >> opt;
        cout << "\n" << endl;

        switch (opt)
        {
        case 1:
            Process_1.bookTickit();
            break;
        case 2:
            Process_1.adminLogin();
            break;
        case 3:
            exit(1);
        default:
            break;
        }
    }   
    return 0;
}
