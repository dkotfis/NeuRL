package edu.rutgers.rl3.comp.mario;

import org.rlcommunity.rlglue.codec.util.EnvironmentLoader;

import rlVizLib.general.ParameterHolder;

public class GeneralizedMario extends GlueMario {

	public static ParameterHolder getDefaultParameters() {
		ParameterHolder p = new ParameterHolder();

		p.addBooleanParam("fast", false);
		p.addBooleanParam("dark", false);
		
		p.addIntegerParam("level seed", 121);
		p.addIntegerParam("level type", 0);
		p.addIntegerParam("level difficulty", 0);
		
		p.addIntegerParam("instance", 0);
		return p;
	}
	
	
	public GeneralizedMario(ParameterHolder params) {
		setParameters(params);
	}
	
	public static void main(String[] args) {
        new EnvironmentLoader(new GeneralizedMario(GeneralizedMario.getDefaultParameters())).run();
	}
}
