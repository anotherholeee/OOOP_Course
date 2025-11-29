#include <windows.h>
#include <iostream>
#include "menu.h"

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== СИСТЕМА ТЕСТИРОВАНИЯ ===" << std::endl;
    mainMenu();

    return 0;
}