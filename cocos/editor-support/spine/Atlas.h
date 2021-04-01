/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated May 1, 2019. Replaces all prior versions.
 *
 * Copyright (c) 2013-2019, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS
 * INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef Spine_Atlas_h
#define Spine_Atlas_h

#include <spine/Vector.h>
#include <spine/Extension.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>
#include <spine/HasRendererObject.h>

namespace spine {
enum Format {
	Format_Alpha,
	Format_Intensity,
	Format_LuminanceAlpha,
	Format_RGB565,
	Format_RGBA4444,
	Format_RGB888,
	Format_RGBA8888
};

enum TextureFilter {
	TextureFilter_Unknown,
	TextureFilter_Nearest,
	TextureFilter_Linear,
	TextureFilter_MipMap,
	TextureFilter_MipMapNearestNearest,
	TextureFilter_MipMapLinearNearest,
	TextureFilter_MipMapNearestLinear,
	TextureFilter_MipMapLinearLinear
};

enum TextureWrap {
	TextureWrap_MirroredRepeat,
	TextureWrap_ClampToEdge,
	TextureWrap_Repeat
};

class SP_API AtlasPage : public SpineObject, public HasRendererObject {
public:
	String name;
	String texturePath;
	Format format;
	TextureFilter minFilter;
	TextureFilter magFilter;
	TextureWrap uWrap;
	TextureWrap vWrap;
	int width, height;

	explicit AtlasPage(const String &inName) : name(inName), format(Format_RGBA8888), minFilter(TextureFilter_Nearest),
		magFilter(TextureFilter_Nearest), uWrap(TextureWrap_ClampToEdge),
		vWrap(TextureWrap_ClampToEdge), width(0), height(0) {
	}
};

class SP_API AtlasRegion : public SpineObject {
public:
	AtlasPage *page;
	String name;
	int x, y, width, height;
	float u, v, u2, v2;
	float offsetX, offsetY;
	int originalWidth, originalHeight;
	int index;
	bool rotate;
	int degrees;
	Vector<int> splits;
	Vector<int> pads;
};

class TextureLoader;

class SP_API Atlas : public SpineObject {
public:
	Atlas(const String &path, TextureLoader *textureLoader, bool createTexture = true);

	Atlas(const char *data, int length, const char *dir, TextureLoader *textureLoader, bool createTexture = true);

	~Atlas();

	void flipV();

	/// Returns the first region found with the specified name. This method uses String comparison to find the region, so the result
	/// should be cached rather than calling this method multiple times.
	/// @return The region, or NULL.
	AtlasRegion *findRegion(const String &name);

	Vector<AtlasPage*> &getPages();

private:
	Vector<AtlasPage *> _pages;
	Vector<AtlasRegion *> _regions;
	TextureLoader *_textureLoader;

	void load(const char *begin, int length, const char *dir, bool createTexture);

	class Str {
	public:
		const char *begin;
		const char *end;
	};

	static void trim(Str *str);

	/// Tokenize string without modification. Returns 0 on failure
	static int readLine(const char **begin, const char *end, Str *str);

	/// Moves str->begin past the first occurence of c. Returns 0 on failure
	static int beginPast(Str *str, char c);

	/// Returns 0 on failure
	static int readValue(const char **begin, const char *end, Str *str);

	/// Returns the number of tuple values read (1, 2, 4, or 0 for failure)
	static int readTuple(const char **begin, const char *end, Str tuple[]);

	static char *mallocString(Str *str);

	static int indexOf(const char **array, int count, Str *str);

	static int equals(Str *str, const char *other);

	static int toInt(Str *str);

	static Atlas *abortAtlas(Atlas *atlas);
};
}

#endif /* Spine_Atlas_h */
