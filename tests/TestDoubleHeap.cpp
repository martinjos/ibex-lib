/* ============================================================================
 * I B E X - CellHeap Tests
 * ============================================================================
 * Copyright   : Ecole des Mines de Nantes (FRANCE)
 * License     : This program can be distributed under the terms of the GNU LGPL.
 *               See the file COPYING.LESSER.
 *
 * Author(s)   : Jordan Ninin
 * Created     : Mar 2, 2014
 * ---------------------------------------------------------------------------- */

#include "TestDoubleHeap.h"
#include "ibex_DoubleHeap.h"

using namespace std;

namespace ibex {



class TestCostFunc1  : public CostFunc<Interval> {
public:
	TestCostFunc1() { } ;
	double cost(const Interval& c) const { return c.diam();};
};

class TestCostFunc2 : public CostFunc<Interval> {
public:
	TestCostFunc2() { } ;
	double cost(const Interval& c) const { return c.lb();};
};

class TestCostFunc3 : public  CostFunc<Interval> {
public:
	TestCostFunc3(): CostFunc<Interval>(true), loup(10) { } ;
	double cost(const Interval& c) const { return c.ub()*loup;};
	void set_loup(double lb) { loup = lb; }

private:
	double loup;
};


void TestDoubleHeap::test01() {

	int nb= 10;
	TestCostFunc1 costf1;
	TestCostFunc2 costf2;

	DoubleHeap<Interval> h(costf1,costf2,50);

	for (int i=1; i<=nb ;i++) {
		if ((i%2)==1) h.push(new Interval(i,2*i));
		else h.push(new Interval(i,20*i));
	}

	TEST_ASSERT(h.minimum1()==1);
	TEST_ASSERT(h.minimum2()==1);

	h.pop1();
	h.pop1();
	TEST_ASSERT(h.minimum1()==5);
	TEST_ASSERT(h.minimum2()==2);

	h.pop2();
	TEST_ASSERT(h.minimum1()==5);
	TEST_ASSERT(h.minimum2()==4);

	h.contract(20);
	TEST_ASSERT(h.minimum1()==5);
	TEST_ASSERT(h.minimum2()==5);

	h.pop2();
	h.pop2();
	TEST_ASSERT(h.minimum1()==9);
	TEST_ASSERT(h.minimum2()==9);

	TEST_ASSERT(h.size()==1);

	h.push(new Interval(10,11));
	h.push(new Interval(12,14));
	h.push(new Interval(12,12));
	h.push(new Interval(12,13.1));

	TEST_ASSERT(h.minimum1()==0);
	TEST_ASSERT(h.minimum2()==9);
	TEST_ASSERT(h.size()==5);

	h.pop1();
	TEST_ASSERT(h.minimum1()==1);
	TEST_ASSERT(h.minimum2()==9);
	TEST_ASSERT(h.size()==4);

	h.pop2();
	TEST_ASSERT(h.minimum1()==1);
	TEST_ASSERT(h.minimum2()==10);
	TEST_ASSERT(h.size()==3);

	h.flush();
	TEST_ASSERT(h.size()==0);
}


void TestDoubleHeap::test02() {

	int nb= 10;
	TestCostFunc2 costf2;
	TestCostFunc3 costf3;

	DoubleHeap<Interval> h(costf2,costf3,50);

	for (int i=1; i<=nb ;i++) {
		if ((i%2)==1) h.push(new Interval(i,2*i));
		else h.push(new Interval(i,20*i));
	}

	TEST_ASSERT(h.minimum1()==1);
	TEST_ASSERT(h.minimum2()==20);

	h.pop2();
	h.pop2();
	TEST_ASSERT(h.minimum1()==2);
	TEST_ASSERT(h.minimum2()==100);

	h.pop1();
	TEST_ASSERT(h.minimum1()==4);
	TEST_ASSERT(h.minimum2()==100);

	// it is necessary to update the loup.
	costf3.set_loup(100);
	h.contract(7.5);
	TEST_ASSERT(h.minimum1()==4);
	TEST_ASSERT(h.minimum2()==1000);
	TEST_ASSERT(h.size()==4);


	h.pop2();
	h.pop2();
	TEST_ASSERT(h.minimum1()==4);
	TEST_ASSERT(h.minimum2()==8000);
	TEST_ASSERT(h.size()==2);

	h.push(new Interval(10,11));
	h.push(new Interval(12,14));
	h.push(new Interval(12,12));
	h.push(new Interval(12,13.1));

	TEST_ASSERT(h.minimum1()==4);
	TEST_ASSERT(h.minimum2()==1100);
	TEST_ASSERT(h.size()==6);

	h.pop1();
	TEST_ASSERT(h.minimum1()==6);
	TEST_ASSERT(h.minimum2()==1100);
	TEST_ASSERT(h.size()==5);

	h.pop2();
	TEST_ASSERT(h.minimum1()==6);
	TEST_ASSERT(h.minimum2()==1200);
	TEST_ASSERT(h.size()==4);

	h.flush();
	TEST_ASSERT(h.size()==0);
}



} // end namespace
