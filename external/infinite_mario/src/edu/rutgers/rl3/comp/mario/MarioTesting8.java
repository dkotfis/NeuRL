package edu.rutgers.rl3.comp.mario;

import org.rlcommunity.rlglue.codec.util.EnvironmentLoader;

import rlVizLib.general.ParameterHolder;

public class MarioTesting8 extends GlueMario {
	
	public static ParameterHolder getDefaultParameters() {
		ParameterHolder p = new ParameterHolder();

		p.addBooleanParam("fast", true);
		p.addBooleanParam("dark", true);
		
		return p;
	}

	public static ParameterHolder changeParams(ParameterHolder params) {
		params.addIntegerParam("instance", 0);
		params.addIntegerParam("level seed", 22115321);
		params.addIntegerParam("level type", 1);
		params.addIntegerParam("level difficulty", 10);
		return params;
	}
	
	public MarioTesting8(ParameterHolder params) {
		setParameters(changeParams(params));

		param.level_width = 320;
		param.max_trial_steps = 1000;
		param.reward_goal = 0;
		param.reward_death = 0;
		param.reward_step = -.01;
		param.reward_coin = 1;
		param.reward_kill = 0;
		param.speed_walk = 1.6;
		param.speed_run = 2.2;
		param.speed_jump = -1.9;
		param.speed_jump_sliding = -2;
		param.accel_gravity = .82;
		param.jump_time = 10;
		param.jump_time_sliding = -6;
	}
	
	public static void main(String[] args) {
        new EnvironmentLoader(new MarioProving8(MarioProving8.getDefaultParameters())).run();
	}
}
