#include "test.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

Test::Test() : questionCount(0), answerCount(0), resultCount(0) {
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        questions[i] = nullptr;
    }
}

Test::Test(string name, string theme)
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

string Test::getTestName() const { return testName; }
string Test::getTestTheme() const { return testTheme; }
int Test::getQuestionCount() const { return questionCount; }
int Test::getAnswerCount() const { return answerCount; }
int Test::getResultCount() const { return resultCount; }

void Test::setTestName(const string& name) { testName = name; }
void Test::setTestTheme(const string& theme) { testTheme = theme; }

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
    cout << "\n=== ИНФОРМАЦИЯ О ТЕСТЕ ===" << endl;
    cout << "Название: " << testName << endl;
    cout << "Тема: " << testTheme << endl;
    cout << "Количество вопросов: " << questionCount << endl;
    cout << "Количество ответов: " << answerCount << endl;
    cout << "Количество результатов: " << resultCount << endl;
}

void Test::showMenu() {
    int choice;
    do {
        cout << "\n=== МЕНЮ ТЕСТА: " << testName << " ===" << endl;
        cout << "1. Добавить текстовый вопрос" << endl;
        cout << "2. Добавить числовой вопрос" << endl;
        cout << "3. Показать все вопросы" << endl;
        cout << "4. Пройти тест" << endl;
        cout << "5. Показать результаты" << endl;
        cout << "6. Сохранить результаты в файл" << endl;
        cout << "7. Информация о тесте" << endl;
        cout << "0. Выход в главное меню" << endl;

        choice = getInputInt("Выберите действие: ", 0, 7);

        switch (choice) {
            case 1: addTextQuestion(); break;
            case 2: addNumericQuestion(); break;
            case 3: displayAllQuestions(); break;
            case 4: takeTest(); break;
            case 5: displayResultsTable(); break;
            case 6: saveResultsToFile(); break;
            case 7: displayTestInfo(); break;
            case 0: cout << "Выход..." << endl; break;
        }
    } while (choice != 0);
}

void Test::addTextQuestion() {
    if (questionCount >= MAX_QUESTIONS) {
        cout << "Достигнуто максимальное количество вопросов!" << endl;
        return;
    }

    cout << "\n--- Текстовый вопрос ---" << endl;

    auto questionText = getInput<string>("Введите текст вопроса: ");

    string variants[MAX_VARIANTS];
    int variantsCount = 4;

    cout << "Введите 4 варианта ответов:" << endl;
    for (int i = 0; i < variantsCount; i++) {
        variants[i] = getInput<string>("Вариант " + to_string(i+1) + ": ");
    }

    int rightAnswer = getInputInt("Номер правильного ответа (1-4): ", 1, 4) - 1;
    int scores = getInputInt("Баллы за вопрос: ", 0, 100);

    IQuestion* question = new Question<string, string>(
        questionText, variants, variantsCount, rightAnswer, scores, "Текстовый"
    );

    if (addQuestion(question)) {
        cout << "Текстовый вопрос добавлен!" << endl;
    } else {
        delete question;
        cout << "Ошибка добавления вопроса!" << endl;
    }
}

void Test::addNumericQuestion() {
    if (questionCount >= MAX_QUESTIONS) {
        cout << "Достигнуто максимальное количество вопросов!" << endl;
        return;
    }

    cout << "\n--- Числовой вопрос ---" << endl;

    auto questionText = getInput<string>("Введите текст вопроса: ");

    int variants[MAX_VARIANTS];
    int variantsCount = 4;

    cout << "Введите 4 числовых варианта ответов:" << endl;
    for (int i = 0; i < variantsCount; i++) {
        variants[i] = getInputInt("Вариант " + to_string(i+1) + ": ");
    }

    int rightAnswer = getInputInt("Номер правильного ответа (1-4): ", 1, 4) - 1;
    int scores = getInputInt("Баллы за вопрос: ", 0, 100);

    IQuestion* question = new Question<string, int>(
        questionText, variants, variantsCount, rightAnswer, scores, "Числовой"
    );

    if (addQuestion(question)) {
        cout << "Числовой вопрос добавлен!" << endl;
    } else {
        delete question;
        cout << "Ошибка добавления вопроса!" << endl;
    }
}

void Test::displayAllQuestions() const {
    cout << "\n=== ВОПРОСЫ ТЕСТА: " << testName << " ===" << endl;
    if (questionCount == 0) {
        cout << "Вопросов пока нет!" << endl;
        return;
    }

    for (int i = 0; i < questionCount; i++) {
        cout << "\nВопрос " << (i + 1) << " (" << questions[i]->getType() << "):" << endl;
        questions[i]->displayQuestion();
    }
}

void Test::takeTest() {
    if (questionCount == 0) {
        cout << "Нет вопросов для тестирования!" << endl;
        return;
    }

    cout << "\n=== НАЧАЛО ТЕСТА ===" << endl;

    auto fio = getInput<string>("Введите ваше ФИО: ");
    auto faculty = getInput<string>("Введите факультет: ");
    int groupNum = getInputInt("Введите номер группы (6 цифр): ", 100000, 999999);
    auto date = getCurrentDate();

    Answer answer(fio, faculty, groupNum, date, testName);
    addAnswer(answer);

    int totalScore = 0;
    int maxScore = 0;

    for (int i = 0; i < questionCount; i++) {
        cout << "\n--- Вопрос " << (i + 1) << " ---" << endl;
        questions[i]->displayQuestion();

        int variantsCount = questions[i]->getVariantsCount();
        int userAnswer = getInputInt("Ваш ответ (номер варианта): ", 1, variantsCount) - 1;

        if (questions[i]->checkAnswer(userAnswer)) {
            cout << "✓ Правильно! +" << questions[i]->getScores() << " баллов" << endl;
            totalScore += questions[i]->getScores();
        } else {
            cout << "✗ Неправильно!" << endl;
        }

        maxScore += questions[i]->getScores();
    }

    float percentage = (maxScore > 0) ? (static_cast<float>(totalScore) / maxScore * 100) : 0;
    Result result(fio, faculty, groupNum, date, testName, percentage);
    addResult(result);

    cout << "\n=== РЕЗУЛЬТАТ ТЕСТА ===" << endl;
    cout << "Набрано баллов: " << totalScore << " из " << maxScore << endl;
    cout << "Процент выполнения: " << fixed << setprecision(1) << percentage << "%" << endl;
    cout << "Статус: " << (percentage >= 60.0f ? "Сдал" : "Не сдал") << endl;
}

void Test::displayResults() const {
    if (resultCount == 0) {
        cout << "Результатов пока нет!" << endl;
        return;
    }

    cout << "\n=== РЕЗУЛЬТАТЫ ТЕСТА: " << testName << " ===" << endl;
    cout << left << setw(25) << "ФИО"
         << setw(15) << "Факультет"
         << setw(8) << "Группа"
         << setw(10) << "Результат"
         << setw(10) << "Статус" << endl;
    cout << string(68, '-') << endl;

    for (int i = 0; i < resultCount; i++) {
        results[i].display();
    }
}

void Test::displayResultsTable() const {
    if (resultCount == 0) {
        cout << "Результатов пока нет!" << endl;
        return;
    }

    cout << "\n=== РЕЗУЛЬТАТЫ ТЕСТА: " << testName << " ===" << endl;

    Result::displayTableHeader();

    for (int i = 0; i < resultCount; i++) {
        results[i].displayTableRow(i + 1);
    }

    Result::displayTableFooter();
    cout << "Всего результатов: " << resultCount << endl;
}

void Test::saveResultsToFile() const {
    if (resultCount == 0) {
        cout << "Нет результатов для сохранения!" << endl;
        return;
    }

    string filename = testName + "_results.txt";

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }

    file << "ОТЧЕТ О РЕЗУЛЬТАТАХ ТЕСТИРОВАНИЯ" << endl;
    file << "Дата создания отчета: " << getCurrentDate() << endl;
    file << "Тест: " << testName << endl;
    file << "Тема: " << testTheme << endl;
    file << "Всего результатов: " << resultCount << endl;
    file << endl;

    file << "+----+---------------------+-------------+--------+----------+--------+" << endl;
    file << "| №  | ФИО                 | Факультет   | Группа | Результат| Статус |" << endl;
    file << "+----+---------------------+-------------+--------+----------+--------+" << endl;

    for (int i = 0; i < resultCount; i++) {
        results[i].saveToFile(file, i + 1);
    }

    file << "+----+---------------------+-------------+--------+----------+--------+" << endl;

    int passedCount = 0;
    float averageResult = 0;
    for (int i = 0; i < resultCount; i++) {
        if (results[i].getPassed()) {
            passedCount++;
        }
        averageResult += results[i].getResult();
    }
    averageResult /= resultCount;

    file << endl << "СТАТИСТИКА:" << endl;
    file << "Сдали тест: " << passedCount << " из " << resultCount
         << " (" << fixed << setprecision(1) << (static_cast<float>(passedCount) / resultCount * 100) << "%)" << endl;
    file << "Средний результат: " << averageResult << "%" << endl;

    file.close();
    cout << "Результаты успешно сохранены в файл: " << filename << endl;
}