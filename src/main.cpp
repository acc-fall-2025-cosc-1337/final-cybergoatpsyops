#include <iostream>
#include <ctime>
#include <cstdlib>
#include "die.h"
#include "shooter.h"
#include "roll.h"
#include "come_out_phase.h"
#include "point_phase.h"

int main() 
{
	srand(time(0));

	Die die1;
	Die die2;
	Shooter shooter;
	Roll* roll = shooter.throw_dice(die1, die2);
	int rolled_value = roll->roll_value();

	ComeOutPhase come_out_phase;

	while (come_out_phase.get_outcome(roll) == RollOutcome::natural || 
		   come_out_phase.get_outcome(roll) == RollOutcome::craps) {
		std::cout << "Rolled " << rolled_value << " roll again" << std::endl;
		roll = shooter.throw_dice(die1, die2);
		rolled_value = roll->roll_value();
	}

	std::cout << "Rolled " << rolled_value << " start of point phase" << std::endl;
	std::cout << "Roll until " << rolled_value << " or a 7 is rolled" << std::endl;

	int point = rolled_value;
	roll = shooter.throw_dice(die1, die2);
	rolled_value = roll->roll_value();

	PointPhase point_phase(point);

	while (point_phase.get_outcome(roll) != RollOutcome::seven_out && 
		   point_phase.get_outcome(roll) != RollOutcome::point) {
		std::cout << "Rolled " << rolled_value << " roll again" << std::endl;
		roll = shooter.throw_dice(die1, die2);
		rolled_value = roll->roll_value();
	}

	std::cout << "Rolled " << rolled_value << " end of point phase" << std::endl;

	shooter.display_rolled_values();

	return 0;
}