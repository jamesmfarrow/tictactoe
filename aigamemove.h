#ifndef AIGAMEMOVE_H
#define AIGAMEMOVE_H


class AIGameMove
{
private:
    int m_x{};
    int m_y{};

public:
    //score public for easy access
    int score;

    //default constructor
    AIGameMove() { }

    //constructor
    AIGameMove(int x,int y) : m_x(x), m_y(y){ }

    void setX(int x) { m_x = x; }
    void setY(int y) { m_y = y; }
    int getX() { return m_x; }
    int getY() { return m_y; }
    void setScore(int val) { score = val; }
    int getScore();

    //equality operator overload
    bool operator==(const AIGameMove& obj)
    {
        return (this->m_x == obj.m_x && this->m_y == obj.m_y);
    }

};

#endif // AIGAMEMOVE_H
