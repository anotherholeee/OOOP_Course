#include "utils.h"
#include <ctime>

string getCurrentDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    return string(buffer);
}

int getInputInt(const string& prompt, int minVal, int maxVal) {
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