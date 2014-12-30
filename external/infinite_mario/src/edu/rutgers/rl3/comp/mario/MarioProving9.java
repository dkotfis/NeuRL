package edu.rutgers.rl3.comp.mario;

import org.rlcommunity.rlglue.codec.util.EnvironmentLoader;

import rlVizLib.general.ParameterHolder;

public class MarioProving9 extends GlueMario {
	
	public static ParameterHolder getDefaultParameters() {
		ParameterHolder p = new ParameterHolder();

		p.addBooleanParam("fast", true);
		p.addBooleanParam("dark", true);
		
		return p;
	}

	public static ParameterHolder changeParams(ParameterHolder params) {
		params.addIntegerParam("instance", 0);
		params.addIntegerParam("level seed", 11999321);
		params.addIntegerParam("level type", 2);
		params.addIntegerParam("level difficulty", 4);
		return params;
	}
	
	public MarioProving9(ParameterHolder params) {
		setParameters(changeParams(params));

		param.level_width = 500;
		param.max_trial_steps = 2000;
		param.reward_goal = 100;
		param.reward_death = -10;
		param.reward_step = -.01;
		param.reward_coin = 1;
		param.reward_kill = 1;
		param.speed_walk = 0.6;
		param.speed_run = 1.2;
		param.speed_jump = -1.9;
		param.speed_jump_sliding = -2;
		param.accel_gravity = .82;
		param.jump_time = 7;
		param.jump_time_sliding = -6;
	}
	
	public static void main(String[] args) {
        new EnvironmentLoader(new MarioProving9(MarioProving9.getDefaultParameters())).run();
	}
}
