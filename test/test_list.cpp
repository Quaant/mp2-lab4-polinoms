#include <gtest.h>
#include "list.h"

using namespace std;

TEST(Tlist, can_create_list_with_different_types)
{
    EXPECT_NO_THROW(Tlist<double> a);
    EXPECT_NO_THROW(Tlist<int> a);
    EXPECT_NO_THROW(Tlist<monom> a);
}
TEST(Tlist, constructor_with_vecgor)
{
    vector<int> v = {1, 2, 3, 4, 5};
    Tlist<int> a;
    EXPECT_NO_THROW(a = Tlist<int>(v));
    for (int i = 0; i < size(v); i++)
    {
        EXPECT_EQ(v[i], a[i]);
    }
}

TEST(Tlist, constructor_with_list)
{
    Tlist<int> a;
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    a.pushFront(a3);
    a.pushFront(a2);
    a.pushFront(a1);
    Tlist<int> b(a);
    EXPECT_EQ(a[0], b[0]);
    EXPECT_EQ(a[1], b[1]);
    EXPECT_EQ(a[2], b[2]);
}
TEST(Tlist, operator_ravno)
{
    Tlist<int> a;
    int a1 = 1;
    int a2 = 2;
    a.pushFront(a2);
    a.pushFront(a1);
    Tlist<int> b;
    b = a;
    EXPECT_EQ(a[0], b[0]);
    EXPECT_EQ(a[1], b[1]);
}

TEST(Tlist, popFront)
{
    Tlist<int> a;
    int a1 = 1;
    int a2 = 2;
    a.pushFront(a2);
    a.pushFront(a1);
    a.popFront();
    EXPECT_EQ(a.sizee(), 1);
}
TEST(Tlist, PushAfter)
{
    Tlist<int> a;
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    a.pushFront(a2);
    a.pushFront(a1);
    a.PushAfter(0, a3);
    EXPECT_EQ(a[1], 3);
}
TEST(Tlist, EraseAfter)
{
    Tlist<int> a;
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    a.pushFront(a3);
    a.pushFront(a2);
    a.pushFront(a1);
    a.EraseAfter(0);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 3);
}
