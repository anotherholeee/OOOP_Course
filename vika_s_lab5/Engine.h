#ifndef ENGINE_H
#define ENGINE_H



class Engine {
private:
    int power;
public:
    explicit Engine(int pwr = 100);
    void start() const;
    virtual void inputInfo();
    int getPower() const;
    virtual ~Engine() = default;
};

#endif