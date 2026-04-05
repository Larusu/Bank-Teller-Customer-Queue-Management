#include "AppController.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() 
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    AppController app;
    app.run();

    #ifdef _WIN32
    system("pause");
    #else
    std::cout << "Press Enter to exit...";
    std::cin.get();
    #endif
}
