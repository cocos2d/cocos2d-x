/*
-----------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2006-2008 Henry van Merode

Usage of this program is free for non-commercial use and licensed under the
the terms of the GNU Lesser General Public License.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_AFFECTOR_TOKENS_H__
#define __PU_PARTICLE_AFFECTOR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** The AffectorTranslator parses 'affector' tokens
	*/
	class _ParticleUniverseExport AffectorTranslator : public ScriptTranslator
	{
		protected:
			ParticleAffector* mAffector;

		public:
			AffectorTranslator(void);
			virtual ~AffectorTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport ParticleAffectorWriter : public ScriptWriter
	{
		public:
			static const String KEYWORD_AFFECTOR;
			static const String KEYWORD_EXTERN;
			static const String KEYWORD_ENABLED;
			static const String KEYWORD_POSITION;
			static const String KEYWORD_MASS;
			static const String KEYWORD_EXCLUDE_EMITTER;
			static const String KEYWORD_SPECIALISATION;
			static const String KEYWORD_SPEC_DEFAULT;
			static const String KEYWORD_SPEC_TTL_INCREASE;
			static const String KEYWORD_SPEC_TTL_DECREASE;

			ParticleAffectorWriter(void) {};
			virtual ~ParticleAffectorWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
