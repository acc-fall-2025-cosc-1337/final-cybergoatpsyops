#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "die.h"
#include "roll.h"
#include "shooter.h"
#include "come_out_phase.h"
#include "point_phase.h"

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

TEST_CASE("Shooter returns a Roll and verify that the roll result has one of the following values: 2-12") {
	Die die1;
	Die die2;
	Shooter shooter;
	for (int i = 0; i < 10; ++i) {
		Roll* roll = shooter.throw_dice(die1, die2);
		int value = roll->roll_value();
		REQUIRE(value >= 2);
		REQUIRE(value <= 12);
	}
}

TEST_CASE("ComeOutPhase get outcomes returns values RollOutcome::natural, RollOutcome::craps, and RollOutcome::point") {
	ComeOutPhase come_out_phase;
	Die die1;
	Die die2;
	Roll roll(die1, die2);
	
	// Loop until we get all outcomes
	bool natural = false;
	bool craps = false;
	bool point = false;

	int max_rolls = 1000;
	for (int i = 0; i < max_rolls; ++i) {
		roll.roll_dice();
		RollOutcome outcome = come_out_phase.get_outcome(&roll);
		if (outcome == RollOutcome::natural) natural = true;
		if (outcome == RollOutcome::craps) craps = true;
		if (outcome == RollOutcome::point) point = true;
		
		if (natural && craps && point) break;
	}
	
	REQUIRE(natural);
	REQUIRE(craps);
	REQUIRE(point);
}

TEST_CASE("PointPhase get outcomes returns values RollOutcome::point, RollOutcome::seven_out, and RollOutcome::nopoint") {
	PointPhase point_phase(4); // Set point to 4
	Die die1;
	Die die2;
	Roll roll(die1, die2);
	
	// Loop until we get all outcomes
	bool point_match = false;
	bool seven_out = false;
	bool nopoint = false;

	int max_rolls = 1000;
	for (int i = 0; i < max_rolls; ++i) {
		roll.roll_dice();
		RollOutcome outcome = point_phase.get_outcome(&roll);
		if (outcome == RollOutcome::point) point_match = true;
		if (outcome == RollOutcome::seven_out) seven_out = true;
		if (outcome == RollOutcome::nopoint) nopoint = true;
		
		if (point_match && seven_out && nopoint) break;
	}
	
	REQUIRE(point_match);
	REQUIRE(seven_out);
	REQUIRE(nopoint);
}
