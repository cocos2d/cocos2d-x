/***************************************************************************/
/*                                                                         */
/*  ttsubpix.c                                                             */
/*                                                                         */
/*    TrueType Subpixel Hinting.                                           */
/*                                                                         */
/*  Copyright 2010-2012 by                                                 */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/

#include <ft2build.h>
#include FT_INTERNAL_DEBUG_H
#include FT_INTERNAL_CALC_H
#include FT_INTERNAL_STREAM_H
#include FT_INTERNAL_SFNT_H
#include FT_TRUETYPE_TAGS_H
#include FT_OUTLINE_H

#include "ttsubpix.h"


#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING

  FT_LOCAL_DEF( FT_Bool )
  is_member_of_family_class( const FT_String*  detected_font_name,
                             const FT_String*  rule_font_name )
  {
    FT_UInt  i, j;


    /* Does font name match rule family? */
    if ( strcmp( detected_font_name, rule_font_name ) == 0 )
      return TRUE;

    /* Is font name a wildcard ""? */
    if ( strcmp( rule_font_name, "" ) == 0 )
      return TRUE;

    /* Is font name contained in a class list? */
    for ( i = 0; i < FAMILY_CLASS_RULES_SIZE; i++ )
    {
      if ( strcmp( FAMILY_CLASS_Rules[i].name, rule_font_name ) == 0 )
      {
        for ( j = 0; j < MAX_CLASS_MEMBERS; j++ )
        {
          if ( strcmp( FAMILY_CLASS_Rules[i].member[j], "" ) == 0 )
            continue;
          if ( strcmp( FAMILY_CLASS_Rules[i].member[j],
                       detected_font_name ) == 0 )
            return TRUE;
        }
      }
    }

    return FALSE;
  }


  FT_LOCAL_DEF( FT_Bool )
  is_member_of_style_class( const FT_String*  detected_font_style,
                            const FT_String*  rule_font_style )
  {
    FT_UInt  i, j;


    /* Does font style match rule style? */
    if ( strcmp( detected_font_style, rule_font_style ) == 0 )
      return TRUE;

    /* Is font style a wildcard ""? */
    if ( strcmp( rule_font_style, "" ) == 0 )
      return TRUE;

    /* Is font style contained in a class list? */
    for ( i = 0; i < STYLE_CLASS_RULES_SIZE; i++ )
    {
      if ( strcmp( STYLE_CLASS_Rules[i].name, rule_font_style ) == 0 )
      {
        for ( j = 0; j < MAX_CLASS_MEMBERS; j++ )
        {
          if ( strcmp( STYLE_CLASS_Rules[i].member[j], "" ) == 0 )
            continue;
          if ( strcmp( STYLE_CLASS_Rules[i].member[j],
                       detected_font_style ) == 0 )
            return TRUE;
        }
      }
    }

    return FALSE;
  }


  FT_LOCAL_DEF( FT_Bool )
  sph_test_tweak( TT_Face         face,
                  FT_String*      family,
                  FT_UInt         ppem,
                  FT_String*      style,
                  FT_UInt         glyph_index,
                  SPH_TweakRule*  rule,
                  FT_UInt         num_rules )
  {
    FT_UInt  i;


    /* rule checks may be able to be optimized further */
    for ( i = 0; i < num_rules; i++ )
    {
      if ( family                                                   &&
           ( is_member_of_family_class ( family, rule[i].family ) ) )
        if ( rule[i].ppem == 0    ||
             rule[i].ppem == ppem )
          if ( style                                             &&
               is_member_of_style_class ( style, rule[i].style ) )
            if ( rule[i].glyph == 0                                ||
                 FT_Get_Char_Index( (FT_Face)face,
                                    rule[i].glyph ) == glyph_index )
        return TRUE;
    }

    return FALSE;
  }


  FT_LOCAL_DEF( FT_UInt )
  scale_test_tweak( TT_Face         face,
                    FT_String*      family,
                    FT_UInt         ppem,
                    FT_String*      style,
                    FT_UInt         glyph_index,
                    SPH_ScaleRule*  rule,
                    FT_UInt         num_rules )
  {
    FT_UInt  i;


    /* rule checks may be able to be optimized further */
    for ( i = 0; i < num_rules; i++ )
    {
      if ( family                                                   &&
           ( is_member_of_family_class ( family, rule[i].family ) ) )
        if ( rule[i].ppem == 0    ||
             rule[i].ppem == ppem )
          if ( style                                            &&
               is_member_of_style_class( style, rule[i].style ) )
            if ( rule[i].glyph == 0                                ||
                 FT_Get_Char_Index( (FT_Face)face,
                                    rule[i].glyph ) == glyph_index )
        return rule[i].scale;
    }

    return 1000;
  }


#define TWEAK_RULES( x )                                       \
  if ( sph_test_tweak( face, family, ppem, style, glyph_index, \
                       x##_Rules, x##_RULES_SIZE ) )           \
    loader->exec->sph_tweak_flags |= SPH_TWEAK_##x;

#define TWEAK_RULES_EXCEPTIONS( x )                                        \
  if ( sph_test_tweak( face, family, ppem, style, glyph_index,             \
                       x##_Rules_Exceptions, x##_RULES_EXCEPTIONS_SIZE ) ) \
    loader->exec->sph_tweak_flags &= ~SPH_TWEAK_##x;


  FT_LOCAL_DEF( void )
  sph_set_tweaks( TT_Loader  loader,
                  FT_UInt    glyph_index )
  {
    TT_Face     face   = (TT_Face)loader->face;
    FT_String*  family = face->root.family_name;
    int         ppem   = loader->size->metrics.x_ppem;
    FT_String*  style  = face->root.style_name;


    /* don't apply rules if style isn't set */
    if ( !face->root.style_name )
      return;

#ifdef SPH_DEBUG_MORE_VERBOSE
    printf( "%s,%d,%s,%c=%d ",
            family, ppem, style, glyph_index, glyph_index );
#endif

    TWEAK_RULES( PIXEL_HINTING );

    if ( loader->exec->sph_tweak_flags & SPH_TWEAK_PIXEL_HINTING )
    {
      loader->exec->ignore_x_mode = FALSE;
      return;
    }

    TWEAK_RULES( ALLOW_X_DMOVE );
    TWEAK_RULES( ALLOW_X_DMOVEX );
    TWEAK_RULES( ALLOW_X_MOVE_ZP2 );
    TWEAK_RULES( ALWAYS_DO_DELTAP );
    TWEAK_RULES( ALWAYS_SKIP_DELTAP );
    TWEAK_RULES( DEEMBOLDEN );
    TWEAK_RULES( DELTAP_SKIP_EXAGGERATED_VALUES );
    TWEAK_RULES( DO_SHPIX );
    TWEAK_RULES( EMBOLDEN );
    TWEAK_RULES( MIAP_HACK );
    TWEAK_RULES( NORMAL_ROUND );
    TWEAK_RULES( NO_ALIGNRP_AFTER_IUP );
    TWEAK_RULES( NO_CALL_AFTER_IUP );
    TWEAK_RULES( NO_DELTAP_AFTER_IUP );
    TWEAK_RULES( RASTERIZER_35 );
    TWEAK_RULES( SKIP_INLINE_DELTAS );
    TWEAK_RULES( SKIP_IUP );
    TWEAK_RULES( MIRP_CVT_ZERO );

    TWEAK_RULES( SKIP_OFFPIXEL_Y_MOVES );
    TWEAK_RULES_EXCEPTIONS( SKIP_OFFPIXEL_Y_MOVES );

    TWEAK_RULES( SKIP_NONPIXEL_Y_MOVES );
    TWEAK_RULES_EXCEPTIONS( SKIP_NONPIXEL_Y_MOVES );

    TWEAK_RULES( ROUND_NONPIXEL_Y_MOVES );
    TWEAK_RULES_EXCEPTIONS( ROUND_NONPIXEL_Y_MOVES );

    if ( loader->exec->sph_tweak_flags & SPH_TWEAK_RASTERIZER_35 )
      loader->exec->rasterizer_version = 35;
    else
      loader->exec->rasterizer_version = SPH_OPTION_SET_RASTERIZER_VERSION;

    /* re-execute fpgm always to avoid problems */
    loader->exec->size->cvt_ready = FALSE;
    tt_size_ready_bytecode( loader->exec->size,
                            FT_BOOL( loader->load_flags & FT_LOAD_PEDANTIC ) );

    if ( IS_HINTED( loader->load_flags ) )
    {
      TWEAK_RULES( TIMES_NEW_ROMAN_HACK );
      TWEAK_RULES( COURIER_NEW_2_HACK );
    }

    if ( sph_test_tweak( face, family, ppem, style, glyph_index,
           COMPATIBILITY_MODE_Rules, COMPATIBILITY_MODE_RULES_SIZE ) )
    {
      loader->exec->compatibility_mode |= TRUE;
      loader->exec->ignore_x_mode      |= TRUE;
    }
    else
      loader->exec->compatibility_mode &= FALSE;

    if ( IS_HINTED( loader->load_flags ) )
    {
      if ( sph_test_tweak( face, family, ppem, style, glyph_index,
             COMPATIBLE_WIDTHS_Rules, COMPATIBLE_WIDTHS_RULES_SIZE ) )
        loader->exec->compatible_widths |= TRUE;
    }
  }

#endif /* TT_CONFIG_OPTION_SUBPIXEL_HINTING */


/* END */
