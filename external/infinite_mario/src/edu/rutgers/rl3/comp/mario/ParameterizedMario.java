package edu.rutgers.rl3.comp.mario;

import org.rlcommunity.rlglue.codec.util.EnvironmentLoader;

import rlVizLib.general.ParameterHolder;

public class ParameterizedMario extends GlueMario {

	public static ParameterHolder getDefaultParameters() {
		ParameterHolder p = new ParameterHolder();

		p.addBooleanParam("fast", false);
		p.addBooleanParam("dark", false);
		
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
		
		return p;
	}
	
	
	public ParameterizedMario(ParameterHolder params) {
		setParameters(params);
	}
	
	public static void main(String[] args) {
        new EnvironmentLoader(new ParameterizedMario(ParameterizedMario.getDefaultParameters())).run();
	}
}
