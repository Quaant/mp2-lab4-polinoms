#pragma once

#include <iostream>
#include <vector>
#include "monom.h"
using namespace std;

template <typename T>
class Tlist
{
    struct TNode
    {
        TNode *pNext;
        T data;
        TNode(const T &val, TNode *next = nullptr)
            : data(val), pNext(next)
        {
        }
        TNode(TNode *next = nullptr) : data(T()), pNext(next) {}
    };
    TNode *pFirst;
    size_t sz;

public:
    Tlist() : pFirst(nullptr), sz(0) {}
    Tlist(const vector<T> &v) : pFirst(nullptr), sz(0)
    {
        if (v.size() <= 0)
        {
            throw runtime_error("size of vector is low");
        }
        pFirst = new TNode(v[0]);
        sz = v.size();
        TNode *tmp = pFirst;
        for (size_t i = 1; i < v.size(); i++)
        {
            tmp->pNext = new TNode(v[i]);
            tmp = tmp->pNext;
        }
    };

    Tlist(const Tlist &l) : pFirst(nullptr), sz(0)
    {
        if (l.sz <= 0)
        {
            return;
        }
        pFirst = new TNode(l.pFirst->data);
        sz = 1;
        TNode *a = pFirst;
        TNode *b = l.pFirst->pNext;
        while (b != nullptr)
        {
            a->pNext = new TNode(b->data);
            a = a->pNext;
            b = b->pNext;
            sz++;
        }
    };

    Tlist(Tlist &&l) noexcept : pFirst(l.pFirst), sz(l.sz)
    {
        l.pFirst = nullptr;
        l.sz = 0;
    };

    Tlist &operator=(const Tlist &l)
    {
        if (this == &l)
            return *this;

        while (pFirst != nullptr)
        {
            TNode *tmp = pFirst;
            pFirst = pFirst->pNext;
            delete tmp;
        }
        sz = 0;

        if (l.sz <= 0 || l.pFirst == nullptr)
        {
            pFirst = nullptr;
            return *this;
        }

        pFirst = new TNode(l.pFirst->data);
        sz = 1;
        TNode *ths = pFirst;
        TNode *lst = l.pFirst->pNext;

        while (lst != nullptr)
        {
            ths->pNext = new TNode(lst->data);
            ths = ths->pNext;
            lst = lst->pNext;
            sz++;
        }
        return *this;
    };

    ~Tlist()
    {
        while (pFirst != nullptr)
        {
            TNode *tmp = pFirst;
            pFirst = pFirst->pNext;
            delete tmp;
        }
    }

    size_t sizee() const noexcept
    {
        return sz;
    };

    bool isEmpty() const noexcept
    {
        return sz == 0;
    };

    T &Front()
    {
        if (pFirst == nullptr)
            throw runtime_error("List is empty");
        return pFirst->data;
    };

    void pushFront(const T &val)
    {
        TNode *tmp = new TNode(val, pFirst);
        pFirst = tmp;
        sz++;
    };

    void popFront()
    {
        if (pFirst != nullptr)
        {
            TNode *tmp = pFirst;
            pFirst = pFirst->pNext;
            delete tmp;
            sz--;
        }
    };

    T &operator[](size_t pos)
    {
        TNode *tmp = pFirst;
        for (size_t i = 0; i < pos && tmp != nullptr; i++)
        {
            tmp = tmp->pNext;
        }
        if (tmp == nullptr)
            throw out_of_range("Index out of range");
        return tmp->data;
    };

    void PushAfter(size_t pos, const T &val)
    {
        TNode *tmp = new TNode(val);
        TNode *a = pFirst;
        for (size_t i = 0; i < pos && a != nullptr; i++)
        {
            a = a->pNext;
        }
        if (a == nullptr)
            throw out_of_range("Index out of range");
        TNode *b = a->pNext;
        a->pNext = tmp;
        tmp->pNext = b;
        sz++;
    };

    void EraseAfter(size_t pos)
    {
        if (pFirst == nullptr || pFirst->pNext == nullptr)
            throw runtime_error("Cannot erase from empty list");

        TNode *prev = pFirst;
        for (size_t i = 0; i < pos && prev != nullptr; i++)
        {
            prev = prev->pNext;
        }
        if (prev == nullptr || prev->pNext == nullptr)
            throw out_of_range("Index out of range");

        TNode *tmp = prev->pNext;
        prev->pNext = tmp->pNext;
        delete tmp;
        sz--;
    };

    friend Tlist<monom> add(Tlist<monom> l, monom a);

    friend ostream &operator<<(ostream &out, Tlist<monom> &l);
};

Tlist<monom> add(Tlist<monom> l, monom a)
{
    if (l.pFirst == nullptr)
    {
        Tlist<monom>::TNode *ls = new Tlist<monom>::TNode(a);
        l.pFirst = ls;
        l.sz++;
        return l;
    }

    Tlist<monom>::TNode *ls = new Tlist<monom>::TNode(a);
    Tlist<monom>::TNode *tmp = l.pFirst;

    if (a.getPow() > tmp->data.getPow())
    {
        ls->pNext = l.pFirst;
        l.pFirst = ls;
        l.sz++;
        return l;
    }

    while (tmp->pNext != nullptr && a.getPow() < tmp->pNext->data.getPow())
    {
        tmp = tmp->pNext;
    }

    if (tmp->data.getPow() == a.getPow())
    {
        double new_coef = a.getCoef() + tmp->data.getCoef();
        if (new_coef != 0)
        {
            tmp->data.SetCoef(new_coef);
        }
        else
        {
            if (tmp == l.pFirst)
            {
                l.popFront();
            }
            else
            {
                Tlist<monom>::TNode *prev = l.pFirst;
                while (prev->pNext != tmp)
                    prev = prev->pNext;
                prev->pNext = tmp->pNext;
                delete tmp;
                l.sz--;
            }
        }
        delete ls;
    }
    else if (tmp->pNext != nullptr && tmp->pNext->data.getPow() == a.getPow())
    {
        double new_coef = a.getCoef() + tmp->pNext->data.getCoef();
        if (new_coef != 0)
        {
            tmp->pNext->data.SetCoef(new_coef);
        }
        else
        {
            Tlist<monom>::TNode *toDelete = tmp->pNext;
            tmp->pNext = toDelete->pNext;
            delete toDelete;
            l.sz--;
        }
        delete ls;
    }
    else
    {
        ls->pNext = tmp->pNext;
        tmp->pNext = ls;
        l.sz++;
    }

    return l;
}

ostream &operator<<(ostream &out, Tlist<monom> &l)
{
    if (l.pFirst == nullptr)
    {
        out << "0";
        return out;
    }

    Tlist<monom>::TNode *tmp = l.pFirst;

    double coef = tmp->data.getCoef();
    int pow = tmp->data.getPow();

    if (coef < 0)
        out << "-";
    if (abs(coef) != 1 || pow == 0)
        out << abs(coef);

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

    tmp = tmp->pNext;

    while (tmp != nullptr)
    {
        coef = tmp->data.getCoef();
        pow = tmp->data.getPow();
        x_pow = pow / 100;
        y_pow = (pow % 100) / 10;
        z_pow = pow % 10;

        if (coef > 0)
        {
            out << " + ";
            if (coef != 1 || (x_pow == 0 && y_pow == 0 && z_pow == 0))
                out << coef;
        }
        else
        {
            out << " - ";
            if (coef != -1 || (x_pow == 0 && y_pow == 0 && z_pow == 0))
                out << -coef;
        }

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

        tmp = tmp->pNext;
    }

    return out;
}