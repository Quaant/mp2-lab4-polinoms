// #include <iostream>
// #include "../include/list.h"
// #include <vector>

// using namespace std;

// template <typename T>
// Tlist<T>::Tlist(const vector<T> &v)
// {
//     if (v.size() <= 0)
//     {
//         throw runtime_error("size of vector is low");
//     }
//     TNode *tmp = new TNode(nullptr, v[0]);
//     pFirst = tmp;
//     sz = v.size();
//     for (int i = 1; i < v.size(); i++)
//     {
//         TNode *tmp1 = new TNode(nullptr, v[i]);
//         tmp->pNext = tmp1;
//         tmp = tmp1;
//     }
// }

// template <typename T>
// Tlist<T>::Tlist(const Tlist &l)
// {
//     if (l.sz <= 0)
//     {
//         throw runtime_error("size is empty");
//     }
//     pFirst = new TNode(nullptr, l.pFirst->data);
//     sz = 1;
//     TNode *a = pFirst;
//     TNode *b = l.pFirst->pNext;
//     while (b != nullptr)
//     {
//         TNode *tmp = new TNode(nullptr, b->data);
//         a->pNext = tmp;
//         a = tmp;
//         b = b->pNext;
//         sz++;
//     }
// }

// template <typename T>
// Tlist<T>::Tlist(Tlist &&l) noexcept
// {
//     pFirst = nullptr;
//     data = nullptr;
//     pFirst = l.pFirst;
//     data = l.data;
//     delete l.pFirst;
//     delete l.data;
// }

// template <typename T>
// Tlist<T> &Tlist<T>::operator=(const Tlist &l)
// {
//     if (l.sz <= 0)
//     {
//         throw runtime_error("size is empty");
//     }
//     TNode *old = pFirst;
//     sz = l.sz;
//     pFirst = new TNode(nullptr, l.pFirst->data);
//     TNode *ths = pFirst;
//     TNode *lst = l.pFirst->pNext;

//     while (lst != nullptr)
//     {
//         ths->pNext = new TNode(nullptr, lst->data);
//         ths = ths->pNext;
//         lst = lst->pNext;
//     }
//     while (old != nullptr)
//     {
//         TNode *tmp = old;
//         old = old->pNext;
//         delete tmp;
//     }
// }

// template <typename T>
// size_t Tlist<T>::sizee() const noexcept
// {
//     return sz;
// }
// template <typename T>
// bool Tlist<T>::isEmpty() const noexcept
// {
//     return sz == 0;
// }

// template <typename T>
// T &Tlist<T>::Front() noexcept
// {
//     return pFirst->data;
// }

// template <typename T>
// void Tlist<T>::pushFront(const T &val)
// {
//     TNode *tmp = new TNode(pFirst, val);
//     pFirst = tmp;
// }

// template <typename T>
// void Tlist<T>::popFront() noexcept
// {
//     TNode *tmp = pFirst;
//     pFirst = pFirst->pNext;
//     delete tmp;
// }
// template <typename T>
// T &Tlist<T>::operator[](size_t pos)
// {
//     size_t i = 0;
//     const TNode *tmp = pFirst;
//     while (i != pos)
//     {
//         tmp = tmp->pNext;
//         i++;
//     }
//     return tmp->data;
// }
// template <typename T>
// void Tlist<T>::PushAfter(size_t pos, const T &val)
// {
//     TNode *tmp = new TNode(nullptr, val);
//     size_t i = 0;
//     TNode *a = pFirst;

//     while (i != pos - 1)
//     {
//         a = a->pNext;
//     }
//     TNode *b = a->pNext;
//     a->pNext = tmp;
//     tmp->pNext = b;
// }
// template <typename T>
// void Tlist<T>::EraseAfter(size_t pos)
// {
//     // ДОПИЛИТЬ=================================================

//     TNode *prev = new TNode(PFirst, 0);
//     const TNode *tmp = pFirst->pNext;
//     size_t i = 0;
//     while (i != pos)
//     {
//         tmp = tmp->pNext;
//         prev = prev->pNext;
//         i++;
//     }
//     prev->pNext = tmp->pNext;
//     delete tmp;
// }

// Tlist<monom> add(Tlist<monom> l, monom a)
// {
//     //    TNode *ls = new TNode{nullptr, a}; // need constructor
//     Tlist<monom>::TNode *ls = new Tlist<monom>::TNode(a); // need constructor

//     Tlist<monom>::TNode *tmp = l.pFirst;
//     bool flag = false;

//     Tlist<monom>::TNode *next = l.pFirst->pNext;
//     Tlist<monom>::TNode *prev;
//     size_t i = -1;
//     while (tmp != nullptr)
//     {
//         if (next == nullptr)
//         {
//             if (a.getPow() < tmp->data.getPow())
//             {
//                 tmp->pNext = ls; // new TNode
//             }
//         }
//         if (a.getPow() < tmp->data.getPow() && a.getPow() > next->data.getPow())
//         {
//             tmp->pNext = ls;
//             ls->pNext = next;
//             break;
//         }
//         else if (a.getPow() == tmp->data.getPow())
//         {
//             double new_coef = a.getCoef() + tmp->data.getCoef();
//             if (new_coef != 0)
//             {
//                 tmp->data.SetCoef(new_coef);
//             }
//             else
//             {
//                 if (tmp == l.pFirst)
//                 {
//                     l.popFront();
//                 }
//                 else
//                 {
//                     l.EraseAfter(i);
//                 }
//             }
//         }
//         prev = tmp;
//         i++;
//         tmp = tmp->pNext;
//         next = next->pNext;
//     }
//     return l;
// }
// ostream &operator<<(ostream &out, Tlist<monom> &l)
// {
//     Tlist<monom>::TNode *tmp = l.pFirst;
//     out << tmp->data.getCoef() << 'x' << tmp->data.getPow() / 100 << 'y' << (tmp->data.getPow() % 100) / 10 << 'z' << tmp->data.getPow() % 10 << ' ';
//     tmp = tmp->pNext;
//     while (tmp != nullptr)
//     {
//         if (tmp->data.getCoef() > 0)
//         {
//             out << '+' << ' ' << tmp->data.getCoef() << 'x' << tmp->data.getPow() / 100 << 'y' << (tmp->data.getPow() % 100) / 10 << 'z' << tmp->data.getPow() % 10 << ' ';
//         }
//         else
//         {
//             out << '+' << ' ' << '(' << tmp->data.getCoef() << 'x' << tmp->data.getPow() / 100 << 'y' << (tmp->data.getPow() % 100) / 10 << 'z' << tmp->data.getPow() % 10 << ')' << ' ';
//         }
//         tmp = tmp->pNext;
//     }
//     return out;
// }
