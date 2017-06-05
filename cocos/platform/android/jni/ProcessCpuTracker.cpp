#include "platform/android/jni/ProcessCpuTracker.h"

#ifdef ANDROID
#include <jni.h>
#include <android/log.h>
#endif
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <fcntl.h>
#include <sstream>

#ifdef ANDROID
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "ProcessCpuTracker", __VA_ARGS__)
#else
#define LOGD printf
#endif

typedef struct _CpuInfo
{
    long userTime; // Unit: jiffies
    long niceTime;
    long systemTime;
    long idleTime;
    long ioWaitTime;
    long irqTime;
    long softIrqTime;
}CpuInfo;

// Return 0 means the end of buffer
static bool readLine(char* p, const char* end, char** next)
{
    if (p == NULL)
    {
        *next = NULL;
        return false;
    }

    while (*p != '\n' && p < end)
        ++p;

    if (*p == '\n')
    {// line break
        *p = '\0'; // Set to \0 to make a sub-sequence string
        *next = ++p;
        return true;
    }
    else
    {// end of buffer
        *next = NULL;
        return true;
    }
}

static std::vector<CpuInfo> readProcStat()
{
    std::vector<CpuInfo> cpuInfos;
    cpuInfos.reserve(13);
    char buffer[1024] = {0};

#ifdef ANDROID
    int fd = open("/proc/stat", O_RDONLY);

    if (fd < 0)
    {
        return cpuInfos;
    }

    const int len = read(fd, buffer, sizeof(buffer)-1);
    close(fd);

    if (len < 0) {
        LOGD("Unable to open process fd=%d", fd);
        return cpuInfos;
    }
    buffer[len] = 0;
#else
    FILE* fp = fopen("fonts/stat-huawei.txt", "rb");
    if (fp == NULL)
        return cpuInfos;
    fread(buffer, sizeof(buffer)-1, 1, fp);
    fclose(fp);
    size_t len = strlen(buffer);
#endif

    char* p = buffer;
    const char* end = p + len;
    char* next = NULL;
    int cpuIndex;
    const int COLUMN = sizeof(CpuInfo) / sizeof(long);
    size_t i = 0;

    while (readLine(p, end, &next))
    {
        // break if the line with no cpu prefix
        if (p[0] != 'c' || p[1] != 'p' || p[2] != 'u')
            break;

//        LOGD("%s\n", p);
        // Removes 'cpu%d' prefix
        p = p + 3;

        if (*p == ' ')
        { // The first line means the average cpu usage
            cpuIndex = 0;
        }
        else
        {
            cpuIndex = strtol(p, &p, 10) + 1;
        }

//        LOGD("cpu index: %d\n", cpuIndex);

        cpuInfos.resize(cpuIndex + 1);

        for (i = 0; i < COLUMN; ++i)
        {
            long value = strtol(p, &p, 10);
//            LOGD("%ld ", value);

            CpuInfo& info = cpuInfos[cpuIndex];
            long* e = (long*)&info + i;
            *e = value;
        }
//        LOGD("%s", "\n");

        p = next;
    }

    return cpuInfos;
}

void ProcessCpuTracker::update()
{
    static const int JIFFYMILLIS = 10;
    std::vector<CpuInfo> cpuInfos = readProcStat();
    if (!cpuInfos.empty())
    {
        if (_cpuTimeInfos.size() < cpuInfos.size())
        {
            _cpuTimeInfos.resize(cpuInfos.size());
        }

//        LOGD("cpuInfo size: %d", (int)cpuInfos.size());

        for (size_t i = 0, len = cpuInfos.size(); i < len; ++i)
        {
            CpuTimeInfo& cpuTimeInfo = _cpuTimeInfos[i];
            const CpuInfo& cpuInfo = cpuInfos[i];
            // Total user time is user + nice time.
            const long usertime = (cpuInfo.userTime + cpuInfo.niceTime) * JIFFYMILLIS;
            // Total system time is simply system time.
            const long systemtime = cpuInfo.systemTime * JIFFYMILLIS;
            // Total idle time is simply idle time.
            const long idletime = cpuInfo.idleTime * JIFFYMILLIS;
            // Total irq time is iowait + irq + softirq time.
            const long iowaittime = cpuInfo.ioWaitTime * JIFFYMILLIS;
            const long irqtime = cpuInfo.irqTime * JIFFYMILLIS;
            const long softirqtime = cpuInfo.softIrqTime * JIFFYMILLIS;
            // This code is trying to avoid issues with idle time going backwards,
            // but currently it gets into situations where it triggers most of the time. :(
            if (false || (usertime >= cpuTimeInfo.mBaseUserTime && systemtime >= cpuTimeInfo.mBaseSystemTime
                         && iowaittime >= cpuTimeInfo.mBaseIoWaitTime && irqtime >= cpuTimeInfo.mBaseIrqTime
                         && softirqtime >= cpuTimeInfo.mBaseSoftIrqTime && idletime >= cpuTimeInfo.mBaseIdleTime)) {
                cpuTimeInfo.mRelUserTime = usertime - cpuTimeInfo.mBaseUserTime;
                cpuTimeInfo.mRelSystemTime = systemtime - cpuTimeInfo.mBaseSystemTime;
                cpuTimeInfo.mRelIoWaitTime = iowaittime - cpuTimeInfo.mBaseIoWaitTime;
                cpuTimeInfo.mRelIrqTime = irqtime - cpuTimeInfo.mBaseIrqTime;
                cpuTimeInfo.mRelSoftIrqTime = softirqtime - cpuTimeInfo.mBaseSoftIrqTime;
                cpuTimeInfo.mRelIdleTime = idletime - cpuTimeInfo.mBaseIdleTime;
//                if (true) {
//                    LOGD("CPU%d, Total U: %ld, N:%ld S:%ld I:%ld W:%ld Q:%ld O:%ld\n",
//                         (int)i,
//                         cpuInfo.userTime,
//                         cpuInfo.niceTime,
//                         cpuInfo.systemTime,
//                         cpuInfo.idleTime,
//                         cpuInfo.ioWaitTime,
//                         cpuInfo.irqTime,
//                         cpuInfo.softIrqTime
//                         );
//                    LOGD("CPU%d, Rel U:%ld, S:%ld, I:%ld, Q:%ld\n",
//                        (int)i,
//                        cpuTimeInfo.mRelUserTime,
//                        cpuTimeInfo.mRelSystemTime,
//                        cpuTimeInfo.mRelIdleTime,
//                        cpuTimeInfo.mRelIrqTime
//                        );
//                    if (cpuTimeInfo.mRelUserTime < 0
//                        || cpuTimeInfo.mRelSystemTime < 0
//                        || cpuTimeInfo.mRelIdleTime < 0
//                        || cpuTimeInfo.mRelIrqTime < 0)
//                    {
//                        LOGD("CPU%d,base U:%ld, S:%ld, I:%ld, Q:%ld\n",
//                        (int)i,
//                        cpuTimeInfo.mBaseUserTime,
//                        cpuTimeInfo.mBaseSystemTime,
//                        cpuTimeInfo.mBaseIdleTime,
//                        cpuTimeInfo.mBaseIrqTime
//                        );
//                    }
//                }
                cpuTimeInfo.mBaseUserTime = usertime;
                cpuTimeInfo.mBaseSystemTime = systemtime;
                cpuTimeInfo.mBaseIoWaitTime = iowaittime;
                cpuTimeInfo.mBaseIrqTime = irqtime;
                cpuTimeInfo.mBaseSoftIrqTime = softirqtime;
                cpuTimeInfo.mBaseIdleTime = idletime;
            } else {

//                if (usertime < cpuTimeInfo.mBaseUserTime)
//                {
//                    LOGD("ERROR: usertime: %ld, base: %ld", usertime, cpuTimeInfo.mBaseUserTime);
//                }
//
//                if (systemtime < cpuTimeInfo.mBaseSystemTime)
//                {
//                    LOGD("ERROR: systemtime: %ld, base: %ld", systemtime, cpuTimeInfo.mBaseSystemTime);
//                }
//
//                if (iowaittime < cpuTimeInfo.mBaseIoWaitTime)
//                {
//                    LOGD("ERROR: iowaittime: %ld, base: %ld", iowaittime, cpuTimeInfo.mBaseIoWaitTime);
//                }
//
//                if (irqtime < cpuTimeInfo.mBaseIrqTime)
//                {
//                    LOGD("ERROR: irqtime: %ld, base: %ld", irqtime, cpuTimeInfo.mBaseIrqTime);
//                }
//
//                if (softirqtime < cpuTimeInfo.mBaseSoftIrqTime)
//                {
//                    LOGD("ERROR: softirqtime: %ld, base: %ld", softirqtime, cpuTimeInfo.mBaseSoftIrqTime);
//                }
//
//                if (idletime < cpuTimeInfo.mBaseIdleTime)
//                {
//                    LOGD("ERROR: idletime: %ld, base: %ld", idletime, cpuTimeInfo.mBaseIdleTime);
//                }

                if (usertime > 0 || idletime > 0)
                {
                    cpuTimeInfo.mBaseUserTime = usertime;
                    cpuTimeInfo.mBaseSystemTime = systemtime;
                    cpuTimeInfo.mBaseIoWaitTime = iowaittime;
                    cpuTimeInfo.mBaseIrqTime = irqtime;
                    cpuTimeInfo.mBaseSoftIrqTime = softirqtime;
                    cpuTimeInfo.mBaseIdleTime = idletime;
                }

                cpuTimeInfo.mRelUserTime = 0;
                cpuTimeInfo.mRelSystemTime = 0;
                cpuTimeInfo.mRelIoWaitTime = 0;
                cpuTimeInfo.mRelIrqTime = 0;
                cpuTimeInfo.mRelSoftIrqTime = 0;
                cpuTimeInfo.mRelIdleTime = 0;
                LOGD("CPU: %d, /proc/stats has gone backwards; skipping CPU update\n", (int)i);
            }
        }
    }
}

static long printRatio(std::stringstream& ss, long numerator, long denominator) {
    long hundreds = 0;
    if (denominator > 0)
    {
        long thousands = (numerator*1000)/denominator;
        hundreds = thousands/10;
        ss << hundreds;
        if (hundreds < 10) {
            long remainder = thousands - (hundreds*10);

            if (remainder != 0) {
                ss << '.';
                ss << remainder;
            }
        }
    }
    else
    {
        ss << '0';
    }
    ss << " ";

    return hundreds;
}

static long printProcessCPU(std::stringstream& ss, long totalTime, long user)
{   
    return printRatio(ss, user, totalTime);
}

void ProcessCpuTracker::printCurrentState()
{
    std::stringstream ss;
    long totalCpuUsage = 0;
    for (size_t i = 0, len = _cpuTimeInfos.size(); i < len; ++i)
    {
        CpuTimeInfo& cpuTimeInfo = _cpuTimeInfos[i];
        const long totalTime = cpuTimeInfo.mRelUserTime + cpuTimeInfo.mRelSystemTime + cpuTimeInfo.mRelIoWaitTime
        + cpuTimeInfo.mRelIrqTime + cpuTimeInfo.mRelSoftIrqTime + cpuTimeInfo.mRelIdleTime;

//        if (totalTime <= 0)
//        {
//            LOGD("cjh totalTime, i=%d: %ld mRelUserTime: %ld, mRelSystemTime: %ld, mRelIoWaitTime: %ld, mRelIrqTime: %ld, mRelSoftIrqTime: %ld, mRelIdleTime: %ld",
//                (int)i,
//                totalTime,
//                cpuTimeInfo.mRelUserTime,
//                cpuTimeInfo.mRelSystemTime,
//                cpuTimeInfo.mRelIoWaitTime,
//                cpuTimeInfo.mRelIrqTime,
//                cpuTimeInfo.mRelSoftIrqTime,
//                cpuTimeInfo.mRelIdleTime
//            );
//        }

        const long preCoreUsage = printProcessCPU(ss, totalTime, cpuTimeInfo.mRelUserTime);
        if (i > 0)
        {
            totalCpuUsage += preCoreUsage;
        }
    }

    ss << "T:";
    ss << totalCpuUsage;
    std::string str = ss.str();
    LOGD("CPU: %s", str.c_str());
}


