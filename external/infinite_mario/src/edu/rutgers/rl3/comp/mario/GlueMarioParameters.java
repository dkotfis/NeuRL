package edu.rutgers.rl3.comp.mario;

import com.mojang.mario.level.LevelGenerator;

public class GlueMarioParameters {
	public int ticks_per_action = 5;
	/*
		
		p.addIntegerParam("level seed", 121);
		p.addIntegerParam("level type", 0);
		p.addIntegerParam("level difficulty", 0);
		p.addIntegerParam("level width", 320);

		p.addIntegerParam("max trial steps", 1000);

		p.addDoubleParam("reward goal", 100.0);
		p.addDoubleParam("reward death", -10.0);
		p.addDoubleParam("reward step", -0.01);
		p.addDoubleParam("reward coin", 1.0);
		p.addDoubleParam("reward kill", 1.0);

		p.addDoubleParam("speed walk", .6);
		p.addDoubleParam("speed run", 1.2);
		p.addDoubleParam("speed jump", -1.9);
		p.addDoubleParam("speed slidejump", -2.0);
		
		p.addDoubleParam("accel fall", .82);
		
		p.addIntegerParam("jump time", 7);
		p.addIntegerParam("slidejump time", -6);
	*/

	public int level_seed = 121;
	public int level_type = 0;
	public int level_difficulty = 0;
	public int level_width = 320;
	public int level_height = 15;
	
	public int max_trial_steps = 1000;
	
	public static double reward_goal = 100;
	public static double reward_death = -10;
	public static double reward_step = -.01;
	public static double reward_coin = 1;
	public static double reward_kill = 1;
	
	public double speed_walk = 0.6;
	public double speed_run = 1.2;
	public double speed_jump = -1.9;
	public double speed_jump_sliding = -2;
	
	public double monster_speed = 1.75;
	public double monster_fall = .95;
	public double monster_fall_winged = .85;
	
	public double accel_gravity = .82;
	
	public int jump_time = 7;
	public int jump_time_sliding = -6;
	
	public LevelGenerator getGenerator() {
        return new LevelGenerator(level_width+50, level_height);
	}
	
	public String getTaskSpec() {
		double[] rewards = {reward_death, reward_goal, reward_kill, reward_step};
		double min = reward_coin;
		double max = reward_coin;
		for (double r : rewards) {
			if (r<min) min = r;
			if (r>max) max = r;
		}
		return "VERSION Mario-v1 PROBLEMTYPE episodic DISCOUNTFACTOR 1 ACTIONS INTS (-1 1) (2 0 1)  REWARDS ("+min+" "+max+")";
	}
}
