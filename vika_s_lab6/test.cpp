#include "test.h"
#include "utils.h"
#include <iostream>
#include <fstream>

Test::Test() : questionCount(0), answerCount(0), resultCount(0) {
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        questions[i] = nullptr;
    }
}

Test::Test(std::string name, std::string theme)
    : testName(std::move(name)), testTheme(std::move(theme)), questionCount(0), answerCount(0), resultCount(0) {
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        questions[i] = nullptr;
    }
}

Test::Test(const Test& other)
    : testName(other.testName), testTheme(other.testTheme),
      questionCount(other.questionCount), answerCount(other.answerCount), resultCount(other.resultCount) {
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        questions[i] = nullptr;
    }
    for (int i = 0; i < questionCount; i++) {
        questions[i] = other.questions[i];
    }
    for (int i = 0; i < answerCount; i++) {
        answers[i] = other.answers[i];
    }
    for (int i = 0; i < resultCount; i++) {
        results[i] = other.results[i];
    }
}

Test& Test::operator=(const Test& other) {
    if (this != &other) {
        for (int i = 0; i < questionCount; i++) {
            delete questions[i];
        }

        testName = other.testName;
        testTheme = other.testTheme;
        questionCount = other.questionCount;
        answerCount = other.answerCount;
        resultCount = other.resultCount;

        for (int i = 0; i < questionCount; i++) {
            questions[i] = other.questions[i];
        }
        for (int i = 0; i < answerCount; i++) {
            answers[i] = other.answers[i];
        }
        for (int i = 0; i < resultCount; i++) {
            results[i] = other.results[i];
        }
    }
    return *this;
}

Test::~Test() {
    for (int i = 0; i < questionCount; i++) {
        delete questions[i];
    }
}

std::string Test::getTestName() const { return testName; }
std::string Test::getTestTheme() const { return testTheme; }
int Test::getQuestionCount() const { return questionCount; }
int Test::getAnswerCount() const { return answerCount; }
int Test::getResultCount() const { return resultCount; }

void Test::setTestName(const std::string& name) { testName = name; }
void Test::setTestTheme(const std::string& theme) { testTheme = theme; }

bool Test::addQuestion(IQuestion* question) {
    if (questionCount < MAX_QUESTIONS) {
        questions[questionCount] = question;
        questionCount++;
        return true;
    }
    return false;
}

bool Test::addAnswer(const Answer& answer) {
    if (answerCount < MAX_ANSWERS) {
        answers[answerCount] = answer;
        answerCount++;
        return true;
    }
    return false;
}

bool Test::addResult(const Result& result) {
    if (resultCount < MAX_RESULTS) {
        results[resultCount] = result;
        resultCount++;
        return true;
    }
    return false;
}

void Test::displayTestInfo() const {
    std::cout << "\n=== ИНФОРМАЦИЯ О ТЕСТЕ ===" << std::endl;
    std::cout << "Название: " << testName << std::endl;
    std::cout << "Тема: " << testTheme << std::endl;
    std::cout << "Количество вопросов: " << questionCount << std::endl;
    std::cout << "Количество ответов: " << answerCount << std::endl;
    std::cout << "Количество результатов: " << resultCount << std::endl;
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
        std::cout << "0. Выход в главное меню" << std::endl;

        choice = getInputInt("Выберите действие: ", 0, 7);

        switch (choice) {
            case 1: addTextQuestion(); break;
            case 2: addNumericQuestion(); break;
            case 3: displayAllQuestions(); break;
            case 4: takeTest(); break;
            case 5: displayResultsTable(); break;
            case 6: saveResultsToFile(); break;
            case 7: displayTestInfo(); break;
            case 0: std::cout << "Выход..." << std::endl; break;
        }
    } while (choice != 0);
}

void Test::addTextQuestion() {
    if (questionCount >= MAX_QUESTIONS) {
        std::cout << "Достигнуто максимальное количество вопросов!" << std::endl;
        return;
    }

    std::cout << "\n--- Текстовый вопрос ---" << std::endl;

    auto questionText = getInput<std::string>("Введите текст вопроса: ");

    std::string variants[MAX_VARIANTS];
    int variantsCount = 4;

    std::cout << "Введите 4 варианта ответов:" << std::endl;
    for (int i = 0; i < variantsCount; i++) {
        variants[i] = getInput<std::string>("Вариант " + std::to_string(i+1) + ": ");
    }

    int rightAnswer = getInputInt("Номер правильного ответа (1-4): ", 1, 4) - 1;
    int scores = getInputInt("Баллы за вопрос: ", 0, 100);

    IQuestion* question = new Question<std::string, std::string>(
        questionText, variants, variantsCount, rightAnswer, scores, "Текстовый"
    );

    if (addQuestion(question)) {
        std::cout << "Текстовый вопрос добавлен!" << std::endl;
    } else {
        delete question;
        std::cout << "Ошибка добавления вопроса!" << std::endl;
    }
}

void Test::addNumericQuestion() {
    if (questionCount >= MAX_QUESTIONS) {
        std::cout << "Достигнуто максимальное количество вопросов!" << std::endl;
        return;
    }

    std::cout << "\n--- Числовой вопрос ---" << std::endl;

    auto questionText = getInput<std::string>("Введите текст вопроса: ");

    int variants[MAX_VARIANTS];
    int variantsCount = 4;

    std::cout << "Введите 4 числовых варианта ответов:" << std::endl;
    for (int i = 0; i < variantsCount; i++) {
variants[i] = getInputInt("Вариант " + std::to_string(i+1) + ": ", -1000000, 1000000);    }

    int rightAnswer = getInputInt("Номер правильного ответа (1-4): ", 1, 4) - 1;
    int scores = getInputInt("Баллы за вопрос: ", 0, 100);

    IQuestion* question = new Question<std::string, int>(
        questionText, variants, variantsCount, rightAnswer, scores, "Числовой"
    );

    if (addQuestion(question)) {
        std::cout << "Числовой вопрос добавлен!" << std::endl;
    } else {
        delete question;
        std::cout << "Ошибка добавления вопроса!" << std::endl;
    }
}

void Test::displayAllQuestions() const {
    std::cout << "\n=== ВОПРОСЫ ТЕСТА: " << testName << " ===" << std::endl;
    if (questionCount == 0) {
        std::cout << "Вопросов пока нет!" << std::endl;
        return;
    }

    for (int i = 0; i < questionCount; i++) {
        std::cout << "\nВопрос " << (i + 1) << " (" << questions[i]->getType() << "):" << std::endl;
        questions[i]->displayQuestion();
    }
}

void Test::takeTest() {
    if (questionCount == 0) {
        std::cout << "Нет вопросов для тестирования!" << std::endl;
        return;
    }

    std::cout << "\n=== НАЧАЛО ТЕСТА ===" << std::endl;

    auto fio = getInput<std::string>("Введите ваше ФИО: ");
    auto faculty = getInput<std::string>("Введите факультет: ");
    int groupNum = getInputInt("Введите номер группы (6 цифр): ", 100000, 999999);
    auto date = getCurrentDate();

    Answer answer(fio, faculty, groupNum, date, testName);
    addAnswer(answer);

    int totalScore = 0;
    int maxScore = 0;

    for (int i = 0; i < questionCount; i++) {
        std::cout << "\n--- Вопрос " << (i + 1) << " ---" << std::endl;
        questions[i]->displayQuestion();

        int variantsCount = questions[i]->getVariantsCount();
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
    Result result(fio, faculty, groupNum, date, testName, percentage);
    addResult(result);

    std::cout << "\n=== РЕЗУЛЬТАТ ТЕСТА ===" << std::endl;
    std::cout << "Набрано баллов: " << totalScore << " из " << maxScore << std::endl;
    std::cout << "Процент выполнения: " << std::fixed << std::setprecision(1) << percentage << "%" << std::endl;
    std::cout << "Статус: " << (percentage >= 60.0f ? "Сдал" : "Не сдал") << std::endl;
}

void Test::displayResults() const {
    if (resultCount == 0) {
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

    for (int i = 0; i < resultCount; i++) {
        results[i].display();
    }
}

void Test::displayResultsTable() const {
    if (resultCount == 0) {
        std::cout << "Результатов пока нет!" << std::endl;
        return;
    }

    std::cout << "\n=== РЕЗУЛЬТАТЫ ТЕСТА: " << testName << " ===" << std::endl;

    Result::displayTableHeader();

    for (int i = 0; i < resultCount; i++) {
        results[i].displayTableRow(i + 1);
    }

    Result::displayTableFooter();
    std::cout << "Всего результатов: " << resultCount << std::endl;
}

void Test::saveResultsToFile() const {
    if (resultCount == 0) {
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
    file << "Всего результатов: " << resultCount << std::endl;
    file << std::endl;

    file << "+----+---------------------+-------------+--------+----------+--------+" << std::endl;
    file << "| №  | ФИО                 | Факультет   | Группа | Результат| Статус |" << std::endl;
    file << "+----+---------------------+-------------+--------+----------+--------+" << std::endl;

    for (int i = 0; i < resultCount; i++) {
        results[i].saveToFile(file, i + 1);
    }

    file << "+----+---------------------+-------------+--------+----------+--------+" << std::endl;

    int passedCount = 0;
    float averageResult = 0;
    for (int i = 0; i < resultCount; i++) {
        if (results[i].getPassed()) {
            passedCount++;
        }
        averageResult += results[i].getResult();
    }
    averageResult /= resultCount;

    file << std::endl << "СТАТИСТИКА:" << std::endl;
    file << "Сдали тест: " << passedCount << " из " << resultCount
         << " (" << std::fixed << std::setprecision(1) << (static_cast<float>(passedCount) / resultCount * 100) << "%)" << std::endl;
    file << "Средний результат: " << averageResult << "%" << std::endl;

    file.close();
    std::cout << "Результаты успешно сохранены в файл: " << filename << std::endl;
}