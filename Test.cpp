#include "doctest.h"
#include "sources/OrgChart.hpp"
#include <iostream>

TEST_CASE("add_root_and_subordinate_expect_level_order_correct") {
	ariel::OrgChart chart;

	CHECK_NOTHROW(chart.add_root("CEO"));
	CHECK_NOTHROW(chart.add_sub("CEO", "VP"));
	CHECK_NOTHROW(chart.add_sub("VP", "Programmer"));

	auto iter = chart.begin_level_order();

	CHECK(*iter == "CEO");
	++iter;
	CHECK(*iter == "VP");
	++iter;
	CHECK(*iter == "Programmer");
	++iter;
	CHECK(iter == chart.end_level_order());
}

TEST_CASE("add_root_and_subordinate_expect_reverse_order_correct") {
	ariel::OrgChart chart;

	CHECK_NOTHROW(chart.add_root("CEO"));
	CHECK_NOTHROW(chart.add_sub("CEO", "VP"));
	CHECK_NOTHROW(chart.add_sub("VP", "Programmer"));

	auto iter = chart.begin_reverse_order();

	CHECK(*iter == "Programmer");
	++iter;
	CHECK(*iter == "VP");
	++iter;
	CHECK(*iter == "CEO");
	++iter;
	CHECK(iter == chart.reverse_order());
}

TEST_CASE("add_root_and_subordinate_expect_preorder_correct") {
	ariel::OrgChart chart;

	CHECK_NOTHROW(chart.add_root("CEO"));
	CHECK_NOTHROW(chart.add_sub("CEO", "VP"));
	CHECK_NOTHROW(chart.add_sub("CEO", "CTO"));

	auto iter = chart.begin_preorder();

	CHECK(*iter == "CEO");
	++iter;
	CHECK(*iter == "VP");
	++iter;
	CHECK(*iter == "CTO");
	++iter;
	CHECK(iter == chart.end_preorder());
}

TEST_CASE("add_sub_with_no_root_expect_throw") {
	ariel::OrgChart chart;

	CHECK_THROWS(chart.add_sub("CEO", "Manager"));
}

TEST_CASE("add_empty_root_role_expect_throw") {
	ariel::OrgChart chart;

	CHECK_THROWS(chart.add_root(""));
}

TEST_CASE("add_empty_subordinate_role_expect_throw") {
	ariel::OrgChart chart;

	CHECK_NOTHROW(chart.add_root("CEO"));
	CHECK_THROWS(chart.add_sub("CEO", ""));
}

TEST_CASE("add_subordinate_to_non_existent_role_expect_throw") {
	ariel::OrgChart chart;

	CHECK_NOTHROW(chart.add_root("CEO"));
	CHECK_THROWS(chart.add_sub("King", "Manager`"));
}
