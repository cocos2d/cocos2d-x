/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OPENSL_ES_ANDROID_H_
#define OPENSL_ES_ANDROID_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/* Android common types                                                      */
/*---------------------------------------------------------------------------*/

typedef sl_int64_t             SLAint64;           /* 64 bit signed integer */


/*---------------------------------------------------------------------------*/
/* Android Effect interface                                                  */
/*---------------------------------------------------------------------------*/

extern SLAPIENTRY const SLInterfaceID SL_IID_ANDROIDEFFECT;

/** Android Effect interface methods */

struct SLAndroidEffectItf_;
typedef const struct SLAndroidEffectItf_ * const * SLAndroidEffectItf;

struct SLAndroidEffectItf_ {

    SLresult (*CreateEffect) (SLAndroidEffectItf self,
            SLInterfaceID effectImplementationId);

    SLresult (*ReleaseEffect) (SLAndroidEffectItf self,
            SLInterfaceID effectImplementationId);

    SLresult (*SetEnabled) (SLAndroidEffectItf self,
            SLInterfaceID effectImplementationId,
            SLboolean enabled);

    SLresult (*IsEnabled) (SLAndroidEffectItf self,
            SLInterfaceID effectImplementationId,
            SLboolean *pEnabled);

    SLresult (*SendCommand) (SLAndroidEffectItf self,
            SLInterfaceID effectImplementationId,
            SLuint32 command,
            SLuint32 commandSize,
            void *pCommandData,
            SLuint32 *replySize,
            void *pReplyData);
};


/*---------------------------------------------------------------------------*/
/* Android Effect Send interface                                             */
/*---------------------------------------------------------------------------*/

extern SLAPIENTRY const SLInterfaceID SL_IID_ANDROIDEFFECTSEND;

/** Android Effect Send interface methods */

struct SLAndroidEffectSendItf_;
typedef const struct SLAndroidEffectSendItf_ * const * SLAndroidEffectSendItf;

struct SLAndroidEffectSendItf_ {
    SLresult (*EnableEffectSend) (
        SLAndroidEffectSendItf self,
        SLInterfaceID effectImplementationId,
        SLboolean enable,
        SLmillibel initialLevel
    );
    SLresult (*IsEnabled) (
        SLAndroidEffectSendItf self,
        SLInterfaceID effectImplementationId,
        SLboolean *pEnable
    );
    SLresult (*SetDirectLevel) (
        SLAndroidEffectSendItf self,
        SLmillibel directLevel
    );
    SLresult (*GetDirectLevel) (
        SLAndroidEffectSendItf self,
        SLmillibel *pDirectLevel
    );
    SLresult (*SetSendLevel) (
        SLAndroidEffectSendItf self,
        SLInterfaceID effectImplementationId,
        SLmillibel sendLevel
    );
    SLresult (*GetSendLevel)(
        SLAndroidEffectSendItf self,
        SLInterfaceID effectImplementationId,
        SLmillibel *pSendLevel
    );
};


/*---------------------------------------------------------------------------*/
/* Android Effect Capabilities interface                                     */
/*---------------------------------------------------------------------------*/

extern SLAPIENTRY const SLInterfaceID SL_IID_ANDROIDEFFECTCAPABILITIES;

/** Android Effect Capabilities interface methods */

struct SLAndroidEffectCapabilitiesItf_;
typedef const struct SLAndroidEffectCapabilitiesItf_ * const * SLAndroidEffectCapabilitiesItf;

struct SLAndroidEffectCapabilitiesItf_ {

    SLresult (*QueryNumEffects) (SLAndroidEffectCapabilitiesItf self,
            SLuint32 *pNumSupportedEffects);


    SLresult (*QueryEffect) (SLAndroidEffectCapabilitiesItf self,
            SLuint32 index,
            SLInterfaceID *pEffectType,
            SLInterfaceID *pEffectImplementation,
            SLchar *pName,
            SLuint16 *pNameSize);
};


/*---------------------------------------------------------------------------*/
/* Android Configuration interface                                           */
/*---------------------------------------------------------------------------*/
extern SLAPIENTRY const SLInterfaceID SL_IID_ANDROIDCONFIGURATION;

/** Android Configuration interface methods */

struct SLAndroidConfigurationItf_;
typedef const struct SLAndroidConfigurationItf_ * const * SLAndroidConfigurationItf;

struct SLAndroidConfigurationItf_ {

    SLresult (*SetConfiguration) (SLAndroidConfigurationItf self,
            const SLchar *configKey,
            const void *pConfigValue,
            SLuint32 valueSize);

    SLresult (*GetConfiguration) (SLAndroidConfigurationItf self,
           const SLchar *configKey,
           SLuint32 *pValueSize,
           void *pConfigValue
       );
};


/*---------------------------------------------------------------------------*/
/* Android Simple Buffer Queue Interface                                     */
/*---------------------------------------------------------------------------*/

extern SLAPIENTRY const SLInterfaceID SL_IID_ANDROIDSIMPLEBUFFERQUEUE;

struct SLAndroidSimpleBufferQueueItf_;
typedef const struct SLAndroidSimpleBufferQueueItf_ * const * SLAndroidSimpleBufferQueueItf;

typedef void (/*SLAPIENTRY*/ *slAndroidSimpleBufferQueueCallback)(
	SLAndroidSimpleBufferQueueItf caller,
	void *pContext
);

/** Android simple buffer queue state **/

typedef struct SLAndroidSimpleBufferQueueState_ {
	SLuint32	count;
	SLuint32	index;
} SLAndroidSimpleBufferQueueState;


struct SLAndroidSimpleBufferQueueItf_ {
	SLresult (*Enqueue) (
		SLAndroidSimpleBufferQueueItf self,
		const void *pBuffer,
		SLuint32 size
	);
	SLresult (*Clear) (
		SLAndroidSimpleBufferQueueItf self
	);
	SLresult (*GetState) (
		SLAndroidSimpleBufferQueueItf self,
		SLAndroidSimpleBufferQueueState *pState
	);
	SLresult (*RegisterCallback) (
		SLAndroidSimpleBufferQueueItf self,
		slAndroidSimpleBufferQueueCallback callback,
		void* pContext
	);
};


/*---------------------------------------------------------------------------*/
/* Android File Descriptor Data Locator                                      */
/*---------------------------------------------------------------------------*/

/** Addendum to Data locator macros  */
#define SL_DATALOCATOR_ANDROIDFD                ((SLuint32) 0x800007BC)

#define SL_DATALOCATOR_ANDROIDFD_USE_FILE_SIZE ((SLAint64) 0xFFFFFFFFFFFFFFFFll)

/** File Descriptor-based data locator definition, locatorType must be SL_DATALOCATOR_ANDROIDFD */
typedef struct SLDataLocator_AndroidFD_ {
    SLuint32        locatorType;
    SLint32         fd;
    SLAint64        offset;
    SLAint64        length;
} SLDataLocator_AndroidFD;


/*---------------------------------------------------------------------------*/
/* Android Android Simple Buffer Queue Data Locator                          */
/*---------------------------------------------------------------------------*/

/** Addendum to Data locator macros  */
#define SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE ((SLuint32) 0x800007BD)

/** BufferQueue-based data locator definition where locatorType must be SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE*/
typedef struct SLDataLocator_AndroidSimpleBufferQueue {
	SLuint32	locatorType;
	SLuint32	numBuffers;
} SLDataLocator_AndroidSimpleBufferQueue;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OPENSL_ES_ANDROID_H_ */
