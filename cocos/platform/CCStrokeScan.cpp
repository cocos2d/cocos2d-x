#include "platform/CCStrokeScan.h"

#include "base/ccTypes.h"

#include <cassert>
#include <algorithm>

namespace cocos2d
{
    namespace detail
    {
        class LineBounds
        {
        public:
            LineBounds( std::size_t matrixWidth, int destWidth );

            void queueStart( int x );
            void queueEnd( int x );

            int getStart();
            int getEnd();

            void roll();

        private:
            std::vector< int > starts;
            std::vector< int > ends;
        };
        
        class MatrixResult
        {
        public:
            MatrixResult();
            
            unsigned int nonZeroCount;
            unsigned int weightedAlpha;
        };

        static std::uint32_t blend
        ( std::uint32_t c0, std::uint32_t c1, std::uint32_t a1 );

        static std::uint32_t colorA( std::uint32_t c );
        static std::uint32_t colorB( std::uint32_t c );
        static std::uint32_t colorG( std::uint32_t c );
        static std::uint32_t colorR( std::uint32_t c );

        static std::uint32_t toColor
        ( std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a );

        static std::uint32_t getColorAt
        ( unsigned char* src, int width, int height, int x, int y );

        static MatrixResult applyMatrix
        ( const std::uint8_t* matrix, std::size_t matrixWidth,
          unsigned char* src, int srcx, int srcy, int width, int height );

        static constexpr std::uint32_t fullAlphaSquared = 65025;
    }
}

enum class cocos2d::detail::StrokeScan::Progress
{
    jump,
    forward,
    rewind
};
    
cocos2d::detail::StrokeScan::StrokeScan
( std::uint8_t* matrix, std::size_t matrixWidth, unsigned char*& src,
  int& width, int& height, const FontStroke& stroke, int strokeSize )
    : _matrix( matrix ),
      _matrixWidth( matrixWidth ),
      _src( src ),
      _width( width ),
      _height( height ),
      _stroke( stroke ),
      _strokeSize( strokeSize ),
      _destWidth( width + strokeSize * 2 ),
      _destHeight( height + strokeSize * 2 ),
      _dest
      ( static_cast< unsigned char* >
        ( malloc( sizeof( unsigned char ) * _destWidth * _destHeight * 4 ) ) ),
      _strokeColor
      ( toColor
        ( stroke._strokeColor.r * stroke._strokeAlpha / 255,
          stroke._strokeColor.g * stroke._strokeAlpha / 255,
          stroke._strokeColor.b * stroke._strokeAlpha / 255,
          stroke._strokeAlpha ) )

{    
    assert( _strokeSize > 0 );
}

void cocos2d::detail::StrokeScan::run()
{
    scan();
    
    std::swap( _dest, _src );
    free( _dest );

    _width = _destWidth;
    _height = _destHeight;
}

void cocos2d::detail::StrokeScan::scan()
{
    LineBounds bounds( _matrixWidth, _destWidth );
    std::size_t destIndex( 0 );
    
    for ( int desty( 0 ); desty != _destHeight; ++desty )
    {
        assert( destIndex == std::size_t( desty * _destWidth ) * 4 );
            
        queueBounds( bounds, desty + _strokeSize );

        destIndex =
            boundedScan( destIndex, bounds.getStart(), bounds.getEnd(), desty );
        
        bounds.roll();
    }
}

void cocos2d::detail::StrokeScan::queueBounds
( LineBounds& bounds, int bottomLine ) const
{
    const int lineStart( findFirstNonTransparent( bottomLine ) );
    assert( lineStart >= _strokeSize );

    bounds.queueStart( lineStart );

    if ( lineStart == _destWidth )
        bounds.queueEnd( 0 );
    else
        bounds.queueEnd( findLastNonTransparent( bottomLine ) + 1 );
}

std::size_t cocos2d::detail::StrokeScan::boundedScan
( std::size_t destIndex, int startx, int endx, int desty ) const
{
    bool doScan( false );
        
    if ( startx < endx )
    {
        doScan = true;
        startx -= _strokeSize;
        endx += _strokeSize;
    }

    destIndex += startx * 4;
    fillTransparent( destIndex, -1, startx );

    if ( doScan )
    {
        assert( endx <= _destWidth );
        assert
            ( destIndex == std::size_t( startx + desty * _destWidth ) * 4 );

        destIndex = scanDestinationLine( destIndex, startx, endx, desty );

        assert( destIndex == std::size_t( endx + desty * _destWidth ) * 4 );

        destIndex += ( _destWidth - endx ) * 4;
        fillTransparent( destIndex, endx - 1, _destWidth );
    }

    return destIndex;
}

int cocos2d::detail::StrokeScan::scanDestinationLine
( int destIndex, int startx, int endx, int desty ) const
{
    assert( endx > startx );
    
    int lastJump( startx );
        
    for ( int destx( startx ); destx != endx; )
    {
        std::uint32_t& destColor
            ( *reinterpret_cast< std::uint32_t* >
              ( &_dest[ destIndex ] ) );
            
        const Progress progress( apply( destx, desty, destColor ) );
        unsigned int stepSize;
            
        if ( progress == Progress::jump )
        {
            fillTransparent( destIndex, lastJump, destx );
            stepSize = std::min< unsigned int >( endx - destx, _matrixWidth );
        }
        else
        {
            applyInRange( destIndex, lastJump, destx, desty );
            stepSize = 1;
        }
            
        lastJump = destx;
        destx += stepSize;
        destIndex += 4 * stepSize;
    }
        
    fillTransparent( destIndex, lastJump, endx );

    return destIndex;
}

cocos2d::detail::StrokeScan::Progress
cocos2d::detail::StrokeScan::apply
( int destx, int desty, std::uint32_t& destColor ) const
{
    const int srcx( destx - _strokeSize );
    const int srcy( desty - _strokeSize );

    const std::uint32_t srcColor
        ( getColorAt( _src, _width, _height, srcx, srcy ) );
    const std::uint32_t srcAlpha( colorA( srcColor ) );

    if ( srcAlpha == 255 )
    {
        destColor = srcColor;
        return Progress::forward;
    }

    const MatrixResult matrixResult
        ( applyMatrix
          ( _matrix, _matrixWidth, _src, srcx, srcy, _width, _height ) );
    const unsigned int weightedAlpha
        ( std::min< unsigned int >( 255, matrixResult.weightedAlpha ) );
    
    const std::uint32_t strokeAlpha
        ( weightedAlpha * _stroke._strokeAlpha / 255 );

    assert( strokeAlpha <= 255 );

    if ( srcAlpha == 0 )
    {
        destColor =
            toColor
            ( colorR( _strokeColor ) * strokeAlpha / 255,
              colorG( _strokeColor ) * strokeAlpha / 255,
              colorB( _strokeColor ) * strokeAlpha / 255,
              strokeAlpha );

        if ( matrixResult.nonZeroCount == 0 )
            return Progress::jump;

        return Progress::rewind;
    }

    const std::uint32_t complementarySrcAlpha( 255 - srcAlpha );
    const std::uint32_t a
        ( srcAlpha
          + strokeAlpha * complementarySrcAlpha / 255 );
    const std::uint32_t multipliedAlpha
        ( strokeAlpha * complementarySrcAlpha );
            
    const std::uint32_t r
        ( blend
          ( colorR( srcColor ), colorR( _strokeColor ),
            multipliedAlpha ) );

    const std::uint32_t g
        ( blend
          ( colorG( srcColor ), colorG( _strokeColor ),
            multipliedAlpha ) );

    const std::uint32_t b
        ( blend
          ( colorB( srcColor ), colorB( _strokeColor ),
            multipliedAlpha ) );

    destColor = toColor( r, g, b, a );

    return Progress::rewind;
}

int cocos2d::detail::StrokeScan::findFirstNonTransparent( int desty ) const
{
    const int srcy( desty - _strokeSize );

    if ( ( srcy < 0 ) || ( srcy >= _height ) )
        return _destWidth;
    
    int cursor( ( srcy * _width ) * 4 + 3 );
    
    for ( int srcx( 0 ); srcx != _width; ++srcx, cursor += 4 )
        if ( _src[ cursor ] != 0 )
            return srcx + _strokeSize;

    return _destWidth;
}

int cocos2d::detail::StrokeScan::findLastNonTransparent( int desty ) const
{
    const int srcy( desty - _strokeSize );

    if ( ( srcy < 0 ) || ( srcy >= _height ) )
        return -1;
    
    int cursor( ( ( srcy + 1 ) * _width - 1 ) * 4 + 3 );
    
    for ( int srcx( 0 ); srcx != _width; ++srcx, cursor -= 4 )
        if ( _src[ cursor ] != 0 )
            return _width - srcx - 1 + _strokeSize;

    return -1;
}

void cocos2d::detail::StrokeScan::fillTransparent
( std::size_t upperIndex, int lowerx, int upperx ) const
{
    assert( upperIndex <= std::size_t( _destWidth * _destHeight * 4 ) );
    
    if ( upperx == lowerx )
        return;

    unsigned char* const end( _dest + upperIndex );
    std::fill( end - ( upperx - lowerx - 1 ) * 4, end, 0 );
}

void cocos2d::detail::StrokeScan::applyInRange
( std::size_t upperIndex, int lowerx, int upperx, int desty ) const
{
    std::size_t i( upperIndex );
    
    for ( int x( upperx - 1 ); x > lowerx; --x )
    {
        i -= 4;
        std::uint32_t& destColor
            ( *reinterpret_cast< std::uint32_t* >( &_dest[ i ] ) );
        apply( x, desty, destColor );
    }
}

cocos2d::detail::LineBounds::LineBounds
( std::size_t matrixWidth, int destWidth )
    : starts( matrixWidth, destWidth ),
      ends( matrixWidth, 0 )
{
    
}

void cocos2d::detail::LineBounds::queueStart( int x )
{
    starts.back() = x;
}

void cocos2d::detail::LineBounds::queueEnd( int x )
{
    ends.back() = x;
}

int cocos2d::detail::LineBounds::getStart()
{
    return  *std::min_element( starts.begin(), starts.end() );
}
    
int cocos2d::detail::LineBounds::getEnd()
{
    return *std::max_element( ends.begin(), ends.end() );
}

void cocos2d::detail::LineBounds::roll()
{
    const std::size_t count( starts.size() );
            
    for ( std::size_t i( 1 ); i != count; ++i )
    {
        starts[ i - 1 ] = starts[ i ];
        ends[ i - 1 ] = ends[ i ];
    }
}

cocos2d::detail::MatrixResult::MatrixResult()
    : nonZeroCount( 0 ),
      weightedAlpha( 0 )
{

}

static std::uint32_t cocos2d::detail::blend
( std::uint32_t c0, std::uint32_t c1, std::uint32_t a1 )
{
    const std::uint32_t result( c0 + c1 * a1 / fullAlphaSquared );
    assert( result <= 255 );
    return result;
}

static std::uint32_t cocos2d::detail::colorA( std::uint32_t c )
{
    return ( c & 0xff000000 ) >> 24;
}

static std::uint32_t cocos2d::detail::colorB( std::uint32_t c )
{
    return ( c & 0xff0000 ) >> 16;
}

static std::uint32_t cocos2d::detail::colorG( std::uint32_t c )
{
    return ( c & 0xff00 ) >> 8;
}

static std::uint32_t cocos2d::detail::colorR( std::uint32_t c )
{
    return c & 0xff;
}

static std::uint32_t cocos2d::detail::toColor
( std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a )
{
    assert( r <= 255 );
    assert( g <= 255 );
    assert( b <= 255 );
    assert( a <= 255 );
    
    return ( a << 24 ) | ( b << 16 ) | ( g << 8 ) | r;
}

static std::uint32_t cocos2d::detail::getColorAt
( unsigned char* src, int width, int height, int x, int y )
{
    if ( ( x < 0 ) || ( x >= width ) || ( y < 0 ) || ( y >= height ) )
        return 0;
    else
        return
            *reinterpret_cast< std::uint32_t* >
            ( &src[ ( y * width + x ) * 4 ] );
}

static cocos2d::detail::MatrixResult cocos2d::detail::applyMatrix
( const std::uint8_t* matrix, std::size_t matrixWidth,
  unsigned char* src, int srcx, int srcy, int width, int height )
{
    const int matrixHalfWidth( matrixWidth / 2 );
    MatrixResult result;

    std::size_t i( 0 );
    
    for ( std::size_t y( 0 ); y != matrixWidth; ++y )
        for ( std::size_t x( 0 ); x != matrixWidth; ++x )
        {
            const std::uint8_t coeff( matrix[ i ] );
            ++i;

            const int refx( srcx - matrixHalfWidth + x );
            const int refy( srcy - matrixHalfWidth + y );

            if ( ( refx >= 0 ) && ( refx < width )
                 && ( refy >= 0 ) && ( refy < height ) )
            {
                const unsigned int value
                    ( static_cast< unsigned int >
                      ( src[ ( refy * width + refx ) * 4 + 3 ] ) );

                if ( coeff != 0 )
                    result.weightedAlpha += value;
                
                result.nonZeroCount += ( value != 0 );
            }
        }

    return result;
}
