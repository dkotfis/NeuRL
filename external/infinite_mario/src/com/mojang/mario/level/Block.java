package com.mojang.mario.level;

public class Block {
	public double reward = 0.0;
	public int x ;
	public int y;
	public Block(int xtemp, int ytemp, float rewardTemp) {
	//	System.out.println("block.java x: " + x + "y: " + y + "reward: " + reward);
		x = xtemp;
		y = ytemp;
		reward = rewardTemp;
	}
	public Block getBlock(){
		return this;
	}
}
