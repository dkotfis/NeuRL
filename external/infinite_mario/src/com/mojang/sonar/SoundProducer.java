package com.mojang.sonar;

public interface SoundProducer
{
    public float read(float[] buf, int readRate);
    public void skip(int samplesToSkip, int readRate);
    public boolean isLive();
}