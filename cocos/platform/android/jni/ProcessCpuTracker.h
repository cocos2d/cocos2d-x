#pragma once

#include <vector>

class ProcessCpuTracker
{
public:
    void update();
    void printCurrentState();

private:
    struct CpuTimeInfo
    {
        CpuTimeInfo()
        : mBaseUserTime(0)
        , mBaseSystemTime(0)
        , mBaseIoWaitTime(0)
        , mBaseIrqTime(0)
        , mBaseSoftIrqTime(0)
        , mBaseIdleTime(0)
        , mRelUserTime(0)
        , mRelSystemTime(0)
        , mRelIoWaitTime(0)
        , mRelIrqTime(0)
        , mRelSoftIrqTime(0)
        , mRelIdleTime(0)
        {
        }
        // All times are in milliseconds. They are converted from jiffies to milliseconds
        // when extracted from the kernel.
        long mBaseUserTime;
        long mBaseSystemTime;
        long mBaseIoWaitTime;
        long mBaseIrqTime;
        long mBaseSoftIrqTime;
        long mBaseIdleTime;

        long mRelUserTime;
        long mRelSystemTime;
        long mRelIoWaitTime;
        long mRelIrqTime;
        long mRelSoftIrqTime;
        long mRelIdleTime;
    };

    std::vector<CpuTimeInfo> _cpuTimeInfos;
};


