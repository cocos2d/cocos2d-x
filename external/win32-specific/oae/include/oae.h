
/*

    Copyright (C) 2013, Anis A. Hireche. All rights reserved.

*/

#ifndef OAE_H
#define OAE_H

#define OAE_VERSION_MAJOR       1u
#define OAE_VERSION_MINOR       6u
#define OAE_VERSION_PATCH       0u
#define OAE_VERSION_BUILD       7u

#define OAE_VERSION_TOTAL       ((OAE_VERSION_MAJOR << 24u) | (OAE_VERSION_MINOR << 16u) | (OAE_VERSION_PATCH << 8u) | OAE_VERSION_BUILD)

namespace oae
{
    struct Listener
    {
        virtual                 ~Listener                                               ()  = 0 {};

        virtual float           GetDopplerFactor                                        ()  const = 0;
        virtual float           GetSpeedOfSound                                         ()  const = 0;

        virtual float           GetDistanceUnit                                         ()  const = 0;
        virtual float           GetMasterGain                                           ()  const = 0;

        virtual const char*     GetDistanceModel                                        ()  const = 0;
        virtual const char*     GetDistanceModelName                                    (   const unsigned int& index   ) const = 0;

        virtual bool            SetDopplerFactor                                        (   const float& factor         ) = 0;
        virtual bool            SetSpeedOfSound                                         (   const float& factor         ) = 0;
        virtual bool            SetDistanceUnit                                         (   const float& factor         ) = 0;

        virtual bool            SetMasterGain                                           (   const float& gain           ) = 0;
        virtual bool            SetDistanceModel                                        (   const char* name            ) = 0;

        virtual bool            SetPosition                                             (   const float* vector         ) = 0;
        virtual bool            SetVelocity                                             (   const float* vector         ) = 0;

        virtual bool            SetOrientation                                          (   float** matrix              ) const = 0;
        virtual bool            GetOrientation                                          (   float** matrix              ) const = 0;

        virtual bool            GetPosition                                             (   float* vector               ) const = 0;
        virtual bool            GetVelocity                                             (   float* vector               ) const = 0;
    };

    struct Screamer
    {
        virtual                 ~Screamer                                               ()  = 0 {};

        virtual bool            Seek                                                    (   const unsigned int& time    ) = 0;
        virtual bool            Loop                                                    (   const bool& mode            ) = 0;

        virtual bool            GetDirectFilterGainHighPassFilterAuto                   ()  const = 0;
        virtual bool            GetSendFilterGainHighPassFilterAuto                     ()  const = 0;

        virtual bool            GetSourceState                                          ()  const = 0;
        virtual bool            GetSourceRelative                                       ()  const = 0;

        virtual bool            GetReverbDecayHighPassFilterLimit                       ()  const = 0;
        virtual bool            GetEaxReverbDecayHighPassFilterLimit                    ()  const = 0;

        virtual bool            GetSendGainAuto                                         ()  const = 0;
        virtual bool            GetReverbEffectSendAuto                                 ()  const = 0;
        virtual bool            GetEaxReverbEffectSendAuto                              ()  const = 0;

        virtual bool            GetChorusEffectSendAuto                                 ()  const = 0;
        virtual bool            GetFlangerEffectSendAuto                                ()  const = 0;
        virtual bool            GetEchoEffectSendAuto                                   ()  const = 0;

        virtual bool            GetRingModulatorEffectSendAuto                          ()  const = 0;
        virtual bool            GetDistortionEffectSendAuto                             ()  const = 0;

        virtual bool            GetEqualizerEffectSendAuto                              ()  const = 0;
        virtual bool            GetCompressorEffectSendAuto                             ()  const = 0;
        virtual bool            GetAutoWahEffectSendAuto                                ()  const = 0;

        virtual bool            GetPitchShifterEffectSendAuto                           ()  const = 0;
        virtual bool            GetFrequencyShifterEffectSendAuto                       ()  const = 0;
        virtual bool            GetVocalMorpherEffectSendAuto                           ()  const = 0;

        virtual unsigned int    GetChorusWaveform                                       ()  const = 0;
        virtual unsigned int    GetFlangerWaveform                                      ()  const = 0;

        virtual unsigned int    GetRingModulatorWaveform                                ()  const = 0;
        virtual unsigned int    GetVocalMorpherWaveform                                 ()  const = 0;

        virtual unsigned int    GetFrequencyShifterLeftDirection                        ()  const = 0;
        virtual unsigned int    GetFrequencyShifterRightDirection                       ()  const = 0;

        virtual unsigned int    GetVocalMorpherFirstPhoneme                             ()  const = 0;
        virtual unsigned int    GetVocalMorpherSecondPhoneme                            ()  const = 0;

        virtual unsigned int    GetCurrentTime                                          ()  const = 0;
        virtual unsigned int    GetTotalLength                                          ()  const = 0;

        virtual unsigned int    GetCompressedCurrentPosition                            ()  const = 0;
        virtual unsigned int    GetCompressedTotalSize                                  ()  const = 0;

        virtual unsigned int    GetUncompressedCurrentPosition                          ()  const = 0;
        virtual unsigned int    GetUncompressedTotalSize                                ()  const = 0;

        virtual unsigned int    GetBitRate                                              ()  const = 0;
        virtual unsigned int    GetFrequencyRate                                        ()  const = 0;
        virtual unsigned int    GetChannelConfig                                        ()  const = 0;

        virtual int             GetPitchShifterCoarseTune                               ()  const = 0;
        virtual int             GetPitchShifterFineTune                                 ()  const = 0;

        virtual int             SetVocalMorpherPhonemeFirstCoarseTuning                 ()  const = 0;
        virtual int             SetVocalMorpherPhonemeSecondCoarseTuning                ()  const = 0;

        virtual float           GetPitchFactor                                          ()  const = 0;
        virtual float           GetRollOffFactor                                        ()  const = 0;

        virtual float           GetAirAbsorptionFactor                                  ()  const = 0;
        virtual float           GetRoomRollOffFactor                                    ()  const = 0;

        virtual float           GetChorusDepth                                          ()  const = 0;
        virtual float           GetChorusFeedback                                       ()  const = 0;

        virtual float           GetFlangerDepth                                         ()  const = 0;
        virtual float           GetFlangerFeedback                                      ()  const = 0;

        virtual float           GetEqualizerLowMidWidth                                 ()  const = 0;
        virtual float           GetEqualizerHighMidWidth                                ()  const = 0;

        virtual float           GetReverbDensity                                        ()  const = 0;
        virtual float           GetEaxReverbDensity                                     ()  const = 0;

        virtual float           GetReverbDiffusion                                      ()  const = 0;
        virtual float           GetEaxReverbDiffusion                                   ()  const = 0;

        virtual float           GetReverbDecayHighPassFilterRatio                       ()  const = 0;
        virtual float           GetEaxReverbDecayHighPassFilterRatio                    ()  const = 0;

        virtual float           GetEaxReverbDecayLowPassFilterRatio                     ()  const = 0;
        virtual float           GetEaxReverbEchoDepth                                   ()  const = 0;
        virtual float           GetEaxReverbModulationDepth                             ()  const = 0;

        virtual float           GetReverbRoomRollOffFactor                              ()  const = 0;
        virtual float           GetEaxReverbRoomRollOffFactor                           ()  const = 0;

        virtual float           GetEchoDamping                                          ()  const = 0;
        virtual float           GetEchoFeedback                                         ()  const = 0;
        virtual float           GetEchoSpread                                           ()  const = 0;

        virtual float           GetDistortionEdge                                       ()  const = 0;
        virtual float           GetAutoWahResonance                                     ()  const = 0;

        virtual float           GetReverbDecayTime                                      ()  const = 0;
        virtual float           GetEaxReverbDecayTime                                   ()  const = 0;

        virtual float           GetEaxReverbEchoTime                                    ()  const = 0;
        virtual float           GetEaxReverbModulationTime                              ()  const = 0;

        virtual float           GetReverbReflectionsDelay                               ()  const = 0;
        virtual float           GetEaxReverbReflectionsDelay                            ()  const = 0;

        virtual float           GetReverbLateDelay                                      ()  const = 0;
        virtual float           GetEaxReverbLateDelay                                   ()  const = 0;

        virtual float           GetChorusDelay                                          ()  const = 0;
        virtual float           GetFlangerDelay                                         ()  const = 0;

        virtual float           GetEchoDelay                                            ()  const = 0;
        virtual float           GetEchoLeftRightDelay                                   ()  const = 0;

        virtual float           GetAutoWahAttackTime                                    ()  const = 0;
        virtual float           GetAutoWahReleaseTime                                   ()  const = 0;

        virtual float           GetEaxReverbHighPassFilterReference                     ()  const = 0;
        virtual float           GetEaxReverbLowPassFilterReference                      ()  const = 0;

        virtual float           GetChorusRate                                           ()  const = 0;
        virtual float           GetFlangerRate                                          ()  const = 0;
        virtual float           GetVocalMorpherRate                                     ()  const = 0;

        virtual float           GetRingModulatorFrequency                               ()  const = 0;
        virtual float           GetRingModulatorHighPassFilterCutoff                    ()  const = 0;

        virtual float           GetDistortionLowPassFilterCutoff                        ()  const = 0;
        virtual float           GetDistortionEqualizationCenter                         ()  const = 0;
        virtual float           GetDistortionEqualizationBandwidth                      ()  const = 0;

        virtual float           GetEqualizerLowCutoff                                   ()  const = 0;
        virtual float           GetEqualizerHighCutoff                                  ()  const = 0;

        virtual float           GetEqualizerLowMidFrequency                             ()  const = 0;
        virtual float           GetEqualizerHighMidFrequency                            ()  const = 0;
        virtual float           GetFrequencyShifterFrequency                            ()  const = 0;

        virtual float           GetDistortionGain                                       ()  const = 0;
        virtual float           GetAutoWahPeakGain                                      ()  const = 0;

        virtual float           GetEqualizerLowGain                                     ()  const = 0;
        virtual float           GetEqualizerLowMidGain                                  ()  const = 0;

        virtual float           GetEqualizerHighMidGain                                 ()  const = 0;
        virtual float           GetEqualizerHighGain                                    ()  const = 0;

        virtual float           GetReverbGain                                           ()  const = 0;
        virtual float           GetEaxReverbGain                                        ()  const = 0;

        virtual float           GetReverbGainHighPassFilter                             ()  const = 0;
        virtual float           GetEaxReverbGainHighPassFilter                          ()  const = 0;
        virtual float           GetEaxReverbGainLowPassFilter                           ()  const = 0;

        virtual float           GetReverbLateGain                                       ()  const = 0;
        virtual float           GetEaxReverbLateGain                                    ()  const = 0;

        virtual float           GetReverbReflectionsGain                                ()  const = 0;
        virtual float           GetEaxReverbReflectionsGain                             ()  const = 0;

        virtual float           GetReverbAirAbsorptionGainHighPassFilter                ()  const = 0;
        virtual float           GetEaxReverbAirAbsorptionGainHighPassFilter             ()  const = 0;

        virtual float           GetReverbEffectGain                                     ()  const = 0;
        virtual float           GetEaxReverbEffectGain                                  ()  const = 0;

        virtual float           GetChorusEffectGain                                     ()  const = 0;
        virtual float           GetFlangerEffectGain                                    ()  const = 0;

        virtual float           GetEchoEffectGain                                       ()  const = 0;
        virtual float           GetRingModulatorEffectGain                              ()  const = 0;
        virtual float           GetDistortionEffectGain                                 ()  const = 0;

        virtual float           GetEqualizerEffectGain                                  ()  const = 0;
        virtual float           GetCompressorEffectGain                                 ()  const = 0;
        virtual float           GetAutoWahEffectGain                                    ()  const = 0;

        virtual float           GetPitchShifterEffectGain                               ()  const = 0;
        virtual float           GetFrequencyShifterEffectGain                           ()  const = 0;
        virtual float           GetVocalMorpherEffectGain                               ()  const = 0;

        virtual float           GetLowPassFilterGain                                    ()  const = 0;
        virtual float           GetLowPassFilterGainHighPassFilter                      ()  const = 0;

        virtual float           GetHighPassFilterGain                                   ()  const = 0;
        virtual float           GetHighPassFilterGainLowPassFilter                      ()  const = 0;

        virtual float           GetBandPassFilterGain                                   ()  const = 0;
        virtual float           GetBandPassFilterGainLowPassFilter                      ()  const = 0;
        virtual float           GetBandPassFilterGainHighPassFilter                     ()  const = 0;

        virtual float           GetOuterConeGainHighPassFilter                          ()  const = 0;
        virtual float           GetMinimumGain                                          ()  const = 0;
        virtual float           GetMaximumGain                                          ()  const = 0;

        virtual float           GetGain                                                 ()  const = 0;
        virtual float           GetOuterConeGain                                        ()  const = 0;

        virtual float           GetReferenceDistance                                    ()  const = 0;
        virtual float           GetMaximumDistance                                      ()  const = 0;

        virtual float           GetInnerConeAngle                                       ()  const = 0;
        virtual float           GetOuterConeAngle                                       ()  const = 0;

        virtual int             GetChorusPhase                                          ()  const = 0;
        virtual int             GetFlangerPhase                                         ()  const = 0;

        virtual bool            SetDirectFilterGainHighPassFilterAuto                   (   const bool& mode            ) = 0;
        virtual bool            SetSendFilterGainHighPassFilterAuto                     (   const bool& mode            ) = 0;

        virtual bool            SetSourceState                                          (   const bool& mode            ) = 0;
        virtual bool            SetSourceRelative                                       (   const bool& mode            ) = 0;

        virtual bool            SetReverbDecayHighPassFilterLimit                       (   const bool& mode            ) = 0;
        virtual bool            SetEaxReverbDecayHighPassFilterLimit                    (   const bool& mode            ) = 0;

        virtual bool            SetReverbEffect                                         (   const bool& mode            ) = 0;
        virtual bool            SetEaxReverbEffect                                      (   const bool& mode            ) = 0;

        virtual bool            SetChorusEffect                                         (   const bool& mode            ) = 0;
        virtual bool            SetFlangerEffect                                        (   const bool& mode            ) = 0;

        virtual bool            SetEchoEffect                                           (   const bool& mode            ) = 0;
        virtual bool            SetRingModulatorEffect                                  (   const bool& mode            ) = 0;
        virtual bool            SetDistortionEffect                                     (   const bool& mode            ) = 0;

        virtual bool            SetEqualizerEffect                                      (   const bool& mode            ) = 0;
        virtual bool            SetCompressorEffect                                     (   const bool& mode            ) = 0;
        virtual bool            SetAutoWahEffect                                        (   const bool& mode            ) = 0;

        virtual bool            SetPitchShifterEffect                                   (   const bool& mode            ) = 0;
        virtual bool            SetFrequencyShifterEffect                               (   const bool& mode            ) = 0;
        virtual bool            SetVocalMorpherEffect                                   (   const bool& mode            ) = 0;

        virtual bool            SetSendGainAuto                                         (   const bool& mode            ) = 0;
        virtual bool            SetReverbEffectSendAuto                                 (   const bool& mode            ) = 0;
        virtual bool            SetEaxReverbEffectSendAuto                              (   const bool& mode            ) = 0;

        virtual bool            SetChorusEffectSendAuto                                 (   const bool& mode            ) = 0;
        virtual bool            SetFlangerEffectSendAuto                                (   const bool& mode            ) = 0;
        virtual bool            SetEchoEffectSendAuto                                   (   const bool& mode            ) = 0;

        virtual bool            SetRingModulatorEffectSendAuto                          (   const bool& mode            ) = 0;
        virtual bool            SetDistortionEffectSendAuto                             (   const bool& mode            ) = 0;

        virtual bool            SetEqualizerEffectSendAuto                              (   const bool& mode            ) = 0;
        virtual bool            SetCompressorEffectSendAuto                             (   const bool& mode            ) = 0;
        virtual bool            SetAutoWahEffectSendAuto                                (   const bool& mode            ) = 0;

        virtual bool            SetPitchShifterEffectSendAuto                           (   const bool& mode            ) = 0;
        virtual bool            SetFrequencyShifterEffectSendAuto                       (   const bool& mode            ) = 0;
        virtual bool            SetVocalMorpherEffectSendAuto                           (   const bool& mode            ) = 0;

        virtual bool            SetChorusWaveform                                       (   const unsigned int& mode    ) = 0;
        virtual bool            SetFlangerWaveform                                      (   const unsigned int& mode    ) = 0;

        virtual bool            SetRingModulatorWaveform                                (   const unsigned int& mode    ) = 0;
        virtual bool            SetVocalMorpherWaveform                                 (   const unsigned int& mode    ) = 0;

        virtual bool            SetFrequencyShifterLeftDirection                        (   const unsigned int& mode    ) = 0;
        virtual bool            SetFrequencyShifterRightDirection                       (   const unsigned int& mode    ) = 0;

        virtual bool            SetVocalMorpherFirstPhoneme                             (   const unsigned int& mode    ) = 0;
        virtual bool            SetVocalMorpherSecondPhoneme                            (   const unsigned int& mode    ) = 0;

        virtual bool            SetPitchShifterCoarseTune                               (   const int& factor           ) = 0;
        virtual bool            SetPitchShifterFineTune                                 (   const int& factor           ) = 0;

        virtual bool            SetVocalMorpherPhonemeFirstCoarseTuning                 (   const int& factor           ) = 0;
        virtual bool            SetVocalMorpherPhonemeSecondCoarseTuning                (   const int& factor           ) = 0;

        virtual bool            SetPitchFactor                                          (   const float& factor         ) = 0;
        virtual bool            SetRollOffFactor                                        (   const float& factor         ) = 0;

        virtual bool            SetAirAbsorptionFactor                                  (   const float& factor         ) = 0;
        virtual bool            SetRoomRollOffFactor                                    (   const float& factor         ) = 0;

        virtual bool            SetChorusDepth                                          (   const float& factor         ) = 0;
        virtual bool            SetChorusFeedback                                       (   const float& factor         ) = 0;

        virtual bool            SetFlangerDepth                                         (   const float& factor         ) = 0;
        virtual bool            SetFlangerFeedback                                      (   const float& factor         ) = 0;

        virtual bool            SetEqualizerLowMidWidth                                 (   const float& factor         ) = 0;
        virtual bool            SetEqualizerHighMidWidth                                (   const float& factor         ) = 0;

        virtual bool            SetReverbDensity                                        (   const float& factor         ) = 0;
        virtual bool            SetEaxReverbDensity                                     (   const float& factor         ) = 0;

        virtual bool            SetReverbDiffusion                                      (   const float& factor         ) = 0;
        virtual bool            SetEaxReverbDiffusion                                   (   const float& factor         ) = 0;

        virtual bool            SetReverbDecayHighPassFilterRatio                       (   const float& factor         ) = 0;
        virtual bool            SetEaxReverbDecayHighPassFilterRatio                    (   const float& factor         ) = 0;

        virtual bool            SetEaxReverbDecayLowPassFilterRatio                     (   const float& factor         ) = 0;
        virtual bool            SetEaxReverbEchoDepth                                   (   const float& factor         ) = 0;
        virtual bool            SetEaxReverbModulationDepth                             (   const float& factor         ) = 0;

        virtual bool            SetReverbRoomRollOffFactor                              (   const float& factor         ) = 0;
        virtual bool            SetEaxReverbRoomRollOffFactor                           (   const float& factor         ) = 0;

        virtual bool            SetEchoDamping                                          (   const float& factor         ) = 0;
        virtual bool            SetEchoFeedback                                         (   const float& factor         ) = 0;
        virtual bool            SetEchoSpread                                           (   const float& factor         ) = 0;

        virtual bool            SetDistortionEdge                                       (   const float& factor         ) = 0;
        virtual bool            SetAutoWahResonance                                     (   const float& factor         ) = 0;

        virtual bool            SetReverbDecayTime                                      (   const float& time           ) = 0;
        virtual bool            SetEaxReverbDecayTime                                   (   const float& time           ) = 0;

        virtual bool            SetEaxReverbEchoTime                                    (   const float& time           ) = 0;
        virtual bool            SetEaxReverbModulationTime                              (   const float& time           ) = 0;

        virtual bool            SetReverbReflectionsDelay                               (   const float& time           ) = 0;
        virtual bool            SetEaxReverbReflectionsDelay                            (   const float& time           ) = 0;

        virtual bool            SetReverbLateDelay                                      (   const float& time           ) = 0;
        virtual bool            SetEaxReverbLateDelay                                   (   const float& time           ) = 0;

        virtual bool            SetChorusDelay                                          (   const float& time           ) = 0;
        virtual bool            SetFlangerDelay                                         (   const float& time           ) = 0;

        virtual bool            SetEchoDelay                                            (   const float& time           ) = 0;
        virtual bool            SetEchoLeftRightDelay                                   (   const float& time           ) = 0;

        virtual bool            SetAutoWahAttackTime                                    (   const float& time           ) = 0;
        virtual bool            SetAutoWahReleaseTime                                   (   const float& time           ) = 0;

        virtual bool            SetEaxReverbHighPassFilterReference                     (   const float& frequency      ) = 0;
        virtual bool            SetEaxReverbLowPassFilterReference                      (   const float& frequency      ) = 0;

        virtual bool            SetChorusRate                                           (   const float& frequency      ) = 0;
        virtual bool            SetFlangerRate                                          (   const float& frequency      ) = 0;
        virtual bool            SetVocalMorpherRate                                     (   const float& frequency      ) = 0;

        virtual bool            SetRingModulatorFrequency                               (   const float& frequency      ) = 0;
        virtual bool            SetRingModulatorHighPassFilterCutoff                    (   const float& frequency      ) = 0;

        virtual bool            SetDistortionLowPassFilterCutoff                        (   const float& frequency      ) = 0;
        virtual bool            SetDistortionEqualizationCenter                         (   const float& frequency      ) = 0;
        virtual bool            SetDistortionEqualizationBandwidth                      (   const float& frequency      ) = 0;

        virtual bool            SetEqualizerLowCutoff                                   (   const float& frequency      ) = 0;
        virtual bool            SetEqualizerHighCutoff                                  (   const float& frequency      ) = 0;

        virtual bool            SetEqualizerLowMidFrequency                             (   const float& frequency      ) = 0;
        virtual bool            SetEqualizerHighMidFrequency                            (   const float& frequency      ) = 0;
        virtual bool            SetFrequencyShifterFrequency                            (   const float& frequency      ) = 0;

        virtual bool            SetDistortionGain                                       (   const float& gain           ) = 0;
        virtual bool            SetAutoWahPeakGain                                      (   const float& gain           ) = 0;

        virtual bool            SetEqualizerLowGain                                     (   const float& gain           ) = 0;
        virtual bool            SetEqualizerLowMidGain                                  (   const float& gain           ) = 0;

        virtual bool            SetEqualizerHighMidGain                                 (   const float& gain           ) = 0;
        virtual bool            SetEqualizerHighGain                                    (   const float& gain           ) = 0;

        virtual bool            SetReverbGain                                           (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbGain                                        (   const float& gain           ) = 0;

        virtual bool            SetReverbGainHighPassFilter                             (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbGainHighPassFilter                          (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbGainLowPassFilter                           (   const float& gain           ) = 0;

        virtual bool            SetReverbLateGain                                       (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbLateGain                                    (   const float& gain           ) = 0;

        virtual bool            SetReverbReflectionsGain                                (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbReflectionsGain                             (   const float& gain           ) = 0;

        virtual bool            SetReverbAirAbsorptionGainHighPassFilter                (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbAirAbsorptionGainHighPassFilter             (   const float& gain           ) = 0;

        virtual bool            SetReverbEffectGain                                     (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbEffectGain                                  (   const float& gain           ) = 0;

        virtual bool            SetChorusEffectGain                                     (   const float& gain           ) = 0;
        virtual bool            SetFlangerEffectGain                                    (   const float& gain           ) = 0;

        virtual bool            SetEchoEffectGain                                       (   const float& gain           ) = 0;
        virtual bool            SetRingModulatorEffectGain                              (   const float& gain           ) = 0;
        virtual bool            SetDistortionEffectGain                                 (   const float& gain           ) = 0;

        virtual bool            SetEqualizerEffectGain                                  (   const float& gain           ) = 0;
        virtual bool            SetCompressorEffectGain                                 (   const float& gain           ) = 0;
        virtual bool            SetAutoWahEffectGain                                    (   const float& gain           ) = 0;

        virtual bool            SetPitchShifterEffectGain                               (   const float& gain           ) = 0;
        virtual bool            SetFrequencyShifterEffectGain                           (   const float& gain           ) = 0;
        virtual bool            SetVocalMorpherEffectGain                               (   const float& gain           ) = 0;

        virtual bool            SetDirectLowPassFilterGain                              (   const float& gain           ) = 0;
        virtual bool            SetDirectLowPassFilterGainHighPassFilter                (   const float& gain           ) = 0;

        virtual bool            SetDirectHighPassFilterGain                             (   const float& gain           ) = 0;
        virtual bool            SetDirectHighPassFilterGainLowPassFilter                (   const float& gain           ) = 0;

        virtual bool            SetDirectBandPassFilterGain                             (   const float& gain           ) = 0;
        virtual bool            SetDirectBandPassFilterGainLowPassFilter                (   const float& gain           ) = 0;
        virtual bool            SetDirectBandPassFilterGainHighPassFilter               (   const float& gain           ) = 0;

        virtual bool            SetReverbLowPassFilterGain                              (   const float& gain           ) = 0;
        virtual bool            SetReverbLowPassFilterGainHighPassFilter                (   const float& gain           ) = 0;

        virtual bool            SetReverbHighPassFilterGain                             (   const float& gain           ) = 0;
        virtual bool            SetReverbHighPassFilterGainLowPassFilter                (   const float& gain           ) = 0;

        virtual bool            SetReverbBandPassFilterGain                             (   const float& gain           ) = 0;
        virtual bool            SetReverbBandPassFilterGainLowPassFilter                (   const float& gain           ) = 0;
        virtual bool            SetReverbBandPassFilterGainHighPassFilter               (   const float& gain           ) = 0;

        virtual bool            SetEaxReverbLowPassFilterGain                           (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbLowPassFilterGainHighPassFilter             (   const float& gain           ) = 0;

        virtual bool            SetEaxReverbHighPassFilterGain                          (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbHighPassFilterGainLowPassFilter             (   const float& gain           ) = 0;

        virtual bool            SetEaxReverbBandPassFilterGain                          (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbBandPassFilterGainLowPassFilter             (   const float& gain           ) = 0;
        virtual bool            SetEaxReverbBandPassFilterGainHighPassFilter            (   const float& gain           ) = 0;

        virtual bool            SetChorusLowPassFilterGain                              (   const float& gain           ) = 0;
        virtual bool            SetChorusLowPassFilterGainHighPassFilter                (   const float& gain           ) = 0;

        virtual bool            SetChorusHighPassFilterGain                             (   const float& gain           ) = 0;
        virtual bool            SetChorusHighPassFilterGainLowPassFilter                (   const float& gain           ) = 0;

        virtual bool            SetChorusBandPassFilterGain                             (   const float& gain           ) = 0;
        virtual bool            SetChorusBandPassFilterGainLowPassFilter                (   const float& gain           ) = 0;
        virtual bool            SetChorusBandPassFilterGainHighPassFilter               (   const float& gain           ) = 0;

        virtual bool            SetFlangerLowPassFilterGain                             (   const float& gain           ) = 0;
        virtual bool            SetFlangerLowPassFilterGainHighPassFilter               (   const float& gain           ) = 0;

        virtual bool            SetFlangerHighPassFilterGain                            (   const float& gain           ) = 0;
        virtual bool            SetFlangerHighPassFilterGainLowPassFilter               (   const float& gain           ) = 0;

        virtual bool            SetFlangerBandPassFilterGain                            (   const float& gain           ) = 0;
        virtual bool            SetFlangerBandPassFilterGainLowPassFilter               (   const float& gain           ) = 0;
        virtual bool            SetFlangerBandPassFilterGainHighPassFilter              (   const float& gain           ) = 0;

        virtual bool            SetEchoLowPassFilterGain                                (   const float& gain           ) = 0;
        virtual bool            SetEchoLowPassFilterGainHighPassFilter                  (   const float& gain           ) = 0;

        virtual bool            SetEchoHighPassFilterGain                               (   const float& gain           ) = 0;
        virtual bool            SetEchoHighPassFilterGainLowPassFilter                  (   const float& gain           ) = 0;

        virtual bool            SetEchoBandPassFilterGain                               (   const float& gain           ) = 0;
        virtual bool            SetEchoBandPassFilterGainLowPassFilter                  (   const float& gain           ) = 0;
        virtual bool            SetEchoBandPassFilterGainHighPassFilter                 (   const float& gain           ) = 0;

        virtual bool            SetRingModulatorLowPassFilterGain                       (   const float& gain           ) = 0;
        virtual bool            SetRingModulatorLowPassFilterGainHighPassFilter         (   const float& gain           ) = 0;

        virtual bool            SetRingModulatorHighPassFilterGain                      (   const float& gain           ) = 0;
        virtual bool            SetRingModulatorHighPassFilterGainLowPassFilter         (   const float& gain           ) = 0;

        virtual bool            SetRingModulatorBandPassFilterGain                      (   const float& gain           ) = 0;
        virtual bool            SetRingModulatorBandPassFilterGainLowPassFilter         (   const float& gain           ) = 0;
        virtual bool            SetRingModulatorBandPassFilterGainHighPassFilter        (   const float& gain           ) = 0;

        virtual bool            SetDistortionLowPassFilterGain                          (   const float& gain           ) = 0;
        virtual bool            SetDistortionLowPassFilterGainHighPassFilter            (   const float& gain           ) = 0;

        virtual bool            SetDistortionHighPassFilterGain                         (   const float& gain           ) = 0;
        virtual bool            SetDistortionHighPassFilterGainLowPassFilter            (   const float& gain           ) = 0;

        virtual bool            SetDistortionBandPassFilterGain                         (   const float& gain           ) = 0;
        virtual bool            SetDistortionBandPassFilterGainLowPassFilter            (   const float& gain           ) = 0;
        virtual bool            SetDistortionBandPassFilterGainHighPassFilter           (   const float& gain           ) = 0;

        virtual bool            SetEqualizerLowPassFilterGain                           (   const float& gain           ) = 0;
        virtual bool            SetEqualizerLowPassFilterGainHighPassFilter             (   const float& gain           ) = 0;

        virtual bool            SetEqualizerHighPassFilterGain                          (   const float& gain           ) = 0;
        virtual bool            SetEqualizerHighPassFilterGainLowPassFilter             (   const float& gain           ) = 0;

        virtual bool            SetEqualizerBandPassFilterGain                          (   const float& gain           ) = 0;
        virtual bool            SetEqualizerBandPassFilterGainLowPassFilter             (   const float& gain           ) = 0;
        virtual bool            SetEqualizerBandPassFilterGainHighPassFilter            (   const float& gain           ) = 0;

        virtual bool            SetCompressorLowPassFilterGain                          (   const float& gain           ) = 0;
        virtual bool            SetCompressorLowPassFilterGainHighPassFilter            (   const float& gain           ) = 0;

        virtual bool            SetCompressorHighPassFilterGain                         (   const float& gain           ) = 0;
        virtual bool            SetCompressorHighPassFilterGainLowPassFilter            (   const float& gain           ) = 0;

        virtual bool            SetCompressorBandPassFilterGain                         (   const float& gain           ) = 0;
        virtual bool            SetCompressorBandPassFilterGainLowPassFilter            (   const float& gain           ) = 0;
        virtual bool            SetCompressorBandPassFilterGainHighPassFilter           (   const float& gain           ) = 0;

        virtual bool            SetAutoWahLowPassFilterGain                             (   const float& gain           ) = 0;
        virtual bool            SetAutoWahLowPassFilterGainHighPassFilter               (   const float& gain           ) = 0;

        virtual bool            SetAutoWahHighPassFilterGain                            (   const float& gain           ) = 0;
        virtual bool            SetAutoWahHighPassFilterGainLowPassFilter               (   const float& gain           ) = 0;

        virtual bool            SetAutoWahBandPassFilterGain                            (   const float& gain           ) = 0;
        virtual bool            SetAutoWahBandPassFilterGainLowPassFilter               (   const float& gain           ) = 0;
        virtual bool            SetAutoWahBandPassFilterGainHighPassFilter              (   const float& gain           ) = 0;

        virtual bool            SetPitchShifterLowPassFilterGain                        (   const float& gain           ) = 0;
        virtual bool            SetPitchShifterLowPassFilterGainHighPassFilter          (   const float& gain           ) = 0;

        virtual bool            SetPitchShifterHighPassFilterGain                       (   const float& gain           ) = 0;
        virtual bool            SetPitchShifterHighPassFilterGainLowPassFilter          (   const float& gain           ) = 0;

        virtual bool            SetPitchShifterBandPassFilterGain                       (   const float& gain           ) = 0;
        virtual bool            SetPitchShifterBandPassFilterGainLowPassFilter          (   const float& gain           ) = 0;
        virtual bool            SetPitchShifterBandPassFilterGainHighPassFilter         (   const float& gain           ) = 0;

        virtual bool            SetFrequencyShifterLowPassFilterGain                    (   const float& gain           ) = 0;
        virtual bool            SetFrequencyShifterLowPassFilterGainHighPassFilter      (   const float& gain           ) = 0;

        virtual bool            SetFrequencyShifterHighPassFilterGain                   (   const float& gain           ) = 0;
        virtual bool            SetFrequencyShifterHighPassFilterGainLowPassFilter      (   const float& gain           ) = 0;

        virtual bool            SetFrequencyShifterBandPassFilterGain                   (   const float& gain           ) = 0;
        virtual bool            SetFrequencyShifterBandPassFilterGainLowPassFilter      (   const float& gain           ) = 0;
        virtual bool            SetFrequencyShifterBandPassFilterGainHighPassFilter     (   const float& gain           ) = 0;

        virtual bool            SetVocalMorpherLowPassFilterGain                        (   const float& gain           ) = 0;
        virtual bool            SetVocalMorpherLowPassFilterGainHighPassFilter          (   const float& gain           ) = 0;

        virtual bool            SetVocalMorpherHighPassFilterGain                       (   const float& gain           ) = 0;
        virtual bool            SetVocalMorpherHighPassFilterGainLowPassFilter          (   const float& gain           ) = 0;

        virtual bool            SetVocalMorpherBandPassFilterGain                       (   const float& gain           ) = 0;
        virtual bool            SetVocalMorpherBandPassFilterGainLowPassFilter          (   const float& gain           ) = 0;
        virtual bool            SetVocalMorpherBandPassFilterGainHighPassFilter         (   const float& gain           ) = 0;

        virtual bool            SetOuterConeGainHighPassFilter                          (   const float& gain           ) = 0;
        virtual bool            SetMinimumGain                                          (   const float& gain           ) = 0;
        virtual bool            SetMaximumGain                                          (   const float& gain           ) = 0;

        virtual bool            SetGain                                                 (   const float& gain           ) = 0;
        virtual bool            SetOuterConeGain                                        (   const float& gain           ) = 0;

        virtual bool            SetReferenceDistance                                    (   const float& distance       ) = 0;
        virtual bool            SetMaximumDistance                                      (   const float& distance       ) = 0;

        virtual bool            SetInnerConeAngle                                       (   const float& angle          ) = 0;
        virtual bool            SetOuterConeAngle                                       (   const float& angle          ) = 0;

        virtual bool            SetChorusPhase                                          (   const int& angle            ) = 0;
        virtual bool            SetFlangerPhase                                         (   const int& angle            ) = 0;

        virtual bool            SetEaxReverbReflectionsPan                              (   const float* vector         ) = 0;
        virtual bool            SetEaxReverbLatePan                                     (   const float* vector         ) = 0;

        virtual bool            SetPosition                                             (   const float* vector         ) = 0;
        virtual bool            SetVelocity                                             (   const float* vector         ) = 0;
        virtual bool            SetConeDirection                                        (   const float* vector         ) = 0;

        virtual bool            GetEaxReverbReflectionsPan                              (   float* vector               ) const = 0;
        virtual bool            GetEaxReverbLatePan                                     (   float* vector               ) const = 0;

        virtual bool            GetPosition                                             (   float* vector               ) const = 0;
        virtual bool            GetVelocity                                             (   float* vector               ) const = 0;
        virtual bool            GetConeDirection                                        (   float* vector               ) const = 0;
    };

    struct Streamer
    {
        virtual                 ~Streamer                                               ()  = 0 {};

        virtual unsigned int    GetCurrentPosition                                      ()  = 0;
        virtual unsigned int    GetTotalSize                                            ()  = 0;

        virtual unsigned int    ReadStream                                              (   void* output,
                                                                                            const unsigned int& size    ) = 0;
        virtual void            SeekStream                                              (   const unsigned int& offset  ) = 0;
    };

    struct Renderer
    {
        virtual                 ~Renderer                                               ()  = 0 {};

        virtual Screamer*       GetScreamer                                             (   const char* name            ) = 0;
        virtual Screamer*       GetScreamer                                             (   Streamer* stream            ) = 0;
        virtual Listener*       GetListener                                             ()  = 0;

        virtual bool            ReleaseScreamer                                         (   Screamer* emitter           ) = 0;
        virtual bool            ReleaseListener                                         ()  = 0;
        virtual bool            ReleaseRenderer                                         ()  = 0;
    };

    const char*                 GetDriverInfo                                           (   const char* name            );
    const char*                 GetDriverName                                           (   const unsigned int& index   );
    const char*                 GetDeviceName                                           (   const unsigned int& index   );
    void                        GetFatalError                                           (   char** error                );

    unsigned int                GetTotalVersion                                         ();
    Renderer*                   GetRenderDevice                                         (   const char* name,
                                                                                            const unsigned int& rate    );
}

#endif
