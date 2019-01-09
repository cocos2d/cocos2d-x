/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef Spine_EventData_h
#define Spine_EventData_h

#include <spine/SpineObject.h>
#include <spine/SpineString.h>

namespace spine {
/// Stores the setup pose values for an Event.
class SP_API EventData : public SpineObject {
	friend class SkeletonBinary;

	friend class SkeletonJson;

	friend class Event;

public:
	explicit EventData(const String &name);

	/// The name of the event, which is unique within the skeleton.
	const String &getName() const;

	int getIntValue();

	void setIntValue(int inValue);

	float getFloatValue();

	void setFloatValue(float inValue);

	const String &getStringValue();

	void setStringValue(const String &inValue);

	const String &getAudioPath();

	void setAudioPath(const String &inValue);

	float getVolume();

	void setVolume(float inValue);

	float getBalance();

	void setBalance(float inValue);

private:
	const String _name;
	int _intValue;
	float _floatValue;
	String _stringValue;
	String _audioPath;
	float _volume;
	float _balance;
};
}

#endif /* Spine_EventData_h */
