#include "../include/list.h"
#include <string>
#include <algorithm>
#include "../include/polinom.h"
#include "../include/monom.h"

using namespace std;
int main()
{
    // TLIST<MONOM>

    //  Tlist<monom> l;
    //  string s = "-2x5y3z4";
    //  monom a(s);
    //  string s1 = "13x1y2";
    //  monom a1(s1);
    //  string s2 = "-4x3z4";
    //  monom a2(s2);
    //  l = add(l, a2);
    //  l = add(l, a);
    //  l = add(l, a1);
    //  cout << l;

    // POLINOMS

    string s = "4x4y3z4 + 3x3y2z2";
    polinom a(s);
    string s1 = "-2x5y3z4 + 13x2y3";
    polinom a1(s1);
    polinom res = a1 * a;
    cout << res;
    // polinom res = a * a1;
    // cout << res;

    // OTHER TESTS

    // Tlist<int> a;
    // int a1 = 1;
    // int a2 = 2;
    // int a3 = 3;
    // a.pushFront(a2);
    // a.pushFront(a1);
    // a.PushAfter(0, a3);
    // cout << a[0];
}
