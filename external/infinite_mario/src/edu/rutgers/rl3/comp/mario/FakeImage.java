package edu.rutgers.rl3.comp.mario;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.ImageCapabilities;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.awt.image.ImageProducer;
import java.awt.image.VolatileImage;

public class FakeImage extends VolatileImage {

	@Override
	public void flush() {
		// TODO Auto-generated method stub

	}

	@Override
	public Graphics getGraphics() {
		// TODO Auto-generated method stub
		return new FakeGraphics();
	}

	@Override
	public int getHeight(ImageObserver observer) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public Object getProperty(String name, ImageObserver observer) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ImageProducer getSource() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int getWidth(ImageObserver observer) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean contentsLost() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public Graphics2D createGraphics() {
		// TODO Auto-generated method stub
		return new FakeGraphics();
	}

	@Override
	public ImageCapabilities getCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int getHeight() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public BufferedImage getSnapshot() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int getWidth() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int validate(GraphicsConfiguration gc) {
		// TODO Auto-generated method stub
		return 0;
	}

}
