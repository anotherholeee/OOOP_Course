#include "question.h"
#include <iostream>

template<class TQuestion, class TVariants>
Question<TQuestion, TVariants>::Question() 
    : variantsCount(0), rightVariantNumber(0), scores(0) {}

template<class TQuestion, class TVariants>
Question<TQuestion, TVariants>::Question(TQuestion questionText, const TVariants* variantsArray, int varCount,
         int rightVariant, int scores, std::string type)
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
std::string Question<TQuestion, TVariants>::getQuestionText() const { 
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
std::string Question<TQuestion, TVariants>::getType() const { 
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
    std::cout << "\n=== " << typeName << " вопрос ===" << std::endl;
    std::cout << "Вопрос: " << questionText << std::endl;
    std::cout << "Варианты ответов:" << std::endl;
    for (int i = 0; i < variantsCount; i++) {
        std::cout << (i + 1) << ". " << variants[i] << std::endl;
    }
    std::cout << "Баллы за вопрос: " << scores << std::endl;
}

// Явные инстанцирования
template class Question<std::string, std::string>;
template class Question<std::string, int>;