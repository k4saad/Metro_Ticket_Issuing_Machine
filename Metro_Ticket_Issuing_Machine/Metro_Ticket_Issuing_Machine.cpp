#include <iostream>
#include<string>
#include"MTIM_DBAbstraction.h"
int main()
{
    MTIM_DBAbstraction Process_1("Metro_Ticket_Issuing_Machine.db");
    Process_1.bookTickit();
    
    return 0;
}
