#pragma once

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class monom
{
protected:
    double coef;
    int pow;

public:
    monom()
    {
        coef = 0;
        pow = 0;
    };
    monom(const string &str)
    {
        string s = str;

        if (str[0] == '+')
        {
            s = str.substr(1, size(str));
        }

        coef = 1;
        pow = 0;
        int ind = -1;
        string buffer_coef = "";
        string x = "0";
        string y = "0";
        string z = "0";

        for (int i = 0; i < size(s); i++)
        {
            if (s[i] == 'x' || s[i] == 'y' || s[i] == 'z')
            {
                ind = i;
                break;
            }
        }
        if (ind == -1)
        {
            pow = 0;
            coef = stod(s);
        }
        else
        {

            for (int i = 0; i < ind; i++)
            {
                buffer_coef += s[i];
                // cout << "!!!" << s[i] << "!!!" << ' ';
            }
            coef = stod(buffer_coef);
            for (int i = ind; i < size(s); i++)
            {
                if (s[i] == 'x')
                {
                    x = s[i + 1];
                }
                if (s[i] == 'y')
                {
                    y = s[i + 1];
                }
                if (s[i] == 'z')
                {
                    z = s[i + 1];
                }
            }
            string buffer_pow = "";
            if (!x.empty() || x != "0")
            {
                buffer_pow += x;
            }
            if (!y.empty() || y != "0")
            {
                buffer_pow += y;
            }
            else if (y == "0")
            {
                buffer_pow += "0";
            }
            if (!z.empty() || z != "0")
            {
                buffer_pow += z;
            }
            else if (z == "0")
            {
                buffer_pow += "0";
            }
            pow = stod(buffer_pow);
        }
    }
    monom(double c, int p)
    {
        if (p > 999)
        {
            throw("pow can be only < 1000");
        }
        coef = c;
        pow = p;
    };
    monom(const monom &a)
    {
        coef = a.coef;
        pow = a.pow;
    };
    monom(monom &&a) noexcept
    {
        coef = 0;
        pow = 0;
        coef = a.coef;
        pow = a.pow;
        a.coef = 0;
        a.pow = 0;
    }
    ~monom() {};
    bool operator<(const monom &a)
    {
        if (pow < a.pow)
        {
            return true;
        }
        return false;
    }
    bool operator>(const monom &a)
    {
        return (!(*this < a));
    };
    double getCoef() const
    {
        return coef;
    };
    int getPow() const
    {
        return pow;
    };
    int getX() const
    {
        return pow / 100;
    };
    int getY() const
    {
        return (pow % 100) / 10;
    }
    int getZ() const
    {
        return (pow % 10);
    }
    void SetCoef(double c)
    {
        coef = c;
    }
    void SetPow(int p)
    {
        pow = p;
    }
    bool operator==(const monom &a) const
    {
        if (pow == a.pow && coef == a.coef)
        {
            return true;
        }
        return false;
    };
    monom &operator=(const monom &a)
    {
        coef = a.coef;
        pow = a.pow;
        return *this;
    }
    monom operator+(const monom &a)
    {
        if (pow != a.pow)
        {
            throw("U cant make this");
        };
        coef += a.coef;
        return *this;
    }
    monom operator-(const monom &a)
    {
        if (pow != a.pow)
        {
            throw("U cant make this");
        };
        coef -= a.coef;
        return *this;
    }
    monom operator*(const double c)
    {
        coef *= c;
        return *this;
    }
    monom operator*(const monom &a)
    {
        coef *= a.coef;
        if ((a.getX() + getX()) <= 9 && (a.getY() + getY()) <= 9 && (a.getZ() + getZ()) <= 9)
        {
            pow += a.pow;
        }
        pow += a.pow;
        return *this;
    }
    friend istream &operator>>(istream &in, monom &m)
    {
        in >> m.coef >> m.pow;
        return in;
    };
    friend ostream &operator<<(ostream &out, const monom &m)
    {
        double coef = m.getCoef();
        int pow = m.getPow();

        // Коэффициент
        if (coef == 1.0)
        {
            // Ничего не выводим для 1, кроме случаев, когда степень = 0
            if (pow == 0)
            {
                out << "1";
            }
        }
        else if (coef == -1.0)
        {
            // Только минус для -1, кроме случаев, когда степень = 0
            if (pow == 0)
            {
                out << "-1";
            }
            else
            {
                out << "-";
            }
        }
        else
        {
            out << coef;
        }

        // Степени переменных
        if (pow > 0)
        {
            int x_pow = pow / 100;
            int y_pow = (pow % 100) / 10;
            int z_pow = pow % 10;

            if (x_pow > 0)
            {
                out << "x";
                if (x_pow > 1)
                    out << "^" << x_pow;
            }
            if (y_pow > 0)
            {
                out << "y";
                if (y_pow > 1)
                    out << "^" << y_pow;
            }
            if (z_pow > 0)
            {
                out << "z";
                if (z_pow > 1)
                    out << "^" << z_pow;
            }
        }

        return out;
    }
};
