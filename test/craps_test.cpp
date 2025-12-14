#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "die.h"
#include "roll.h"

TEST_CASE("Verify Test Configuration", "verification") {
	REQUIRE(true == true);
}

TEST_CASE("Die rolls return value from 1 to 6") {
	Die die;
	for (int i = 0; i < 10; ++i) {
		int roll = die.roll();
		REQUIRE(roll >= 1);
		REQUIRE(roll <= 6);
	}
}

TEST_CASE("Roll returns value from 2 to 12") {
	Die die1;
	Die die2;
	Roll roll(die1, die2);
	for (int i = 0; i < 10; ++i) {
		roll.roll_dice();
		int value = roll.roll_value();
		REQUIRE(value >= 2);
		REQUIRE(value <= 12);
	}
}
