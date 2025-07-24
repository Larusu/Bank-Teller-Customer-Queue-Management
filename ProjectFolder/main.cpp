#include "AppController.h"
#include <windows.h>

using namespace std;

int main() 
{
    SetConsoleOutputCP(CP_UTF8);
    AppController app;
    app.run();

    system("pause");
}