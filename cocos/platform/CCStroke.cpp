#include "platform/CCStroke.h"

#include "platform/CCStrokeScan.h"

#include "base/ccTypes.h"

#include <cstdint>
#include <cassert>
#include <algorithm>

namespace cocos2d
{
    namespace detail
    {
        static void transparentStroke
        ( unsigned char*& src, int& width, int& height,
          const FontStroke& stroke );

        static void convolutionFull
        ( unsigned char*& src, int& width, int& height,
          const FontStroke& stroke );

        static int getStrokeSize( const FontStroke& stroke );
        
        static std::unique_ptr< std::uint8_t[] > buildMatrix
        ( std::size_t matrixWidth );
    }
}

void cocos2d::drawStroke
( unsigned char*& src, int& width, int& height, const FontStroke& stroke )
{
    if ( stroke._strokeAlpha == 0 )
        detail::transparentStroke( src, width, height, stroke );
    else
        detail::convolutionFull( src, width, height, stroke );
}

static void cocos2d::detail::transparentStroke
( unsigned char*& src, int& width, int& height, const FontStroke& stroke )
{
    const int strokeSize( getStrokeSize( stroke ) );

    if ( ( strokeSize <= 0 ) || !stroke._strokeEnabled )
        return;

    const int destWidth( width + strokeSize * 2 );
    const int destHeight( height + strokeSize * 2 );
    static constexpr int bpp( 4 );
    const int lineLength( destWidth * bpp );
    const std::size_t destSize
        ( sizeof( unsigned char ) * lineLength * destHeight );
    unsigned char* dest( static_cast< unsigned char* >( malloc( destSize ) ) );

    std::fill( dest, dest + strokeSize * lineLength, 0 );
    std::fill
        ( dest + ( destHeight - strokeSize ) * lineLength, dest + destSize, 0 );
    
    for ( int y( strokeSize ); y != destHeight - strokeSize; ++y )
    {
        unsigned char* const lineBegin( dest + y * lineLength );
        std::fill( lineBegin, lineBegin + strokeSize * bpp, 0 );

        unsigned char* const lineEnd( lineBegin + lineLength );
        std::fill( lineEnd - strokeSize * bpp, lineEnd, 0 );
        
        for ( int x( strokeSize ); x != destWidth - strokeSize; ++x )
        {
            const std::size_t i( ( y - strokeSize ) * width + x - strokeSize );
            const std::uint32_t srcColor
                ( reinterpret_cast< std::uint32_t*>( src )[ i ] );

            const std::size_t j( y * destWidth + x );
            std::uint32_t&  destColor
                ( *reinterpret_cast< std::uint32_t* >( &dest[ j * bpp ] ) );
            
            destColor = srcColor;
        }
    }

    std::swap( dest, src );
    free( dest );

    width = destWidth;
    height = destHeight;
}

static void cocos2d::detail::convolutionFull
( unsigned char*& src, int& width, int& height, const FontStroke& stroke )
{
    const int strokeSize( getStrokeSize( stroke ) );
    
    if ( ( strokeSize <= 0 ) || !stroke._strokeEnabled )
        return;

    const std::size_t matrixWidth( 2 * strokeSize + 1 );

    const std::unique_ptr< std::uint8_t[] > matrix
        ( buildMatrix( matrixWidth ) );

    detail::StrokeScan scanner
        ( matrix.get(), matrixWidth, src, width, height, stroke, strokeSize );
    scanner.run();
}

static int cocos2d::detail::getStrokeSize( const FontStroke& stroke )
{
    return std::ceil( stroke._strokeSize );
}

static std::unique_ptr< std::uint8_t[] >
cocos2d::detail::buildMatrix( std::size_t matrixWidth )
{
    const int matrixHalfWidth( matrixWidth / 2 );
    const std::size_t matrixSize( matrixWidth * matrixWidth );
    std::unique_ptr< std::uint8_t[] > result( new std::uint8_t[ matrixSize ] );

    for ( std::size_t i( 0 ); i != matrixSize; ++i )
    {
        const int x( i % matrixWidth );
        const int y( i / matrixWidth );

        const int dx( x - matrixHalfWidth );
        const int dy( y - matrixHalfWidth );

        if ( std::sqrt( dx * dx + dy * dy ) <= matrixHalfWidth )
            result[ i ] = 1;
        else
            result[ i ] = 0;
    }

    return result;
}
