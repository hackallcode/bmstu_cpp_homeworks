#include <iostream>
#include <exception>

#define assert(X) { \
	if(!(X)) {\
		std::cout << "see function:'" << __FUNCTION__ << "' line: " << __LINE__ << std::endl;\
		throw std::logic_error(#X); \
	}\
}

#define RUN_TEST(func, message) \
{ try {\
	func();\
	std::cout << #func << " " << message << std::endl;\
  } catch(std::exception& e) { \
	std::cout << #func << " failed. reason: " << e.what() << std::endl; \
  }\
}


#include "BooleanFunction.h"

void test_ctor0()
{
    try
    {
        BooleanFunction f("111");
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }

    try
    {
        BooleanFunction f({ true, false, true });
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_ctor1()
{
    BooleanFunction f;
    assert(f.size() == 0);
    assert(f.dimension() == 0);

    try
    {
        f.at(0);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_ctor2()
{
    BooleanFunction f(3);
    assert(f.size() == 8);
    assert(f.dimension() == 3);

    try
    {
        assert(static_cast<int>(f.at(0)) == 0);
        assert(true);
        f.at(8);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_ctor3()
{
    BooleanFunction f(14, 3);
    assert(f.size() == 8);
    assert(f.dimension() == 3);

    try
    {
        assert(static_cast<int>(f.at(0)) == 0);
        assert(static_cast<int>(f.at(1)) == 1);
        assert(static_cast<int>(f.at(2)) == 1);
        assert(static_cast<int>(f.at(3)) == 1);
        assert(static_cast<int>(f.at(4)) == 0);
        assert(static_cast<int>(f.at(5)) == 0);
        assert(static_cast<int>(f.at(6)) == 0);
        assert(static_cast<int>(f.at(7)) == 0);
        assert(true);
        f.at(8);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_ctor_string()
{
    BooleanFunction f("01110000");
    assert(f.size() == 8);
    assert(f.dimension() == 3);

    try
    {
        assert(static_cast<int>(f.at(0)) == 0);
        assert(static_cast<int>(f.at(1)) == 1);
        assert(static_cast<int>(f.at(2)) == 1);
        assert(static_cast<int>(f.at(3)) == 1);
        assert(static_cast<int>(f.at(4)) == 0);
        assert(static_cast<int>(f.at(5)) == 0);
        assert(static_cast<int>(f.at(6)) == 0);
        assert(static_cast<int>(f.at(7)) == 0);
        assert(true);
        f.at(8);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_ctor_vec()
{
    std::vector<BooleanFunction::value_type> vec = { true, false, true, true, false, false, false, false };
    BooleanFunction f(vec);
    assert(f.size() == 8);
    assert(f.dimension() == 3);

    try
    {
        assert(static_cast<int>(f.at(0)) == 1);
        assert(static_cast<int>(f.at(1)) == 0);
        assert(static_cast<int>(f.at(2)) == 1);
        assert(static_cast<int>(f.at(3)) == 1);
        assert(static_cast<int>(f.at(4)) == 0);
        assert(static_cast<int>(f.at(5)) == 0);
        assert(static_cast<int>(f.at(6)) == 0);
        assert(static_cast<int>(f.at(7)) == 0);
        assert(true);
        f.at(8);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_ctor_copy()
{
    std::vector<BooleanFunction::value_type> vec = { true, false, true, true, false, false, false, false };
    BooleanFunction g(vec);

    assert(g == BooleanFunction({ true, false, true, true, false, false, false, false }));

    BooleanFunction f(g);
    assert(f.size() == 8);
    assert(f.dimension() == 3);

    try
    {
        assert(static_cast<int>(f.at(0)) == 1);
        assert(static_cast<int>(f.at(1)) == 0);
        assert(static_cast<int>(f.at(2)) == 1);
        assert(static_cast<int>(f.at(3)) == 1);
        assert(static_cast<int>(f.at(4)) == 0);
        assert(static_cast<int>(f.at(5)) == 0);
        assert(static_cast<int>(f.at(6)) == 0);
        assert(static_cast<int>(f.at(7)) == 0);
        assert(true);
        f.at(8);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_op_copy()
{
    BooleanFunction g(14, 3);
    BooleanFunction f;
    assert(f.size() == 0);
    assert(f.dimension() == 0);
    f = g;

    try
    {
        assert(static_cast<int>(f.at(0)) == 0);
        assert(static_cast<int>(f.at(1)) == 1);
        assert(static_cast<int>(f.at(2)) == 1);
        assert(static_cast<int>(f.at(3)) == 1);
        assert(static_cast<int>(f.at(4)) == 0);
        assert(static_cast<int>(f.at(5)) == 0);
        assert(static_cast<int>(f.at(6)) == 0);
        assert(static_cast<int>(f.at(7)) == 0);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_op_xor()
{
    BooleanFunction g(14, 3);
    BooleanFunction f(4, 3);

    assert(f.size() == 8);
    assert(f.dimension() == 3);
    f += g;
    assert(f.size() == 8);
    assert(f.dimension() == 3);

    try
    {
        assert(static_cast<int>(f.at(0)) == 0);
        assert(static_cast<int>(f.at(1)) == 1);
        assert(static_cast<int>(f.at(2)) == 0);
        assert(static_cast<int>(f.at(3)) == 1);
        assert(static_cast<int>(f.at(4)) == 0);
        assert(static_cast<int>(f.at(5)) == 0);
        assert(static_cast<int>(f.at(6)) == 0);
        assert(static_cast<int>(f.at(7)) == 0);

        f += BooleanFunction(64, 5);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_op_and()
{
    BooleanFunction g(14, 3);
    BooleanFunction f(4, 3);

    assert(f.size() == 8);
    assert(f.dimension() == 3);
    f *= g;
    assert(f.size() == 8);
    assert(f.dimension() == 3);

    try
    {
        assert(static_cast<int>(f.at(0)) == 0);
        assert(static_cast<int>(f.at(1)) == 0);
        assert(static_cast<int>(f.at(2)) == 1);
        assert(static_cast<int>(f.at(3)) == 0);
        assert(static_cast<int>(f.at(4)) == 0);
        assert(static_cast<int>(f.at(5)) == 0);
        assert(static_cast<int>(f.at(6)) == 0);
        assert(static_cast<int>(f.at(7)) == 0);

        f *= BooleanFunction(64, 5);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_op_or()
{
    BooleanFunction g(14, 3);
    BooleanFunction f(16, 3);

    assert(f.size() == 8);
    assert(f.dimension() == 3);
    f |= g;
    assert(f.size() == 8);
    assert(f.dimension() == 3);

    try
    {
        assert(static_cast<int>(f.at(0)) == 0);
        assert(static_cast<int>(f.at(1)) == 1);
        assert(static_cast<int>(f.at(2)) == 1);
        assert(static_cast<int>(f.at(3)) == 1);
        assert(static_cast<int>(f.at(4)) == 1);
        assert(static_cast<int>(f.at(5)) == 0);
        assert(static_cast<int>(f.at(6)) == 0);
        assert(static_cast<int>(f.at(7)) == 0);

        f |= BooleanFunction(64, 5);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_op_not()
{
    BooleanFunction f(14, 3);

    assert(f.size() == 8);
    assert(f.dimension() == 3);
    ~f;

    try
    {
        assert(static_cast<int>(f.at(0)) == 1);
        assert(static_cast<int>(f.at(1)) == 0);
        assert(static_cast<int>(f.at(2)) == 0);
        assert(static_cast<int>(f.at(3)) == 0);
        assert(static_cast<int>(f.at(4)) == 1);
        assert(static_cast<int>(f.at(5)) == 1);
        assert(static_cast<int>(f.at(6)) == 1);
        assert(static_cast<int>(f.at(7)) == 1);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_op_eq()
{
    BooleanFunction f(14, 3);

    assert(f == BooleanFunction(14, 3));
    assert(f == BooleanFunction("01110000"));
    assert(f != BooleanFunction(15, 3));
    assert(f != BooleanFunction("11110010"));
}

void test_op_more()
{
    BooleanFunction f(14, 3);

    assert(f >= BooleanFunction(14, 3));
    assert(!(f >= BooleanFunction("11110000")));
    assert((f >= BooleanFunction("00110000")));
    try
    {
        f >= BooleanFunction("00110110");
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void test_it()
{
    BooleanFunction f(14, 3);

    BooleanFunction::iterator it = f.begin();

    assert(static_cast<int>(*it) == 0);
    ++it;
    assert(static_cast<int>(*it) == 1);
    ++it;
    assert(static_cast<int>(*it) == 1);
    ++it;
    assert(static_cast<int>(*it) == 1);
    ++it;
    assert(static_cast<int>(*it) == 0);
    ++it;
    assert(static_cast<int>(*it) == 0);
    ++it;
    assert(static_cast<int>(*it) == 0);
    ++it;
    assert(static_cast<int>(*it) == 0);
}

void test_it_begin_end()
{
    BooleanFunction f(5);

    for (auto & v : f)
    {
        assert(static_cast<bool>(v) == false);
    }
}

void test_access()
{
    BooleanFunction f(14, 3);

    assert(static_cast<int>(f[0]) == 0);
    assert(static_cast<int>(f[1]) == 1);
    assert(static_cast<int>(f[2]) == 1);
    assert(static_cast<int>(f[3]) == 1);
    assert(static_cast<int>(f[4]) == 0);
    assert(static_cast<int>(f[5]) == 0);
    assert(static_cast<int>(f[6]) == 0);
    assert(static_cast<int>(f[7]) == 0);

    f[4] = true;
    assert(static_cast<int>(f[4]) == 1);

    f[1] = 0;
    assert(static_cast<int>(f[1]) == 0);

    f[1] = f[3];
    assert(static_cast<int>(f[1]) == 1);
}

void test_property()
{
    BooleanFunction f(14, 3);

    assert(!f.is_linear());
    assert(!f.is_monotone());
    assert(!f.is_T1());
    assert(f.is_T0());
    assert(!f.is_balanced());
    assert(!f.is_functionally_complete_system());
    assert(!f.is_self_dual());
    assert(f.weight() == 3);
}

void test_property1()
{
    BooleanFunction f("1000");

    assert(!f.is_linear());
    assert(!f.is_monotone());
    assert(!f.is_T1());
    assert(!f.is_T0());
    assert(!f.is_balanced());
    assert(f.is_functionally_complete_system());
    assert(!f.is_self_dual());
    assert(f.weight() == 1);
}

void test_property2()
{
    assert(BooleanFunction("0110").is_linear());
    assert(!BooleanFunction("0110").is_monotone());
    assert(!BooleanFunction("0110").is_T1());
    assert(BooleanFunction("0110").is_T0());
    assert(BooleanFunction("0110").is_balanced());
    assert(!BooleanFunction("0110").is_functionally_complete_system());
    assert(!BooleanFunction("0110").is_self_dual());
    assert(BooleanFunction("0110").weight() == 2);

    assert(BooleanFunction("0001").is_monotone());
}

void test_anf()
{
    std::vector<BooleanFunction::value_type> f = BooleanFunction("0100").anf();
    // 0*1 + 1*y + 0*x + 1*xy
    assert(static_cast<int>(f[0]) == 0); // 0*1
    assert(static_cast<int>(f[1]) == 1); // 1*y
    assert(static_cast<int>(f[2]) == 0); // 0*x
    assert(static_cast<int>(f[3]) == 1); // 1*xy
}

void test_from_anf()
{
    std::vector<BooleanFunction::value_type> anf = { false, true, false, true };

    assert(BooleanFunction::from_anf(anf) == BooleanFunction("0100"));
}

void test_const()
{
    assert(BooleanFunction::one(3) == BooleanFunction("11111111"));
    assert(BooleanFunction::one(5) == BooleanFunction("1"));
    assert(BooleanFunction::one(3) == BooleanFunction("1111"));

    assert(BooleanFunction::zero(3) == BooleanFunction("00000000"));
    assert(BooleanFunction::zero(5) == BooleanFunction("0"));
    assert(BooleanFunction::zero(3) == BooleanFunction("0000"));

    assert(BooleanFunction::var(0, 2) == BooleanFunction("0101"));
    assert(BooleanFunction::var(0, 2) == BooleanFunction("01010101"));

    assert(BooleanFunction::var(1, 2) == BooleanFunction("0011"));
    assert(BooleanFunction::var(1, 2) == BooleanFunction("0011001100110011"));

    BooleanFunction xor = BooleanFunction::var(1, 2) + BooleanFunction::var(0, 2);
    assert(xor == BooleanFunction("0110"));
}

void test_calc()
{
    BooleanFunction g("00010111");
    assert(g({ true, false, true }));
    assert(g({ true, true, true }));
    assert(g({ true, true, false }));
    assert(!g({ false, true, false }));
    assert(!g({ false, false, false }));
    assert(!g({ false, false, true }));
}

void test_combo()
{
    BooleanFunction G("00010111");

    BooleanFunction x0 = BooleanFunction::var(0, 1);
    BooleanFunction x1 = BooleanFunction::var(1, 2);
    BooleanFunction y = BooleanFunction::var(2, 3);
    BooleanFunction z0 = BooleanFunction::var(3, 4);
    BooleanFunction z1 = BooleanFunction::var(4, 5);

    BooleanFunction XOR("0110");
    BooleanFunction AND("0001");

    // c(x0, x1, y, z0, z1) = G(x0+x1, y, z0*z1);
    BooleanFunction c = G({
        XOR({ x0, x1 }),
        y,
        AND({ z0, z1 })
    });

    std::vector<BooleanFunction::value_type> coef = c.anf();

    assert(!coef[0]);
    assert(!coef[1]);
    assert(!coef[2]);
    assert(coef[4 + 1]); // x0y
    assert(coef[4 + 2]); // x1y
    assert(coef[16 + 8 + 1]);  // z0z1x0
    assert(coef[16 + 8 + 2]); // z0z1x0
    assert(coef[16 + 8 + 4]);  // z0z1y
    assert(!coef[31]);
}

void test_combo2()
{
    BooleanFunction G("0100");

    BooleanFunction x = BooleanFunction::var(0, 1);
    BooleanFunction y = BooleanFunction::var(1, 2);

    BooleanFunction XOR("0110");

    // G(x0, x1) = x0 + x0x1
    // c(x, y) = G(x+y, x+y);
    BooleanFunction c = G({
        XOR({ x, x }),
        XOR({ y, y })
    });

    BooleanFunction test(c.anf());
    assert(test.weight() == 0);
}

void test_bonus()
{
    BooleanFunction x = BooleanFunction::var(2, 5);
    assert(get_polynom(x) == "x2");
    x.ReduceFunc();
    assert(get_polynom(x) == "x0");
    assert(x.is_symmetric());
}

int main()
{
    RUN_TEST(test_ctor0, "successed");
    RUN_TEST(test_ctor1, "successed");
    RUN_TEST(test_ctor2, "successed");
    RUN_TEST(test_ctor3, "successed");
    RUN_TEST(test_from_anf, "successed");
    RUN_TEST(test_ctor_string, "successed");
    RUN_TEST(test_ctor_vec, "successed");
    RUN_TEST(test_ctor_copy, "successed");

    RUN_TEST(test_op_xor, "successed");
    RUN_TEST(test_op_and, "successed");
    RUN_TEST(test_op_or, "successed");
    RUN_TEST(test_op_not, "successed");

    RUN_TEST(test_op_eq, "successed");
    RUN_TEST(test_op_more, "successed");

    RUN_TEST(test_it, "successed");
    RUN_TEST(test_it_begin_end, "successed");
    RUN_TEST(test_access, "successed");

    RUN_TEST(test_property, "successed");
    RUN_TEST(test_property1, "successed");
    RUN_TEST(test_property2, "successed");

    RUN_TEST(test_anf, "successed");

    RUN_TEST(test_const, "successed");

    RUN_TEST(test_calc, "successed");
    RUN_TEST(test_combo, "successed");
    RUN_TEST(test_combo2, "successed");

    /* Тест бонусных функций */
    RUN_TEST(test_bonus, "successed");

    system("pause");
}