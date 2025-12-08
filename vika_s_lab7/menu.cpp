#include "menu.h"
#include "test.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <memory>

void mainMenu() {
    static const int MAX_TESTS = 20;
    std::vector<std::unique_ptr<Test>> tests;
    int choice;

    do {
        std::cout << "\n=== ГЛАВНОЕ МЕНЮ СИСТЕМЫ ТЕСТИРОВАНИЯ ===" << std::endl;
        std::cout << "1. Создать новый тест" << std::endl;
        std::cout << "2. Работать с существующим тестом" << std::endl;
        std::cout << "3. Показать все тесты" << std::endl;
        std::cout << "0. Выход из программы" << std::endl;

        choice = getInputInt("Выберите действие: ", 0, 3);

        switch (choice) {
            case 1: {
                if (tests.size() >= MAX_TESTS) {
                    std::cout << "Достигнуто максимальное количество тестов!" << std::endl;
                    break;
                }
                auto name = getInput<std::string>("Введите название теста: ");
                auto theme = getInput<std::string>("Введите тему теста: ");
                tests.push_back(std::make_unique<Test>(name, theme));
                std::cout << "Тест создан!" << std::endl;
                break;
            }
            case 2: {
                if (tests.empty()) {
                    std::cout << "Нет созданных тестов!" << std::endl;
                    break;
                }
                std::cout << "\nСписок тестов:" << std::endl;
                for (size_t i = 0; i < tests.size(); i++) {
                    std::cout << (i + 1) << ". " << tests[i]->getTestName()
                         << " (" << tests[i]->getTestTheme() << ")" << std::endl;
                }
                int testChoice = getInputInt("Выберите тест: ", 1, static_cast<int>(tests.size())) - 1;
                tests[testChoice]->showMenu();
                break;
            }
            case 3: {
                if (tests.empty()) {
                    std::cout << "Нет созданных тестов!" << std::endl;
                    break;
                }
                std::cout << "\n=== ВСЕ ТЕСТЫ ===" << std::endl;
                for (size_t i = 0; i < tests.size(); i++) {
                    std::cout << "\nТест " << (i + 1) << ":" << std::endl;
                    tests[i]->displayTestInfo();
                }
                break;
            }
            case 0: std::cout << "Выход из программы..." << std::endl; break;
        }
    } while (choice != 0);
}