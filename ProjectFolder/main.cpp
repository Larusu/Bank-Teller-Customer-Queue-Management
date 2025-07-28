#include "AppController.h"
#include <windows.h>

int main() 
{
    SetConsoleOutputCP(CP_UTF8);
    AppController app;
    app.run();

    system("pause");
}