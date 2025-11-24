#include<iostream>
#include<windows.h>
#include<string>
#include<iomanip>

using namespace std;

// Вспомогательная функция для ввода
template<typename T>
T getInput(const string& prompt) {
    cout << prompt;
    T value;
    if constexpr (std::is_same_v<T, string>) {
        getline(cin, value);
    } else {
        cin >> value;
        cin.ignore();
    }
    return value;
}

class User {
protected:
    string fio;
    string faculty;
    int groupNum;
public:
    User() : groupNum(0) {};
    User(string fio, string faculty, int groupNum) : fio(fio), faculty(faculty), groupNum(groupNum) {};
    User(const User& copy) : fio(copy.fio), faculty(copy.faculty), groupNum(copy.groupNum) {}
    virtual ~User() {}

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
        if (newGroupNum > 0 && newGroupNum < 1000) {
            groupNum = newGroupNum;
        }
    }
};

class Answer : public User {
protected:
    string date;
    string testName;
public:
    Answer() : date(""), testName("") {};
    Answer(const string& fio, const string& faculty, int groupNum, const string& date, const string& testName)
        : User(fio, faculty, groupNum), date(date), testName(testName) {};
    Answer(const Answer& copy) : User(copy), date(copy.date), testName(copy.testName) {};
    virtual ~Answer() {}

    string getDate() const { return date; }
    string getTestName() const { return testName; }

    void setDate(const string& newDate) { date = newDate; }
    void setTestName(const string& newTestName) { testName = newTestName; }
};

// Базовый класс для вопросов
class IQuestion {
public:
    virtual ~IQuestion() = default;
    virtual void displayQuestion() const = 0;
    virtual bool checkAnswer(int userAnswer) const = 0;
    virtual int getScores() const = 0;
    virtual string getType() const = 0;
    virtual string getQuestionText() const = 0;
};

// Шаблонный класс вопросов
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

    Question(const TQuestion& questionText, const TVariants* variantsArray, int varCount,
             int rightVariant, int scores, const string& type)
        : questionText(questionText), variantsCount(varCount),
          rightVariantNumber(rightVariant), scores(scores), typeName(type) {
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

    virtual ~Question() {}

    string getQuestionText() const override { return questionText; }
    int getVariantsCount() const { return variantsCount; }
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
    ~Result() {}

    float getResult() const { return result; }
    bool getPassed() const { return passed; }

    void setResult(float newResult) {
        result = newResult;
        passed = (result >= 60.0f);
    }

    void display() const {
        // Используем публичные геттеры вместо прямого доступа к protected полям
        cout << left << setw(25) << getFio()
             << setw(15) << getFaculty()
             << setw(8) << getGroupNum()
             << setw(10) << fixed << setprecision(1) << result << "%"
             << setw(10) << (passed ? "Сдал" : "Не сдал") << endl;
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
    IQuestion* questions[MAX_QUESTIONS];
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

    Test(const string& name, const string& theme)
        : testName(name), testTheme(theme), questionCount(0), answerCount(0), resultCount(0) {
        for (int i = 0; i < MAX_QUESTIONS; i++) {
            questions[i] = nullptr;
        }
    }

    // Конструктор копирования
    Test(const Test& other)
        : testName(other.testName), testTheme(other.testTheme),
          questionCount(other.questionCount), answerCount(other.answerCount), resultCount(other.resultCount) {
        for (int i = 0; i < MAX_QUESTIONS; i++) {
            questions[i] = nullptr;
        }
        for (int i = 0; i < questionCount; i++) {
            // Здесь нужно реализовать глубокое копирование вопросов
            // Для простоты оставляем как есть
            questions[i] = other.questions[i];
        }
        for (int i = 0; i < answerCount; i++) {
            answers[i] = other.answers[i];
        }
        for (int i = 0; i < resultCount; i++) {
            results[i] = other.results[i];
        }
    }

    // Оператор присваивания
    Test& operator=(const Test& other) {
        if (this != &other) {
            // Освобождаем старую память
            for (int i = 0; i < questionCount; i++) {
                delete questions[i];
            }

            testName = other.testName;
            testTheme = other.testTheme;
            questionCount = other.questionCount;
            answerCount = other.answerCount;
            resultCount = other.resultCount;

            for (int i = 0; i < questionCount; i++) {
                // Здесь нужно реализовать глубокое копирование вопросов
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

    // Меню работы с тестом
    void showMenu() {
        int choice;
        do {
            cout << "\n=== МЕНЮ ТЕСТА: " << testName << " ===" << endl;
            cout << "1. Добавить текстовый вопрос" << endl;
            cout << "2. Добавить числовой вопрос" << endl;
            cout << "3. Добавить вопрос с выбором из списка" << endl;
            cout << "4. Показать все вопросы" << endl;
            cout << "5. Пройти тест" << endl;
            cout << "6. Показать результаты" << endl;
            cout << "7. Информация о тесте" << endl;
            cout << "0. Выход в главное меню" << endl;
            cout << "Выберите действие: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: addTextQuestion(); break;
                case 2: addNumericQuestion(); break;
                case 3: addListQuestion(); break;
                case 4: displayAllQuestions(); break;
                case 5: takeTest(); break;
                case 6: displayResults(); break;
                case 7: displayTestInfo(); break;
                case 0: cout << "Выход..." << endl; break;
                default: cout << "Неверный выбор!" << endl;
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

        string questionText = getInput<string>("Введите текст вопроса: ");

        string variants[MAX_VARIANTS];
        int variantsCount = 4;

        cout << "Введите 4 варианта ответов:" << endl;
        for (int i = 0; i < variantsCount; i++) {
            variants[i] = getInput<string>("Вариант " + to_string(i+1) + ": ");
        }

        int rightAnswer = getInput<int>("Номер правильного ответа (1-4): ") - 1;
        int scores = getInput<int>("Баллы за вопрос: ");

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

        string questionText = getInput<string>("Введите текст вопроса: ");

        int variants[MAX_VARIANTS];
        int variantsCount = 4;

        cout << "Введите 4 числовых варианта ответов:" << endl;
        for (int i = 0; i < variantsCount; i++) {
            variants[i] = getInput<int>("Вариант " + to_string(i+1) + ": ");
        }

        int rightAnswer = getInput<int>("Номер правильного ответа (1-4): ") - 1;
        int scores = getInput<int>("Баллы за вопрос: ");

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

    void addListQuestion() {
        if (questionCount >= MAX_QUESTIONS) {
            cout << "Достигнуто максимальное количество вопросов!" << endl;
            return;
        }

        cout << "\n--- Вопрос со списком ---" << endl;

        string questionText = getInput<string>("Введите текст вопроса: ");

        string variants[MAX_VARIANTS];
        int variantsCount = getInput<int>("Количество вариантов ответов: ");
        if (variantsCount > MAX_VARIANTS) {
            variantsCount = MAX_VARIANTS;
            cout << "Установлено максимальное количество вариантов: " << MAX_VARIANTS << endl;
        }

        for (int i = 0; i < variantsCount; i++) {
            variants[i] = getInput<string>("Вариант " + to_string(i+1) + ": ");
        }

        int rightAnswer = getInput<int>("Номер правильного ответа (1-" + to_string(variantsCount) + "): ") - 1;
        int scores = getInput<int>("Баллы за вопрос: ");

        IQuestion* question = new Question<string, string>(
            questionText, variants, variantsCount, rightAnswer, scores, "Список"
        );

        if (addQuestion(question)) {
            cout << "Вопрос со списком добавлен!" << endl;
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

        // Регистрация пользователя
        string fio = getInput<string>("Введите ваше ФИО: ");
        string faculty = getInput<string>("Введите факультет: ");
        int groupNum = getInput<int>("Введите номер группы: ");
        string date = getInput<string>("Введите дату (гггг-мм-дд): ");

        Answer answer(fio, faculty, groupNum, date, testName);
        addAnswer(answer);

        int userAnswers[MAX_QUESTIONS];
        int totalScore = 0;
        int maxScore = 0;

        for (int i = 0; i < questionCount; i++) {
            cout << "\n--- Вопрос " << (i + 1) << " ---" << endl;
            questions[i]->displayQuestion();

            int userAnswer = getInput<int>("Ваш ответ (номер варианта): ") - 1;
            userAnswers[i] = userAnswer;

            if (questions[i]->checkAnswer(userAnswer)) {
                cout << "✓ Правильно! +" << questions[i]->getScores() << " баллов" << endl;
                totalScore += questions[i]->getScores();
            } else {
                cout << "✗ Неправильно!" << endl;
            }

            maxScore += questions[i]->getScores();
        }

        // Расчет и сохранение результата
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


};

// Главное меню программы
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
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                if (testCount >= MAX_TESTS) {
                    cout << "Достигнуто максимальное количество тестов!" << endl;
                    break;
                }
                string name = getInput<string>("Введите название теста: ");
                string theme = getInput<string>("Введите тему теста: ");
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
                int testChoice = getInput<int>("Выберите тест: ") - 1;
                if (testChoice >= 0 && testChoice < testCount) {
                    tests[testChoice].showMenu();
                } else {
                    cout << "Неверный выбор!" << endl;
                }
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
            default: cout << "Неверный выбор!" << endl;
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