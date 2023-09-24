#ifndef COIN_H
#define COIN_H
class Coin
{
private:
    char _result;
    static constexpr char HEAD = 'H';
    static constexpr char TAIL = 'T';

public:
    Coin();
    char GetResult();
    bool Toss();
    bool WinOrLose(char userChoice);
};
#endif // COIN_H