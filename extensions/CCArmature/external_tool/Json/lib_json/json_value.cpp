// Copyright 2007-2010 Baptiste Lepilleur
// Distributed under MIT license, or public domain if desired and
// recognized in your jurisdiction.
// See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#if !defined(JSON_IS_AMALGAMATION)
# include "value.h"
# include "writer.h"
# ifndef JSON_USE_SIMPLE_INTERNAL_ALLOCATOR
#  include "json_batchallocator.h"
# endif // #ifndef JSON_USE_SIMPLE_INTERNAL_ALLOCATOR
#endif // if !defined(JSON_IS_AMALGAMATION)
#include <iostream>
#include <utility>
#include <stdexcept>
#include <cstring>
#include <cassert>
#ifdef JSON_USE_CPPTL
# include <cpptl/conststring.h>
#endif
#include <cstddef>    // size_t

#include <string.h>

#define JSON_ASSERT_UNREACHABLE assert( false )
#define JSON_ASSERT( condition ) assert( condition );  // @todo <= change this into an exception throw
#define JSON_FAIL_MESSAGE( message ) throw std::runtime_error( message );
#define JSON_ASSERT_MESSAGE( condition, message ) if (!( condition )) JSON_FAIL_MESSAGE( message )

namespace CSJson {

const Value Value::jsonNull;
const Int Value::minInt = Int( ~(UInt(-1)/2) );
const Int Value::maxInt = Int( UInt(-1)/2 );
const UInt Value::maxUInt = UInt(-1);
const Int64 Value::minInt64 = Int64( ~(UInt64(-1)/2) );
const Int64 Value::maxInt64 = Int64( UInt64(-1)/2 );
const UInt64 Value::maxUInt64 = UInt64(-1);
const LargestInt Value::minLargestInt = LargestInt( ~(LargestUInt(-1)/2) );
const LargestInt Value::maxLargestInt = LargestInt( LargestUInt(-1)/2 );
const LargestUInt Value::maxLargestUInt = LargestUInt(-1);


/// Unknown size marker
static const unsigned int unknown = (unsigned)-1;


/** Duplicates the specified string value.
 * @param value Pointer to the string to duplicate. Must be zero-terminated if
 *              length is "unknown".
 * @param length Length of the value. if equals to unknown, then it will be
 *               computed using strlen(value).
 * @return Pointer on the duplicate instance of string.
 */
static inline char *
duplicateStringValue( const char *value, 
                      unsigned int length = unknown )
{
   if ( length == unknown )
      length = (unsigned int)strlen(value);
   char *newString = static_cast<char *>( malloc( length + 1 ) );
   JSON_ASSERT_MESSAGE( newString != 0, "Failed to allocate string value buffer" );
   memcpy( newString, value, length );
   newString[length] = 0;
   return newString;
}


/** Free the string duplicated by duplicateStringValue().
 */
static inline void 
releaseStringValue( char *value )
{
   if ( value )
      free( value );
}

} // namespace CSJson


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// ValueInternals...
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
#if !defined(JSON_IS_AMALGAMATION)
# ifdef JSON_VALUE_USE_INTERNAL_MAP
#  include "json_internalarray.inl"
#  include "json_internalmap.inl"
# endif // JSON_VALUE_USE_INTERNAL_MAP

# include "json_valueiterator.inl"
#endif // if !defined(JSON_IS_AMALGAMATION)

namespace CSJson {

// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class Value::CommentInfo
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////


Value::CommentInfo::CommentInfo()
   : comment_( 0 )
{
}

Value::CommentInfo::~CommentInfo()
{
   if ( comment_ )
      releaseStringValue( comment_ );
}


void 
Value::CommentInfo::setComment( const char *text )
{
   if ( comment_ )
      releaseStringValue( comment_ );
   JSON_ASSERT( text != 0 );
   JSON_ASSERT_MESSAGE( text[0]=='\0' || text[0]=='/', "Comments must start with /");
   // It seems that /**/ style comments are acceptable as well.
   comment_ = duplicateStringValue( text );
}


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class Value::CZString
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
# ifndef JSON_VALUE_USE_INTERNAL_MAP

// Notes: index_ indicates if the string was allocated when
// a string is stored.

Value::CZString::CZString( ArrayIndex index )
   : cstr_( 0 )
   , index_( index )
{
}

Value::CZString::CZString( const char *cstr, DuplicationPolicy allocate )
   : cstr_( allocate == duplicate ? duplicateStringValue(cstr) 
                                  : cstr )
   , index_( allocate )
{
}

Value::CZString::CZString( const CZString &other )
: cstr_( other.index_ != noDuplication &&  other.cstr_ != 0
                ?  duplicateStringValue( other.cstr_ )
                : other.cstr_ )
   , index_( other.cstr_ ? (other.index_ == noDuplication ? noDuplication : duplicate)
                         : other.index_ )
{
}

Value::CZString::~CZString()
{
   if ( cstr_  &&  index_ == duplicate )
      releaseStringValue( const_cast<char *>( cstr_ ) );
}

void 
Value::CZString::swap( CZString &other )
{
   std::swap( cstr_, other.cstr_ );
   std::swap( index_, other.index_ );
}

Value::CZString &
Value::CZString::operator =( const CZString &other )
{
   CZString temp( other );
   swap( temp );
   return *this;
}

bool 
Value::CZString::operator<( const CZString &other ) const 
{
   if ( cstr_ )
      return strcmp( cstr_, other.cstr_ ) < 0;
   return index_ < other.index_;
}

bool 
Value::CZString::operator==( const CZString &other ) const 
{
   if ( cstr_ )
      return strcmp( cstr_, other.cstr_ ) == 0;
   return index_ == other.index_;
}


ArrayIndex 
Value::CZString::index() const
{
   return index_;
}


const char *
Value::CZString::c_str() const
{
   return cstr_;
}

bool 
Value::CZString::isStaticString() const
{
   return index_ == noDuplication;
}

#endif // ifndef JSON_VALUE_USE_INTERNAL_MAP


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class Value::Value
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

/*! \internal Default constructor initialization must be equivalent to:
 * memset( this, 0, sizeof(Value) )
 * This optimization is used in ValueInternalMap fast allocator.
 */
Value::Value( ValueType type )
   : type_( type )
   , allocated_( 0 )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   switch ( type )
   {
   case nullValue:
      break;
   case intValue:
   case uintValue:
      value_.int_ = 0;
      break;
   case realValue:
      value_.real_ = 0.0;
      break;
   case stringValue:
      value_.string_ = 0;
      break;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
   case objectValue:
      value_.map_ = new ObjectValues();
      break;
#else
   case arrayValue:
      value_.array_ = arrayAllocator()->newArray();
      break;
   case objectValue:
      value_.map_ = mapAllocator()->newMap();
      break;
#endif
   case booleanValue:
      value_.bool_ = false;
      break;
   default:
      JSON_ASSERT_UNREACHABLE;
   }
}


#if defined(JSON_HAS_INT64)
Value::Value( UInt value )
   : type_( uintValue )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.uint_ = value;
}

Value::Value( Int value )
   : type_( intValue )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.int_ = value;
}

#endif // if defined(JSON_HAS_INT64)


Value::Value( Int64 value )
   : type_( intValue )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.int_ = value;
}


Value::Value( UInt64 value )
   : type_( uintValue )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.uint_ = value;
}

Value::Value( double value )
   : type_( realValue )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.real_ = value;
}

Value::Value( const char *value )
   : type_( stringValue )
   , allocated_( true )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.string_ = duplicateStringValue( value );
}


Value::Value( const char *beginValue, 
              const char *endValue )
   : type_( stringValue )
   , allocated_( true )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.string_ = duplicateStringValue( beginValue, 
                                          (unsigned int)(endValue - beginValue) );
}


Value::Value( const std::string &value )
   : type_( stringValue )
   , allocated_( true )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.string_ = duplicateStringValue( value.c_str(), 
                                          (unsigned int)value.length() );

}

Value::Value( const StaticString &value )
   : type_( stringValue )
   , allocated_( false )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.string_ = const_cast<char *>( value.c_str() );
}


# ifdef JSON_USE_CPPTL
Value::Value( const CppTL::ConstString &value )
   : type_( stringValue )
   , allocated_( true )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.string_ = duplicateStringValue( value, value.length() );
}
# endif

Value::Value( bool value )
   : type_( booleanValue )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   value_.bool_ = value;
}


Value::Value( const Value &other )
   : type_( other.type_ )
   , comments_( 0 )
# ifdef JSON_VALUE_USE_INTERNAL_MAP
   , itemIsUsed_( 0 )
#endif
{
   switch ( type_ )
   {
   case nullValue:
   case intValue:
   case uintValue:
   case realValue:
   case booleanValue:
      value_ = other.value_;
      break;
   case stringValue:
      if ( other.value_.string_ )
      {
         value_.string_ = duplicateStringValue( other.value_.string_ );
         allocated_ = true;
      }
      else
         value_.string_ = 0;
      break;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
   case objectValue:
      value_.map_ = new ObjectValues( *other.value_.map_ );
      break;
#else
   case arrayValue:
      value_.array_ = arrayAllocator()->newArrayCopy( *other.value_.array_ );
      break;
   case objectValue:
      value_.map_ = mapAllocator()->newMapCopy( *other.value_.map_ );
      break;
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   if ( other.comments_ )
   {
      comments_ = new CommentInfo[numberOfCommentPlacement];
      for ( int comment =0; comment < numberOfCommentPlacement; ++comment )
      {
         const CommentInfo &otherComment = other.comments_[comment];
         if ( otherComment.comment_ )
            comments_[comment].setComment( otherComment.comment_ );
      }
   }
}


Value::~Value()
{
   switch ( type_ )
   {
   case nullValue:
   case intValue:
   case uintValue:
   case realValue:
   case booleanValue:
      break;
   case stringValue:
      if ( allocated_ )
         releaseStringValue( value_.string_ );
      break;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
   case objectValue:
      delete value_.map_;
      break;
#else
   case arrayValue:
      arrayAllocator()->destructArray( value_.array_ );
      break;
   case objectValue:
      mapAllocator()->destructMap( value_.map_ );
      break;
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }

   if ( comments_ )
      delete[] comments_;
}

Value &
Value::operator=( const Value &other )
{
   Value temp( other );
   swap( temp );
   return *this;
}

void 
Value::swap( Value &other )
{
   ValueType temp = type_;
   type_ = other.type_;
   other.type_ = temp;
   std::swap( value_, other.value_ );
   int temp2 = allocated_;
   allocated_ = other.allocated_;
   other.allocated_ = temp2;
}

ValueType 
Value::type() const
{
   return type_;
}


int 
Value::compare( const Value &other ) const
{
   if ( *this < other )
      return -1;
   if ( *this > other )
      return 1;
   return 0;
}


bool 
Value::operator <( const Value &other ) const
{
   int typeDelta = type_ - other.type_;
   if ( typeDelta )
      return typeDelta < 0 ? true : false;
   switch ( type_ )
   {
   case nullValue:
      return false;
   case intValue:
      return value_.int_ < other.value_.int_;
   case uintValue:
      return value_.uint_ < other.value_.uint_;
   case realValue:
      return value_.real_ < other.value_.real_;
   case booleanValue:
      return value_.bool_ < other.value_.bool_;
   case stringValue:
      return ( value_.string_ == 0  &&  other.value_.string_ )
             || ( other.value_.string_  
                  &&  value_.string_  
                  && strcmp( value_.string_, other.value_.string_ ) < 0 );
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
   case objectValue:
      {
         int delta = int( value_.map_->size() - other.value_.map_->size() );
         if ( delta )
            return delta < 0;
         return (*value_.map_) < (*other.value_.map_);
      }
#else
   case arrayValue:
      return value_.array_->compare( *(other.value_.array_) ) < 0;
   case objectValue:
      return value_.map_->compare( *(other.value_.map_) ) < 0;
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return false;  // unreachable
}

bool 
Value::operator <=( const Value &other ) const
{
   return !(other < *this);
}

bool 
Value::operator >=( const Value &other ) const
{
   return !(*this < other);
}

bool 
Value::operator >( const Value &other ) const
{
   return other < *this;
}

bool 
Value::operator ==( const Value &other ) const
{
   //if ( type_ != other.type_ )
   // GCC 2.95.3 says:
   // attempt to take address of bit-field structure member `Json::Value::type_'
   // Beats me, but a temp solves the problem.
   int temp = other.type_;
   if ( type_ != temp )
      return false;
   switch ( type_ )
   {
   case nullValue:
      return true;
   case intValue:
      return value_.int_ == other.value_.int_;
   case uintValue:
      return value_.uint_ == other.value_.uint_;
   case realValue:
      return value_.real_ == other.value_.real_;
   case booleanValue:
      return value_.bool_ == other.value_.bool_;
   case stringValue:
      return ( value_.string_ == other.value_.string_ )
             || ( other.value_.string_  
                  &&  value_.string_  
                  && strcmp( value_.string_, other.value_.string_ ) == 0 );
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
   case objectValue:
      return value_.map_->size() == other.value_.map_->size()
             && (*value_.map_) == (*other.value_.map_);
#else
   case arrayValue:
      return value_.array_->compare( *(other.value_.array_) ) == 0;
   case objectValue:
      return value_.map_->compare( *(other.value_.map_) ) == 0;
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return false;  // unreachable
}

bool 
Value::operator !=( const Value &other ) const
{
   return !( *this == other );
}

const char *
Value::asCString() const
{
   JSON_ASSERT( type_ == stringValue );
   return value_.string_;
}


std::string 
Value::asString() const
{
   switch ( type_ )
   {
   case nullValue:
      return "";
   case stringValue:
      return value_.string_ ? value_.string_ : "";
   case booleanValue:
      return value_.bool_ ? "true" : "false";
   case intValue:
   case uintValue:
   case realValue:
   case arrayValue:
   case objectValue:
      JSON_FAIL_MESSAGE( "Type is not convertible to string" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return ""; // unreachable
}

# ifdef JSON_USE_CPPTL
CppTL::ConstString 
Value::asConstString() const
{
   return CppTL::ConstString( asString().c_str() );
}
# endif


Value::Int 
Value::asInt() const
{
   switch ( type_ )
   {
   case nullValue:
      return 0;
   case intValue:
      JSON_ASSERT_MESSAGE( value_.int_ >= minInt  &&  value_.int_ <= maxInt, "unsigned integer out of signed int range" );
      return Int(value_.int_);
   case uintValue:
      JSON_ASSERT_MESSAGE( value_.uint_ <= UInt(maxInt), "unsigned integer out of signed int range" );
      return Int(value_.uint_);
   case realValue:
      JSON_ASSERT_MESSAGE( value_.real_ >= minInt  &&  value_.real_ <= maxInt, "Real out of signed integer range" );
      return Int( value_.real_ );
   case booleanValue:
      return value_.bool_ ? 1 : 0;
   case stringValue:
   case arrayValue:
   case objectValue:
      JSON_FAIL_MESSAGE( "Type is not convertible to int" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}


Value::UInt 
Value::asUInt() const
{
   switch ( type_ )
   {
   case nullValue:
      return 0;
   case intValue:
      JSON_ASSERT_MESSAGE( value_.int_ >= 0, "Negative integer can not be converted to unsigned integer" );
      JSON_ASSERT_MESSAGE( value_.int_ <= maxUInt, "signed integer out of UInt range" );
      return UInt(value_.int_);
   case uintValue:
      JSON_ASSERT_MESSAGE( value_.uint_ <= maxUInt, "unsigned integer out of UInt range" );
      return UInt(value_.uint_);
   case realValue:
      JSON_ASSERT_MESSAGE( value_.real_ >= 0  &&  value_.real_ <= maxUInt,  "Real out of unsigned integer range" );
      return UInt( value_.real_ );
   case booleanValue:
      return value_.bool_ ? 1 : 0;
   case stringValue:
   case arrayValue:
   case objectValue:
      JSON_FAIL_MESSAGE( "Type is not convertible to uint" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}


# if defined(JSON_HAS_INT64)

Value::Int64
Value::asInt64() const
{
   switch ( type_ )
   {
   case nullValue:
      return 0;
   case intValue:
      return value_.int_;
   case uintValue:
      JSON_ASSERT_MESSAGE( value_.uint_ <= UInt64(maxInt64), "unsigned integer out of Int64 range" );
      return value_.uint_;
   case realValue:
      JSON_ASSERT_MESSAGE( value_.real_ >= minInt64  &&  value_.real_ <= maxInt64, "Real out of Int64 range" );
      return Int( value_.real_ );
   case booleanValue:
      return value_.bool_ ? 1 : 0;
   case stringValue:
   case arrayValue:
   case objectValue:
      JSON_FAIL_MESSAGE( "Type is not convertible to Int64" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}


Value::UInt64
Value::asUInt64() const
{
   switch ( type_ )
   {
   case nullValue:
      return 0;
   case intValue:
      JSON_ASSERT_MESSAGE( value_.int_ >= 0, "Negative integer can not be converted to UInt64" );
      return value_.int_;
   case uintValue:
      return value_.uint_;
   case realValue:
      JSON_ASSERT_MESSAGE( value_.real_ >= 0  &&  value_.real_ <= maxUInt64,  "Real out of UInt64 range" );
      return UInt( value_.real_ );
   case booleanValue:
      return value_.bool_ ? 1 : 0;
   case stringValue:
   case arrayValue:
   case objectValue:
      JSON_FAIL_MESSAGE( "Type is not convertible to UInt64" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}
# endif // if defined(JSON_HAS_INT64)


LargestInt 
Value::asLargestInt() const
{
#if defined(JSON_NO_INT64)
    return asInt();
#else
    return asInt64();
#endif
}


LargestUInt 
Value::asLargestUInt() const
{
#if defined(JSON_NO_INT64)
    return asUInt();
#else
    return asUInt64();
#endif
}


double 
Value::asDouble() const
{
   switch ( type_ )
   {
   case nullValue:
      return 0.0;
   case intValue:
      return static_cast<double>( value_.int_ );
   case uintValue:
#if !defined(JSON_USE_INT64_DOUBLE_CONVERSION)
      return static_cast<double>( value_.uint_ );
#else // if !defined(JSON_USE_INT64_DOUBLE_CONVERSION)
      return static_cast<double>( Int(value_.uint_/2) ) * 2 + Int(value_.uint_ & 1);
#endif // if !defined(JSON_USE_INT64_DOUBLE_CONVERSION)
   case realValue:
      return value_.real_;
   case booleanValue:
      return value_.bool_ ? 1.0 : 0.0;
   case stringValue:
   case arrayValue:
   case objectValue:
      JSON_FAIL_MESSAGE( "Type is not convertible to double" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}

float
Value::asFloat() const
{
   switch ( type_ )
   {
   case nullValue:
      return 0.0f;
   case intValue:
      return static_cast<float>( value_.int_ );
   case uintValue:
#if !defined(JSON_USE_INT64_DOUBLE_CONVERSION)
      return static_cast<float>( value_.uint_ );
#else // if !defined(JSON_USE_INT64_DOUBLE_CONVERSION)
      return static_cast<float>( Int(value_.uint_/2) ) * 2 + Int(value_.uint_ & 1);
#endif // if !defined(JSON_USE_INT64_DOUBLE_CONVERSION)
   case realValue:
      return static_cast<float>( value_.real_ );
   case booleanValue:
      return value_.bool_ ? 1.0f : 0.0f;
   case stringValue:
   case arrayValue:
   case objectValue:
      JSON_FAIL_MESSAGE( "Type is not convertible to float" );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0.0f; // unreachable;
}

bool 
Value::asBool() const
{
   switch ( type_ )
   {
   case nullValue:
      return false;
   case intValue:
   case uintValue:
      return value_.int_ != 0;
   case realValue:
      return value_.real_ != 0.0;
   case booleanValue:
      return value_.bool_;
   case stringValue:
      return value_.string_  &&  value_.string_[0] != 0;
   case arrayValue:
   case objectValue:
      return value_.map_->size() != 0;
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return false; // unreachable;
}


bool 
Value::isConvertibleTo( ValueType other ) const
{
   switch ( type_ )
   {
   case nullValue:
      return true;
   case intValue:
      return ( other == nullValue  &&  value_.int_ == 0 )
             || other == intValue
             || ( other == uintValue  && value_.int_ >= 0 )
             || other == realValue
             || other == stringValue
             || other == booleanValue;
   case uintValue:
      return ( other == nullValue  &&  value_.uint_ == 0 )
             || ( other == intValue  && value_.uint_ <= (unsigned)maxInt )
             || other == uintValue
             || other == realValue
             || other == stringValue
             || other == booleanValue;
   case realValue:
      return ( other == nullValue  &&  value_.real_ == 0.0 )
             || ( other == intValue  &&  value_.real_ >= minInt  &&  value_.real_ <= maxInt )
             || ( other == uintValue  &&  value_.real_ >= 0  &&  value_.real_ <= maxUInt )
             || other == realValue
             || other == stringValue
             || other == booleanValue;
   case booleanValue:
      return ( other == nullValue  &&  value_.bool_ == false )
             || other == intValue
             || other == uintValue
             || other == realValue
             || other == stringValue
             || other == booleanValue;
   case stringValue:
      return other == stringValue
             || ( other == nullValue  &&  (!value_.string_  ||  value_.string_[0] == 0) );
   case arrayValue:
      return other == arrayValue
             ||  ( other == nullValue  &&  value_.map_->size() == 0 );
   case objectValue:
      return other == objectValue
             ||  ( other == nullValue  &&  value_.map_->size() == 0 );
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return false; // unreachable;
}


/// Number of values in array or object
ArrayIndex 
Value::size() const
{
   switch ( type_ )
   {
   case nullValue:
   case intValue:
   case uintValue:
   case realValue:
   case booleanValue:
   case stringValue:
      return 0;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:  // size of the array is highest index + 1
      if ( !value_.map_->empty() )
      {
         ObjectValues::const_iterator itLast = value_.map_->end();
         --itLast;
         return (*itLast).first.index()+1;
      }
      return 0;
   case objectValue:
      return ArrayIndex( value_.map_->size() );
#else
   case arrayValue:
      return Int( value_.array_->size() );
   case objectValue:
      return Int( value_.map_->size() );
#endif
   default:
      JSON_ASSERT_UNREACHABLE;
   }
   return 0; // unreachable;
}


bool 
Value::empty() const
{
   if ( isNull() || isArray() || isObject() )
      return size() == 0u;
   else
      return false;
}


bool
Value::operator!() const
{
   return isNull();
}


void 
Value::clear()
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == arrayValue  || type_ == objectValue );

   switch ( type_ )
   {
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
   case objectValue:
    //  value_.map_->clear();
       if (!value_.map_)
       {
           value_.map_->clear();
           delete value_.map_;
           value_.map_ = NULL;
       }
      break;
#else
   case arrayValue:
      value_.array_->clear();
      break;
   case objectValue:
      value_.map_->clear();
      break;
#endif
   default:
      break;
   }
}

void 
Value::resize( ArrayIndex newSize )
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == arrayValue );
   if ( type_ == nullValue )
      *this = Value( arrayValue );
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   ArrayIndex oldSize = size();
   if ( newSize == 0 )
      clear();
   else if ( newSize > oldSize )
      (*this)[ newSize - 1 ];
   else
   {
      for ( ArrayIndex index = newSize; index < oldSize; ++index )
      {
         value_.map_->erase( index );
      }
      assert( size() == newSize );
   }
#else
   value_.array_->resize( newSize );
#endif
}


Value &
Value::operator[]( ArrayIndex index )
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == arrayValue );
   if ( type_ == nullValue )
      *this = Value( arrayValue );
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   CZString key( index );
   ObjectValues::iterator it = value_.map_->lower_bound( key );
   if ( it != value_.map_->end()  &&  (*it).first == key )
      return (*it).second;

   ObjectValues::value_type defaultValue( key, jsonNull );
   it = value_.map_->insert( it, defaultValue );
   return (*it).second;
#else
   return value_.array_->resolveReference( index );
#endif
}


Value &
Value::operator[]( int index )
{
   JSON_ASSERT( index >= 0 );
   return (*this)[ ArrayIndex(index) ];
}


const Value &
Value::operator[]( ArrayIndex index ) const
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == arrayValue );
   if ( type_ == nullValue )
      return jsonNull;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   CZString key( index );
   ObjectValues::const_iterator it = value_.map_->find( key );
   if ( it == value_.map_->end() )
      return jsonNull;
   return (*it).second;
#else
   Value *value = value_.array_->find( index );
   return value ? *value : null;
#endif
}


const Value &
Value::operator[]( int index ) const
{
   JSON_ASSERT( index >= 0 );
   return (*this)[ ArrayIndex(index) ];
}


Value &
Value::operator[]( const char *key )
{
   return resolveReference( key, false );
}


Value &
Value::resolveReference( const char *key, 
                         bool isStatic )
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == objectValue );
   if ( type_ == nullValue )
      *this = Value( objectValue );
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   CZString actualKey( key, isStatic ? CZString::noDuplication 
                                     : CZString::duplicateOnCopy );
   ObjectValues::iterator it = value_.map_->lower_bound( actualKey );
   if ( it != value_.map_->end()  &&  (*it).first == actualKey )
      return (*it).second;

   ObjectValues::value_type defaultValue( actualKey, jsonNull );
   it = value_.map_->insert( it, defaultValue );
   Value &value = (*it).second;
   return value;
#else
   return value_.map_->resolveReference( key, isStatic );
#endif
}


Value 
Value::get( ArrayIndex index, 
            const Value &defaultValue ) const
{
   const Value *value = &((*this)[index]);
   return value == &jsonNull ? defaultValue : *value;
}


bool 
Value::isValidIndex( ArrayIndex index ) const
{
   return index < size();
}



const Value &
Value::operator[]( const char *key ) const
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == objectValue );
   if ( type_ == nullValue )
      return jsonNull;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   CZString actualKey( key, CZString::noDuplication );
   ObjectValues::const_iterator it = value_.map_->find( actualKey );
   if ( it == value_.map_->end() )
      return jsonNull;
   return (*it).second;
#else
   const Value *value = value_.map_->find( key );
   return value ? *value : null;
#endif
}


Value &
Value::operator[]( const std::string &key )
{
   return (*this)[ key.c_str() ];
}


const Value &
Value::operator[]( const std::string &key ) const
{
   return (*this)[ key.c_str() ];
}

Value &
Value::operator[]( const StaticString &key )
{
   return resolveReference( key, true );
}


# ifdef JSON_USE_CPPTL
Value &
Value::operator[]( const CppTL::ConstString &key )
{
   return (*this)[ key.c_str() ];
}


const Value &
Value::operator[]( const CppTL::ConstString &key ) const
{
   return (*this)[ key.c_str() ];
}
# endif


Value &
Value::append( const Value &value )
{
   return (*this)[size()] = value;
}


Value 
Value::get( const char *key, 
            const Value &defaultValue ) const
{
   const Value *value = &((*this)[key]);
   return value == &jsonNull ? defaultValue : *value;
}


Value 
Value::get( const std::string &key,
            const Value &defaultValue ) const
{
   return get( key.c_str(), defaultValue );
}

Value
Value::removeMember( const char* key )
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == objectValue );
   if ( type_ == nullValue )
      return jsonNull;
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   CZString actualKey( key, CZString::noDuplication );
   ObjectValues::iterator it = value_.map_->find( actualKey );
   if ( it == value_.map_->end() )
      return jsonNull;
   Value old(it->second);
   value_.map_->erase(it);
   return old;
#else
   Value *value = value_.map_->find( key );
   if (value){
      Value old(*value);
      value_.map_.remove( key );
      return old;
   } else {
      return null;
   }
#endif
}

Value
Value::removeMember( const std::string &key )
{
   return removeMember( key.c_str() );
}

# ifdef JSON_USE_CPPTL
Value 
Value::get( const CppTL::ConstString &key,
            const Value &defaultValue ) const
{
   return get( key.c_str(), defaultValue );
}
# endif

bool 
Value::isMember( const char *key ) const
{
   const Value *value = &((*this)[key]);
   return value != &jsonNull;
}


bool 
Value::isMember( const std::string &key ) const
{
   return isMember( key.c_str() );
}


# ifdef JSON_USE_CPPTL
bool 
Value::isMember( const CppTL::ConstString &key ) const
{
   return isMember( key.c_str() );
}
#endif

Value::Members 
Value::getMemberNames() const
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == objectValue );
   if ( type_ == nullValue )
       return Value::Members();
   Members members;
   members.reserve( value_.map_->size() );
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   ObjectValues::const_iterator it = value_.map_->begin();
   ObjectValues::const_iterator itEnd = value_.map_->end();
   for ( ; it != itEnd; ++it )
      members.push_back( std::string( (*it).first.c_str() ) );
#else
   ValueInternalMap::IteratorState it;
   ValueInternalMap::IteratorState itEnd;
   value_.map_->makeBeginIterator( it );
   value_.map_->makeEndIterator( itEnd );
   for ( ; !ValueInternalMap::equals( it, itEnd ); ValueInternalMap::increment(it) )
      members.push_back( std::string( ValueInternalMap::key( it ) ) );
#endif
   return members;
}
//
//# ifdef JSON_USE_CPPTL
//EnumMemberNames
//Value::enumMemberNames() const
//{
//   if ( type_ == objectValue )
//   {
//      return CppTL::Enum::any(  CppTL::Enum::transform(
//         CppTL::Enum::keys( *(value_.map_), CppTL::Type<const CZString &>() ),
//         MemberNamesTransform() ) );
//   }
//   return EnumMemberNames();
//}
//
//
//EnumValues 
//Value::enumValues() const
//{
//   if ( type_ == objectValue  ||  type_ == arrayValue )
//      return CppTL::Enum::anyValues( *(value_.map_), 
//                                     CppTL::Type<const Value &>() );
//   return EnumValues();
//}
//
//# endif


bool
Value::isNull() const
{
   return type_ == nullValue;
}


bool 
Value::isBool() const
{
   return type_ == booleanValue;
}


bool
Value::isInt() const
{
   return type_ == intValue;
}


bool 
Value::isUInt() const
{
   return type_ == uintValue;
}


bool 
Value::isIntegral() const
{
   return type_ == intValue  
          ||  type_ == uintValue  
          ||  type_ == booleanValue;
}


bool 
Value::isDouble() const
{
   return type_ == realValue;
}


bool 
Value::isNumeric() const
{
   return isIntegral() || isDouble();
}


bool 
Value::isString() const
{
   return type_ == stringValue;
}


bool 
Value::isArray() const
{
   return type_ == nullValue  ||  type_ == arrayValue;
}


bool 
Value::isObject() const
{
   return type_ == nullValue  ||  type_ == objectValue;
}


void 
Value::setComment( const char *comment,
                   CommentPlacement placement )
{
   if ( !comments_ )
      comments_ = new CommentInfo[numberOfCommentPlacement];
   comments_[placement].setComment( comment );
}


void 
Value::setComment( const std::string &comment,
                   CommentPlacement placement )
{
   setComment( comment.c_str(), placement );
}


bool 
Value::hasComment( CommentPlacement placement ) const
{
   return comments_ != 0  &&  comments_[placement].comment_ != 0;
}

std::string 
Value::getComment( CommentPlacement placement ) const
{
   if ( hasComment(placement) )
      return comments_[placement].comment_;
   return "";
}


std::string 
Value::toStyledString() const
{
   StyledWriter writer;
   return writer.write( *this );
}


Value::const_iterator 
Value::begin() const
{
   switch ( type_ )
   {
#ifdef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
      if ( value_.array_ )
      {
         ValueInternalArray::IteratorState it;
         value_.array_->makeBeginIterator( it );
         return const_iterator( it );
      }
      break;
   case objectValue:
      if ( value_.map_ )
      {
         ValueInternalMap::IteratorState it;
         value_.map_->makeBeginIterator( it );
         return const_iterator( it );
      }
      break;
#else
   case arrayValue:
   case objectValue:
      if ( value_.map_ )
         return const_iterator( value_.map_->begin() );
      break;
#endif
   default:
      break;
   }
   return const_iterator();
}

Value::const_iterator 
Value::end() const
{
   switch ( type_ )
   {
#ifdef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
      if ( value_.array_ )
      {
         ValueInternalArray::IteratorState it;
         value_.array_->makeEndIterator( it );
         return const_iterator( it );
      }
      break;
   case objectValue:
      if ( value_.map_ )
      {
         ValueInternalMap::IteratorState it;
         value_.map_->makeEndIterator( it );
         return const_iterator( it );
      }
      break;
#else
   case arrayValue:
   case objectValue:
      if ( value_.map_ )
         return const_iterator( value_.map_->end() );
      break;
#endif
   default:
      break;
   }
   return const_iterator();
}


Value::iterator 
Value::begin()
{
   switch ( type_ )
   {
#ifdef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
      if ( value_.array_ )
      {
         ValueInternalArray::IteratorState it;
         value_.array_->makeBeginIterator( it );
         return iterator( it );
      }
      break;
   case objectValue:
      if ( value_.map_ )
      {
         ValueInternalMap::IteratorState it;
         value_.map_->makeBeginIterator( it );
         return iterator( it );
      }
      break;
#else
   case arrayValue:
   case objectValue:
      if ( value_.map_ )
         return iterator( value_.map_->begin() );
      break;
#endif
   default:
      break;
   }
   return iterator();
}

Value::iterator 
Value::end()
{
   switch ( type_ )
   {
#ifdef JSON_VALUE_USE_INTERNAL_MAP
   case arrayValue:
      if ( value_.array_ )
      {
         ValueInternalArray::IteratorState it;
         value_.array_->makeEndIterator( it );
         return iterator( it );
      }
      break;
   case objectValue:
      if ( value_.map_ )
      {
         ValueInternalMap::IteratorState it;
         value_.map_->makeEndIterator( it );
         return iterator( it );
      }
      break;
#else
   case arrayValue:
   case objectValue:
      if ( value_.map_ )
         return iterator( value_.map_->end() );
      break;
#endif
   default:
      break;
   }
   return iterator();
}


// class PathArgument
// //////////////////////////////////////////////////////////////////

PathArgument::PathArgument()
   : kind_( kindNone )
{
}


PathArgument::PathArgument( ArrayIndex index )
   : index_( index )
   , kind_( kindIndex )
{
}


PathArgument::PathArgument( const char *key )
   : key_( key )
   , kind_( kindKey )
{
}


PathArgument::PathArgument( const std::string &key )
   : key_( key.c_str() )
   , kind_( kindKey )
{
}

// class Path
// //////////////////////////////////////////////////////////////////

Path::Path( const std::string &path,
            const PathArgument &a1,
            const PathArgument &a2,
            const PathArgument &a3,
            const PathArgument &a4,
            const PathArgument &a5 )
{
   InArgs in;
   in.push_back( &a1 );
   in.push_back( &a2 );
   in.push_back( &a3 );
   in.push_back( &a4 );
   in.push_back( &a5 );
   makePath( path, in );
}


void 
Path::makePath( const std::string &path,
                const InArgs &in )
{
   const char *current = path.c_str();
   const char *end = current + path.length();
   InArgs::const_iterator itInArg = in.begin();
   while ( current != end )
   {
      if ( *current == '[' )
      {
         ++current;
         if ( *current == '%' )
            addPathInArg( path, in, itInArg, PathArgument::kindIndex );
         else
         {
            ArrayIndex index = 0;
            for ( ; current != end && *current >= '0'  &&  *current <= '9'; ++current )
               index = index * 10 + ArrayIndex(*current - '0');
            args_.push_back( index );
         }
         if ( current == end  ||  *current++ != ']' )
            invalidPath( path, int(current - path.c_str()) );
      }
      else if ( *current == '%' )
      {
         addPathInArg( path, in, itInArg, PathArgument::kindKey );
         ++current;
      }
      else if ( *current == '.' )
      {
         ++current;
      }
      else
      {
         const char *beginName = current;
         while ( current != end  &&  !strchr( "[.", *current ) )
            ++current;
         args_.push_back( std::string( beginName, current ) );
      }
   }
}


void 
Path::addPathInArg( const std::string &path, 
                    const InArgs &in, 
                    InArgs::const_iterator &itInArg, 
                    PathArgument::Kind kind )
{
   if ( itInArg == in.end() )
   {
      // Error: missing argument %d
   }
   else if ( (*itInArg)->kind_ != kind )
   {
      // Error: bad argument type
   }
   else
   {
      args_.push_back( **itInArg );
   }
}


void 
Path::invalidPath( const std::string &path, 
                   int location )
{
   // Error: invalid path.
}


const Value &
Path::resolve( const Value &root ) const
{
   const Value *node = &root;
   for ( Args::const_iterator it = args_.begin(); it != args_.end(); ++it )
   {
      const PathArgument &arg = *it;
      if ( arg.kind_ == PathArgument::kindIndex )
      {
         if ( !node->isArray()  ||  node->isValidIndex( arg.index_ ) )
         {
            // Error: unable to resolve path (array value expected at position...
         }
         node = &((*node)[arg.index_]);
      }
      else if ( arg.kind_ == PathArgument::kindKey )
      {
         if ( !node->isObject() )
         {
            // Error: unable to resolve path (object value expected at position...)
         }
         node = &((*node)[arg.key_]);
         if ( node == &Value::jsonNull )
         {
            // Error: unable to resolve path (object has no member named '' at position...)
         }
      }
   }
   return *node;
}


Value 
Path::resolve( const Value &root, 
               const Value &defaultValue ) const
{
   const Value *node = &root;
   for ( Args::const_iterator it = args_.begin(); it != args_.end(); ++it )
   {
      const PathArgument &arg = *it;
      if ( arg.kind_ == PathArgument::kindIndex )
      {
         if ( !node->isArray()  ||  node->isValidIndex( arg.index_ ) )
            return defaultValue;
         node = &((*node)[arg.index_]);
      }
      else if ( arg.kind_ == PathArgument::kindKey )
      {
         if ( !node->isObject() )
            return defaultValue;
         node = &((*node)[arg.key_]);
         if ( node == &Value::jsonNull )
            return defaultValue;
      }
   }
   return *node;
}


Value &
Path::make( Value &root ) const
{
   Value *node = &root;
   for ( Args::const_iterator it = args_.begin(); it != args_.end(); ++it )
   {
      const PathArgument &arg = *it;
      if ( arg.kind_ == PathArgument::kindIndex )
      {
         if ( !node->isArray() )
         {
            // Error: node is not an array at position ...
         }
         node = &((*node)[arg.index_]);
      }
      else if ( arg.kind_ == PathArgument::kindKey )
      {
         if ( !node->isObject() )
         {
            // Error: node is not an object at position...
         }
         node = &((*node)[arg.key_]);
      }
   }
   return *node;
}


} // namespace CSJson
