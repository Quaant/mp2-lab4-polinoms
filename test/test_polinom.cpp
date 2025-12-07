#include <gtest.h>
#include "polinom.h"
#include "monom.h"
TEST(monom, can_create_monom_with_str)
{
    string s = "2x2y2z2";
    monom a(s);
    EXPECT_EQ(a.getCoef(), 2);
    EXPECT_EQ(a.getPow(), 222);
}
TEST(monom, can_create_monom_with_pow_and_coef)
{
    double c = 2.0;
    int p = 222;
    monom a(c, p);
    EXPECT_EQ(a.getCoef(), 2.0);
    EXPECT_EQ(a.getPow(), 222);
}
TEST(polinom, can_create_polinom_with_str)
{
    string s1 = "-2x3y3z4 + 2";
    string s2 = "4x3y3z4 + 3x4y2z2";
    string s3 = "3";
    EXPECT_NO_THROW(polinom a1(s1));
    EXPECT_NO_THROW(polinom a2(s2));
    EXPECT_NO_THROW(polinom a3(s3));
}
TEST(polinom, can_create_polinom_with_other_polinom)
{
    string s = "4x3y3z4 + 3x4y2z2";
    polinom a(s);
    EXPECT_NO_THROW(polinom b(a));
}
TEST(polinom, can_add_monom_in_polinom)
{
    string s = "4x4y3z4 + 3x8y2z2";
    string s1 = "-2x3y3z4";
    string s2 = "11x5y8z8";
    polinom a(s);
    monom m1(s1);
    monom m2(s2);
    a.addMonom(m1);
    a.addMonom(m2);
    EXPECT_EQ(a[1], m2);
    EXPECT_EQ(a[3], m1);
}
TEST(polinom, operator_ravno)
{
    string s = "4x4y3z4 + 3x8y2z2";
    polinom a(s);
    polinom b = a;
    for (size_t i = 0; i < a.sizee(); i++)
    {
        EXPECT_EQ(a[i], b[i]);
    }
}
TEST(polinom, operator_plus)
{
    string s = "4x4y3z4 + 3x8y2z2";
    string s1 = "-2x3y3z4 + 2";
    string s2 = "11x5y8z8 - 4x4y3z4";
    polinom a(s);
    polinom a1(s1);
    polinom a2(s2);
    polinom res1 = a + a1;
    polinom res2 = a + a2;
    EXPECT_EQ(res1.sizee(), 4);
    EXPECT_EQ(res2.sizee(), 2);
}
TEST(polinom, operator_mul)
{
    string s = "4x4y3z4 + 3x3y2z2";
    polinom a(s);
    string s1 = "-2x5y3z4 + 13x2y3";
    polinom a1(s1);
    polinom res = a1 * a;
    EXPECT_EQ(res[0].getCoef(), -8);
    EXPECT_EQ(res[1].getCoef(), -6);
    EXPECT_EQ(res[2].getCoef(), 52);
    EXPECT_EQ(res[3].getCoef(), 39);
    EXPECT_EQ(res[0].getPow(), 968);
    EXPECT_EQ(res[1].getPow(), 856);
    EXPECT_EQ(res[2].getPow(), 664);
    EXPECT_EQ(res[3].getPow(), 552);
}