#include<iostream>
#include<windows.h>
#include<string>
#include<iomanip>
#include <limits>
#include <fstream>
#include <ctime>

using namespace std;


string getCurrentDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    return string(buffer);
}

template<typename T>
T getInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if constexpr (std::is_same_v<T, string>) {
            getline(cin, value);
            if (!value.empty()) {
                return value;
            }
            cout << "Ошибка: ввод не может быть пустым. Попробуйте снова." << endl;
        } else {
            cin >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: введите корректное значение. Попробуйте снова." << endl;
            } else {
                cin.ignore();
                return value;
            }
        }
    }
}

int getInputInt(const string& prompt, int minVal = numeric_limits<int>::min(), int maxVal = numeric_limits<int>::max()) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите целое число. Попробуйте снова." << endl;
        } else if (value < minVal || value > maxVal) {
            cout << "Ошибка: число должно быть в диапазоне от " << minVal << " до " << maxVal << ". Попробуйте снова." << endl;
        } else {
            cin.ignore();
            return value;
        }
    }
}

class User {
protected:
    string fio;
    string faculty;
    int groupNum;
public:
    User() : groupNum(0) {};
    User(string fio, string faculty, int groupNum) : fio(std::move(fio)), faculty(std::move(faculty)), groupNum(groupNum) {};
    User(const User& copy) = default;
    virtual ~User() = default;

    string getFio() const { return fio; }
    string getFaculty() const { return faculty; }
    int getGroupNum() const { return groupNum; }

    void setFio(const string& newFio) {
        if (!newFio.empty()) {
            fio = newFio;
        }
    }

    void setFaculty(const string& newFaculty) {
        if (!newFaculty.empty()) {
            faculty = newFaculty;
        }
    }

    void setGroupNum(int newGroupNum) {
        if (newGroupNum >= 100000 && newGroupNum <= 999999) {
            groupNum = newGroupNum;
        }
    }
};

class Answer : public User {
protected:
    string date;
    string testName;
public:
    Answer() = default;
    Answer(string fio, const string& faculty, int groupNum, string date, string testName)
        : User(std::move(fio), faculty, groupNum), date(std::move(date)), testName(std::move(testName)) {};
    Answer(const Answer& copy) : User(copy), date(copy.date), testName(copy.testName) {};
    ~Answer() override =default;

    string getDate() const { return date; }
    string getTestName() const { return testName; }

    void setDate(const string& newDate) { date = newDate; }
    void setTestName(const string& newTestName) { testName = newTestName; }
};

class IQuestion {
public:
    virtual ~IQuestion() = default;
    virtual void displayQuestion() const = 0;
    virtual bool checkAnswer(int userAnswer) const = 0;
    virtual int getScores() const = 0;
    virtual string getType() const = 0;
    virtual string getQuestionText() const = 0;
    virtual int getVariantsCount() const = 0;
};

template<class TQuestion, class TVariants>
class Question : public IQuestion {
protected:
    static const int MAX_VARIANTS = 10;

    TQuestion questionText;
    TVariants variants[MAX_VARIANTS];
    int variantsCount;
    int rightVariantNumber;
    int scores;
    string typeName;

public:
    Question() : variantsCount(0), rightVariantNumber(0), scores(0) {}

    Question(TQuestion  questionText, const TVariants* variantsArray, int varCount,
             int rightVariant, int scores, string  type)
        : questionText(std::move(questionText)), variantsCount(varCount),
          rightVariantNumber(rightVariant), scores(scores), typeName(std::move(type)) {
        for (int i = 0; i < varCount && i < MAX_VARIANTS; i++) {
            variants[i] = variantsArray[i];
        }
    }

    Question(const Question& copy)
        : questionText(copy.questionText), variantsCount(copy.variantsCount),
          rightVariantNumber(copy.rightVariantNumber), scores(copy.scores), typeName(copy.typeName) {
        for (int i = 0; i < variantsCount; i++) {
            variants[i] = copy.variants[i];
        }
    }

    ~Question() override = default;

    string getQuestionText() const override { return questionText; }
    int getVariantsCount() const override { return variantsCount; }
    TVariants getVariant(int index) const {
        if (index >= 0 && index < variantsCount) return variants[index];
        return TVariants();
    }
    int getRightVariantNumber() const { return rightVariantNumber; }
    int getScores() const override { return scores; }
    string getType() const override { return typeName; }

    void setQuestionText(const TQuestion& newQuestionText) {
        questionText = newQuestionText;
    }

    void setVariants(const TVariants* newVariants, int count) {
        variantsCount = (count > MAX_VARIANTS) ? MAX_VARIANTS : count;
        for (int i = 0; i < variantsCount; i++) {
            variants[i] = newVariants[i];
        }
    }

    void setRightVariantNumber(int newRightVariantNumber) {
        if (newRightVariantNumber >= 0 && newRightVariantNumber < variantsCount) {
            rightVariantNumber = newRightVariantNumber;
        }
    }

    void setScores(int newScores) {
        if (newScores >= 0) {
            scores = newScores;
        }
    }

    bool checkAnswer(int userAnswer) const override {
        return userAnswer == rightVariantNumber;
    }

    void displayQuestion() const override {
        cout << "\n=== " << typeName << " вопрос ===" << endl;
        cout << "Вопрос: " << questionText << endl;
        cout << "Варианты ответов:" << endl;
        for (int i = 0; i < variantsCount; i++) {
            cout << (i + 1) << ". " << variants[i] << endl;
        }
        cout << "Баллы за вопрос: " << scores << endl;
    }
};

class Result : public Answer {
private:
    float result;
    bool passed;

public:
    Result() : result(0), passed(false) {};
    Result(const string& fio, const string& faculty, int groupNum, const string& date,
           const string& testName, float result)
        : Answer(fio, faculty, groupNum, date, testName), result(result), passed(result >= 60.0f) {}

    Result(const Result& copy) : Answer(copy), result(copy.result), passed(copy.passed) {}
    ~Result() override = default;

    float getResult() const { return result; }
    bool getPassed() const { return passed; }

    void setResult(float newResult) {
        result = newResult;
        passed = (result >= 60.0f);
    }

    void display() const {
        cout << left << setw(25) << getFio()
             << setw(15) << getFaculty()
             << setw(8) << getGroupNum()
             << setw(10) << fixed << setprecision(1) << result << "%"
             << setw(10) << (passed ? "Сдал" : "Не сдал") << endl;
    }

    static void displayTableHeader() {
        cout << "+----+---------------------+-------------+--------+----------+--------+" << endl;
        cout << "| №  | ФИО                 | Факультет   | Группа | Результат| Статус |" << endl;
        cout << "+----+---------------------+-------------+--------+----------+--------+" << endl;
    }

    static void displayTableFooter() {
        cout << "+----+---------------------+-------------+--------+----------+--------+" << endl;
    }

    void displayTableRow(int index) const {
        string shortFio = getFio();
        if (shortFio.length() > 19) {
            shortFio = shortFio.substr(0, 16) + "...";
        }

        string shortFaculty = getFaculty();
        if (shortFaculty.length() > 11) {
            shortFaculty = shortFaculty.substr(0, 8) + "...";
        }

        cout << "| " << setw(2) << right << index << " | "
             << setw(19) << left << shortFio << " | "
             << setw(11) << left << shortFaculty << " | "
             << setw(6) << right << getGroupNum() << " | "
             << setw(8) << right << fixed << setprecision(1) << result << "% | "
             << setw(6) << left << (passed ? "Сдал" : "Не сдал") << " |" << endl;
    }

    void saveToFile(ofstream& file, int index) const {
        file << "| " << setw(2) << right << index << " | "
             << setw(19) << left << getFio() << " | "
             << setw(11) << left << getFaculty() << " | "
             << setw(6) << right << getGroupNum() << " | "
             << setw(8) << right << fixed << setprecision(1) << result << "% | "
             << setw(6) << left << (passed ? "Сдал" : "Не сдал") << " |" << endl;
    }
};

class Test {
private:
    static const int MAX_QUESTIONS = 50;
    static const int MAX_ANSWERS = 100;
    static const int MAX_RESULTS = 100;
    static const int MAX_VARIANTS = 10;

    string testName;
    string testTheme;
    IQuestion* questions[MAX_QUESTIONS]{};
    Answer answers[MAX_ANSWERS];
    Result results[MAX_RESULTS];
    int questionCount;
    int answerCount;
    int resultCount;

public:
    Test() : questionCount(0), answerCount(0), resultCount(0) {
        for (int i = 0; i < MAX_QUESTIONS; i++) {
            questions[i] = nullptr;
        }
    }

    Test(string  name, string  theme)
        : testName(std::move(name)), testTheme(std::move(theme)), questionCount(0), answerCount(0), resultCount(0) {
        for (int i = 0; i < MAX_QUESTIONS; i++) {
            questions[i] = nullptr;
        }
    }

    Test(const Test& other)
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

    Test& operator=(const Test& other) {
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

    ~Test() {
        for (int i = 0; i < questionCount; i++) {
            delete questions[i];
        }
    }

    string getTestName() const { return testName; }
    string getTestTheme() const { return testTheme; }
    int getQuestionCount() const { return questionCount; }
    int getAnswerCount() const { return answerCount; }
    int getResultCount() const { return resultCount; }

    void setTestName(const string& name) { testName = name; }
    void setTestTheme(const string& theme) { testTheme = theme; }

    bool addQuestion(IQuestion* question) {
        if (questionCount < MAX_QUESTIONS) {
            questions[questionCount] = question;
            questionCount++;
            return true;
        }
        return false;
    }

    bool addAnswer(const Answer& answer) {
        if (answerCount < MAX_ANSWERS) {
            answers[answerCount] = answer;
            answerCount++;
            return true;
        }
        return false;
    }

    bool addResult(const Result& result) {
        if (resultCount < MAX_RESULTS) {
            results[resultCount] = result;
            resultCount++;
            return true;
        }
        return false;
    }

    void displayTestInfo() const {
        cout << "\n=== ИНФОРМАЦИЯ О ТЕСТЕ ===" << endl;
        cout << "Название: " << testName << endl;
        cout << "Тема: " << testTheme << endl;
        cout << "Количество вопросов: " << questionCount << endl;
        cout << "Количество ответов: " << answerCount << endl;
        cout << "Количество результатов: " << resultCount << endl;
    }

    void showMenu() {
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

private:
    void addTextQuestion() {
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

    void addNumericQuestion() {
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

    void displayAllQuestions() const {
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

    void takeTest() {
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

    void displayResults() const {
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

    void displayResultsTable() const {
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

    void saveResultsToFile() const {
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
};

void mainMenu() {
    static const int MAX_TESTS = 20;
    Test tests[MAX_TESTS];
    int testCount = 0;
    int choice;

    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ СИСТЕМЫ ТЕСТИРОВАНИЯ ===" << endl;
        cout << "1. Создать новый тест" << endl;
        cout << "2. Работать с существующим тестом" << endl;
        cout << "3. Показать все тесты" << endl;
        cout << "0. Выход из программы" << endl;

        choice = getInputInt("Выберите действие: ", 0, 3);

        switch (choice) {
            case 1: {
                if (testCount >= MAX_TESTS) {
                    cout << "Достигнуто максимальное количество тестов!" << endl;
                    break;
                }
                auto name = getInput<string>("Введите название теста: ");
                auto theme = getInput<string>("Введите тему теста: ");
                tests[testCount] = Test(name, theme);
                testCount++;
                cout << "Тест создан!" << endl;
                break;
            }
            case 2: {
                if (testCount == 0) {
                    cout << "Нет созданных тестов!" << endl;
                    break;
                }
                cout << "\nСписок тестов:" << endl;
                for (int i = 0; i < testCount; i++) {
                    cout << (i + 1) << ". " << tests[i].getTestName()
                         << " (" << tests[i].getTestTheme() << ")" << endl;
                }
                int testChoice = getInputInt("Выберите тест: ", 1, testCount) - 1;
                tests[testChoice].showMenu();
                break;
            }
            case 3: {
                if (testCount == 0) {
                    cout << "Нет созданных тестов!" << endl;
                    break;
                }
                cout << "\n=== ВСЕ ТЕСТЫ ===" << endl;
                for (int i = 0; i < testCount; i++) {
                    cout << "\nТест " << (i + 1) << ":" << endl;
                    tests[i].displayTestInfo();
                }
                break;
            }
            case 0: cout << "Выход из программы..." << endl; break;
        }
    } while (choice != 0);
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "=== СИСТЕМА ТЕСТИРОВАНИЯ ===" << endl;
    mainMenu();

    return 0;
}