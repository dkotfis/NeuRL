package com.mojang.mario.sprites;

import java.awt.Graphics;
import java.awt.Image;

import com.mojang.mario.level.SpriteTemplate;
import com.mojang.sonar.SoundSource;

import edu.rutgers.rl3.comp.mario.GlueMario;
import edu.rutgers.rl3.comp.mario.GlueMarioParameters;

public class Sprite implements SoundSource
{
    public static SpriteContext spriteContext;
    private float reward; // reward associated with every object in the world
    
    public float xOld, yOld, x, y, xa, ya;

    public float last_step_x = -1;
    public float last_step_y = -1;
    
    public int xPic, yPic;
    public int wPic = 32;
    public int hPic = 32;
    public int xPicO, yPicO;
    public boolean xFlipPic = false;
    public boolean yFlipPic = false;
    public Image[][] sheet;
    public boolean visible = true;
    
    public int layer = 1;

    public SpriteTemplate spriteTemplate;
	private boolean remove = false;
    
    public void setReward (float reward){
    	this.reward = reward;
    }
    
    public float getReward (){
    	if (reward != 0.0){
    		spriteContext.removeSprite(this);
    	}
    	return this.reward;
    }
    
    public void move()
    {
        x+=xa;
        y+=ya;
    }
    
    public void render(Graphics og, float alpha)
    {
        if (!visible) return;
        
        int xPixel = (int)(xOld+(x-xOld)*alpha)-xPicO;
        int yPixel = (int)(yOld+(y-yOld)*alpha)-yPicO;

        if (!GlueMario.go_dark)
        	og.drawImage(sheet[xPic][yPic], xPixel+(xFlipPic?wPic:0), yPixel+(yFlipPic?hPic:0), xFlipPic?-wPic:wPic, yFlipPic?-hPic:hPic, null);
    }
    
/*  private void blit(Graphics og, Image bitmap, int x0, int y0, int x1, int y1, int w, int h)
    {
        if (!xFlipPic)
        {
            if (!yFlipPic)
            {
                og.drawImage(bitmap, x0, y0, x0+w, y0+h, x1, y1, x1+w, y1+h, null);
            }
            else
            {
                og.drawImage(bitmap, x0, y0, x0+w, y0+h, x1, y1+h, x1+w, y1, null);
            }
        }
        else
        {
            if (!yFlipPic)
            {
                og.drawImage(bitmap, x0, y0, x0+w, y0+h, x1+w, y1, x1, y1+h, null);
            }
            else
            {
                og.drawImage(bitmap, x0, y0, x0+w, y0+h, x1+w, y1+h, x1, y1, null);
            }
        }
    }*/

    public final void tick()
    {
        xOld = x;
        yOld = y;
        move();
    }

    public final void tickNoMove()
    {
        xOld = x;
        yOld = y;
    }

    public float getX(float alpha)
    {
        return (xOld+(x-xOld)*alpha)-xPicO;
    }

    public float getY(float alpha)
    {
        return (yOld+(y-yOld)*alpha)-yPicO;
    }

    //+RL-Comp
    public float getCurrentX() {
    	return x;
    }
    public float getCurrentY() {
    	return y;
    }
    public float getCurrentXs() {
    	if (true)
    		return x-xOld;
    	if (last_step_x == -1)
    		return 0;
    	return x-last_step_x;
    }
    public float getCurrentYs() {
    	if (true)
    		return y-yOld;
    	if (last_step_y == -1)
    		return 0;
    	return y-last_step_y;
    }
    //-RL-Comp
    
    public void collideCheck()
    {
    }

    public void bumpCheck(int xTile, int yTile)
    {
    }

    public boolean shellCollideCheck(Shell shell)
    {
        return false;
    }

    public void release(Mario mario)
    {
    }

    public boolean fireballCollideCheck(Fireball fireball)
    {
        return false;
    }
}