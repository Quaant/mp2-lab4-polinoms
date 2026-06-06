#pragma once

#include "list.h"
using namespace std;

class polinom : private Tlist<monom>
{
public:
    using Tlist<monom>::operator=;
    polinom() : Tlist<monom>() {};
    polinom(const polinom &a) : Tlist<monom>(a) {};
    ~polinom() {};

    // Явно объявляем методы доступа к базовому классу
    using Tlist<monom>::sizee;

    // Добавляем const версию operator[]
    const monom &operator[](size_t index) const
    {
        return Tlist<monom>::operator[](index);
    }

    // Не-const версия operator[]
    monom &operator[](size_t index)
    {
        return Tlist<monom>::operator[](index);
    }

    polinom(const string &s) : Tlist<monom>()
    {
        string str = s;
        str.erase(remove(str.begin(), str.end(), ' '), str.end());

        if (!str.empty() && str[0] != '+' && str[0] != '-')
            str = "+" + str;

        size_t pos = 0;
        while (pos < str.length())
        {
            size_t next_pos = str.find_first_of("+-", pos + 1);
            if (next_pos == string::npos)
                next_pos = str.length();

            string monom_str = str.substr(pos, next_pos - pos);

            if (!monom_str.empty())
            {
                try
                {
                    monom m(monom_str);
                    addMonom(m);
                }
                catch (const exception &e)
                {
                    cerr << "Ошибка при парсинге монома \"" << monom_str
                         << "\": " << e.what() << endl;
                }
            }
            pos = next_pos;
        }
    }

    void addMonom(monom m)
    {
        if (m.getCoef() == 0)
            return;

        *this = ::add(*this, m);
    }

    polinom &operator=(const polinom &p)
    {
        Tlist<monom>::operator=(p);
        return *this;
    }

    polinom operator+(const polinom &p) const
    {
        polinom res = *this;
        size_t sz_p = p.sizee();
        for (size_t i = 0; i < sz_p; i++)
        {
            res = ::add(res, p[i]); // Теперь p[i] работает, так как есть const operator[]
        }
        return res;
    }

    polinom operator-() const
    {
        polinom result;
        for (size_t i = 0; i < sizee(); i++)
        {
            const monom &m = (*this)[i]; // Используем const версию
            result = ::add(result, monom(-m.getCoef(), m.getPow()));
        }
        return result;
    }

    polinom operator-(const polinom &other) const
    {
        polinom result = *this;
        for (size_t i = 0; i < other.sizee(); i++)
        {
            const monom &m = other[i]; // Используем const версию
            monom neg_m(-m.getCoef(), m.getPow());
            result = ::add(result, neg_m);
        }
        return result;
    }

    polinom operator*(const polinom &other) const
    {
        polinom result;
        for (size_t i = 0; i < sizee(); i++)
        {
            for (size_t j = 0; j < other.sizee(); j++)
            {
                const monom &m1 = (*this)[i];
                const monom &m2 = other[j];
                double newCoef = m1.getCoef() * m2.getCoef();
                int pow1 = m1.getPow();
                int pow2 = m2.getPow();
                int x_pow = (pow1 / 100) + (pow2 / 100);
                int y_pow = ((pow1 % 100) / 10) + ((pow2 % 100) / 10);
                int z_pow = (pow1 % 10) + (pow2 % 10);

                if (x_pow > 9 || y_pow > 9 || z_pow > 9)
                {
                    throw runtime_error("Степень превышает допустимое значение 9");
                }

                int newPow = x_pow * 100 + y_pow * 10 + z_pow;
                result = ::add(result, monom(newCoef, newPow));
            }
        }
        return result;
    }

    polinom &operator*=(const polinom &other)
    {
        *this = *this * other;
        return *this;
    }

    bool operator==(const polinom &other) const
    {
        if (sizee() != other.sizee())
        {
            return false;
        }
        for (size_t i = 0; i < sizee(); i++)
        {
            if (!((*this)[i] == other[i]))
            {
                return false;
            }
        }
        return true;
    }

    polinom operator+(double coef) const
    {
        polinom result = *this;
        result.addMonom(monom(coef, 0));
        return result;
    };

    friend ostream &operator<<(ostream &out, const polinom &a)
    {
        if (a.sizee() == 0)
        {
            out << "0";
            return out;
        }

        for (size_t i = 0; i < a.sizee(); i++)
        {
            const monom &m = a[i]; // Используем const версию
            out << m;
        }
        return out;
    }
};