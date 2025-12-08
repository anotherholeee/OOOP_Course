#include "test.h"
#include "utils.h"
#include "question.h"
#include "answer.h"
#include "result.h"
#include <iostream>
#include <fstream>

Test::Test() {}

Test::Test(std::string name, std::string theme)
    : testName(std::move(name)), testTheme(std::move(theme)) {}

Test::Test(const Test& other)
    : testName(other.testName), testTheme(other.testTheme) {
    for (const auto& question : other.questions) {
        if (question) {
            questions.push_back(question->clone());
        }
    }
    for (const auto& answer : other.answers) {
        if (answer) {
            answers.push_back(std::make_unique<Answer>(*answer));
        }
    }
    for (const auto& result : other.results) {
        if (result) {
            results.push_back(std::make_unique<Result>(*result));
        }
    }
}

Test& Test::operator=(const Test& other) {
    if (this != &other) {
        testName = other.testName;
        testTheme = other.testTheme;
        
        questions.clear();
        for (const auto& question : other.questions) {
            if (question) {
                questions.push_back(question->clone());
            }
        }
        
        answers.clear();
        for (const auto& answer : other.answers) {
            if (answer) {
                answers.push_back(std::make_unique<Answer>(*answer));
            }
        }
        
        results.clear();
        for (const auto& result : other.results) {
            if (result) {
                results.push_back(std::make_unique<Result>(*result));
            }
        }
    }
    return *this;
}

Test::~Test() {}

std::string Test::getTestName() const { return testName; }
std::string Test::getTestTheme() const { return testTheme; }
int Test::getQuestionCount() const { return static_cast<int>(questions.size()); }
int Test::getAnswerCount() const { return static_cast<int>(answers.size()); }
int Test::getResultCount() const { return static_cast<int>(results.size()); }

void Test::setTestName(const std::string& name) { testName = name; }
void Test::setTestTheme(const std::string& theme) { testTheme = theme; }

bool Test::addQuestion(std::unique_ptr<IQuestion> question) {
    if (questions.size() < MAX_QUESTIONS) {
        questions.push_back(std::move(question));
        return true;
    }
    return false;
}

bool Test::addAnswer(std::unique_ptr<Answer> answer) {
    if (answers.size() < MAX_ANSWERS) {
        answers.push_back(std::move(answer));
        return true;
    }
    return false;
}

bool Test::addResult(std::unique_ptr<Result> result) {
    if (results.size() < MAX_RESULTS) {
        results.push_back(std::move(result));
        return true;
    }
    return false;
}

void Test::displayTestInfo() const {
    std::cout << "\n=== ИНФОРМАЦИЯ О ТЕСТЕ ===" << std::endl;
    std::cout << "Название: " << testName << std::endl;
    std::cout << "Тема: " << testTheme << std::endl;
    std::cout << "Количество вопросов: " << questions.size() << std::endl;
    std::cout << "Количество ответов: " << answers.size() << std::endl;
    std::cout << "Количество результатов: " << results.size() << std::endl;
}

void Test::showMenu() {
    int choice;
    do {
        std::cout << "\n=== МЕНЮ ТЕСТА: " << testName << " ===" << std::endl;
        std::cout << "1. Добавить текстовый вопрос" << std::endl;
        std::cout << "2. Добавить числовой вопрос" << std::endl;
        std::cout << "3. Показать все вопросы" << std::endl;
        std::cout << "4. Пройти тест" << std::endl;
        std::cout << "5. Показать результаты" << std::endl;
        std::cout << "6. Сохранить результаты в файл" << std::endl;
        std::cout << "7. Информация о тесте" << std::endl;
        std::cout << "8. Управление историей изменений ответов" << std::endl;
        std::cout << "0. Выход в главное меню" << std::endl;

        choice = getInputInt("Выберите действие: ", 0, 8);

        switch (choice) {
            case 1: addTextQuestion(); break;
            case 2: addNumericQuestion(); break;
            case 3: displayAllQuestions(); break;
            case 4: takeTest(); break;
            case 5: displayResultsTable(); break;
            case 6: saveResultsToFile(); break;
            case 7: displayTestInfo(); break;
            case 8: manageTransactions(); break;
            case 0: std::cout << "Выход..." << std::endl; break;
        }
    } while (choice != 0);
}

void Test::addTextQuestion() {
    if (questions.size() >= MAX_QUESTIONS) {
        std::cout << "Достигнуто максимальное количество вопросов!" << std::endl;
        return;
    }

    std::cout << "\n--- Текстовый вопрос ---" << std::endl;

    std::string questionText;
    do {
        questionText = getInputText("Введите текст вопроса (без цифр): ");
    } while (questionText.empty());

    std::string variants[MAX_VARIANTS];
    int variantsCount = 4;

    std::cout << "Введите 4 текстовых варианта ответов (без цифр):" << std::endl;
    for (int i = 0; i < variantsCount; i++) {
        std::string prompt = "Вариант " + std::to_string(i+1) + " (без цифр): ";
        variants[i] = getInputText(prompt);
    }

    int rightAnswer = getInputInt("Номер правильного ответа (1-4): ", 1, 4) - 1;
    int scores = getInputInt("Баллы за вопрос (0-100): ", 0, 100);

    auto question = std::make_unique<Question<std::string, std::string>>(
        questionText, variants, variantsCount, rightAnswer, scores, "Текстовый"
    );

    if (addQuestion(std::move(question))) {
        std::cout << "Текстовый вопрос добавлен!" << std::endl;
    } else {
        std::cout << "Ошибка добавления вопроса!" << std::endl;
    }
}

void Test::addNumericQuestion() {
    if (questions.size() >= MAX_QUESTIONS) {
        std::cout << "Достигнуто максимальное количество вопросов!" << std::endl;
        return;
    }

    std::cout << "\n--- Числовой вопрос ---" << std::endl;

    auto questionText = getInput<std::string>("Введите текст вопроса: ");

    int intVariants[MAX_VARIANTS];
    int variantsCount = 4;

    std::cout << "Введите 4 числовых варианта ответов (целые числа, могут быть отрицательными):" << std::endl;
    for (int i = 0; i < variantsCount; i++) {
        std::string prompt = "Вариант " + std::to_string(i+1) + " (целое число): ";
        std::string numericStr = getInputIntegerString(prompt);

        try {
            intVariants[i] = std::stoi(numericStr);
        } catch (const std::out_of_range&) {
            std::cout << "Ошибка: число слишком большое. Установлено значение 0." << std::endl;
            intVariants[i] = 0;
        } catch (...) {
            std::cout << "Ошибка преобразования числа. Установлено значение 0." << std::endl;
            intVariants[i] = 0;
        }
    }

    int rightAnswer = getInputInt("Номер правильного ответа (1-4): ", 1, 4) - 1;
    int scores = getInputInt("Баллы за вопрос (0-100): ", 0, 100);

    auto question = std::make_unique<Question<std::string, int>>(
        questionText, intVariants, variantsCount, rightAnswer, scores, "Числовой"
    );

    if (addQuestion(std::move(question))) {
        std::cout << "Числовой вопрос добавлен!" << std::endl;
    } else {
        std::cout << "Ошибка добавления вопроса!" << std::endl;
    }
}

void Test::displayAllQuestions() const {
    std::cout << "\n=== ВОПРОСЫ ТЕСТА: " << testName << " ===" << std::endl;
    if (questions.empty()) {
        std::cout << "Вопросов пока нет!" << std::endl;
        return;
    }

    for (size_t i = 0; i < questions.size(); i++) {
        std::cout << "\nВопрос " << (i + 1) << " (" << questions[i]->getType() << "):" << std::endl;
        questions[i]->displayQuestion();
    }
}

void Test::takeTest() {
    if (questions.empty()) {
        std::cout << "Нет вопросов для тестирования!" << std::endl;
        return;
    }

    std::cout << "\n=== НАЧАЛО ТЕСТА ===" << std::endl;

    auto fio = getInput<std::string>("Введите ваше ФИО: ");
    auto faculty = getInput<std::string>("Введите факультет: ");
    int groupNum = getInputInt("Введите номер группы (6 цифр): ", 100000, 999999);
    auto date = getCurrentDate();

    auto answer = std::make_unique<Answer>(fio, faculty, groupNum, date, testName);
    addAnswer(std::move(answer));

    int totalScore = 0;
    int maxScore = 0;

    for (size_t i = 0; i < questions.size(); i++) {
        std::cout << "\n--- Вопрос " << (i + 1) << " [" << questions[i]->getType() << "] ---" << std::endl;
        questions[i]->displayQuestion();

        int variantsCount = questions[i]->getVariantsCount();

        if (questions[i]->getType() == "Числовой") {
            std::cout << "Вводите только цифры!" << std::endl;
        }

        int userAnswer = getInputInt("Ваш ответ (номер варианта): ", 1, variantsCount) - 1;

        if (questions[i]->checkAnswer(userAnswer)) {
            std::cout << "✓ Правильно! +" << questions[i]->getScores() << " баллов" << std::endl;
            totalScore += questions[i]->getScores();
        } else {
            std::cout << "✗ Неправильно!" << std::endl;
        }

        maxScore += questions[i]->getScores();
    }

    float percentage = (maxScore > 0) ? (static_cast<float>(totalScore) / maxScore * 100) : 0;
    auto result = std::make_unique<Result>(fio, faculty, groupNum, date, testName, percentage);
    addResult(std::move(result));

    std::cout << "\n=== РЕЗУЛЬТАТ ТЕСТА ===" << std::endl;
    std::cout << "Набрано баллов: " << totalScore << " из " << maxScore << std::endl;
    std::cout << "Процент выполнения: " << std::fixed << std::setprecision(1) << percentage << "%" << std::endl;
    std::cout << "Статус: " << (percentage >= 60.0f ? "Сдал" : "Не сдал") << std::endl;
}

void Test::displayResults() const {
    if (results.empty()) {
        std::cout << "Результатов пока нет!" << std::endl;
        return;
    }

    std::cout << "\n=== РЕЗУЛЬТАТЫ ТЕСТА: " << testName << " ===" << std::endl;
    std::cout << std::left << std::setw(25) << "ФИО"
              << std::setw(15) << "Факультет"
              << std::setw(8) << "Группа"
              << std::setw(10) << "Результат"
              << std::setw(10) << "Статус" << std::endl;
    std::cout << std::string(68, '-') << std::endl;

    for (const auto& result : results) {
        result->display();
    }
}

void Test::displayResultsTable() const {
    if (results.empty()) {
        std::cout << "Результатов пока нет!" << std::endl;
        return;
    }

    std::cout << "\n=== РЕЗУЛЬТАТЫ ТЕСТА: " << testName << " ===" << std::endl;

    Result::displayTableHeader();

    for (size_t i = 0; i < results.size(); i++) {
        // Ищем соответствующий ответ для этого результата
        std::string fio = results[i]->getFio();
        std::string faculty = results[i]->getFaculty();
        int group = results[i]->getGroupNum();
        std::string date = results[i]->getDate();
        std::string testName = results[i]->getTestName();
        float resultValue = results[i]->getResult();
        bool passed = results[i]->getPassed();

        // Проверяем, есть ли обновленные данные в ответах
        for (const auto& answer : answers) {
            if (answer->getFio() == fio &&
                answer->getFaculty() == faculty &&
                answer->getGroupNum() == group &&
                answer->getDate() == date &&
                answer->getTestName() == testName) {
                // Используем обновленные данные из ответа
                fio = answer->getFio();
                faculty = answer->getFaculty();
                group = answer->getGroupNum();
                date = answer->getDate();
                testName = answer->getTestName();
                break;
            }
        }

        // Выводим строку таблицы с обновленными данными
        std::string shortFio = fio;
        if (shortFio.length() > 19) {
            shortFio = shortFio.substr(0, 16) + "...";
        }

        std::string shortFaculty = faculty;
        if (shortFaculty.length() > 11) {
            shortFaculty = shortFaculty.substr(0, 8) + "...";
        }

        std::cout << "| " << std::setw(2) << std::right << (i + 1) << " | "
                  << std::setw(19) << std::left << shortFio << " | "
                  << std::setw(11) << std::left << shortFaculty << " | "
                  << std::setw(6) << std::right << group << " | "
                  << std::setw(8) << std::right << std::fixed << std::setprecision(1) << resultValue << "% | "
                  << std::setw(6) << std::left << (passed ? "Сдал" : "Не сдал") << " |" << std::endl;
    }

    Result::displayTableFooter();
    std::cout << "Всего результатов: " << results.size() << std::endl;
}

void Test::saveResultsToFile() const {
    if (results.empty()) {
        std::cout << "Нет результатов для сохранения!" << std::endl;
        return;
    }

    std::string filename = testName + "_results.txt";
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось создать файл " << filename << std::endl;
        return;
    }

    file << "ОТЧЕТ О РЕЗУЛЬТАТАХ ТЕСТИРОВАНИЯ" << std::endl;
    file << "Дата создания отчета: " << getCurrentDate() << std::endl;
    file << "Тест: " << testName << std::endl;
    file << "Тема: " << testTheme << std::endl;
    file << "Всего результатов: " << results.size() << std::endl;
    file << std::endl;

    file << "+----+---------------------+-------------+--------+----------+--------+" << std::endl;
    file << "| №  | ФИО                 | Факультет   | Группа | Результат| Статус |" << std::endl;
    file << "+----+---------------------+-------------+--------+----------+--------+" << std::endl;

    for (size_t i = 0; i < results.size(); i++) {
        // Ищем соответствующий ответ для этого результата
        std::string fio = results[i]->getFio();
        std::string faculty = results[i]->getFaculty();
        int group = results[i]->getGroupNum();
        std::string date = results[i]->getDate();
        std::string testName = results[i]->getTestName();
        float resultValue = results[i]->getResult();
        bool passed = results[i]->getPassed();

        // Проверяем, есть ли обновленные данные в ответах
        for (const auto& answer : answers) {
            if (answer->getFio() == fio &&
                answer->getFaculty() == faculty &&
                answer->getGroupNum() == group &&
                answer->getDate() == date &&
                answer->getTestName() == testName) {
                // Используем обновленные данные из ответа
                fio = answer->getFio();
                faculty = answer->getFaculty();
                group = answer->getGroupNum();
                date = answer->getDate();
                testName = answer->getTestName();
                break;
            }
        }

        file << "| " << std::setw(2) << std::right << (i + 1) << " | "
             << std::setw(19) << std::left << fio << " | "
             << std::setw(11) << std::left << faculty << " | "
             << std::setw(6) << std::right << group << " | "
             << std::setw(8) << std::right << std::fixed << std::setprecision(1) << resultValue << "% | "
             << std::setw(6) << std::left << (passed ? "Сдал" : "Не сдал") << " |" << std::endl;
    }

    file << "+----+---------------------+-------------+--------+----------+--------+" << std::endl;

    int passedCount = 0;
    float averageResult = 0;
    for (const auto& result : results) {
        if (result->getPassed()) {
            passedCount++;
        }
        averageResult += result->getResult();
    }
    averageResult /= results.size();

    file << std::endl << "СТАТИСТИКА:" << std::endl;
    file << "Сдали тест: " << passedCount << " из " << results.size()
         << " (" << std::fixed << std::setprecision(1) << (static_cast<float>(passedCount) / results.size() * 100) << "%)" << std::endl;
    file << "Средний результат: " << averageResult << "%" << std::endl;

    file.close();
    std::cout << "Результаты успешно сохранены в файл: " << filename << std::endl;
}

void Test::manageTransactions() {
    if (answers.empty()) {
        std::cout << "Нет добавленных ответов!" << std::endl;
        return;
    }
    
    std::cout << "\n=== ИСТОРИЯ ИЗМЕНЕНИЙ ОТВЕТОВ ===" << std::endl;
    std::cout << "Список ответов:" << std::endl;
    
    for (size_t i = 0; i < answers.size(); i++) {
        std::cout << (i + 1) << ". " << answers[i]->getFio() 
                  << " - " << answers[i]->getTestName() 
                  << " (несохраненных изменений: " 
                  << answers[i]->getChangeHistorySize() << ")" 
                  << std::endl;
    }
    
    int choice = getInputInt("Выберите ответ для управления: ", 
                           1, static_cast<int>(answers.size())) - 1;
    
    Answer& selectedAnswer = *answers[choice];
    
    // Находим соответствующий результат для этого ответа
    std::unique_ptr<Result>* correspondingResult = nullptr;
    for (auto& result : results) {
        if (result->getFio() == selectedAnswer.getFio() &&
            result->getFaculty() == selectedAnswer.getFaculty() &&
            result->getGroupNum() == selectedAnswer.getGroupNum() &&
            result->getDate() == selectedAnswer.getDate() &&
            result->getTestName() == selectedAnswer.getTestName()) {
            correspondingResult = &result;
            break;
        }
    }

    int action;
    do {
        std::cout << "\nОтвет: " << selectedAnswer.getFio()
                  << " [" << selectedAnswer.getTestName() << "]" << std::endl;
        std::cout << "Текущие данные:" << std::endl;
        std::cout << "  ФИО: " << selectedAnswer.getFio() << std::endl;
        std::cout << "  Факультет: " << selectedAnswer.getFaculty() << std::endl;
        std::cout << "  Группа: " << selectedAnswer.getGroupNum() << std::endl;
        std::cout << "  Дата: " << selectedAnswer.getDate() << std::endl;
        std::cout << "  Тест: " << selectedAnswer.getTestName() << std::endl;
        std::cout << "  Несохраненных изменений: "
                  << selectedAnswer.getChangeHistorySize() << std::endl;

        if (correspondingResult) {
            std::cout << "  Соответствующий результат: "
                      << (*correspondingResult)->getResult() << "%" << std::endl;
        }

        std::cout << "\nМЕНЮ ИСТОРИИ ИЗМЕНЕНИЙ:" << std::endl;
        std::cout << "1. Сохранить текущее состояние" << std::endl;
        std::cout << "2. Изменить ФИО" << std::endl;
        std::cout << "3. Изменить факультет" << std::endl;
        std::cout << "4. Изменить группу" << std::endl;
        std::cout << "5. Изменить дату" << std::endl;
        std::cout << "6. Изменить название теста" << std::endl;
        std::cout << "7. Отменить последнее изменение (Ctrl+Z)" << std::endl;
        std::cout << "8. Завершить все транзакции и обновить результат" << std::endl;
        std::cout << "0. Выход" << std::endl;

        action = getInputInt("Выберите действие: ", 0, 8);

        switch (action) {
            case 1:
                selectedAnswer.saveCurrentState();
                std::cout << "Текущее состояние сохранено!" << std::endl;
                break;

            case 2: {
                auto newFio = getInput<std::string>("Введите новое ФИО: ");
                selectedAnswer.setFio(newFio);
                std::cout << "ФИО изменено." << std::endl;
                break;
            }

            case 3: {
                auto newFaculty = getInput<std::string>("Введите новый факультет: ");
                selectedAnswer.setFaculty(newFaculty);
                std::cout << "Факультет изменен." << std::endl;
                break;
            }

            case 4: {
                int newGroup = getInputInt("Введите новый номер группы (6 цифр): ",
                                         100000, 999999);
                selectedAnswer.setGroupNum(newGroup);
                std::cout << "Группа изменена." << std::endl;
                break;
            }

            case 5: {
                auto newDate = getInput<std::string>("Введите новую дату (ГГГГ-ММ-ДД): ");
                selectedAnswer.setDate(newDate);
                std::cout << "Дата изменена." << std::endl;
                break;
            }

            case 6: {
                auto newTestName = getInput<std::string>("Введите новое название теста: ");
                selectedAnswer.setTestName(newTestName);
                std::cout << "Название теста изменено." << std::endl;
                break;
            }

            case 7:
                if (selectedAnswer.undoLastChange()) {
                    std::cout << "Последнее изменение отменено!" << std::endl;
                } else {
                    std::cout << "Нет изменений для отмены!" << std::endl;
                }
                break;

            case 8:
                selectedAnswer.commitAllChanges();

                // Обновляем соответствующий результат с новыми данными
                if (correspondingResult) {
                    // Создаем новый результат с обновленными данными и старым процентом
                    float oldResult = (*correspondingResult)->getResult();
                    auto newResult = std::make_unique<Result>(
                        selectedAnswer.getFio(),
                        selectedAnswer.getFaculty(),
                        selectedAnswer.getGroupNum(),
                        selectedAnswer.getDate(),
                        selectedAnswer.getTestName(),
                        oldResult
                    );

                    // Заменяем старый результат новым
                    *correspondingResult = std::move(newResult);
                    std::cout << "Все изменения сохранены и результат обновлен!" << std::endl;
                } else {
                    std::cout << "Все изменения сохранены, но не найден соответствующий результат!" << std::endl;
                }
                break;
                
            case 0:
                std::cout << "Выход из управления историей изменений..." << std::endl;
                break;
        }
    } while (action != 0);
}