/*
    This example builds the FSB's required for the Designer API examples.
*/

#include "fsbank.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *gTutorialFileNames[] =
{
    "../../fmoddesignerapi/examples/media/2011/2011_cycle_off.ogg",
    "../../fmoddesignerapi/examples/media/2011/2011_cycle_on.ogg",
    "../../fmoddesignerapi/examples/media/2011/2011_cycle_sustain01.ogg",
    "../../fmoddesignerapi/examples/media/2011/2011_cycle_sustain02.ogg",
    "../../fmoddesignerapi/examples/media/2011/2011_cycle_sustain_spawn_grain.ogg",
    "../../fmoddesignerapi/examples/media/2011/beep01.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call01.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call02.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call03.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call04.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call05.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call06.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call07.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call08.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call09.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call10.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call11.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call12.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call13.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call14.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call15.ogg",
    "../../fmoddesignerapi/examples/media/2011/bird_call16.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubble_burst01.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubble_burst02.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubble_burst03.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubble_burst04.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubble_burst05.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubble_burst06.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_close01.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_close02.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_close03.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_close04.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_close05.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_close06.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_small01.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_small02.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_small03.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_small04.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_small05.ogg",
    "../../fmoddesignerapi/examples/media/2011/bubbles_small06.ogg",
    "../../fmoddesignerapi/examples/media/2011/cricket_single_cycle.ogg",
    "../../fmoddesignerapi/examples/media/2011/crickets.ogg",
    "../../fmoddesignerapi/examples/media/2011/decending tone.ogg",
    "../../fmoddesignerapi/examples/media/2011/detonation01.ogg",
    "../../fmoddesignerapi/examples/media/2011/detonation02.ogg",
    "../../fmoddesignerapi/examples/media/2011/detonation03.ogg",
    "../../fmoddesignerapi/examples/media/2011/detonation04.ogg",
    "../../fmoddesignerapi/examples/media/2011/detonation05.ogg",
    "../../fmoddesignerapi/examples/media/2011/detonation06.ogg",
    "../../fmoddesignerapi/examples/media/2011/earth_debris01.ogg",
    "../../fmoddesignerapi/examples/media/2011/earth_debris02.ogg",
    "../../fmoddesignerapi/examples/media/2011/earth_debris03.ogg",
    "../../fmoddesignerapi/examples/media/2011/earth_debris04.ogg",
    "../../fmoddesignerapi/examples/media/2011/earth_debris05.ogg",
    "../../fmoddesignerapi/examples/media/2011/earth_debris06.ogg",
    "../../fmoddesignerapi/examples/media/2011/earth_debris07.ogg",
    "../../fmoddesignerapi/examples/media/2011/earth_debris08.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_long01.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_long02.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_long03.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_long04.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_long05.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_long06.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_short01.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_short02.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_short03.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_short04.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_short05.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_short06.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_small01.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_small02.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_small03.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_small04.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_small05.ogg",
    "../../fmoddesignerapi/examples/media/2011/flame_burst_small06.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_concrete_01.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_concrete_02.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_concrete_03.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_concrete_04.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_concrete_05.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_concrete_06.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_concrete_07.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_concrete_08.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_leaves01.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_leaves02.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_leaves03.ogg",
    "../../fmoddesignerapi/examples/media/2011/footsteps_leaves04.ogg",
    "../../fmoddesignerapi/examples/media/2011/frog01.ogg",
    "../../fmoddesignerapi/examples/media/2011/frog02.ogg",
    "../../fmoddesignerapi/examples/media/2011/frog03.ogg",
    "../../fmoddesignerapi/examples/media/2011/frog04.ogg",
    "../../fmoddesignerapi/examples/media/2011/glass_shard_smash01.ogg",
    "../../fmoddesignerapi/examples/media/2011/glass_shard_smash02.ogg",
    "../../fmoddesignerapi/examples/media/2011/glass_shard_smash03.ogg",
    "../../fmoddesignerapi/examples/media/2011/glass_shard_smash04.ogg",
    "../../fmoddesignerapi/examples/media/2011/glass_shard_smash05.ogg",
    "../../fmoddesignerapi/examples/media/2011/glass_shard_smash06.ogg",
    "../../fmoddesignerapi/examples/media/2011/glass_shard_smash07.ogg",
    "../../fmoddesignerapi/examples/media/2011/glass_shard_smash08.ogg",
    "../../fmoddesignerapi/examples/media/2011/metal_fragment01.ogg",
    "../../fmoddesignerapi/examples/media/2011/metal_fragment02.ogg",
    "../../fmoddesignerapi/examples/media/2011/metal_fragment03.ogg",
    "../../fmoddesignerapi/examples/media/2011/metal_fragment04.ogg",
    "../../fmoddesignerapi/examples/media/2011/metal_fragment05.ogg",
    "../../fmoddesignerapi/examples/media/2011/metal_fragment06.ogg",
    "../../fmoddesignerapi/examples/media/2011/metal_fragment07.ogg",
    "../../fmoddesignerapi/examples/media/2011/metal_fragment08.ogg",
    "../../fmoddesignerapi/examples/media/2011/rifle_blast01.ogg",
    "../../fmoddesignerapi/examples/media/2011/rifle_blast02.ogg",
    "../../fmoddesignerapi/examples/media/2011/rifle_blast03.ogg",
    "../../fmoddesignerapi/examples/media/2011/shotgun_blast01.ogg",
    "../../fmoddesignerapi/examples/media/2011/shotgun_blast02.ogg",
    "../../fmoddesignerapi/examples/media/2011/shotgun_blast03.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_large01.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_large02.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_large03.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_large04.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_large05.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_medium01.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_medium02.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_medium03.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_medium04.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_medium05.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_medium06.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_medium07.ogg",
    "../../fmoddesignerapi/examples/media/2011/splash_medium08.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/bow_still01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/bow_still02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/bow_wake01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/bow_wake02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/bow_wake03.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/buzz01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/buzz02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/cables_creak01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/cables_creak02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/cables_creak03.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/cables_creak04.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/cables_creak05.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/cables_creak06.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/cables_creak07.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/cables_creak08.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/clock_loop.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component03.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component04.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component05.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component06.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component07.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component08.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component09.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_component10.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/engine_load.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/hatch_door_open_close01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/hatch_door_open_close02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/hatch_door_open_close03.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/hatch_door_open_close04.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/hatch_door_open_close05.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact03.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact04.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact05.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact06.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact07.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact08.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact_heavy01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact_heavy02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact_heavy03.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact_heavy04.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact_heavy05.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact_heavy06.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/impact_heavy07.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_03.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_04.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_05.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_06.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_07.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_08.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_09.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_10.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_11.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_creak_light_12.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_screech01.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_screech02.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_screech03.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/metal_screech04.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_a.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_b.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_c.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_comma.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_d.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_e.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_f.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_g.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_h.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_i.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_j.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/morse_code_k.ogg",
    "../../fmoddesignerapi/examples/media/2011/submarine/sonar.ogg",
    "../../fmoddesignerapi/examples/media/2011/waves_submerged_01.ogg",
    "../../fmoddesignerapi/examples/media/2011/waves_submerged_02.ogg",
    "../../fmoddesignerapi/examples/media/2011/waves_submerged_03.ogg",
    "../../fmoddesignerapi/examples/media/2011/waves_submerged_04.ogg",
    "../../fmoddesignerapi/examples/media/2011/waves_submerged_05.ogg",
    "../../fmoddesignerapi/examples/media/2011/waves_submerged_06.ogg",
    "../../fmoddesignerapi/examples/media/2011/waves_submerged_07.ogg",
    "../../fmoddesignerapi/examples/media/2011/waves_submerged_08.ogg",
    "../../fmoddesignerapi/examples/media/ambient_one_four.ogg",
    "../../fmoddesignerapi/examples/media/ambient_one_loop.ogg",
    "../../fmoddesignerapi/examples/media/ambient_three.ogg",
    "../../fmoddesignerapi/examples/media/ambient_two.ogg",
    "../../fmoddesignerapi/examples/media/car/idle.ogg",
    "../../fmoddesignerapi/examples/media/car/offhigh.ogg",
    "../../fmoddesignerapi/examples/media/car/offlow.ogg",
    "../../fmoddesignerapi/examples/media/car/offmid.ogg",
    "../../fmoddesignerapi/examples/media/car/onhigh.ogg",
    "../../fmoddesignerapi/examples/media/car/onlow.ogg",
    "../../fmoddesignerapi/examples/media/car/onmid.ogg",
    "../../fmoddesignerapi/examples/media/drum-loop.ogg",
    "../../fmoddesignerapi/examples/media/interactive_music_1.ogg",
    "../../fmoddesignerapi/examples/media/interactive_music_2.ogg",
    "../../fmoddesignerapi/examples/media/interactive_music_3.ogg",
    "../../fmoddesignerapi/examples/media/max_play_behavior_four.ogg",
    "../../fmoddesignerapi/examples/media/max_play_behavior_one.ogg",
    "../../fmoddesignerapi/examples/media/max_play_behavior_three.ogg",
    "../../fmoddesignerapi/examples/media/max_play_behavior_two.ogg",
    "../../fmoddesignerapi/examples/media/music/excited.ogg",
    "../../fmoddesignerapi/examples/media/music/flsh-idle-01.ogg",
    "../../fmoddesignerapi/examples/media/music/flsh-idle-02.ogg",
    "../../fmoddesignerapi/examples/media/music/flsh-idle-03.ogg",
    "../../fmoddesignerapi/examples/media/music/flsh-idle-04.ogg",
    "../../fmoddesignerapi/examples/media/music/flsh-idle-05.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-bass-a.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-drums-a.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-drums-b.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-drums-c.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-drums-d.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-a.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-alt-a.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-alt-b.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-alt-c.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-alt-d.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-b.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-c.ogg",
    "../../fmoddesignerapi/examples/media/music/layer-guitar-d.ogg",
    "../../fmoddesignerapi/examples/media/music/relaxed.ogg",
    "../../fmoddesignerapi/examples/media/music/state-idle-01.ogg",
    "../../fmoddesignerapi/examples/media/music/state-idle-02.ogg",
    "../../fmoddesignerapi/examples/media/music/state-idle-03.ogg",
    "../../fmoddesignerapi/examples/media/music/state-idle-fadeout.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-01a.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-01b.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-02a.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-02b.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-finish.ogg",
    "../../fmoddesignerapi/examples/media/music/state-race-start.ogg",
    "../../fmoddesignerapi/examples/media/note.ogg",
    "../../fmoddesignerapi/examples/media/onefootstep.wav",
    "../../fmoddesignerapi/examples/media/sequence-end.ogg",
    "../../fmoddesignerapi/examples/media/sequence-four.ogg",
    "../../fmoddesignerapi/examples/media/sequence-one.ogg",
    "../../fmoddesignerapi/examples/media/sequence-start.ogg",
    "../../fmoddesignerapi/examples/media/sequence-three.ogg",
    "../../fmoddesignerapi/examples/media/sequence-two.ogg",
};

const char *gStreamingFileNames[] =
{
    "../../fmoddesignerapi/examples/media/interactive_music_6channel.ogg"
};

const unsigned int gNumTutorialFileNames  = sizeof(gTutorialFileNames) / sizeof(char *);
const unsigned int gNumStreamingFileNames = sizeof(gStreamingFileNames) / sizeof(char *);

#define CHECK_RESULT(_x) { FSBANK_RESULT _result = (_x); if (_result != FSBANK_OK) { return _result; } } 

FSBANK_RESULT printErrors(const FSBANK_SUBSOUND *subSounds)
{
    FSBANK_RESULT result                    = FSBANK_OK;
    const         FSBANK_PROGRESSITEM *item = NULL;

    printf("Build Error!\n");

    do
    {
        result = FSBank_FetchNextProgressItem(&item);
        CHECK_RESULT(result);

        if (item)
        {
            if (item->state == FSBANK_STATE_FAILED)
            {
                const FSBANK_STATEDATA_FAILED *failedStateData = (const FSBANK_STATEDATA_FAILED *)item->stateData;
                printf("Error: %s -- \"%s\"\n", failedStateData->errorString, item->subSoundIndex < 0 ? "System" : subSounds[item->subSoundIndex].fileNames[0]);
            }

            result = FSBank_ReleaseProgressItem(item);
            CHECK_RESULT(result);
        }
    } while (item != NULL);

    return FSBANK_OK;
}


FSBANK_RESULT buildBank(const char **fileNames, unsigned int numFileNames, const char *outputFileName)
{
    FSBANK_RESULT    result    = FSBANK_OK;
    FSBANK_SUBSOUND *subSounds = (FSBANK_SUBSOUND *)alloca(numFileNames * sizeof(FSBANK_SUBSOUND));

    for (unsigned int i = 0; i < numFileNames; i++)
    {
        memset(&subSounds[i], 0, sizeof(FSBANK_SUBSOUND));

        subSounds[i].fileNames          = &fileNames[i];
        subSounds[i].numFileNames       = 1;
        subSounds[i].modeFlags          = FSBANK_MODE_DEFAULT; 
        subSounds[i].overrideFlags      = FSBANK_BUILD_DEFAULT;
        subSounds[i].overrideQuality    = 0;
        subSounds[i].desiredSampleRate  = 0;
    }

    printf("Building %s...\n", outputFileName);

    result = FSBank_Build(subSounds, numFileNames, FSBANK_FORMAT_MP3, FSBANK_BUILD_DEFAULT | FSBANK_BUILD_DONTLOOP, 0, NULL, outputFileName);
    if (result != FSBANK_OK)
    {
        printErrors(subSounds);
        return result;
    }

    printf("done.\n");
    return FSBANK_OK;
}


int main(void)
{
    FSBANK_RESULT result = FSBANK_OK;

    result = FSBank_Init(FSBANK_FSBVERSION_FSB4, FSBANK_INIT_NORMAL | FSBANK_INIT_GENERATEPROGRESSITEMS, 2, NULL);
    CHECK_RESULT(result);

    result = buildBank(gTutorialFileNames, gNumTutorialFileNames, "tutorial_bank.fsb");
    CHECK_RESULT(result);

    result = buildBank(gStreamingFileNames, gNumStreamingFileNames, "streaming_bank.fsb");
    CHECK_RESULT(result);

    result = FSBank_Release();
    CHECK_RESULT(result);

    return FSBANK_OK;
}

