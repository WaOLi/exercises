#define DEBUG
#ifdef DEBUG

#include <iostream>
#include <vector>
#include <random>

/*
    ==============================
     УСЛОВИЕ:
    ==============================
    SecureBox состоит из матрицы булевых значений.
    SecureBox считается открытым, если все значения в матрице равны false.
    SecureBox можно проверить на открытость/закрытость путем вызова функции
    isLocked(). Если SecureBox открыт - функция isLocked вернет false.
    Изменять значения в матрице по координатам можно функцией flip(x,y).
    При изменении одного значения в матрице, некоторым образом изменяются и соседние значения.

    ==============================
     ЗАДАЧА:
    ==============================
    1. Реализовать функцию

    bool OpenBox(SecureBox& box)
    {
        // ....
        return box.isLocked();
    }

    которая путем вызова определенной последовательности box.flip() c некоторыми x,y откроет SecureBox.
    Изменять код класса SecureBox запрещено.
    Функция OpenBox должна работать для SecureBox любой размерности до 100x100 включительно.
    Кроме основного решения допускается любой рабочий "грязный хак" и "взлом" SecureBox.

    2. Предложить свои улучшения SecureBox и выявить потенциально-проблемные места в коде.
*/

class SecureBox
{
public:
    bool isLocked()
    {
        bool locked = false;
        for (uint32_t x = 0; x < m_xSize; x++) {
            for (uint32_t y = 0; y < m_ySize; y++) {
                locked = locked || m_LockSwitchers[x][y];
            }
        }
        return locked;
    }

    bool flip(uint32_t x, uint32_t y)
    {
        if (x >= m_xSize || y >= m_ySize)
            return false;
        for (uint32_t tx = 0; tx < m_xSize; tx++)
            m_LockSwitchers[tx][y] = !m_LockSwitchers[tx][y];
        for (uint32_t ty = 0; ty < m_ySize; ty++)
            m_LockSwitchers[x][ty] = !m_LockSwitchers[x][ty];
        m_LockSwitchers[x][y] = !m_LockSwitchers[x][y];
        return true;
    }

    void lock()
    {
        const uint32_t minNumOfIters = 10;
        const uint32_t addNumOfIters = 1000;

        for (uint32_t iter = minNumOfIters + (rnd() % addNumOfIters); iter != 0; iter--)
            flip(rnd() % m_xSize, rnd() % m_ySize);
    }

    std::vector<std::vector<bool>> getState() {
        return m_LockSwitchers;
    }

    std::pair<uint32_t, uint32_t> getSize() {
        return std::make_pair(m_xSize, m_ySize);
    }

    SecureBox(uint32_t x, uint32_t y) : m_xSize(x), m_ySize(y), rnd(time(0))
    {
        m_LockSwitchers.resize(x);
        for (uint32_t i = 0; i < x; i++)
            m_LockSwitchers[i].resize(y);
        lock();
    }

private:
    std::mt19937_64 rnd;
    std::vector<std::vector<bool>> m_LockSwitchers;
    uint32_t m_xSize, m_ySize;
};

// Задание 1:

std::ostream& operator<<(std::ostream& os, SecureBox& box)
{
    int sizeX = box.getSize().first;
    int sizeY = box.getSize().second;

    for (int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++)
        {
            os << std::noboolalpha <<box.getState()[i][j] << "   ";
        }
        os << "\n\n";
    }
    os << "-----------------------------------------------\n";
    return os;
}

bool OpenBox(SecureBox& box)
{
    int sizeX = box.getSize().first;
    int sizeY = box.getSize().second;
    std::vector<std::vector<bool>> t_box = box.getState();
    while(box.isLocked())
    {
        for (int i = 0; i < sizeX; i++)
        {
            for (int j = 0; j < sizeY; j++)
            {
                if (t_box[i][j] == true)
                {
                    box.flip(i, j);
                }
            }
        }
        t_box = box.getState();
    }
    return box.isLocked();
}


int main()
{
    unsigned int vX = 8, vY = 8;
    std::cin >> vX >> vY;
    SecureBox sb(vX,vY);
    std::cout << sb;
    OpenBox(sb);
    std::cout << sb;
}
#endif


/* Задание 2:
  1)
  Метод isLocked() класса SecureBox не перестает рассматривать элементы встретившись с элементом true, а это излишне
  вместо этой строки:
                        locked = locked || m_LockSwitchers[x][y];
  лучше поместить что-то в роде этого :
                        if(m_LockSwitchers[x][y]) return true;

  и вместо команды (что после циклов):
                        return locked;
  просто положить:
                        return false;
  таким образом метод isLocked() можно сделать гораздо эффективнее!
  
  2)
  Метод lock() за счет условной рандомизации пересечений (х,у) для которых вызывается flip(x,y) не гарантирует что 
  наш box будет содержать хоть один элемент true. По этому можно к примеру добавить в конце метода проверку и
  в случае isLocked() == true рекурсивно вызвать lock() т.е. в конце метода lock() можно добавить:
                        if(!box.isLocked()) lock();
*/