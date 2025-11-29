#ifndef QUESTION_H
#define QUESTION_H

#include "iquestion.h"
#include <string>
using namespace std;

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
    Question();
    Question(TQuestion questionText, const TVariants* variantsArray, int varCount,
             int rightVariant, int scores, string type);
    Question(const Question& copy);
    ~Question() override;

    string getQuestionText() const override;
    int getVariantsCount() const override;
    TVariants getVariant(int index) const;
    int getRightVariantNumber() const;
    int getScores() const override;
    string getType() const override;

    void setQuestionText(const TQuestion& newQuestionText);
    void setVariants(const TVariants* newVariants, int count);
    void setRightVariantNumber(int newRightVariantNumber);
    void setScores(int newScores);

    bool checkAnswer(int userAnswer) const override;
    void displayQuestion() const override;
};

// Реализация шаблонного класса должна быть в заголовочном файле
template<class TQuestion, class TVariants>
Question<TQuestion, TVariants>::Question() 
    : variantsCount(0), rightVariantNumber(0), scores(0) {}

template<class TQuestion, class TVariants>
Question<TQuestion, TVariants>::Question(TQuestion questionText, const TVariants* variantsArray, int varCount,
         int rightVariant, int scores, string type)
    : questionText(std::move(questionText)), variantsCount(varCount),
      rightVariantNumber(rightVariant), scores(scores), typeName(std::move(type)) {
    for (int i = 0; i < varCount && i < MAX_VARIANTS; i++) {
        variants[i] = variantsArray[i];
    }
}

template<class TQuestion, class TVariants>
Question<TQuestion, TVariants>::Question(const Question& copy)
    : questionText(copy.questionText), variantsCount(copy.variantsCount),
      rightVariantNumber(copy.rightVariantNumber), scores(copy.scores), typeName(copy.typeName) {
    for (int i = 0; i < variantsCount; i++) {
        variants[i] = copy.variants[i];
    }
}

template<class TQuestion, class TVariants>
Question<TQuestion, TVariants>::~Question() {}

template<class TQuestion, class TVariants>
string Question<TQuestion, TVariants>::getQuestionText() const { 
    return questionText; 
}

template<class TQuestion, class TVariants>
int Question<TQuestion, TVariants>::getVariantsCount() const { 
    return variantsCount; 
}

template<class TQuestion, class TVariants>
TVariants Question<TQuestion, TVariants>::getVariant(int index) const {
    if (index >= 0 && index < variantsCount) return variants[index];
    return TVariants();
}

template<class TQuestion, class TVariants>
int Question<TQuestion, TVariants>::getRightVariantNumber() const { 
    return rightVariantNumber; 
}

template<class TQuestion, class TVariants>
int Question<TQuestion, TVariants>::getScores() const { 
    return scores; 
}

template<class TQuestion, class TVariants>
string Question<TQuestion, TVariants>::getType() const { 
    return typeName; 
}

template<class TQuestion, class TVariants>
void Question<TQuestion, TVariants>::setQuestionText(const TQuestion& newQuestionText) {
    questionText = newQuestionText;
}

template<class TQuestion, class TVariants>
void Question<TQuestion, TVariants>::setVariants(const TVariants* newVariants, int count) {
    variantsCount = (count > MAX_VARIANTS) ? MAX_VARIANTS : count;
    for (int i = 0; i < variantsCount; i++) {
        variants[i] = newVariants[i];
    }
}

template<class TQuestion, class TVariants>
void Question<TQuestion, TVariants>::setRightVariantNumber(int newRightVariantNumber) {
    if (newRightVariantNumber >= 0 && newRightVariantNumber < variantsCount) {
        rightVariantNumber = newRightVariantNumber;
    }
}

template<class TQuestion, class TVariants>
void Question<TQuestion, TVariants>::setScores(int newScores) {
    if (newScores >= 0) {
        scores = newScores;
    }
}

template<class TQuestion, class TVariants>
bool Question<TQuestion, TVariants>::checkAnswer(int userAnswer) const {
    return userAnswer == rightVariantNumber;
}

template<class TQuestion, class TVariants>
void Question<TQuestion, TVariants>::displayQuestion() const {
    cout << "\n=== " << typeName << " вопрос ===" << endl;
    cout << "Вопрос: " << questionText << endl;
    cout << "Варианты ответов:" << endl;
    for (int i = 0; i < variantsCount; i++) {
        cout << (i + 1) << ". " << variants[i] << endl;
    }
    cout << "Баллы за вопрос: " << scores << endl;
}

#endif