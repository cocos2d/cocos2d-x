package com.enhance.gameservice;

interface IGameTunningService
{
    int setPreferredResolution(int resolution);
    int setFramePerSecond(int fps);
    int boostUp(int seconds);
    int getAbstractTemperature();
    int setGamePowerSaving(boolean enable);
}