#ifndef VECTOR2_H
#define VECTOR2_H

//#include <math.h>
//#include <pspmath.h>
//#include "vfpu_ops.h"

class Vector2
{
public:

    float X, Y;

    inline Vector2()
    {
		X = 0.0f;
		Y = 0.0f;
    }

	~Vector2()
	{
	}

    inline Vector2(const float fX, const float fY )
        : X( fX ), Y( fY )
    {
    }

    inline explicit Vector2( const float scaler )
        : X( scaler), Y( scaler )
    {
    }

    inline explicit Vector2( const float afCoordinate[2] )
        : X( afCoordinate[0] ),
          Y( afCoordinate[1] )
    {
    }

    inline explicit Vector2( const int afCoordinate[2] )
    {
        X = (float)afCoordinate[0];
        Y = (float)afCoordinate[1];
    }

    inline explicit Vector2( float* const r )
        : X( r[0] ), Y( r[1] )
    {
    }

    inline Vector2( const Vector2& rkVector )
        : X( rkVector.X ), Y( rkVector.Y )
    {
    }

	/// Pointer accessor for direct copying
	inline float* ptr()
	{
		return &X;
	}
	/// Pointer accessor for direct copying
	inline const float* ptr() const
	{
		return &X;
	}

    /** Assigns the value of the other vector.
        @param
            rkVector The other vector
    */
    inline Vector2& operator = ( const Vector2& rkVector )
    {
        X = rkVector.X;
        Y = rkVector.Y;

        return *this;
    }

	inline Vector2& operator = ( const float fScalar)
	{
		X = fScalar;
		Y = fScalar;

		return *this;
	}

    inline bool operator == ( const Vector2& rkVector ) const
    {
        return ( X == rkVector.X && Y == rkVector.Y );
    }

    inline bool operator != ( const Vector2& rkVector ) const
    {
        return ( X != rkVector.X || Y != rkVector.Y  );
    }

    // arithmetic operations
    inline Vector2 operator + ( const Vector2& rkVector ) const
    {
        return Vector2(
            X + rkVector.X,
            Y + rkVector.Y);
    }

    inline Vector2 operator - ( const Vector2& rkVector ) const
    {
        return Vector2(
            X - rkVector.X,
            Y - rkVector.Y);
    }

    inline Vector2 operator * ( const float fScalar ) const
    {
        return Vector2(
            X * fScalar,
            Y * fScalar);
    }

    inline Vector2 operator * ( const Vector2& rhs) const
    {
        return Vector2(
            X * rhs.X,
            Y * rhs.Y);
    }

    inline Vector2 operator / ( const float fScalar ) const
    {
        float fInv = 1 / fScalar;

        return Vector2(
            X * fInv,
            Y * fInv);
    }

    inline Vector2 operator / ( const Vector2& rhs) const
    {
        return Vector2(
            X / rhs.X,
            Y / rhs.Y);
    }

    inline const Vector2& operator + () const
    {
        return *this;
    }

    inline Vector2 operator - () const
    {
        return Vector2(-X, -Y);
    }

    // overloaded operators to help Vector2
    inline friend Vector2 operator * ( const float fScalar, const Vector2& rkVector )
    {
        return Vector2(
            fScalar * rkVector.X,
            fScalar * rkVector.Y);
    }

    inline friend Vector2 operator / ( const float fScalar, const Vector2& rkVector )
    {
        return Vector2(
            fScalar / rkVector.X,
            fScalar / rkVector.Y);
    }

    inline friend Vector2 operator + (const Vector2& lhs, const float rhs)
    {
        return Vector2(
            lhs.X + rhs,
            lhs.Y + rhs);
    }

    inline friend Vector2 operator + (const float lhs, const Vector2& rhs)
    {
        return Vector2(
            lhs + rhs.X,
            lhs + rhs.Y);
    }

    inline friend Vector2 operator - (const Vector2& lhs, const float rhs)
    {
        return Vector2(
            lhs.X - rhs,
            lhs.Y - rhs);
    }

    inline friend Vector2 operator - (const float lhs, const Vector2& rhs)
    {
        return Vector2(
            lhs - rhs.X,
            lhs - rhs.Y);
    }
    // arithmetic updates
    inline Vector2& operator += ( const Vector2& rkVector )
    {
        X += rkVector.X;
        Y += rkVector.Y;

        return *this;
    }

    inline Vector2& operator += ( const float fScaler )
    {
        X += fScaler;
        Y += fScaler;

        return *this;
    }

    inline Vector2& operator -= ( const Vector2& rkVector )
    {
        X -= rkVector.X;
        Y -= rkVector.Y;

        return *this;
    }

    inline Vector2& operator -= ( const float fScaler )
    {
        X -= fScaler;
        Y -= fScaler;

        return *this;
    }

    inline Vector2& operator *= ( const float fScalar )
    {
        X *= fScalar;
        Y *= fScalar;

        return *this;
    }

    inline Vector2& operator *= ( const Vector2& rkVector )
    {
        X *= rkVector.X;
        Y *= rkVector.Y;

        return *this;
    }

    inline Vector2& operator /= ( const float fScalar )
    {
        X /= fScalar;
        Y /= fScalar;

        return *this;
    }

    inline Vector2& operator /= ( const Vector2& rkVector )
    {
        X /= rkVector.X;
        Y /= rkVector.Y;

        return *this;
    }

	static float mysqrtf(float val)
	{
	   float ret;

	   __asm__ volatile (
		  "mtv %1, S000\n"
		  "vsqrt.s S001, S000\n"
		  "mfv %0, S001\n"
		  : "=r"(ret) : "r"(val));

	   return ret;
	} 

	static float myacosf(float x)
   {
		   float result;
		__asm__ volatile (
			"mtv     %1, S000\n"
			"vcst.s  S001, VFPU_PI_2\n"
			"vasin.s S000, S000\n"
			"vocp.s  S000, S000\n"
			"vmul.s  S000, S000, S001\n"
			"mfv     %0, S000\n"
			: "=r"(result) : "r"(x));
		return result;
   }

	static float myasinf(float x)
   {
	       float result;
		__asm__ volatile (
			"mtv     %1, S000\n"
			"vcst.s  S001, VFPU_PI_2\n"
			"vasin.s S000, S000\n"
			"vmul.s  S000, S000, S001\n"
			"mfv     %0, S000\n"
			: "=r"(result) : "r"(x));
		return result;
   } 

   static void vfpu_sincos(float r, float *s, float *c)
	{
		__asm__ volatile (
			"mtv      %2, S002\n"
			"vcst.s   S003, VFPU_2_PI\n"
			"vmul.s   S002, S002, S003\n"
			"vrot.p   C000, S002, [s, c]\n"
			"mfv      %0, S000\n"
			"mfv      %1, S001\n"
		: "=r"(*s), "=r"(*c): "r"(r));
	}

	// special points
    static const Vector2 ZERO;
	static const Vector2 One;
    static const Vector2 UNIT_X;
    static const Vector2 UNIT_Y;
    static const Vector2 NEGATIVE_UNIT_X;
    static const Vector2 NEGATIVE_UNIT_Y;
    static const Vector2 UNIT_SCALE;

	static void DistanceSquared(Vector2 value1, Vector2 value2, float &result);
	static void Distance(Vector2 value1, Vector2 value2, float &result);
	static float Dot(Vector2 value1, Vector2 value2);
    static void Dot(Vector2 value1, Vector2 value2, float &result);
	float Length();
    float LengthSquared();
	static void Normalize( Vector2 value, Vector2 &result);
};

#endif

