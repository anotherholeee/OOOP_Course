#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <memory>

class IQuestion {
public:
    virtual ~IQuestion() = default;
    virtual void displayQuestion() const = 0;
    virtual bool checkAnswer(int userAnswer) const = 0;
    virtual int getScores() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getQuestionText() const = 0;
    virtual int getVariantsCount() const = 0;
    virtual std::unique_ptr<IQuestion> clone() const = 0;
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
    std::string typeName;

public:
    Question();
    Question(TQuestion questionText, const TVariants* variantsArray, int varCount,
             int rightVariant, int scores, std::string type);
    Question(const Question& copy);
    ~Question() override = default;

    std::string getQuestionText() const override;
    int getVariantsCount() const override;
    TVariants getVariant(int index) const;
    int getRightVariantNumber() const;
    int getScores() const override;
    std::string getType() const override;

    std::unique_ptr<IQuestion> clone() const override;

    void setQuestionText(const TQuestion& newQuestionText);
    void setVariants(const TVariants* newVariants, int count);
    void setRightVariantNumber(int newRightVariantNumber);
    void setScores(int newScores);

    bool checkAnswer(int userAnswer) const override;
    void displayQuestion() const override;
};

#endif