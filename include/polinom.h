#pragma once

#include "monom.h"
#include "list.h"
using namespace std;

class polinom : private Tlist<monom>
{
private:
    Tlist<monom> lst;

public:
    using Tlist<monom>::operator=;
    polinom() : Tlist<monom>() {};
    polinom(const polinom &a) : Tlist<monom>(a) {};
    ~polinom() {};
    polinom(const string &s)
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

        *this = add(*this, m);
    }

    size_t sizee() const noexcept
    {
        return Tlist<monom>::sizee();
    }

    using Tlist<monom>::operator[];

    polinom &operator=(polinom &p)
    {
        static_cast<Tlist<monom> &>(*this) = static_cast<const Tlist<monom> &>(p);
        return *this;
    }

    polinom operator+(polinom &p)
    {
        polinom res = *this;
        size_t sz_p = p.sizee();
        for (size_t i = 0; i < sz_p; i++)
        {
            res = add(res, p[i]);
        }
        return res;
    }
    polinom operator-()
    {
        polinom result;
        for (size_t i = 0; i < sizee(); i++)
        {
            monom m = (*this)[i];
            result = add(result, monom(-m.getCoef(), m.getPow()));
        }
        return result;
    }
    polinom operator-(polinom &other)
    {
        polinom result = *this;

        for (size_t i = 0; i < other.sizee(); i++)
        {
            monom m = other[i];
            m.SetCoef(-m.getCoef());
            result = ::add(result, m);
        }

        return result;
    }
    polinom operator*(polinom other)
    {
        polinom result;

        for (size_t i = 0; i < sizee(); i++)
        {
            for (size_t j = 0; j < other.sizee(); j++)
            {
                monom m1 = (*this)[i];
                monom m2 = other[j];

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

    polinom operator+(double coef)
    {
        monom a(coef, 0);
        addMonom(a);
        return *this;
    };

    friend ostream &operator<<(ostream &out, polinom a)
    {
        out << static_cast<Tlist<monom> &>(a);
        return out;
    }
};
