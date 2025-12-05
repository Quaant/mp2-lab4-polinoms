#include "../include/list.h"
#include <string>
#include <algorithm>
#include "../include/polinom.h"
#include "../include/monom.h"

using namespace std;
int main()
{
    // Tlist<monom>
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

    // polinom
    string s = "-2x3y3z4 + 2";
    polinom a(s);
    string s1 = "4x3y3z4 + 3x4y2z2";
    polinom a1(s1);
    polinom res = a * a1;
    cout << res;
}
