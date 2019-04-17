#pragma once

#include "../../../common/Directory.h"
#include "../../../common/Array.h"
#include "../../../graphics/IRenderer.h"
#include "../../../xml/include/xmlutils.h"


#define GET_ATTRIBUTEN(NAME)	if(style==##NAME)return m_n##NAME;
#define GET_ATTRIBUTED(NAME)	if(style==##NAME)return m_n##NAME;
#define GET_ATTRIBUTE(NAME)		if(style==##NAME)return m_##NAME;

#define VALIDATE_ATTRIBUTE(NAME) if(nStyle==##NAME)return m_bHave##NAME;

#ifndef	M_PI
#define	M_PI		3.14159265358979323846
#endif

//------------------------------------------------------------------------------------------------------

namespace SVG
{
	const long c_ag_LineCapFlat				= 0;
	const long c_ag_LineCapSquare			= 1;
	const long c_ag_LineCapTriangle			= 3;
	const long c_ag_LineCapNoAnchor			= 16;
	const long c_ag_LineCapSquareAnchor		= 17;
	const long c_ag_LineCapRoundAnchor		= 18;
	const long c_ag_LineCapDiamondAnchor	= 19;
	const long c_ag_LineCapArrowAnchor		= 20;
	const long c_ag_LineCapAnchorMask		= 240;
	const long c_ag_LineCapCustom			= 255;

	const long c_ag_DashCapFlat				= 0;
	const long c_ag_DashCapRound			= 2;
	const long c_ag_DashCapTriangle			= 3;

	const long c_ag_LineJoinMiter			= 0;
	const long c_ag_LineJoinBevel			= 1;
	const long c_ag_LineJoinRound			= 2;
	const long c_ag_LineJoinMiterClipped	= 3;

	const long c_ag_PenAlignmentCenter		= 0;
	const long c_ag_PenAlignmentInset		= 1;
	const long c_ag_PenAlignmentOutset		= 2;
	const long c_ag_PenAlignmentLeft		= 3;
	const long c_ag_PenAlignmentRight		= 4;

	const long c_dirHorizontal				= 1;
	const long c_dirVertical				= -1;

	const long PNG_ENCODER					= 0;
	const long JPG_ENCODER					= 1;
	const long INVALID_ENCODER				= -1;

	const long c_BrushTypeSolid				= 1000;
	const long c_BrushTypeHorizontal		= 2001;
	const long c_BrushTypeVertical			= 2002;
	const long c_BrushTypeDiagonal1			= 2003;
	const long c_BrushTypeDiagonal2			= 2004;
	const long c_BrushTypeCenter			= 2005;
	const long c_BrushTypePathGradient1		= 2006;	
	const long c_BrushTypePathGradient2		= 2007;
	const long c_BrushTypeCylinderHor		= 2008;
	const long c_BrushTypeCylinderVer		= 2009;
	const long c_BrushTypeTexture			= 3008;
	const long c_BrushTypePattern			= 3009;
	const long c_BrushTypeHatch1			= 4009;
	const long c_BrushTypeHatch53			= 4061;
}

namespace StringHelpers
{
    static bool RemoveTagHTMLA(std::string& strXml, const std::string& strBeginTrag, const std::string& strEndTrag)
	{
        std::string::size_type from	= 0;
        std::string::size_type to =	0;

        from = strXml.find(strBeginTrag, from);
        if (std::string::npos == from)
            return false;

        to = strXml.find(strEndTrag, from);
        if (std::string::npos == to)
            return false;

        if ((to != from) && to > from)
		{
            std::string strRes;
			if ( from - 1 > 0 )
                strRes = strXml.substr(0, from);

            strRes += strXml.substr(to + 1, strXml.length() - to - 1);
            strXml = strRes;

            return RemoveTagHTMLA(strXml, strBeginTrag, strEndTrag);
		}

        return false;
	}
    static bool RemoveCommentsA(std::string& strXml)
	{
        std::string::size_type from	= 0;
        std::string::size_type to =	0;

        from = strXml.find("<!--", from);
        if (std::string::npos == from)
            return false;

        to = strXml.find("-->", from);
        if (std::string::npos == to)
            return false;

        if ((to != from) && to > from)
		{
            std::string result;
            if (from - 1 > 0)
                result = strXml.substr(0, from - 1);

            result += strXml.substr(to + 3, strXml.length() - to - 3);

			strXml = result;

            return RemoveCommentsA(strXml);
		}

        return false;
	}
    static bool RemoveTagHTML(std::wstring& strXml, const std::wstring& strBeginTrag, const std::wstring& strEndTrag)
	{
        std::wstring::size_type from	= 0;
        std::wstring::size_type to =	0;

        from = strXml.find(strBeginTrag, from);
        if (std::wstring::npos == from)
            return false;

        to = strXml.find(strEndTrag, from);
        if (std::wstring::npos == to)
            return false;

        if ((to != from) && to > from)
		{
            std::wstring strRes;
            if (from - 1 > 0)
                strRes = strXml.substr(0, from);

            strRes += strXml.substr(to + 1, strXml.length() - to - 1);
			strXml = strRes;

			return RemoveTagHTML(strXml, strBeginTrag, strEndTrag);
		}

		return false;
	}
	static bool RemoveComments(std::wstring& strXml)
	{
		std::wstring::size_type from	= 0;
        std::wstring::size_type to =	0;

        from = strXml.find(L"<!--", from);
        if (std::wstring::npos == from)
            return false;

        to = strXml.find(L"-->", from);
        if (std::wstring::npos == to)
            return false;

        if ((to != from) && to > from)
		{
            std::wstring result;
            if (from - 1 > 0)
                result = strXml.substr(0, from - 1);

            result += strXml.substr(to + 3, strXml.length() - to - 3);

			strXml = result;

            return RemoveComments(strXml);
		}

        return false;
	}
    static bool LoadXmlFile(const std::wstring& File, std::string& strXmlA)
	{
        return NSFile::CFileBinary::ReadAllTextUtf8A(File, strXmlA);
	}

    static std::wstring Tokenize(const std::wstring& value, const std::wstring& find, std::wstring::size_type& off)
    {
        std::wstring::size_type pos = value.find(find, off);
        if (std::wstring::npos == pos)
        {
            off = std::wstring::npos;
            return value.substr(off);
        }
        std::wstring sRet = value.substr(off, pos - off);
        off = pos + 1;
        if (off >= value.length())
            off = std::wstring::npos;
        return sRet;
    }
};

namespace SVG
{
    static double DoubleFromString(std::wstring& strValue)
	{
        const wchar_t* buffer = strValue.c_str();
        int nLen = strValue.length();

		int i = 0;
		for (; i < nLen; ++i)
		{
            if (((buffer[i] >= wchar_t('0')) && (buffer[i] <= wchar_t('9'))) || (buffer[i] == wchar_t('.')))
				continue;
			return 1.0;
		}
        return std::stod(strValue);
	}
}

namespace SVG
{
	enum ENodeType
	{
		ECircle,         
		EClipPath,
		EDefs,       
		EEllipse,
		EG,
		ELine,
		ELinearGradient,
		EPath,
		EPolygon,
		EPolyline,
		ERadialGradient,
		ERectangle,
		EStop,
		ESvg,
		ETitle,
		EText,
		EImage,
		EUse,  
		ESymbol,
		EPattern,

		EGraphicsContainer,

		ENodesCount
	};
	enum Attribute
	{
		Opacity,

		FillColor,
		FillOpacity,
		FillRule,

		StrokeColor,
		StrokeWidth,
		StrokeOpacity,
		StrokeLineCap,
		StrokeLineJoin,
		StrokeMiterLimit,
		StrokeDashArray,
		StrokeDashOffset,

		FontSize,
		FontFamily,
		FontMetrics,
		FontWeight,
		FontStyleAttr,

		FontTextAnchor,
		FontTextAnchorStart,
		FontTextAnchorMiddle,
		FontTextAnchorEnd,

		FontWeightNormal,
		FontWeightBold,

		FontStyleNormal,
		FontStyleItalic,
		FontStyleOblique,
		FontStyleInherit,

		TLinearGradient,

		///

		None
	};
	enum Metrics
	{
		EM,
		EX, 
		PX,
		PT,
		PC,
		CM,
		MM,
		INCH,

		PCT,	//	percent

		UNDEFINED
	};

	struct Point
	{
	public:
		Point () 
		{
			X	=	0.0;
			Y	=	0.0;
		}
		Point (double dX, double dY) : X(dX), Y(dY)
		{

		}

		inline void operator+= (const Point& point)
		{
			X	+=	point.X;
			Y	+=	point.Y;
		}
		inline Point operator+ (const Point& point)
		{
			return Point ( X + point.X, Y + point.Y );
		}
		inline void operator*= (const Point& point)
		{
			X	*=	point.X;
			Y	*=	point.Y;
		}

	public:
		double X;
		double Y;
	};
	struct Rect
	{
	public:
		Rect ()
		{
			X		=	0.0;
			Y		=	0.0;
			Width	=	0.0;
			Height	=	0.0;
		}
		Rect (double dX, double dY, double dWidth, double dHeight) : X(dX), Y(dY), Width(dWidth), Height(dHeight)
		{

		}

		inline double CenterX ()
		{
			return X + Width * 0.5;
		}

		inline double CenterY ()
		{
			return Y + Height * 0.5;
		}
		inline double GetX() const
		{
			return X;
		}
		inline double GetY() const
		{
			return Y;
		}

        inline double GetWidth() const
		{
			return Width;
		}
        inline double GetHeight() const
		{
			return Height;
		}

	public:

		double X;
		double Y;
		double Width;
		double Height;
	};
	struct PointPath
	{
		PointPath (): oPoint()
		{
			code	=	-1;
			subCode =	-1;
		}

		Point	oPoint;
		int		code;
		int		subCode;

		//	M(m)	-	move to
		//	Z(z)	-	close path
		//	L(l)	-	line to
		//	V(v)	-	vertical line
		//	H(h)	-	horizontal line
		//	C(c)	-	curve to			(x1 y1 x2 y2 x y)
		//	Q(q)	-	quadratic bezier	(x1 y1 x y)

	};
	struct StopColor
	{
	public:
		StopColor()
		{
			m_fOffset	=	0.0;
			m_nColor	=	-1;
			m_fOpacity	=	0.0;
		}

        inline bool FromStyle(const std::wstring& oStyle)
		{
            return true;
		}
        inline bool FromXml(XmlUtils::CXmlNode& oXml)
		{
			return TRUE;
		}

	public:
		double			m_fOffset;
		unsigned long	m_nColor;
		double			m_fOpacity;
	};
}

namespace SVG
{
	class StrUtils
	{
	public:
        static inline long LongValue(const std::wstring& value)
        {
            std::wstring::size_type len = value.length(); const wchar_t* buf = value.c_str();
            for (std::wstring::size_type i = 0; i < len; ++i)
			{
                if (isdigit(buf[i]) || (buf[i] == L'-') /* || (value[i] == L'.') || (value[i] == L',') */)
					continue;

                return std::stol(value.substr(0, i));
			}

            return std::stol(value);
		}
        static inline double DoubleValue(const std::wstring& value)
        {
            std::wstring::size_type len = value.length(); const wchar_t* buf = value.c_str();
            for (std::wstring::size_type i = 0; i < len; ++i)
			{
                if (isdigit(buf[i]) || (buf[i] == L'.') || (buf[i] == L',') || (buf[i] == L'-') || (buf[i] == 'e'))
					continue;

                return std::stol(value.substr(0, i));
			}

            return std::stod(value);
		}
        static inline double DoubleValuePct(const std::wstring& sVal)
		{
            if (!sVal.empty())
			{
                if (('%') == sVal[sVal.length() - 1])
				{
                    return std::stod(sVal.substr(0, sVal.length() - 1)) * 0.01;
				}
			}

            return std::stod(sVal);
		}
        static bool DoubleValues(const std::wstring& SourceW, CArray<double>& Values)
		{
            std::wstring number	= L"";
            std::wstring::size_type length = SourceW.length();
            const wchar_t* Source = SourceW.c_str();

            for (std::wstring::size_type i = 0; i < length; ++i)
			{
                if ('-' == Source[i])
				{
					if (i > 1)
					{
                        if ('e' == Source[i - 1])
						{
                            number += Source[i];
							continue;
						}
					}

                    if (!number.empty())
                        Values.Add(std::stod(number));

                    number = L"";
				}

                if (isdigit(Source[i]) || (Source[i] == '.') || (Source[i] == '-') || (Source[i] == 'e'))
				{
                    number += Source[i];
					continue;
				}	

                if (!number.empty())
                    Values.Add(std::stod(number));

                number = L"";
			}

            if (!number.empty())
                Values.Add(std::stod(number));

			return (0 != Values.GetSize());
		}

        static inline std::wstring RemoveSymbol(std::wstring& src, wchar_t symbol)
		{
            std::wstring result;
            const wchar_t* buf = src.c_str();
            std::wstring::size_type len = src.length();
            for (std::wstring::size_type i = 0; i < len; i++)
            {
                wchar_t currentChar = buf[i];
                if (currentChar != symbol)
                    result += currentChar;
            }
			src = result;
            return result;
		}

        static inline std::wstring RemoveSpaces(std::wstring& src)
        {
            return RemoveSymbol(src, ' ');
        }

        static inline Metrics GetMetrics(const std::wstring& value )		//	only for long numbers in value
		{
            const wchar_t* buf = value.c_str();
            std::wstring::size_type len = value.length();
            for (std::wstring::size_type i = 0; i < len; ++i)
			{
                if (isdigit(buf[i]) || (buf[i] == '.') || (buf[i] == ','))
					continue;

                std::wstring metrics = value.substr(i, len - i);

                if (metrics.empty())
					return PX;

                if (metrics == L"px")
					return PX;
                if (metrics == L"mm")
					return MM;
                if (metrics == L"cm")
					return CM;
                if (metrics == L"%")
					return PCT;
                if (metrics == L"in")
					return INCH;
                if (metrics == L"em")  //	default	-	16px
					return EM;
                if (metrics == L"pt")
					return PT;

				return UNDEFINED;
			}

			return UNDEFINED;
		}
        static inline std::wstring UrlRefValue(const std::wstring& sUrlRef)
		{
            if (sUrlRef.length() > 3)
			{
                std::wstring str = sUrlRef;
                str = StrUtils::RemoveSpaces(str);
                const wchar_t* buf = str.c_str();

                if ((buf[0] == 'u') || (buf[1] == 'r') || (buf[2] == 'l'))
				{
                    std::wstring::size_type Oct = str.find(L"#");
                    if (std::wstring::npos != Oct)
					{
                        if (')' == str[str.length() - 1])
                            return str.substr(Oct, str.length() - Oct - 1);

                        return str.substr(Oct, str.length() - Oct);
					}
				}
			}

            return L"";
		}
        static inline bool UrlRefValue2(std::wstring& sUrlRef)
		{
            std::wstring sRet = StrUtils::UrlRefValue(sUrlRef);

            if (!sRet.empty())
			{
				sUrlRef = sRet;
                return true;
			}

            return false;
		}

        static inline int Decode16(wchar_t c)
        {
            if (c >= '0' && c <= '9')
                return c - '0';
            if (c >= 'A' && c <= 'F')
                return 10 + c - 'A';
            if (c >= 'a' && c <= 'f')
                return 10 + c - 'a';
            return 0;
        }

        static std::wstring UrlDecode(const std::wstring& Source)
		{
            std::wstring strDecoded;

            const wchar_t* buf = Source.c_str();
            std::wstring::size_type len = Source.length();

            for ( std::wstring::size_type i = 0; i < len; ++i )
			{
                if ('%' == buf[i] && isxdigit(buf[i + 1]) && isxdigit(buf[i + 2]))
				{
                    int byHex1 = Decode16(buf[i + 1]);
                    int byHex2 = Decode16(buf[i + 2]);

                    strDecoded += (wchar_t)(byHex1 * 16 + byHex2);

					i += 2;
				}
				else 
				{
                    strDecoded += buf[i];
				}
			}

			return strDecoded;
		}
	};
	struct CubicBezier
	{
	public:
		CubicBezier()
		{

		}
		CubicBezier(double X1, double Y1, double CX0, double CY0, double CX1, double CY1)
		{
			m_Points[0].X	=	X1;
			m_Points[0].Y	=	Y1;

			m_Points[1].X	=	CX0;
			m_Points[1].Y	=	CY0;

			m_Points[2].X	=	CX1;
			m_Points[2].Y	=	CY1;
		}
	public:

		Point	m_Points[3];
	};

	class CArcToCubicBezier
	{
	public:
        CArcToCubicBezier(double fX, double fY, double fWidth, double fHeight, double fStartAngle, double fSweepAngle, bool bClockDirection = false)
		{
			AddArc ( fX, fY, fWidth, fHeight, -fStartAngle, -fSweepAngle );
		}
        inline const CArray<CubicBezier>& GetCurves() const
		{
			return m_arrCurves;
		}

	private:

        inline int EllipseArc(double fX, double fY, double fXRad, double fYRad, double fAngle1, double fAngle2, bool bClockDirection)
		{
			int nRet = 0;

			while ( fAngle1 < 0 )
				fAngle1 += 360;

			while ( fAngle1 > 360 )
				fAngle1 -= 360;

			while ( fAngle2 < 0 )
				fAngle2 += 360;

			while ( fAngle2 >= 360 )
				fAngle2 -= 360;

			if ( !bClockDirection )
			{
				if ( fAngle1 <= fAngle2 )
                    nRet = EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, fAngle2, false );
				else
				{
                    nRet += EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, 360, false );
                    nRet += EllipseArc2( fX, fY, fXRad, fYRad, 0, fAngle2, false );
				}
			}
			else
			{
				if ( fAngle1 >= fAngle2 )
                    nRet = EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, fAngle2, true );
				else
				{
                    nRet += EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, 0, true );
                    nRet += EllipseArc2( fX, fY, fXRad, fYRad, 360, fAngle2, true );
				}
			}

			return nRet;
		}
		inline double AngToEllPrm(double fAngle, double fXRad, double fYRad)
		{
			// Функция для перевода реального угла в параметрическое задание эллписа
			// т.е. x= a cos(t) y = b sin(t) - параметрическое задание эллписа.
			// x = r cos(p), y = r sin(p) => t = atan2( sin(p) / b, cos(p) / a );
			return atan2( sin( fAngle ) / fYRad,  cos( fAngle ) / fXRad );
		}
        inline int EllipseArc2(double fX, double fY, double fXRad, double fYRad, double fAngle1, double fAngle2, bool bClockDirection)
		{
			// переведем углы в радианы
			int nRet = 0;

			double dAngle1 = fAngle1 * 3.141592 / 180;
			double dAngle2 = fAngle2 * 3.141592 / 180;

			// Выясним в каких четвертях находятся начальная и конечная точки
			unsigned int nFirstPointQuard  = int(fAngle1) / 90 + 1; 
			unsigned int nSecondPointQuard = int(fAngle2) / 90 + 1;
            nSecondPointQuard = min( 4, std::max( 1, nSecondPointQuard ) );
            nFirstPointQuard  = min( 4, std::max( 1, nFirstPointQuard ) );
			// Проведем линию в начальную точку дуги
			double fStartX = 0.0, fStartY = 0.0, fEndX = 0.0, fEndY = 0.0;

			fStartX = fX + fXRad * cos( AngToEllPrm( dAngle1, fXRad, fYRad ) );
			fStartY = fY + fYRad * sin( AngToEllPrm( dAngle1, fXRad, fYRad ) );

			// _LineTo(fStartX, fStartY);

			// Дальше рисуем по четверям

			double fCurX = fStartX, fCurY = fStartY;
			double dStartAngle = dAngle1;
			double dEndAngle = 0;

			if ( !bClockDirection )
			{
				for( unsigned int nIndex = nFirstPointQuard; nIndex <= nSecondPointQuard; nIndex++ ) 
				{
					if ( nIndex == nSecondPointQuard )
						dEndAngle = dAngle2;
					else
						dEndAngle = (90 * (nIndex ) ) * 3.141592f / 180;
					if ( !( nIndex == nFirstPointQuard ) )
						dStartAngle = (90 * (nIndex - 1 ) ) * 3.141592f / 180;

                    EllipseArc3(fX, fY, fXRad, fYRad, AngToEllPrm( dStartAngle, fXRad, fYRad ), AngToEllPrm( dEndAngle, fXRad, fYRad ), &fEndX, &fEndY, false);
				}
			}
			else
			{
				for( unsigned int nIndex = nFirstPointQuard; nIndex >= nSecondPointQuard; nIndex-- ) 
				{
					if ( nIndex == nFirstPointQuard )
						dStartAngle = dAngle1;
					else
						dStartAngle = (90 * (nIndex ) ) * 3.141592f / 180;
					if ( !( nIndex == nSecondPointQuard ) )
						dEndAngle = (90 * (nIndex - 1 ) ) * 3.141592f / 180;
					else
						dEndAngle = dAngle2;

                    EllipseArc3(fX, fY, fXRad, fYRad, AngToEllPrm( dStartAngle, fXRad, fYRad ), AngToEllPrm( dEndAngle, fXRad, fYRad ), &fEndX, &fEndY, false);
				}
			}

			return nRet;
		}
        inline int EllipseArc3(double fX, double fY, double fXRad, double fYRad, double dAngle1, double dAngle2, double *pfXCur, double *pfYCur, bool bClockDirection = false)
		{
			// Рассчитаем начальную, конечную и контрольные точки
			double fX1  = 0.0, fX2  = 0.0, fY1  = 0.0, fY2  = 0.0;
			double fCX1 = 0.0, fCX2 = 0.0, fCY1 = 0.0, fCY2 = 0.0;

			double fAlpha = sin( dAngle2 - dAngle1 ) * ( sqrt( 4.0 + 3.0 * tan( (dAngle2 - dAngle1) / 2.0 ) * tan( (dAngle2 - dAngle1) / 2.0 ) ) - 1.0 ) / 3.0;

			double fKoef = 1;

			fX1 = fX + fXRad * cos( dAngle1 );
			fY1 = fY + fYRad * sin( dAngle1 );

			fX2 = fX + fXRad * cos( dAngle2 );
			fY2 = fY + fYRad * sin( dAngle2 );

			fCX1 = fX1 - fAlpha * fXRad * sin ( dAngle1 );
			fCY1 = fY1 + fAlpha * fYRad * cos ( dAngle1 );

			fCX2 = fX2 + fAlpha * fXRad * sin ( dAngle2 );
			fCY2 = fY2 - fAlpha * fYRad * cos ( dAngle2 );

			if ( !bClockDirection )
			{
				CubicBezier	oBezier ( fCX1, fCY1, fCX2, fCY2, fX2, fY2 );
				m_arrCurves.Add ( oBezier );

				*pfXCur = fX2; 
				*pfYCur = fY2;
			}
			else
			{
				CubicBezier	oBezier ( fCX1, fCY1, fCX2, fCY2, fX2, fY2 );
				m_arrCurves.Add ( oBezier );

				*pfXCur = fX1; 
				*pfYCur = fY1;
			}

			return 0;
		}
		inline bool AddArc(double fX, double fY, double fWidth, double fHeight, double fStartAngle, double fSweepAngle)
		{
			if (0.0 >= fWidth || 0.0 >= fHeight)
				return false;

			BOOL bClockDirection = FALSE;
			double fEndAngle = 360 - ( fSweepAngle + fStartAngle );
			double fSrtAngle = 360 - fStartAngle;
			if( fSweepAngle > 0 )
				bClockDirection = TRUE;

			return (0 == EllipseArc(fX + fWidth / 2, fY + fHeight / 2, fWidth / 2, fHeight / 2, fSrtAngle, fEndAngle, bClockDirection)) ? true : false;
		}

	private:

        CArray<CubicBezier> m_arrCurves;
	};
}

namespace SVG
{
	struct IRefStorage;
	struct IRef
	{
		virtual ~IRef () 
		{

		}

		virtual BOOL RefreshXLinkSource(IRefStorage* pStorage) = 0;
		virtual BOOL Normalize(const double& dAfX, const double& dAfY) = 0;
	};
	struct ISvgRef: public IRef
	{
		virtual ~ISvgRef () 
		{

		}

		// base
		inline const ENodeType nodeType() const
		{
			return m_nodeType;
		}
        inline const std::wstring& nodeId() const
		{
			return m_nodeId;
		}

		// clip-path
        inline const std::wstring& GetUrlClip() const
		{
			return m_urlClipPath;
		}
		inline void AttachClip(ISvgRef* pClip)
		{
			if (m_pClip)
				return;

			m_pClip = pClip;
		}
		inline ISvgRef* GetClip()
		{
			return m_pClip;
		}

	public:

		// base

        ENodeType    m_nodeType;
        std::wstring m_nodeId;

		// clip-path

        std::wstring m_urlClipPath;			//	id -> url(#AABB)
        ISvgRef*     m_pClip;
	};
	struct IRefStorage : public IRef
	{
		virtual ~IRefStorage ()
		{

		}

		virtual BOOL HashRef(ISvgRef* pRef, BOOL bDef)	=	0;
        virtual BOOL GetRef(const std::wstring& ID, ISvgRef*& pRef)	=	0;

		virtual ISvgRef* Get(long index) = 0;
		virtual long GetSize()	=	0;
		virtual BOOL Push(ISvgRef* pRef) = 0;
	};
}

namespace SVG
{
	class ColorTable
	{
	public:
		ColorTable ()
		{
			InitClrTable ();
		}

        inline int Find(const std::wstring& sKey)
		{
            std::map<std::wstring, unsigned int>::iterator iter = m_Table.find(sKey);
            if (iter == m_Table.end())
                return -1;

            unsigned int clr = iter->second;
            return ((clr & 0xFF) << 16) | ((clr & 0xFF00)) | ((clr & 0xFF0000) >> 16);
		}

	private:
        void InitClrTable();
	private:

        std::map<std::wstring, unsigned int> m_Table;
	};
	class ColorParser
	{
	public:
        static long ColorFromString(const std::wstring& sColor);
        static long ColorFromRgbString(const std::wstring& Rgb);
        static long ColorFromHexString(const std::wstring& Hex);

	private:
		static ColorTable	m_oTable;
	};
	class GradientColor
	{
	public:
		GradientColor()
		{

		}

        bool Add(XmlUtils::CXmlNode& oXml)
		{
			StopColor color;

            color.m_nColor		=	(unsigned long)ColorParser::ColorFromString(oXml.GetAttributeOrValue(L"stop-color", L"#000000"));
            color.m_fOffset		=	StrUtils::DoubleValuePct(oXml.GetAttributeOrValue(L"offset", L"0.0"));
            color.m_fOpacity	=	StrUtils::DoubleValuePct(oXml.GetAttributeOrValue(L"stop-opacity", L"1.0"));

            std::wstring Styles		=	oXml.GetAttributeOrValue(L"style", L"");

            if (!Styles.empty())
			{
                std::wstring::size_type sTok = 0;
                while (std::wstring::npos != sTok)
				{
                    std::wstring sSrc =	StringHelpers::Tokenize(Styles, L";", sTok);
                    if (std::wstring::npos != sTok)
					{
                        std::wstring::size_type index = 0;

						StrUtils::RemoveSpaces(sSrc);
                        std::wstring sAttr = StringHelpers::Tokenize(sSrc, L":", index);
                        if (std::wstring::npos == index)
							continue;

                        std::wstring sVal =	sSrc.substr(index, sSrc.length() - index);
                        if (L"stop-color" == sAttr)
						{
                            color.m_nColor = (unsigned long)ColorParser::ColorFromString(sVal);
                            continue;
						}
                        else if (L"offset" == sAttr)
						{				
                            color.m_fOffset = StrUtils::DoubleValuePct(sVal);
                            continue;
						}
                        else if (L"stop-opacity" == sAttr)
						{
                            color.m_fOpacity = StrUtils::DoubleValuePct(sVal);
                            continue;
						}
					}
				}
			}

			m_colors.Add(color);
            return true;
		}
        inline bool Add(const StopColor& color)
		{			
			m_colors.Add(color);
            return true;
		}

		//
		inline const StopColor& Get(int index) const
		{
			return m_colors[index];
		}
		inline long Count()	const
		{
			return (long)m_colors.GetCount();
		}

	private:
        CArray<StopColor> m_colors;
	};
}

namespace SVG
{
	class ViewBox
	{
	public:
		ViewBox ()
		{
			m_nWidth	=	0;
			m_nHeight	=	0;
			m_nX		=	0;
			m_nY		=	0;

            m_bInUse	=	false;
		}

        bool FromXml(XmlUtils::CXmlNode& oXmlNode)
		{
            return FromString(oXmlNode.GetAttribute(L"viewBox"));
		}
        bool FromString(const std::wstring& Str)
		{
            CArray<double> Values;
			if (StrUtils::DoubleValues(Str, Values))
			{
				if (4 == Values.GetSize())
				{
					m_nX		=	static_cast<int>(Values[0]);
					m_nY		=	static_cast<int>(Values[1]);
					m_nWidth	=	static_cast<int>(Values[2]);
					m_nHeight	=	static_cast<int>(Values[3]);

                    m_bInUse	=	true;

                    return true;
				}
			}

            return false;
		}

		inline int GetX() const
		{
			return m_nX;
		}
		inline int GetY() const
		{
			return m_nY;
		}

		inline int GetWidth() const
		{
			return m_nWidth;
		}
		inline int GetHeight() const
		{
			return m_nHeight;
		}

	public:

		int		m_nWidth;
		int		m_nHeight;
		int		m_nX;
		int		m_nY;

        bool	m_bInUse;
	};
	class UnitSystem
	{
	public:
		UnitSystem ()
		{
            m_bIsValid	=	false;

			m_nFontSize	=	0.0;
			m_dOffSetX	=	0.0;
			m_dOffSetY	=	0.0;
		}

		inline void SetViewBox(int SvgWidth, int SvgHeight, const ViewBox& oBox, Metrics oMetrics)
		{
            m_bIsValid		=	true;

			m_nSvgWidth		=	SvgWidth;
			m_nSvgHeight	=	SvgHeight;

			m_oViewBox		=	oBox;

			if (oBox.m_bInUse)
			{
				if ( 0 != (int)oBox.m_nWidth && 0 != (int)oBox.m_nHeight )
				{
					m_dFactorX	=	(double) (m_nSvgWidth)	/ abs ( (double) (oBox.m_nWidth) );
					m_dFactorY	=	m_dFactorX;//(double) (m_nSvgHeight) / (double) (oBox.m_nHeight);

					m_dOffSetX	=	-oBox.m_nX;// * m_dFactorX;
					m_dOffSetY	=	-oBox.m_nY;// * m_dFactorY;

					m_dFactorQ	=	( sqrt ( (double) ( m_nSvgWidth * m_nSvgWidth + m_nSvgHeight * m_nSvgHeight ) ) ) / 
						( sqrt ( (double) ( oBox.m_nWidth * oBox.m_nWidth + oBox.m_nHeight * oBox.m_nHeight ) ) );

					return;
				}
			}

			if ( MM == oMetrics )
			{
				//m_dFactorX	=	3.543307;
				//m_dFactorY	=	3.543307;
				//m_dFactorQ	=	3.543307;

				//return;
			}

			m_dFactorX	=	1.0;
			m_dFactorY	=	1.0;
			m_dFactorQ	=	1.0;
		}

		inline void SetFontSizeForEM(double Size)
		{
			m_nFontSize	= Size;
		}
		inline double GetFactorFontSize()
		{
			return m_dFactorQ;
		}

		template <typename T>	
		inline T Convert(T value, Metrics m, int direction)		//	'1' - x	; '-1' - y
		{
			if (!m_bIsValid)
				return value;

			if (m == UNDEFINED)	//	in VB CO
			{
				if (1 == direction)			value *=	m_dFactorX;
				else if (-1 == direction)	value	*=	m_dFactorY;
			}
			else if (m == INCH)
			{
				if (1 == direction)			value	*=	90 * m_dFactorX;
				else if (-1 == direction)	value	*=	90 * m_dFactorY;
			}
			else if (m == PCT)
			{
				if (1 == direction)			value	=	m_nSvgWidth * 0.01 * value;
				else if (-1 == direction)	value	=	m_nSvgHeight * 0.01 * value;
			}
			else if (m == EM)
			{
				if (1 == direction)			value	*=	m_nFontSize * m_dFactorX;
				else if (-1 == direction)	value	*=	m_nFontSize * m_dFactorY;
			}
			else if (m == CM)
			{
				if (1 == direction)			value	*=	90 * m_dFactorX / 2.54;
				else if (-1 == direction)	value	*=	90 * m_dFactorY / 2.54;
			}
			else if (m == MM)
			{
				if (1 == direction)			value	*=	90 * m_dFactorX / 25.4;
				else if (-1 == direction)	value	*=	90 * m_dFactorY / 25.4;
			}

			return value;
		}

		inline double GetPX(double value, Metrics m)
		{
			/*	

			"1pt" equals "1.25px" (and therefore 1.25 user units)
			"1pc" equals "15px" (and therefore 15 user units)
			"1mm" would be "3.543307px" (3.543307 user units)
			"1cm" equals "35.43307px" (and therefore 35.43307 user units)
			"1in" equals "90px" (and therefore 90 user units)

			*/

			if (m == PC)		return value * 15.0;
			else if (m == PT)	return value * 1.25;
			else if (m == MM)	return value * 3.543307;
			else if (m == CM)	return value * 35.43307;
			else if (m == INCH)	return value * 90.0;

			return value;
		}
		inline double StrokeWidth(double value, Metrics m) 
		{
			if (m == UNDEFINED)	value *= m_dFactorQ;
			else if (m == INCH)	value *= 90 * m_dFactorQ;
			else if (m == EM)	value *= m_nFontSize * m_dFactorQ;			
			else if (m == PCT)	value  = sqrt ((double)(m_nSvgWidth * m_nSvgWidth + m_nSvgHeight * m_nSvgHeight)) / sqrt (2.0) * 0.01 * value;
			else if (m == CM)	value *= 90 * m_dFactorQ / 2.54;
			else if (m == MM)	value *= 90 * m_dFactorQ / 25.4;

			return value;
		}

		//
		inline const double& OffSetX () const 
		{
			return m_dOffSetX; 
		}
		inline const double& OffSetY () const
		{
			return m_dOffSetY; 
		}
		inline const int& GetWidth () const
		{
			return m_nSvgWidth;
		}
		inline const int& GetHeight () const 
		{
			return m_nSvgHeight; 
		}

	private:

        bool	m_bIsValid;

		int		m_nSvgWidth;
		int		m_nSvgHeight;

		ViewBox	m_oViewBox;

		double	m_dFactorX;
		double	m_dFactorY;

		double	m_dFactorQ;
		double	m_nFontSize;

		double	m_dOffSetX;
		double	m_dOffSetY;
	};
	class Style	//	map добавим по мере надобности
	{
	public:
		Style()
		{
			SetDefault ();
		}

		inline void SetDefault ()
		{
			m_nOpacity				=	1.0;

			m_nFillColor			=	0;//-1;
			m_nFillOpacity			=	1.0;

			m_nStrokeColor			=	-1;
			m_nStrokeWidth			=	1.0;
			m_nStrokeOpacity		=	1.0;
			m_nStrokeLineCap		=	-1;
			m_nStrokeLineJoin		=	c_ag_LineJoinMiter;

			m_pRefFill				=	NULL;
			m_pRefStroke			=	NULL;

			m_bHaveOpacity			=	false;
			m_bHaveFillColor		=	false;
			m_bHaveFillOpacity		=	false;
			m_bHaveStrokeColor		=	false;
			m_bHaveStrokeWidth		=	false;
			m_bHaveStrokeOpacity	=	false;
			m_bHaveStrokeLineCap	=	false;
			m_bHaveStrokeLineJoin	=	false;

			m_IsCSS					=	false;
		}
		inline void ClearOpacity ()
		{
			m_nOpacity				=	1.0;
		}

		//
        inline bool SetStyle (const std::wstring& Styles, BOOL Clear, UnitSystem& oUnitSystem, IRefStorage* pStorage, const ColorTable& Table = ColorTable()) //	from string
		{
			if ( Clear )
			{
				SetDefault ();
			}

			std::wstring::size_type To = 0;
			while ( std::wstring::npos != To )
			{
                std::wstring Source = StringHelpers::Tokenize(Styles, L";", To);
				if (std::wstring::npos != To)
				{
					std::wstring::size_type Ind = 0;

					StrUtils::RemoveSpaces(Source);

					std::wstring attr = StringHelpers::Tokenize(Source, L":", Ind);
					if (std::wstring::npos == Ind)
						continue;

					std::wstring Value = Source.substr(Ind, Source.length() - Ind);

					if (L"opacity" == attr)
					{
						m_nOpacity		=	DoubleFromString(Value);
						m_bHaveOpacity	=	true;
					}
					else if (L"fill" == attr)
					{
						m_fillUrlRef = StrUtils::UrlRefValue(Value);
						if (!m_fillUrlRef.empty())
						{
							if (pStorage) 
							{
								ISvgRef* pDef	=	NULL;
								if (pStorage->GetRef(m_fillUrlRef, pDef))
								{
									m_pRefFill	=	pDef;
									continue;
								}
							}
						}

						m_nFillColor		=	ColorParser::ColorFromString(Value);
						m_bHaveFillColor	=	true;
					}
					else if (L"fill-opacity" == attr)
					{
						m_nFillOpacity		=	DoubleFromString(Value);
						m_bHaveFillOpacity	=	true;
					}
					else if (L"stroke" == attr)
					{				
						std::wstring sUrlRef		=	StrUtils::UrlRefValue(Value);
						if (!sUrlRef.empty())
						{
							if (pStorage) 
							{
								ISvgRef* pDef	=	NULL;
								if (pStorage->GetRef(sUrlRef, pDef))
								{
									m_pRefStroke	=	pDef;
									continue;
								}
							}
						}

						m_nStrokeColor			=	ColorParser::ColorFromString ( Value );
						m_bHaveStrokeColor		=	true;
					}
					else if (L"stroke-width" == attr)
					{
						m_nStrokeWidth			=	DoubleValue (Value, oUnitSystem);
						m_bHaveStrokeWidth		=	true;
					}
					else if (L"stroke-opacity" == attr)
					{
						m_nStrokeOpacity		=	DoubleFromString(Value);
						m_bHaveStrokeOpacity	=	true;
					}
					else if (L"stroke-linecap" == attr)
					{
						m_nStrokeLineCap	=	c_ag_LineCapFlat;

						if (L"round" == Value)
						{
							m_nStrokeLineCap	=	c_ag_LineCapRoundAnchor;
						}

						if (L"square" == Value)
						{
							m_nStrokeLineCap	=	c_ag_LineCapSquareAnchor;
						}

						m_bHaveStrokeLineCap	=	true;
					}
					else if (L"stroke-linejoin"	==	attr)
					{
						m_nStrokeLineJoin	=	c_ag_LineJoinMiter;

						if (L"round" == Value)
						{
							m_nStrokeLineJoin	=	c_ag_LineJoinRound;
						}

						if (L"bevel" == Value)
						{
							m_nStrokeLineJoin	=	c_ag_LineJoinBevel;
						}

						m_bHaveStrokeLineJoin	=	true;
					}
				}
			}

			return true;
		}
		inline bool SetStyle (XmlUtils::CXmlNode& oXmlNode, bool bResetStyle, UnitSystem& oUnitSystem, IRefStorage* pStorage, const ColorTable& Table = ColorTable())
		{
			if (bResetStyle)
				SetDefault ();

			std::wstring FillColor = oXmlNode.GetAttributeOrValue(L"fill");

			std::wstring sUrlRef = StrUtils::UrlRefValue(FillColor);
			if (!sUrlRef.empty())
			{
				ISvgRef* pDef = NULL;
				if (pStorage->GetRef(sUrlRef, pDef))
				{
					m_pRefFill = pDef;
				}
			}
			else
			{
				m_nFillColor = ColorParser::ColorFromString(oXmlNode.GetAttributeOrValue(L"fill", L"#000000"));
			}

			std::wstring strOpacity	= oXmlNode.GetAttributeOrValue(L"opacity"), L"");
			if (!strOpacity.empty())
			{
				m_nOpacity			=	DoubleFromString (strOpacity);
				m_bHaveOpacity		=	true;
			}

			std::wstring strFillOpacity = oXmlNode.GetAttributeOrValue(L"fill-opacity", L"1.0");
			if (!strOpacity.empty())
			{
				m_nFillOpacity		=	DoubleFromString (strFillOpacity);
				m_bHaveFillOpacity	=	true;
			}

			// stroke settings
			std::wstring StrokeColor = oXmlNode.GetAttributeOrValue(L"stroke");

			std::wstring DefSID = StrUtils::UrlRefValue(StrokeColor);
			if (DefSID.length() > 1)
			{
				ISvgRef* pDef	=	NULL;
				if ( pStorage->GetRef ( DefSID, pDef ) )
				{
					m_pRefStroke	=	pDef;
				}
			}
			else
			{
				m_nStrokeColor = ColorParser::ColorFromString(oXmlNode.GetAttributeOrValue(L"stroke", L"#000000"));
			}

			m_nStrokeOpacity	=	DoubleFromString(oXmlNode.GetAttributeOrValue(L"stroke-opacity", L"1.0"));
			m_nStrokeWidth		=	DoubleValue(oXmlNode, L"stroke-width", oUnitSystem); // StrUtils::DoubleValue ( oXmlNode.GetAttributeOrValue ( _T("stroke-width"), _T("1.0") ) );

			std::wstring LineCap = oXmlNode.GetAttributeOrValue(L"stroke-linecap", L"");
			if (!LineCap.empty())
			{
				m_nStrokeLineCap = c_ag_LineCapFlat;

				if (L"round" == LineCap)
				{
					m_nStrokeLineCap	=	c_ag_LineCapRoundAnchor;
				}

				if (L"square" == LineCap)
				{
					m_nStrokeLineCap	=	c_ag_LineCapSquare;
				}
			}

			std::wstring LineJoin = oXmlNode.GetAttributeOrValue(L"stroke-linejoin", L"miter");
			if (!LineJoin.empty())
			{
				m_nStrokeLineJoin = c_ag_LineJoinMiter;

				if (L"round" == LineJoin)
				{
					m_nStrokeLineJoin	=	c_ag_LineJoinRound;
				}

				if (L"bevel" == LineJoin)
				{
					m_nStrokeLineJoin	=	c_ag_LineJoinBevel;
				}
			}

			return true;
		}
		inline bool UpdateStyle (XmlUtils::CXmlNode& oXmlNode, UnitSystem& oUnitSystem, IRefStorage* pStorage, const ColorTable& Table = ColorTable())
		{
			// FILL

			std::wstring strFillColor = oXmlNode.GetAttributeOrValue(L"fill");

			if (!strFillColor.empty())
			{
				std::wstring sUrlRef = StrUtils::UrlRefValue(strFillColor);
				if (!sUrlRef.empty())
				{
					ISvgRef* pDef	=	NULL;
					if (pStorage->GetRef(sUrlRef, pDef))
						m_pRefFill	=	pDef;
				}
				else
				{
					m_nFillColor		=	ColorParser::ColorFromString(oXmlNode.GetAttributeOrValue(L"fill", L"#000000"));
					m_bHaveFillColor	=	true;
				}
			}

			std::wstring strOpacity	= oXmlNode.GetAttributeOrValue(L"opacity", L"");
			if (!strOpacity.empty())
			{
				m_nOpacity			=	DoubleFromString(strOpacity);
				m_bHaveOpacity		=	true;
			}

			std::wstring strFillOpacity = oXmlNode.GetAttributeOrValue(L"fill-opacity", L"1.0");
			if (!strOpacity.empty())
			{
				m_nFillOpacity		=	DoubleFromString (strFillOpacity);
				m_bHaveFillOpacity	=	true;
			}

			// STROKE
			std::wstring StrokeColor = oXmlNode.GetAttributeOrValue(L"stroke");
			if (StrokeColor.length() > 1)
			{
				std::wstring sUrlRef = StrUtils::UrlRefValue(StrokeColor);
				if (!sUrlRef.empty())
				{
					ISvgRef* pDef	=	NULL;
					if (pStorage->GetRef(sUrlRef, pDef))
					{
						m_pRefStroke	=	pDef;
					}
				}
				else
				{
					m_nStrokeColor		=	ColorParser::ColorFromString(oXmlNode.GetAttributeOrValue(L"stroke", L"#000000"));
					m_bHaveStrokeColor	=	true;
				}
			}

			if (!oXmlNode.GetAttributeOrValue(L"stroke-opacity").empty())
			{
				m_nStrokeOpacity		=	DoubleFromString(oXmlNode.GetAttributeOrValue(L"stroke-opacity", L"1.0"));
				m_bHaveStrokeOpacity	=	true;
			}

			if (!oXmlNode.GetAttributeOrValue(L"stroke-width").empty())
			{
				m_nStrokeWidth			=	DoubleValue(oXmlNode, L"stroke-width", oUnitSystem); // StrUtils::DoubleValue ( oXmlNode.GetAttributeOrValue ( _T("stroke-width"), _T("1.0") ) );
				m_bHaveStrokeWidth		=	true;
			}

			std::wstring LineCap = oXmlNode.GetAttributeOrValue(L"stroke-linecap", L"");
			if (!LineCap.empty())
			{
				if (L"round" == LineCap)
				{
					m_nStrokeLineCap		=	c_ag_LineCapRoundAnchor;
					m_bHaveStrokeLineCap	=	true;
				}

				if (L"square" == LineCap)
				{
					m_nStrokeLineCap		=	c_ag_LineCapSquare;
					m_bHaveStrokeLineCap	=	true;
				}
			}

			std::wstring strLineJoin = oXmlNode.GetAttributeOrValue(L"stroke-linejoin", L"miter");
			if (!strLineJoin.empty())
			{
				m_nStrokeLineJoin			=	c_ag_LineJoinMiter;

				if (L"round" == strLineJoin)
				{
					m_nStrokeLineJoin		=	c_ag_LineJoinRound;
					m_bHaveStrokeLineJoin	=	true;
				}

				if (L"bevel" == strLineJoin)
				{
					m_nStrokeLineJoin		=	c_ag_LineJoinBevel;
					m_bHaveStrokeLineJoin	=	true;
				}
			}

			return true;
		}

		// EX 
		inline Style(const std::wstring& Styles, bool Clear, UnitSystem& oUnitSystem, IRefStorage* pStorage, const ColorTable& Table = ColorTable())
		{
			SetStyle(Styles, Clear, oUnitSystem, pStorage, Table);
		}
		inline bool UpdateStyle (const std::wstring& Styles, UnitSystem& oUnitSystem, IRefStorage* pStorage, const ColorTable& Table = ColorTable())
		{
			return SetStyle(Styles, false, oUnitSystem, pStorage, Table);
		}
		inline void Combine(const Style& oSrc)
		{
			// opacity
			if(oSrc.ValidAttribute(Opacity))
			{
				m_nOpacity *= oSrc.m_nOpacity;
			}
		}

		//
		inline long LongAttribute (SVG::Attribute style) const
		{
			GET_ATTRIBUTEN(FillColor);
			GET_ATTRIBUTEN(StrokeColor);
			GET_ATTRIBUTEN(StrokeLineCap);
			GET_ATTRIBUTEN(StrokeLineJoin);

			return 0;
		}
		inline double DoubleAttribute (SVG::Attribute style) const
		{
			GET_ATTRIBUTED(Opacity);
			GET_ATTRIBUTED(FillOpacity);
			GET_ATTRIBUTED(StrokeWidth);
			GET_ATTRIBUTED(StrokeOpacity);

			return 0.0;
		}
		inline void ClearFillColor()
		{
			m_nFillColor = -3;
		}

		//
		inline bool ValidAttribute (Attribute nStyle) const
		{
			VALIDATE_ATTRIBUTE (Opacity);
			VALIDATE_ATTRIBUTE (FillColor);
			VALIDATE_ATTRIBUTE (FillOpacity);
			VALIDATE_ATTRIBUTE (StrokeColor);
			VALIDATE_ATTRIBUTE (StrokeWidth);
			VALIDATE_ATTRIBUTE (StrokeOpacity);
			VALIDATE_ATTRIBUTE (StrokeLineCap);
			VALIDATE_ATTRIBUTE (StrokeLineJoin);

			return false;
		}
		inline static void UpdateValidateAttributes (const Style& oSrc, Style& oTo)
		{
			if (oSrc.ValidAttribute(Opacity) && (false == oTo.ValidAttribute(Opacity)))
				oTo.m_nOpacity			=	oSrc.m_nOpacity;
			else if(oSrc.ValidAttribute(Opacity) && oTo.ValidAttribute(Opacity))
				oTo.m_nOpacity			*=	oSrc.m_nOpacity;

			if (oSrc.ValidAttribute(FillColor))
				oTo.m_nFillColor		=	oSrc.m_nFillColor;
			if (oSrc.ValidAttribute(FillOpacity))
				oTo.m_nFillOpacity		=	oSrc.m_nFillOpacity;
			if (oSrc.ValidAttribute(StrokeColor))
				oTo.m_nStrokeColor		=	oSrc.m_nStrokeColor;
			if (oSrc.ValidAttribute(StrokeWidth))
				oTo.m_nStrokeWidth		=	oSrc.m_nStrokeWidth;
			if (oSrc.ValidAttribute(StrokeOpacity))
				oTo.m_nStrokeOpacity	=	oSrc.m_nStrokeOpacity;
			if (oSrc.ValidAttribute(StrokeLineCap))
				oTo.m_nStrokeLineCap	=	oSrc.m_nStrokeLineCap;
			if (oSrc.ValidAttribute(StrokeOpacity))
				oTo.m_nStrokeLineJoin	=	oSrc.m_nStrokeLineJoin;
		}

		//
		inline ISvgRef* GetFill() const 
		{
			return	m_pRefFill;
		}
		inline ISvgRef* GetStroke() const 
		{
			return	m_pRefStroke;
		}

		inline const CString& GetFillUrlRef() const
		{
			return m_fillUrlRef;
		}

		inline void SetCSS(BOOL isCSS)
		{
			m_IsCSS	=	isCSS;
		}
		inline bool IsCSS() const 
		{
			return m_IsCSS;
		}

	private:

		inline static double DoubleValue (XmlUtils::CXmlNode& oXmlNode, std::wstring strAttr, UnitSystem& oUnitSystem)
		{
			return DoubleValue (oXmlNode.GetAttribute (strAttr), oUnitSystem);
		}
		inline static double DoubleValue (std::wstring& sVal, UnitSystem& us)
		{
			if (0 == sVal.GetLength())
				return 0.0;

			double number = StrUtils::DoubleValue(sVal);
			SVG::Metrics ms = StrUtils::GetMetrics(sVal);

			return us.StrokeWidth (number, ms);
		}

	private:

		bool		m_bHaveOpacity;
		bool		m_bHaveFillColor;
		bool		m_bHaveFillOpacity;
		bool		m_bHaveStrokeColor;
		bool		m_bHaveStrokeWidth;
		bool		m_bHaveStrokeOpacity;
		bool		m_bHaveStrokeLineCap;
		bool		m_bHaveStrokeLineJoin;

		double		m_nOpacity;

		long		m_nFillColor;
		double		m_nFillOpacity;

		// stroke
		long		m_nStrokeColor;
		double		m_nStrokeWidth;
		double		m_nStrokeOpacity;
		long		m_nStrokeLineCap;
		long		m_nStrokeLineJoin;

		ISvgRef*	m_pRefFill;
		ISvgRef*	m_pRefStroke;
		std::wstring		m_fillUrlRef;

		bool		m_IsCSS;
	};
	class StyleStack
	{
	public:
		StyleStack()
		{

		}

		inline bool Push(const Style& oStyle, bool combine = true)
		{
			if ((0 == m_styles.GetCount()) || (false == combine))
			{
				m_styles.Add (oStyle);
				return true;
			}

			if (combine)
			{
				Style oStyleTo = oStyle;
				oStyleTo.Combine(GetTop());
				m_styles.Add(oStyleTo);

				return true;
			}

			m_styles.Add(oStyle);
			return true;
		}
		inline bool Pop()
		{
			if (m_styles.GetCount())
			{
				m_styles.RemoveAt(m_styles.GetCount() - 1);
				return true;
			}

			return false;
		}
		inline Style GetTop()
		{
			Style oStyle;

			if (m_styles.GetCount())
				oStyle = m_styles[m_styles.GetCount() - 1];

			return oStyle;
		}

	private:

		CArray<Style> m_styles;
	};
	class FontStyle
	{
	public:
		FontStyle ()
		{
			SetDefault ();
		}

		bool SetStyle(const std::wstring& src)
		{
			/*
			<text id="svg_7" text-decoration="underline" 
			font-style="italic"
			fill="#cc0000" 
			dominant-baseline="text-before-edge" 
			space="preserve" 
			text-anchor="start" 
			font-weight="normal" 
			font-family="Arial"
			font-size="40pt" 
			y="100" 
			x="100">Simple Text</text>
			*/

			return true;
		}
		bool SetStyle(XmlUtils::CXmlNode& oXml)
		{
			m_nFontSize			=	StrUtils::DoubleValue(oXml.GetAttribute(L"font-size"));
			m_nFontMetrics		=	StrUtils::GetMetrics(oXml.GetAttribute(L"font-size"));
			m_FontFamily		=	oXml.GetAttributeOrValue(L"font-family", L"Arial");

			m_nFontTextAnchor	=	FontTextAnchorStart;

			std::wstring anchor = oXml.GetAttributeOrValue(L"text-anchor", L"start");
			if (L"middle" == anchor)
				m_nFontTextAnchor	=	FontTextAnchorMiddle;
			if (L"end" == anchor)
				m_nFontTextAnchor	=	FontTextAnchorEnd;

			m_nFontWeight			=	FontWeightNormal;

			std::wstring FontWeight	= oXml.GetAttributeOrValue(L"font-weight", L"");
			if (L"bold" == FontWeight)
				m_nFontWeight		=	FontWeightBold;

			m_nFontStyleAttr		=	FontStyleNormal;

			std::wstring StyleAttr = oXml.GetAttributeOrValue(L"font-style", L"");
			if (L"italic" == StyleAttr)
				m_nFontStyleAttr	=	FontStyleItalic;
			if (L"oblique" == StyleAttr)
				m_nFontStyleAttr	=	FontStyleItalic;	//	FontStyleOblique;
			//if (L"inherit" == FontWeight)
			//	m_nFontStyleAttr	=	FontStyleInherit;

			return true;
		}
		bool SetStyle(const std::wstring& Styles, bool Clear)
		{
			if (Clear)
			{
				SetDefault();
			}

			std::wstring::size_type To = 0;
			while (std::wstring::npos != To)
			{
				std::wstring Source	= StringHelpers::Tokenize(Styles, L";", To);
				if (std::wstring::npos != To)
				{
					std::wstring::size_type Ind = 0;

					StrUtils::RemoveSpaces(Source);

					std::wstring Attribute = StringHelpers::Tokenize(Source, L":", Ind);
					if (std::wstring::npos == Ind)
						continue;

					std::wstring Value = Source.substr(Ind, Source.length() - Ind));
					if (L"font-size" == Attribute)
					{
						m_nFontSize		=	StrUtils::DoubleValue ( Value );
						m_nFontMetrics	=	StrUtils::GetMetrics ( Value );
						continue;
					}

					if (L"font-family" == Attribute)
					{
						m_FontFamily	=	Value;
						continue;
					}

					if (L"text-anchor" == Attribute)
					{			
						m_nFontTextAnchor	=	FontTextAnchorStart;
						if (L"middle" == Value)
							m_nFontTextAnchor	=	FontTextAnchorMiddle;
						if (L"end" == Value)
							m_nFontTextAnchor	=	FontTextAnchorEnd;

						continue;
					}

					if (L"font-weight") == Attribute)
					{
						m_nFontWeight		=	FontWeightNormal;
						if (L"bold" == Value)
							m_nFontWeight	=	FontWeightBold;
					}

					if (L"font-style") == Attribute)
					{
						m_nFontStyleAttr		=	FontStyleNormal;

						if (L"italic" == Value)
							m_nFontStyleAttr	=	FontStyleItalic;
						if (L"oblique" == Value)
							m_nFontStyleAttr	=	FontStyleItalic;	//	FontStyleOblique;
						//if (L"inherit" == FontWeight)
						//	m_nFontWeight		=	FontStyleInherit;
					}
				}
			}

			return true;
		}
		bool UpdateStyle(XmlUtils::CXmlNode& oXmlNode)
		{
			if (!oXmlNode.GetAttribute ( L"font-size" ).empty())
				m_nFontSize			=	StrUtils::DoubleValue ( oXmlNode.GetAttribute ( L"font-size") );

			if (!oXmlNode.GetAttribute ( L"font-size" ).empty())
				m_nFontMetrics		=	StrUtils::GetMetrics ( oXmlNode.GetAttribute ( _T("font-size") ) );

			if (!oXmlNode.GetAttributeOrValue ( L"font-family", L"Arial" ).empty())
				m_FontFamily		=	oXmlNode.GetAttributeOrValue ( L"font-family", L"Arial");

			if (!oXmlNode.GetAttributeOrValue ( L"text-anchor", L"" ).empty())
			{
				m_nFontTextAnchor	=	FontTextAnchorStart;

				std::wstring anchor		=	oXmlNode.GetAttributeOrValue ( L"text-anchor", L"start" );
				if ( L"middle" == anchor )
					m_nFontTextAnchor	=	FontTextAnchorMiddle;
				if ( L"end" == anchor )
					m_nFontTextAnchor	=	FontTextAnchorEnd;
			}

			if (!oXmlNode.GetAttributeOrValue ( L"font-weight", L"" ).empty())
			{
				m_nFontWeight			=	FontWeightNormal;

				std::wstring FontWeight	= oXmlNode.GetAttributeOrValue(L"font-weight", L"");
				if (L"bold" == FontWeight)
					m_nFontWeight		=	FontWeightBold;
			}

			if (!oXmlNode.GetAttributeOrValue(L"font-style", L"").empty())
			{
				m_nFontStyleAttr		=	FontStyleNormal;

				std::wstring StyleAttr = oXmlNode.GetAttributeOrValue(L"font-style", L"");
				if ( L"italic" == StyleAttr )
					m_nFontStyleAttr	=	FontStyleItalic;
				if ( L"oblique" == StyleAttr )
					m_nFontStyleAttr	=	FontStyleItalic;	//	FontStyleOblique;
				//if ( L"inherit" == FontWeight )
				//	m_nFontStyleAttr	=	FontStyleInherit;
			}

			return true;
		}

		inline double DoubleAttribute(SVG::Attribute style) const
		{
			GET_ATTRIBUTED(FontSize);

			return 0.0;
		}
		inline long LongAttribute(SVG::Attribute style) const
		{
			GET_ATTRIBUTEN(FontMetrics);
			GET_ATTRIBUTEN(FontTextAnchor);
			GET_ATTRIBUTEN(FontWeight);
			GET_ATTRIBUTEN(FontStyleAttr);

			return 0;
		}
		inline std::wstring GetAttribute(SVG::Attribute style) const
		{
			GET_ATTRIBUTE(FontFamily);

			return L"";
		}
		inline void SetDefault ()
		{
			m_FontFamily		=	L"";
			m_nFontTextAnchor	=	FontTextAnchorStart;
			m_nFontSize			=	0.0;
			m_nFontWeight		=	FontWeightNormal;
			m_nFontStyleAttr	=	FontStyleNormal;
		}

	private:

		std::wstring m_FontFamily;
		int		m_nFontTextAnchor;
		int		m_nFontWeight;
		int		m_nFontStyleAttr;
		std::wstring m_Preserve;
		std::wstring m_DominantBaseline;
		std::wstring m_TextDecoration;

		double	m_nFontSize;
		Metrics	m_nFontMetrics;
	};

	class CStyleCSS
	{
	public:
		CStyleCSS() : m_IsValid(false)
		{

		}

		inline bool Read (XmlUtils::CXmlNode& oXml, UnitSystem& us, IRefStorage* model, const ColorTable& colors = ColorTable())
		{
			// TODO: универсальный селектор													* {margin:0; padding:0;}
			// TODO: селекторами элементов												    p {font-family: Garamond, serif;}
			// TODO: селекторами классов											    .note {color: red; background: yellow; font-weight: bold;}
			// TODO: селекторами идентификаторов								  #paragraph1 {margin: 0;}
			// TODO: селекторами атрибутов					 a[href="http://www.somesite.com"]{font-weight:bold;}
			// TODO: селекторами потомков (контекстными селекторами)	div#paragraph1 p.note {color: red;}
			// TODO: селекторами дочерних элементов								   p.note > b {color: green;}
			// TODO: селекторами сестринских элементов								   h1 + p {font-size: 24pt;}
			// TODO: селекторами псевдоклассов										 a:active {color:yellow;}
			// TODO: селекторами псевдоэлементов							  p::first-letter {font-size: 32px;}

			std::wstring source = oXml.GetText();

			StrUtils::RemoveSymbol(source, ' ');
			StrUtils::RemoveSymbol(source, '\n');
			StrUtils::RemoveSymbol(source, '\t');

			if (source.empty())
				return false;

			std::wstring::size_type begin	=	0;
			std::wstring::size_type right	=	0;

			while (std::wstring::npos != right)
			{
				right = source.find(L"}", right);
				if (std::wstring::npos == right)
					break;

				std::wstring src = source.substr(begin, right);
				std::wstring::size_type left = src.find(L"{", left);
				if (std::wstring::npos == left)
					break;

				std::wstring selector = src.substr(0, left);
				if (!selector.empty())
				{
					Style style;
					style.SetStyle(src.substr(left + 1, src.length() - left), true, us, model, colors);

					ReadSelList(selector, ',');
					for (int i = 0; i < m_selectors.GetCount(); ++i)
					{
						selector = m_selectors[i];
						if ('.' == selector.c_str[0])
						{
							StrUtils::RemoveSymbol('.');
							m_classStyles.SetAt(selector, style);
						}
						else
						{
							AddTagStyle(m_selectors[i], style);
						}

						m_IsValid	=	true;
					}
				}

				right++;
				begin = right;
			}

			return true;
		}

		inline bool GetStyleForType(int tag, Style& style)
		{
			if (m_typeStyles[tag].IsCSS())
			{
				style = m_typeStyles[tag];
				return true;
			}

			return false;
		}
		inline bool GetClassStyle(const std::wstring& name, Style& style)
		{
			std::map<std::wstring, Style>::iterator iter = m_classStyles.find(name);
			if (iter == m_classStyles.end())
				return false;

			style = iter->second;
			return true;
		}

		inline bool IsValid()
		{
			return m_IsValid;
		}

	private:

		inline bool AddTagStyle(const std::wstring& selector, Style& style)
		{
			if (L"rect"				== selector)	{ m_typeStyles[ERectangle]	=	style;	m_typeStyles[ERectangle].SetCSS(true);	return true; }
			else if (L"ellipse"		== selector)	{ m_typeStyles[EEllipse]	=	style;	m_typeStyles[EEllipse].SetCSS(true);	return true; }
			else if (L"circle"		== selector)	{ m_typeStyles[ECircle]		=	style;	m_typeStyles[ECircle].SetCSS(true);		return true; }		
			else if (L"path"		== selector)	{ m_typeStyles[EPath]		=	style;	m_typeStyles[EPath].SetCSS(true);		return true; }
			else if (L"polygon"		== selector)	{ m_typeStyles[EPolygon]	=	style;	m_typeStyles[EPolygon].SetCSS(true);	return true; }
			else if (L"polyline"	== selector)	{ m_typeStyles[EPolyline]	=	style;	m_typeStyles[EPolyline].SetCSS(true);	return true; }
			else if (L"text"		== selector)	{ m_typeStyles[EText]		=	style;	m_typeStyles[EText].SetCSS(true);		return true; }
			else if (L"image"		== selector)	{ m_typeStyles[EImage]		=	style;	m_typeStyles[EImage].SetCSS(true);		return true; }
			else if (L"line"		== selector)	{ m_typeStyles[ELine]		=	style;	m_typeStyles[ELine].SetCSS(true);		return true; }

			//else if (L"symbol"	== selector)	{ m_typeStyles[ESymbol]				=	style;	m_typeStyles[ESymbol].SetCSS(true);					return true; }
			//else if (L"g")		== selector)	{ m_typeStyles[EGraphicsContainer]	=	style;	m_typeStyles[EGraphicsContainer].SetCSS(true);		return true; }

			return false;
		}
		inline void ReadSelList(const std::wstring& src, wchar_t splitter)
		{
			m_selectors.RemoveAll();

			std::wstring selector;

			if (!src.empty())
			{
				std::wstring::size_type symbol = 0, begin = 0;
				while (std::wstring::npos != symbol)
				{
					symbol = src.find(splitter, symbol);
					if (std::wstring::npos == symbol)
					{
						if (src.length() - begin >= 1)
						{
							selector = src.substr(begin, src.length() - begin);
							if (!selector.empty())
								m_selectors.Add(selector);
						}

						break;
					}

					selector = src.substr(begin, symbol);
					if (selector.length())
						m_selectors.Add(selector);

					symbol++;
					begin = symbol;
				}
			}
		}

	private:
		bool					m_IsValid;

		std::map<std::wstring, Style>	m_classStyles;					//	селекторы классов
		Style							m_typeStyles[ENodesCount];		//	селекторы элементов
		CArray<std::wstring>			m_selectors;

		// TODO: остальные типа селекторов
	};
}

namespace SVG
{
	class Matrix
	{
	public:
		Matrix()
		{
			Identity();
		}
		Matrix(double mat[9])
		{
			memcpy (m_fMat, mat, 9 * sizeof(double));
		}
		Matrix(double m1, double m2, double m3, double m4, double m5, double m6, double m7, double m8, double m9) 
		{
			m_fMat[0] = m1;
			m_fMat[1] = m2;
			m_fMat[2] = m3;

			m_fMat[3] = m4;
			m_fMat[4] = m5;
			m_fMat[5] = m6;

			m_fMat[6] = m7;
			m_fMat[7] = m8;
			m_fMat[8] = m9;
		}
		Matrix(const CString& transforms, UnitSystem& us)
		{
			FromString (transforms, us);
		}

		inline Matrix Copy() const
		{
			return (*this);
		}
		inline const double& operator [] (int i) const
		{
			return m_fMat[i]; 
		}
		inline Matrix& operator *= (const Matrix& transform)
		{
			double mat[9];

			for (int i = 0 ; i < 3; ++i)
			{
				for( int k = 0; k < 3; ++k)
				{
					mat [i*3 + k] = 0;

					for (int j = 0; j < 3; ++j)
					{
						mat[i*3 + k] += m_fMat[i * 3 + j] * transform.m_fMat [j*3 + k];
					}
				}
			}

			*this = Matrix(mat);

			return (*this);
		}
		inline Matrix& Move(double fX, double fY)
		{
			m_fMat[2] += fX;
			m_fMat[5] += fY;

			return (*this);
		}
		inline Matrix& Translate(double dX, double dY)
		{
			m_fMat[2] = dX;
			m_fMat[5] = dY;

			return (*this);
		}

		//
		inline static Matrix ScaleTransform(double dX, double dY)
		{
			Matrix mat;

			mat.m_fMat[0] = dX;
			mat.m_fMat[4] = dY;

			return mat;
		}
		inline static Matrix RotateTransform(double angle)
		{
			Matrix mat;

			mat.m_fMat[0] =	cos(angle);
			mat.m_fMat[1] =	-sin(angle);

			mat.m_fMat[3] = sin(angle);
			mat.m_fMat[4] = cos(angle);

			return mat;
		}
		inline static Matrix TranslateTransform(double dX, double dY)
		{
			Matrix mat;

			mat.m_fMat[2] = dX;
			mat.m_fMat[5] = dY;

			return mat;		
		}
		inline static Matrix ApplyAt(double dX, double dY, const Matrix& transform)
		{
			Matrix mat;

			mat.m_fMat[2] = -dX;
			mat.m_fMat[5] = -dY;

			mat	*=	transform; 

			mat.m_fMat[2] += dX;
			mat.m_fMat[5] += dY;

			return mat;		
		}
		inline static Matrix RotateAtPoint(const Point& point, const double& angle)
		{
			Matrix mat;

			mat.m_fMat[6] = -point.X;
			mat.m_fMat[7] = -point.Y;

			mat *= Matrix::RotateTransform (angle);

			mat.m_fMat[6] += point.X;
			mat.m_fMat[7] += point.Y;

			return mat;		
		}

		//
		inline Point TranformPoint (const Point& point)
		{
			return Point(point.X * m_fMat[0] + point.Y * m_fMat [3] + m_fMat[6], point.X * m_fMat[1] + point.Y * m_fMat [4] + m_fMat[7]);
		}

	private:

		inline void Identity()
		{
			m_fMat[0] = 1;
			m_fMat[1] = 0;
			m_fMat[2] = 0;

			m_fMat[3] = 0;
			m_fMat[4] = 1;
			m_fMat[5] = 0;

			m_fMat[6] = 0;
			m_fMat[7] = 0;
			m_fMat[8] = 1;
		}
		inline BOOL FromString(const CString& sTransforms, UnitSystem& us)
		{
			CSimpleArray<CString> arrMatrix;
			if (GetTranforms(sTransforms, arrMatrix))
			{
				Matrix matrix;				

				for (int i = 0; i < arrMatrix.GetSize(); ++i)
					matrix *= Matrix::ReadMatrix(arrMatrix[i], us);

				*this = matrix;

				return TRUE;
			}

			return FALSE;
		}
		inline static CString GetTransform(const CString& strMat, int& index)
		{
			index = 0;
			CString strText = strMat.Tokenize ( _T("("), index);
			if (-1 == index)
			{
				index = -1;
				return CString(_T(""));
			}

			int length = strText.GetLength();
			for (int i = 0; i < length; ++i)
			{
				if (_T(' ') == strText[i])
				{
					strText.Delete(i); 
					i--;
					continue;
				}
			}

			return strText;
		}
		inline static Matrix ReadMatrix(const CString& sSrc, UnitSystem& us)
		{
			int index = -1;
			CString matType = GetTransform(sSrc, index);
			if (0 == matType.GetLength() || -1 == index)
				return Matrix();

			CString sMat = sSrc.Mid(index, sSrc.GetLength() - index);
			if (0 == sMat.GetLength())
				return Matrix();

			CSimpleArray<double> mat;
			if (StrUtils::DoubleValues(sMat, mat))
			{
				int count = mat.GetSize();
				if (CString(_T("matrix")) == matType)
				{					
					Matrix oTransform;

					/*

					oTransform.m_fMat [ 0 ]	=	mat [ 0 ];														//	a
					oTransform.m_fMat [ 1 ]	=	mat [ 2 ];														//	c
					oTransform.m_fMat [ 2 ]	=	mat [ 4 ];		//	e	//	tx
					oTransform.m_fMat [ 3 ]	=	mat [ 1 ];														//	b
					oTransform.m_fMat [ 4 ]	=	mat [ 3 ];														//	d
					oTransform.m_fMat [ 5 ]	=	mat [ 5 ];		//	f	//	ty
					oTransform.m_fMat [ 6 ]	=	0.0;
					oTransform.m_fMat [ 7 ]	=	0.0;
					oTransform.m_fMat [ 8 ]	=	1.0;

					*/

					//matrix(0<a> 1<b> 2<c> 3<d> 4<e> 5<f>)
					oTransform.m_fMat[0] = mat[0];														//	a
					oTransform.m_fMat[1] = mat[2];														//	c
					oTransform.m_fMat[2] = us.Convert(mat[4], UNDEFINED, c_dirHorizontal);		//	e	//	tx
					oTransform.m_fMat[3] = mat[1];														//	b
					oTransform.m_fMat[4] = mat[3];														//	d
					oTransform.m_fMat[5] = us.Convert(mat[5], UNDEFINED, c_dirVertical);		//	f	//	ty
					oTransform.m_fMat[6] = 0.0;
					oTransform.m_fMat[7] = 0.0;
					oTransform.m_fMat[8] = 1.0;

					return oTransform;
				}
				else if (CString ( _T("translate") ) == matType)
				{
					if (1 == count)	return	Matrix::TranslateTransform(us.Convert(mat[0], UNDEFINED, c_dirHorizontal), 0.0);
					if (2 == count)	return	Matrix::TranslateTransform(us.Convert(mat[0], UNDEFINED, c_dirHorizontal), us.Convert(mat[1], UNDEFINED, c_dirVertical));
				}
				else if (CString(_T("scale")) == matType)
				{
					if (1 == count)	return Matrix::ScaleTransform(mat[0], mat[0]);
					if (2 == count)	return Matrix::ScaleTransform(mat[0], mat[1]);
				}
				else if (CString ( _T("rotate") ) == matType)
				{
					if (1 == count)	return	Matrix::RotateTransform(mat[0] * M_PI / 180.0);
					if (3 == count)
					{
						Matrix oTransform = Matrix::TranslateTransform(mat[1], mat[2]);

						oTransform	*=	Matrix::RotateTransform(mat[0] * M_PI / 180);
						oTransform	*=	Matrix::TranslateTransform(-mat[1], -mat[2]);

						return	oTransform;
					}
				}
				else if ( CString ( _T("skewX") ) == matType)
				{
					Matrix oTransform;
					oTransform.m_fMat[1] = tan(mat[0] * M_PI / 180.0);		//	c

					return oTransform;
				}
				else if (CString(_T("skewY")) == matType)
				{
					Matrix oTransform;
					oTransform.m_fMat[3] = tan(mat[0] * M_PI / 180.0);		//	b

					return oTransform;
				}
			}

			return Matrix();
		}
		inline static BOOL GetTranforms(const CString& strMat, CSimpleArray<CString>& refTransforms)
		{
			int index = 0;
			while (-1 != index)
			{
				refTransforms.Add(strMat.Tokenize( _T(")"), index));
			}

			return (0 != refTransforms.GetSize());
		}

	private:

		double	m_fMat[9];
	};
	class MatrixStack
	{
	public:
		MatrixStack()
		{

		}

		inline BOOL Push(const Matrix& transform, BOOL combine = TRUE)	//	каждая последующая трансформация применяется к вершине стэка
		{
			if ((0 == m_transforms.GetCount()) || (FALSE == combine))
			{
				m_transforms.Add(transform);
				return TRUE;
			}

			if (combine)
			{
				Matrix top = GetTop ();
				top *= transform;

				m_transforms.Add(top);
				return TRUE;
			}

			m_transforms.Add(transform);
			return TRUE;
		}
		inline BOOL Pop()
		{
			if (m_transforms.GetCount())
			{
				m_transforms.RemoveAt(m_transforms.GetCount() - 1);
				return TRUE;
			}

			return FALSE;
		}

		inline const Matrix GetTop() const 
		{
			Matrix transform;

			if (m_transforms.GetCount())
				transform = m_transforms[m_transforms.GetCount() - 1];

			return transform;
		}
		inline const Matrix GetFinal()
		{
			Matrix transform;

			for (size_t i = 0; i < m_transforms.GetCount(); ++i)
				transform *= m_transforms[i];

			return transform;
		}

	private:
		CAtlArray <Matrix>	m_transforms;
	};
	class PathParser
	{
	public:
		PathParser()
		{
			m_bIsClose	=	FALSE;
		}
		PathParser(UnitSystem& oUs, const CString& path)
		{
			FromString (oUs, path);
		}

		inline BOOL FromString(UnitSystem& oUnitSystem, const CString& path)
		{
			m_Points.RemoveAll ();

			int To	=	0;
			BOOL	EndSegment	=	FALSE;
			CString Tokens = _T("mMLlCcVvHhCcQqTtSsaAhHvV");

			int count = path.GetLength();
			for (int i = 0; i < count; ++i)
			{
				WCHAR symbol = path [i];

				//	move to
				if (_T('m') == symbol || _T('M') == symbol || _T('l') == symbol || _T('L') == symbol || _T('t') == symbol || _T('T') == symbol)
				{
					To = i + 1;

					CString Source	 =	path.Tokenize ( Tokens, To );

					// ATLTRACE ( _T("%c : - %s\n"), symbol, Source );

					CSimpleArray<double> Values;
					if (StrUtils::DoubleValues(Source, Values))
					{
						if ((symbol == _T('M')) || (symbol == _T('m')))
						{
							int Segments	=	(int)Values.GetSize () / 2;
							if (Segments > 0)
							{
								PointPath oPointM;
								oPointM.code	=	path[i];
								oPointM.oPoint	=	Point ( Values [ 0 ], Values [ 1 ] );
								oPointM.subCode	=	path[i];
								m_Points.Add ( oPointM );
							}

							int iNextCode = (symbol == _T('M')) ? _T('L') : _T('l');
							for ( int j = 1; j <  Segments; ++j )
							{
								PointPath oPoint;
								oPoint.code		=	iNextCode;
								oPoint.oPoint	=	Point ( Values [ 0 + 2 * j ], Values [ 1 + 2 * j ] );
								oPoint.subCode	=	path[i];

								m_Points.Add ( oPoint );	
								EndSegment	=	FALSE;
								//	ATLTRACE ( _T("LineTo : %c, -  %f, %f\n"), oPoint.code, oPoint.oPoint.X, oPoint.oPoint.Y );
							}
						}
						else
						{
							if (m_Points.GetCount() > 0 && EndSegment == FALSE )
							{
								if ( symbol == _T('M') )
								{
									PointPath oEndPoint;
									oEndPoint.code		=	 _T('Z');
									m_Points.Add ( oEndPoint );
								}

								if ( symbol == _T('m') )
								{
									PointPath oEndPoint;
									oEndPoint.code		=	 _T('z');
									m_Points.Add ( oEndPoint );
								}
							}

							int Segments	=	(int)Values.GetSize () / 2;
							for ( int j = 0; j <  Segments; ++j )
							{
								PointPath oPoint;
								oPoint.code	=	symbol;

								if ( m_Points.GetCount() > 0 && EndSegment == FALSE )
								{
									if ( oPoint.code == _T('M') )
										oPoint.code = _T('L');

									if ( oPoint.code == _T('m') )
										oPoint.code = _T('l');
								}

								oPoint.oPoint	=	Point ( Values [ 0 + 2 * j ], Values [ 1 + 2 * j ] );

								m_Points.Add ( oPoint );	

								EndSegment	=	FALSE;

								//	ATLTRACE ( _T("LineTo : %c, -  %f, %f\n"), oPoint.code, oPoint.oPoint.X, oPoint.oPoint.Y );
							}
						}
					}

					if (To == -1)
					{
						m_Points.RemoveAll ();
						return FALSE;
					}
				}
				else if ( _T('h') == symbol || _T('H') == symbol ||   _T('v') == symbol || _T('V') == symbol )
				{
					To = i + 1;

					CString Source	=	path.Tokenize ( Tokens, To );

					CSimpleArray<double> Values;
					if (StrUtils::DoubleValues(Source, Values))
					{
						for ( int j = 0; j < Values.GetSize(); ++j )
						{
							PointPath oPoint;
							oPoint.code	= symbol;

							if ( _T('h') == symbol || _T('H') == symbol )
								oPoint.oPoint.X	=	Values [ j ];

							if ( _T('v') == symbol || _T('V') == symbol )
								oPoint.oPoint.Y	=	Values [ j ];

							m_Points.Add(oPoint);
						}
					}

					if ( To == -1 )
					{
						m_Points.RemoveAll ();
						return FALSE;
					}
				}			
				else if ( _T('a') == symbol || _T('A') == symbol )	// Elliptical arc curve
				{
					To = i + 1;

					CString Source	=	path.Tokenize ( Tokens, To );

					CSimpleArray<double> Values;
					if (StrUtils::DoubleValues(Source, Values))
					{
						//rx ry x-axis-rotation large-arc-flag sweep-flag x y

						int Size	=	( Values.GetSize () / 7 ) * 7;
						for ( int j = 0; j < Size; j += 7 )
						{
							PointPath oPoint;
							oPoint.code	=	symbol;

							oPoint.oPoint	=	Point ( Values [ j ], Values [ j + 1 ] );		//	rx ry
							m_Points.Add ( oPoint );

							oPoint.oPoint	=	Point ( Values [ j + 2 ], Values [ j + 3 ] );	//	x-axis-rotation large-arc-flag
							m_Points.Add ( oPoint );	

							oPoint.oPoint	=	Point ( Values [ j + 4 ], Values [ j + 4 ] );	//	sweep-flag
							m_Points.Add ( oPoint );	

							oPoint.oPoint	=	Point ( Values [ j + 5 ], Values [ j + 6 ] );	//	x y
							m_Points.Add ( oPoint );	
						}
					}

					if ( To == -1 )
					{
						m_Points.RemoveAll();
						return FALSE;
					}
				}				
				else if ( _T('q') == symbol || _T('Q') == symbol || _T('s') == symbol || _T('S') == symbol )	// Quadratic Bezier 
				{
					To = i + 1;

					CString Source	=	path.Tokenize ( Tokens, To );

					CSimpleArray<double> Values;
					if (StrUtils::DoubleValues(Source, Values))
					{
						PointPath oPoint;
						oPoint.code	=	symbol;

						oPoint.oPoint	=	Point ( Values [ 0 ], Values [ 1 ] );
						m_Points.Add ( oPoint );

						oPoint.oPoint	=	Point ( Values [ 2 ], Values [ 3 ] );
						m_Points.Add ( oPoint );	

						// ATLTRACE ( _T("LineTo : %f, %f "), oPoint.oPoint.X, oPoint.oPoint.Y );
					}

					if ( To == -1 )
					{
						m_Points.RemoveAll ();
						return FALSE;
					}
				}				
				else if ( _T('c') == symbol || _T('C') == symbol )	// Cubic  Bezier 
				{
					To = i + 1;

					CString Source	=	path.Tokenize ( Tokens, To );

					// ATLTRACE ( _T("%c : - %s\n"), symbol, Source );

					CSimpleArray<double> Values;
					if (StrUtils::DoubleValues(Source, Values))
					{
						int Size	=	( Values.GetSize () / 6 ) * 6;
						for ( int j = 0; j < Size; j += 6 )
						{
							PointPath oPoint;
							oPoint.code	=	symbol;

							oPoint.oPoint	=	Point ( Values [ j ], Values [ j + 1 ] );
							m_Points.Add ( oPoint );

							oPoint.oPoint	=	Point ( Values [ j + 2 ], Values [ j + 3 ] );
							m_Points.Add ( oPoint );	

							oPoint.oPoint	=	Point ( Values [ j + 4 ], Values [ j + 5 ] );
							m_Points.Add ( oPoint );	

							// ATLTRACE ( _T("add curve : [ %f, %f ] \n"), oPoint.oPoint.X, oPoint.oPoint.Y );
						}
					}

					if (To == -1)
					{
						m_Points.RemoveAll();
						return FALSE;
					}
				}				
				else if (_T('z') == symbol || _T('Z') == symbol)	//	close path
				{
					PointPath point;
					point.code		=	symbol;

					m_Points.Add(point);	

					m_bIsClose		=	TRUE;
					EndSegment		=	TRUE;
				}				
			}

			count = (long)m_Points.GetCount();
			for (long i = 0; i < count; ++i)
			{
				if (_T('a') == m_Points [i].code || _T('A') == m_Points [i].code)
				{
					m_Points [ i ].oPoint.X			=	oUnitSystem.Convert ( m_Points [ i ].oPoint.X, UNDEFINED, c_dirHorizontal );
					m_Points [ i ].oPoint.Y			=	oUnitSystem.Convert ( m_Points [ i ].oPoint.Y, UNDEFINED, c_dirVertical );

					m_Points [ i + 3 ].oPoint.X		=	oUnitSystem.Convert ( m_Points [ i + 3 ].oPoint.X, UNDEFINED, c_dirHorizontal );
					m_Points [ i + 3 ].oPoint.Y		=	oUnitSystem.Convert ( m_Points [ i + 3 ].oPoint.Y, UNDEFINED, c_dirVertical );

					i += 3;

					continue;
				}

				m_Points [ i ].oPoint.X		=	oUnitSystem.Convert ( m_Points [ i ].oPoint.X, UNDEFINED, c_dirHorizontal );
				m_Points [ i ].oPoint.Y		=	oUnitSystem.Convert ( m_Points [ i ].oPoint.Y, UNDEFINED, c_dirVertical );
			}

			return TRUE;
		}
		inline CAtlArray <PointPath>& GetPoints ()
		{
			return m_Points;
		}
		inline BOOL IsClose()
		{
			return m_bIsClose;
		}
		inline void SetPoint(long index, const Point& val)
		{
			if ((long)m_Points.GetCount() > index)
				m_Points[index].oPoint = val;
		}
		inline Point GetPoint(long index)
		{
			if ((long)m_Points.GetCount() > index)
				return m_Points[index].oPoint;

			return Point();
		}

	private:

		BOOL					m_bIsClose;
		CAtlArray <PointPath>	m_Points;
	};
	class ImageBase64		//	for inner data image's
	{
	public:
		ImageBase64 ()
		{
			m_pBuffer		=	NULL;
			m_nBufferSize	=	0L;
		}
		~ImageBase64 ()
		{
			if ( m_pBuffer )
			{
				delete [] m_pBuffer;
				m_pBuffer		=	NULL;

				m_nBufferSize	=	0L;
			}
		}

		inline BOOL FromString (const CString& Src)
		{
			if ( m_pBuffer )
			{
				RELEASEOBJECT(m_pBuffer);

				m_nBufferSize	=	0L;
			}

			CString BASE64	=	CString ( _T("base64") );
			int to			=	Src.Find ( BASE64, 0 );
			if ( -1 != to )
			{
				to				=	Src.Find ( _T(","), to );
				CString Options	=	Src.Mid ( 0, to + 1 );	

				int EncoderType	=	INVALID_ENCODER;
				if ( -1 != Options.Find ( _T("jpeg"), 0 ) )
					EncoderType	=	JPG_ENCODER;

				if ( -1 != Options.Find ( _T("png"), 0 ) )
					EncoderType	=	PNG_ENCODER;

				if ( INVALID_ENCODER != EncoderType )
				{
					CString buffer	=	Src.Mid ( Options.GetLength (), Src.GetLength () - Options.GetLength () );

					int Ind = -1;
					while ( 0 != Ind )
						Ind = buffer.Remove ( _T(' ') );		//	в некоторых SVG были пробелы

					return CreateImage ( (BYTE*) ( buffer.GetBuffer () ), buffer.GetLength (), EncoderType );
				}
			}

			return FALSE;
		}
		inline BOOL GetImage (IUnknown*& image)
		{
			return ImageBase64::EncodeBufferToImageCOM(m_pBuffer, m_nBufferSize, image);
		}

	private:

		BOOL CreateImage (BYTE* pBuffer, unsigned long Length, int ImageEncoder = INVALID_ENCODER);

		static BOOL EncodeBufferToImageCOM (const BYTE* pBuffer, const unsigned long& ImageSize, IUnknown*& pImage);
		static BOOL GdiImageToImageCOM (Gdiplus::Bitmap* pBitmap, IUnknown*& pImage);
		static BOOL Base64Decode(LPTSTR szSrc, int nSrcLen, BYTE *pbDest, int *pnDestLen) throw();

	private:

		BYTE*			m_pBuffer;
		int				m_nBufferSize;
	};
}

namespace SVG
{
	class RefElement : public ISvgRef
	{
	public:
		virtual ~RefElement()
		{

		}

		virtual BOOL FromXml (CXmlNode& oXml, IRefStorage* model, UnitSystem& oUs)
		{
			m_XLinkRef				=	oXml.GetAttribute(_T("xlink:href"));
			m_nodeId				=	oXml.GetAttribute(_T("id"));
			m_model					=	model;

			m_gradientTransform		=	Matrix(oXml.GetAttribute(_T("gradientTransform")), oUs);

			if (m_XLinkRef.GetLength())
			{
				StrUtils::RemoveSpaces (m_XLinkRef);

				if (_T('#') == m_XLinkRef[0])
				{
					m_XLinkRef = m_XLinkRef.Mid(1, m_XLinkRef.GetLength()-1);
				}
			}

			return FALSE;
		}
		virtual BOOL FromString (CString Str, IRefStorage* pStorage)
		{
			return FALSE;
		}

		virtual BOOL Normalize (const double& dAddFMX, const double& dAddFMY) = 0;
	protected:
		inline static double DoubleValue (CXmlNode& oXml, CString oAttr, UnitSystem& oUs, long direction)
		{
			CString sVal			=	oXml.GetAttribute(oAttr);
			if (sVal.GetLength())
			{
				if (_T('%') == sVal[sVal.GetLength() - 1])
				{
					return _tstof(sVal.Mid(0, sVal.GetLength() - 1)) * 0.01;
				}
			}

			double dVal				=	StrUtils::DoubleValue(sVal);
			SVG::Metrics oValMet	=	StrUtils::GetMetrics(sVal);

			return oUs.Convert(dVal, oValMet, direction);
		}

	protected:

		IRefStorage*	m_model;
		CString			m_XLinkRef;

		Matrix			m_gradientTransform;
	};
	class LinearGradient : public RefElement
	{
	public:
		LinearGradient ()
		{
			m_nodeType	=	ELinearGradient;
			m_pClip		=	NULL;

			m_begin		=	Point(0, 0);
			m_end		=	Point(1, 0);
		}

		virtual BOOL FromXml(CXmlNode& oXml, IRefStorage* model, UnitSystem& oUs)
		{
			RefElement::FromXml(oXml, model, oUs);

			if (oXml.GetAttributeOrValue(_T("x1")).GetLength())
				m_begin.X	=	DoubleValue(oXml, _T("x1"), oUs, c_dirHorizontal);
			if (oXml.GetAttributeOrValue(_T("y1")).GetLength())
				m_begin.Y	=	DoubleValue(oXml, _T("y1"), oUs, c_dirVertical);

			if (oXml.GetAttributeOrValue(_T("x2")).GetLength())
				m_end.X		=	DoubleValue(oXml, _T("x2"), oUs, c_dirHorizontal);
			if (oXml.GetAttributeOrValue(_T("y2")).GetLength())
				m_end.Y		=	DoubleValue(oXml, _T("y2"), oUs, c_dirVertical);

			m_gradientUnits	=	oXml.GetAttributeOrValue(_T("gradientUnits"), _T(""));

			XML::IXMLDOMNodeListPtr comList = NULL;
			if (oXml.GetNodes(comList))
			{
				CXmlNodes nodes;
				if (nodes.FromXmlNodes(comList))
				{
					for (long i = 0; i < nodes.GetCount(); ++i)
					{
						CXmlNode oXml2;
						if (nodes.GetAt(i, oXml2))
						{
							if (_T("stop") == oXml2.GetName())
							{
								m_Color.Add(oXml2);
							}
						}
					}
				}
			}

			return FALSE;
		}
		virtual BOOL FromString(const CString& Str, IRefStorage* model, UnitSystem& oUs)
		{
			return FALSE;
		}
		virtual BOOL RefreshXLinkSource(IRefStorage* model)
		{
			if (m_XLinkRef.GetLength())
			{
				ISvgRef* pDef	=	NULL;
				if (model->GetRef(m_XLinkRef, pDef))
				{
					if (ELinearGradient ==  pDef->nodeType())
					{
						LinearGradient* gradient = static_cast<LinearGradient*>(pDef);
						if (gradient)
						{
							for (int i = 0; i < gradient->GetColors().Count(); ++i)
								m_Color.Add(gradient->GetColors().Get(i));

							return TRUE;
						}
					}
				}
			}

			return FALSE;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			return FALSE;
		}

		//

		inline const GradientColor& GetColors()
		{
			return m_Color;
		}
		inline const CString& GetXml()
		{
			if (0 == m_sXml.GetLength())
			{
				m_sXml.Format(_T("<linearGradient x1='%f' y1='%f' x2='%f' y2='%f' gradientUnits ='%s' gradientTransform='matrix(%f, %f, %f, %f, %f, %f)' sourceType='svg' >"),
					m_begin.X, m_begin.Y, m_end.X, m_end.Y, m_gradientUnits,
					m_gradientTransform[0], m_gradientTransform[1],
					m_gradientTransform[3], m_gradientTransform[4],
					m_gradientTransform[2], m_gradientTransform[5]);

				CString sVal;

				for (int i = 0; i < m_Color.Count(); ++i)
				{
					sVal.Format(_T("<stop stop-color = '%d' offset ='%f' stop-opacity ='%f'/>"), m_Color.Get(i).m_nColor, m_Color.Get(i).m_fOffset, m_Color.Get(i).m_fOpacity);
					m_sXml += sVal;
				}

				m_sXml += _T("</linearGradient>");
			}

			return m_sXml;
		}

	private:

		GradientColor	m_Color;
		CString			m_sXml;
		CString			m_gradientUnits;

		Point			m_begin;
		Point			m_end;
	};
	class RadialGradient : public RefElement
	{
	public:
		RadialGradient ()
		{
			m_nodeType	=	ERadialGradient;
			m_pClip		=	NULL;
		}

		virtual BOOL FromXml(CXmlNode& oXml, IRefStorage* pStorage, UnitSystem& oUs)
		{
			RefElement::FromXml(oXml, pStorage, oUs);

			m_c.X	=	DoubleValue(oXml, _T("cx"), oUs, c_dirHorizontal);
			m_c.Y	=	DoubleValue(oXml, _T("cy"), oUs, c_dirVertical);

			m_f.X	=	DoubleValue(oXml, _T("fx"), oUs, c_dirHorizontal);
			m_f.Y	=	DoubleValue(oXml, _T("fy"), oUs, c_dirVertical);
					
			m_R		=	DoubleValue(oXml, _T("r"), oUs, c_dirHorizontal);

			m_gradientUnits	= oXml.GetAttributeOrValue(_T("gradientUnits"), _T(""));

			XML::IXMLDOMNodeListPtr pXmlNodes = NULL;
			if (oXml.GetNodes(pXmlNodes))
			{
				CXmlNodes oXmlNodes;
				if (oXmlNodes.FromXmlNodes(pXmlNodes))
				{
					for (long i = 0; i < oXmlNodes.GetCount(); ++i)
					{
						CXmlNode oXmlNode2;
						if (oXmlNodes.GetAt(i, oXmlNode2))
						{
							if (_T("stop") == oXmlNode2.GetName())
							{
								m_Color.Add(oXmlNode2);
							}
						}
					}
				}
			}

			return FALSE;
		}
		virtual BOOL FromString(const CString& Str, IRefStorage* pStorage, UnitSystem& oUs)
		{
			return FALSE;
		}
		virtual BOOL RefreshXLinkSource(IRefStorage* pStorage)
		{
			if (m_XLinkRef.GetLength())
			{
				ISvgRef* pDef = NULL;
				if (pStorage->GetRef (m_XLinkRef, pDef))
				{
					if (ELinearGradient == pDef->nodeType())
					{
						LinearGradient* gradient = static_cast<LinearGradient*>(pDef);
						if (gradient)
						{
							for (int i = 0; i < gradient->GetColors().Count(); ++i)
								m_Color.Add(gradient->GetColors().Get(i));

							return TRUE;
						}
					}
				}
			}

			return FALSE;
		}
		virtual BOOL Normalize(const double& dAddFMX, const double& dAddFMY)
		{
			return FALSE;
		}

		//

		inline const GradientColor& GetColors() const
		{
			return m_Color;
		}
		inline const CString& GetXml()
		{
			if (0 == m_sXml.GetLength())
			{
				m_sXml.Format(_T("<radialGradient cx='%f' cy='%f' fx='%f' fy='%f' r='%f' gradientUnits='%s' gradientTransform='matrix(%f, %f, %f, %f, %f, %f)' sourceType='svg' >"),
					m_c.X, m_c.Y, m_f.X, m_f.Y, m_R,
					m_gradientUnits,
					m_gradientTransform[0], m_gradientTransform[1],
					m_gradientTransform[3], m_gradientTransform[4],
					m_gradientTransform[2], m_gradientTransform[5]);

				CString sVal;

				for (int i = 0; i < m_Color.Count(); ++i)
				{
					sVal.Format(_T("<stop stop-color = '%d' offset ='%f' stop-opacity ='%f'/>"), m_Color.Get(i).m_nColor, m_Color.Get(i).m_fOffset, m_Color.Get(i).m_fOpacity);
					m_sXml += sVal;
				}

				m_sXml += _T("</radialGradient>");
			}

			return m_sXml;
		}

	private:

		CString			m_gradientUnits;
		GradientColor	m_Color;		
		Point			m_c;
		Point			m_f;
		double			m_R;
		CString			m_sXml;
	};
}

namespace SVG
{
	class DrawElement : public ISvgRef
	{
	public:
		virtual ~DrawElement()
		{

		}

		virtual BOOL FromXml (CXmlNode& oXml, UnitSystem& oUs)
		{
			m_nodeId		=	oXml.GetAttribute(_T("id"));
			m_className		=	oXml.GetAttribute(_T("class"));

			m_pClip			=	NULL;
			m_urlClipPath	=	oXml.GetAttribute(_T("clip-path"));
			StrUtils::UrlRefValue2(m_urlClipPath);

			return TRUE;
		}
		virtual BOOL FromXml (CString sXml, UnitSystem& oUs)
		{
			return FALSE;
		}

		//
		virtual void SetStyle(const Style& oStyle)
		{
			m_oStyle = oStyle;
		}
		virtual const Style& GetStyle()
		{
			return m_oStyle;
		}
		virtual void SetTransform (const Matrix& oTransform)
		{
			m_oTransform	=	oTransform;
		}
		virtual const Matrix& GetTransform () const 
		{
			return m_oTransform;
		}
		virtual const CString& ClassName ()	const
		{
			return m_className;
		}

		//
		virtual BOOL Normalize (const double& dAddFMX, const double& dAddFMY) 
		{

			return FALSE;
		}

		// link
		virtual BOOL RefreshXLinkSource (IRefStorage* pStorage)
		{
#ifdef _DEBUG
			// ATLTRACE (L"NOT IMPLEMENTED - RefreshXLinkSource: id - %s\n", nodeId());
#endif
			return FALSE;
		}
	protected:

		inline static double DoubleValue (CXmlNode& oXml, CString oAttr, UnitSystem& oUs, long direction)
		{
			double dVal				=	StrUtils::DoubleValue(oXml.GetAttribute(oAttr));
			SVG::Metrics oValMet	=	StrUtils::GetMetrics(oXml.GetAttribute(oAttr));

			return oUs.Convert(dVal, oValMet, direction);
		}

	protected:
		Style	m_oStyle;
		Matrix	m_oTransform;
		CString	m_className;
	};
	class Line : public DrawElement
	{
	public:
		Line ()
		{
			m_nodeType	=	ELine;
			m_pClip		=	NULL;
		}

		virtual BOOL FromXml(CXmlNode& oXml, UnitSystem& oUs)
		{
			DrawElement::FromXml (oXml, oUs);

			m_From.X	=	DoubleValue(oXml, _T("x1"), oUs, c_dirHorizontal);
			m_From.Y	=	DoubleValue(oXml, _T("y1"), oUs, c_dirVertical);
			m_To.X		=	DoubleValue(oXml, _T("x2"), oUs, c_dirHorizontal);
			m_To.Y		=	DoubleValue(oXml, _T("y2"), oUs, c_dirVertical);

			return FALSE;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			m_From	*=	Point(dAfX, dAfY);
			m_To	*=	Point(dAfX, dAfY);

			return TRUE;
		}

		inline const Point& GetFrom() const
		{
			return	m_From;
		}
		inline const Point& GetTo() const
		{
			return	m_To;
		}

	private:

		Point m_From;
		Point m_To;
	};
	class Rectangle : public DrawElement
	{
	public:
		Rectangle ()
		{
			m_nodeType	=	ERectangle;
			m_pClip		=	NULL;

			m_Arc.X		=	0.0;
			m_Arc.Y		=	0.0;
		}

		virtual BOOL FromXml(CXmlNode& oXml, UnitSystem& oUs)
		{
			DrawElement::FromXml(oXml, oUs);

			m_From.X	=	DoubleValue(oXml, _T("x"), oUs, c_dirHorizontal);
			m_From.Y	=	DoubleValue(oXml, _T("y"), oUs, c_dirVertical);
			m_To.X		=	m_From.X + DoubleValue(oXml, _T("width"),  oUs, c_dirHorizontal);
			m_To.Y		=	m_From.Y + DoubleValue(oXml, _T("height"), oUs, c_dirVertical);

			m_Arc.X		=	DoubleValue(oXml, _T("rx"), oUs, c_dirHorizontal);
			m_Arc.Y		=	DoubleValue(oXml, _T("ry"), oUs, c_dirVertical);

			return TRUE;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			m_From	*=	Point(dAfX, dAfY);
			m_To	*=	Point(dAfX, dAfY);
			m_Arc	*=	Point(dAfX, dAfY);

			return FALSE;
		}

		inline const Point& GetFrom() const
		{
			return	m_From;
		}
		inline const Point& GetTo() const
		{
			return	m_To;
		}
		inline const Point& GetArc() const
		{
			return	m_Arc;
		}

	private:

		Point m_From;
		Point m_To;

		Point m_Arc;
	};
	class Ellipse : public DrawElement
	{
	public:
		Ellipse ()
		{
			m_nodeType	=	EEllipse;
			m_pClip		=	NULL;
		}

		virtual BOOL FromXml(CXmlNode& oXml, UnitSystem& oUs)
		{
			DrawElement::FromXml(oXml, oUs);

			m_C.X	=	DoubleValue(oXml, _T("cx"), oUs, c_dirHorizontal);
			m_C.Y	=	DoubleValue(oXml, _T("cy"), oUs, c_dirVertical);
			m_R.X	=	DoubleValue(oXml, _T("rx"), oUs, c_dirHorizontal);
			m_R.Y	=	DoubleValue(oXml, _T("ry"), oUs, c_dirVertical);

			return TRUE;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			m_C	*=	Point(dAfX, dAfY);
			m_R	*=	Point(dAfX, dAfY);

			return TRUE;
		}

	public:
		Point	m_C;
		Point	m_R;
	};
	class Circle : public DrawElement
	{
	public:
		Circle ()
		{
			m_nodeType	=	ECircle;
			m_pClip		=	NULL;
		}

		virtual BOOL FromXml(CXmlNode& oXml, UnitSystem& oUs)
		{
			DrawElement::FromXml (oXml, oUs);

			m_C.X	=	DoubleValue(oXml, _T("cx"), oUs, c_dirHorizontal);
			m_C.Y	=	DoubleValue(oXml, _T("cy"), oUs, c_dirVertical);
			m_R.X	=	DoubleValue(oXml, _T("r"),  oUs, c_dirHorizontal);
			m_R.Y	=	m_R.X;

			return TRUE;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			m_C	*=	Point(dAfX, dAfY);
			m_R	*=	Point(dAfX, dAfY);

			return TRUE;
		}

	public:

		Point	m_C;
		Point	m_R;
	};
	class Path : public DrawElement
	{
	public:
		Path ()
		{
			m_nodeType	=	EPath;
			m_pClip		=	NULL;
		}

		virtual BOOL FromXml (CXmlNode& oXml, UnitSystem& oUs)
		{
			DrawElement::FromXml(oXml, oUs);

			m_oUs = oUs;

			m_oParser.FromString(oUs, oXml.GetAttribute(_T("d")));

			return FALSE;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			long count = (long)m_oParser.GetPoints().GetCount();
			for (long i = 0; i < count; ++i)
			{
				Point oPoint	=	m_oParser.GetPoint(i);
				oPoint			*=	Point (dAfX, dAfY);
				m_oParser.SetPoint(i, oPoint);
			}

			return TRUE;
		}

		inline PathParser& GetPath ()
		{
			return m_oParser;
		}
		inline double GetX (long index)
		{
			return m_oParser.GetPoints()[index].oPoint.X;
		}
		inline double GetY (long index)
		{
			return m_oParser.GetPoints()[index].oPoint.Y;
		}
		inline const Point& Get (long index)
		{
			return m_oParser.GetPoints()[index].oPoint;
		}

		inline int GetCode (long index)
		{
			return m_oParser.GetPoints()[index].code;
		}
		inline int GetSubCode (long index)
		{
			return m_oParser.GetPoints()[index].subCode;
		}
		inline long GetSize ()
		{
			return (long)m_oParser.GetPoints().GetCount();
		}

	private:

		inline static double DoubleValue(UnitSystem& oUnitSystem, double Value, long Direction)
		{			
			return	oUnitSystem.Convert(Value, UNDEFINED, Direction);
		}

	private:

		PathParser	m_oParser;
		UnitSystem	m_oUs;
		CString		m_ClipRule;
	};
	class Polyline : public DrawElement
	{
	public:
		Polyline ()
		{
			m_nodeType	=	EPolyline;
			m_pClip		=	NULL;
		}

		virtual BOOL FromXml (CXmlNode& oXml, UnitSystem& oUs)
		{
			DrawElement::FromXml (oXml, oUs);
			m_points.RemoveAll ();
			StrUtils::DoubleValues(oXml.GetAttribute(_T("points")), m_points);

			for (size_t i = 0; i < m_points.GetCount(); i += 2)
			{
				m_points[i]		=	DoubleValue(oUs, m_points[i], c_dirHorizontal);
				m_points[i+1]	=	DoubleValue(oUs, m_points[i+1], c_dirVertical);
			}

			return (m_points.GetCount() > 0);
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			for (size_t i = 0; i < m_points.GetCount(); i += 2)
			{
				m_points[i]		*=	dAfX;
				m_points[i + 1]	*=	dAfY;
			}

			return TRUE;
		}

		inline double GetX (long index) const
		{
			return m_points[index * 2];
		}
		inline double GetY (long index) const
		{
			return m_points[index * 2 + 1];
		}
		inline long GetSize () const
		{
			return (long)m_points.GetCount() / 2;
		}

	private:

		inline static double DoubleValue(UnitSystem& oUnitSystem, double Value, long Direction)
		{			
			return oUnitSystem.Convert(Value, UNDEFINED, Direction);
		}

	protected:

		CAtlArray <double> m_points;		
	};
	class Polygon : public Polyline
	{
	public:
		Polygon ()
		{
			m_nodeType	=	EPolygon;
			m_pClip		=	NULL;
		}

		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			for (size_t i = 0; i < m_points.GetCount(); i += 2)
			{
				m_points[i]		*=	dAfX;
				m_points[i + 1]	*=	dAfY;
			}

			return TRUE;
		}
	};
	class Text : public DrawElement
	{
	public:
		Text ()
		{
			m_nodeType	=	EText;
			m_pClip		=	NULL;
		}

		virtual BOOL FromXml ( CXmlNode& oXmlNode, UnitSystem& oUnitSystem )
		{
			DrawElement::FromXml ( oXmlNode, oUnitSystem );

			m_oUs	=	oUnitSystem;

			m_Pos.X			=	DoubleValue ( oXmlNode, _T("x"), oUnitSystem, c_dirHorizontal );
			m_Pos.Y			=	DoubleValue ( oXmlNode, _T("y"), oUnitSystem, c_dirVertical );
			m_Shift.X		=	DoubleValue ( oXmlNode, _T("dx"), oUnitSystem, c_dirHorizontal );
			m_Shift.Y		=	DoubleValue ( oXmlNode, _T("dy"), oUnitSystem, c_dirVertical );

			m_Source		=	oXmlNode.GetText ();

			// стиль может задаваться вообще где то вверху по дереву
			m_oFontStyle.UpdateStyle ( oXmlNode );

			return TRUE;
		}
		virtual BOOL Normalize ( const double& dAddFMX, const double& dAddFMY )
		{
			m_Pos	*=	Point ( dAddFMX, dAddFMY );
			m_Shift	*=	Point ( dAddFMX, dAddFMY );

			return TRUE;
		}

		inline const FontStyle& GetFontStyle ()
		{
			return m_oFontStyle;
		}
		inline const CString& GetText ()
		{
			return m_Source;
		}

	public:

		Point		m_Pos;
		Point		m_Shift;

		CString		m_Source;
		FontStyle	m_oFontStyle;

		UnitSystem	m_oUs;
	};
	class Image : public DrawElement
	{
	protected:		
		class CImageManager
		{
		public:
			CImageManager()
			{
			}
		public:
			inline CString GenerateImage(const CString& strInput)
			{
				if (IsNeedDownload(strInput))
					return DownloadImage(strInput);

				BOOL doCopyFile	=	FALSE;

				CString strExts = _T(".jpg");
				int nIndexExt = strInput.ReverseFind(TCHAR('.'));
				if (-1 != nIndexExt)
					strExts = strInput.Mid(nIndexExt);

				if (strExts == _T(".tmp"))
				{
					strExts		=	_T(".png");
					doCopyFile	=	TRUE;
				}

				if ( FALSE == doCopyFile )
					return strInput;

				TCHAR sTempPath[MAX_PATH];
				if ( 0 == GetTempPath ( MAX_PATH, sTempPath ) )
					return strInput;

				SYSTEMTIME oTime;
				GetSystemTime ( &oTime );

				CString fileName;
				fileName.Format (_T("%s\\%d%d%d%d%d%d%s"), sTempPath, oTime.wYear, oTime.wDay, oTime.wHour, oTime.wMinute, oTime.wSecond, oTime.wMilliseconds, strExts );

				CImageManager::CopyFile(strInput, fileName, NULL, NULL);

				return fileName;
			}

			inline bool IsNeedDownload(const CString& strFile)
			{
				int n1 = strFile.Find(_T("www"));
				int n2 = strFile.Find(_T("http"));
				int n3 = strFile.Find(_T("ftp"));

				if (((n1 >= 0) && (n1 < 10)) || ((n2 >= 0) && (n2 < 10)) || ((n3 >= 0) && (n3 < 10)))
					return true;
				return false;
			}
			inline CString DownloadImage(const CString& strFile)
			{
				CFileDownloader oDownloader(strFile, TRUE);
				oDownloader.StartWork ( 1 );
				while ( oDownloader.IsRunned() )
				{
					::Sleep( 10 );
				}

				if ( oDownloader.IsFileDownloaded() )
				{
					return GenerateImage( oDownloader.GetFilePath() );
				}
				return _T("");
			}

			static BOOL CopyFile(CString strExists, CString strNew, LPPROGRESS_ROUTINE lpFunc, LPVOID lpData) 
			{
				DeleteFile(strNew);
				return ::CopyFileEx(strExists, strNew, lpFunc, lpData, FALSE, 0); 
			}
		};

	public:
		Image ()
		{
			m_nodeType	=	EImage;
			m_pClip		=	NULL;
		}

		virtual BOOL FromXml (CXmlNode& oXml, UnitSystem& oUs)
		{
			DrawElement::FromXml (oXml, oUs);

			m_Or.X					=	DoubleValue(oXml, _T("x"),		oUs, c_dirHorizontal);
			m_Or.Y					=	DoubleValue(oXml, _T("y"),		oUs, c_dirVertical);
			m_Size.X				=	DoubleValue(oXml, _T("width"),	oUs, c_dirHorizontal);
			m_Size.Y				=	DoubleValue(oXml, _T("height"), oUs, c_dirVertical);

			m_sPreserveAspectRatio	=	oXml.GetAttributeOrValue(_T("preserveAspectRatio"), _T(""));

			m_XLinkRef	=	oXml.GetAttribute(_T("xlink:href"));
			if (m_XLinkRef.GetLength ())
			{
				StrUtils::RemoveSpaces (m_XLinkRef);

				/*

				if ( _T('#') == m_XLinkRef [0] )
				{

				}

				*/

				if (m_XLinkRef.GetLength () > 4)
				{
					CImageManager onlineImage;
					if (onlineImage.IsNeedDownload(m_XLinkRef))
					{					
						m_ImagePath = onlineImage.GenerateImage(m_XLinkRef);
						if ( m_ImagePath.GetLength() > 1 )
							return TRUE;
					}

					if (_T('d') == m_XLinkRef[0] && _T('a') == m_XLinkRef[1] && _T('t') == m_XLinkRef[2] && _T('a') == m_XLinkRef[3])
					{
						m_bin64Image.FromString(m_XLinkRef);
					}
					else
					{
						m_ImagePath		=	StrUtils::UrlDecode (m_XLinkRef).MakeLower();

						CString URLFile	=	CString(_T("file:///"));
						int to			=	m_ImagePath.Find(URLFile, 0);
						if (-1 != to)
						{
							m_ImagePath	=	m_ImagePath.Mid(URLFile.GetLength(), m_ImagePath.GetLength() - to - URLFile.GetLength());
						}
					}
				}
			}

			return TRUE;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			m_Or	*=	Point(dAfX, dAfY);
			m_Size	*=	Point(dAfX, dAfY);

			return TRUE;
		}

		inline const Point& GetFrom() const
		{
			return	m_Or;
		}
		inline const Point& GetSize() const
		{
			return	m_Size;
		}
		inline const CString& GetXLink() const
		{
			return m_XLinkRef;
		}

		inline CString LivePath(const CString& sWorkingDirectory)
		{
			if (GetXLink().GetLength())
			{	
				CString sFile = FileUtils::GetFullPathName (GetXLink());
				if ((0 == sFile.GetLength()) || !FileUtils::FileExists (sFile))
				{
					sFile = CString(sWorkingDirectory + "\\" + GetXLink());
					if (!FileUtils::FileExists (sFile))
					{
						sFile = GetXLink();				
						if (!FileUtils::FileExists (sFile))
						{
							return m_ImagePath;	
						}
					}					
				}

				return FileUtils::GetFullPathName(sFile);
			}

			return m_ImagePath;
		}

		inline const CString& PreserveAspectRatio() const
		{
			return m_sPreserveAspectRatio;
		}

	public:

		Point			m_Or;
		Point			m_Size;	

		CString			m_sPreserveAspectRatio;

		CString			m_XLinkRef;
		CString			m_ImagePath;

		ImageBase64		m_bin64Image;
	};

	class Use : public DrawElement
	{
	public:
		Use()
		{
			m_nodeType		=	EUse;
			m_pClip			=	NULL;

			m_bBrokeRefLink	=	FALSE;
			m_pRefLink		=	NULL;
		}

		virtual BOOL FromXml(CXmlNode& oXml, UnitSystem& oUs)
		{
			DrawElement::FromXml (oXml, oUs);

			m_bBrokeRefLink	=	FALSE;

			m_From.X		=	DoubleValue(oXml, _T("x"), oUs, c_dirHorizontal);
			m_From.Y		=	DoubleValue(oXml, _T("y"), oUs, c_dirVertical);
			m_To.X			=	DoubleValue(oXml, _T("width"), oUs, c_dirHorizontal) + m_From.X;
			m_To.Y			=	DoubleValue(oXml, _T("height"), oUs, c_dirVertical) + m_From.Y;

			m_XLinkRef		=	oXml.GetAttribute(_T("xlink:href"));

			if (m_XLinkRef.GetLength())
			{
				StrUtils::RemoveSpaces (m_XLinkRef);
				if (m_XLinkRef.GetLength())
				{
					if (_T('#') == m_XLinkRef[0])
					{
						m_XLinkRef = m_XLinkRef.Mid(1, m_XLinkRef.GetLength() - 1);
					}
				}
			}

			return TRUE;
		}
		virtual BOOL RefreshXLinkSource (IRefStorage* pStorage)
		{
			if (NULL != m_pRefLink)		//	связь уже есть, нет смысла опять искать соотвествие
				return TRUE;

			if (m_bBrokeRefLink)		//	нету связи
				return FALSE;

			if (m_XLinkRef.GetLength())
			{
				ISvgRef* pRefLink	=	NULL;
				if (pStorage->GetRef(m_XLinkRef, pRefLink))
				{
					m_pRefLink = pRefLink;

					// ATLTRACE(_T("RefLink for object : %s - %s\n"), nodeId(), m_pRefLink->nodeId());

					return TRUE;
				}
			}

			m_bBrokeRefLink	=	TRUE;

			return FALSE;
		}
		virtual BOOL Normalize(const double& dAddFMX, const double& dAddFMY)
		{

			return FALSE;
		}

		inline ISvgRef* GetRefLink ()
		{
			return m_pRefLink;
		}

		inline const Point& GetFrom() const
		{
			return	m_From;
		}
		inline const Point& GetTo() const
		{
			return	m_To;
		}

		inline const CString& GetXLink() const
		{
			return m_XLinkRef;
		}

	private:

		Point		m_From;
		Point		m_To;

		CString		m_XLinkRef;
		BOOL		m_bBrokeRefLink;
		ISvgRef*	m_pRefLink;
	};
}

namespace SVG
{
	class Painter;
	//
	class DrawBuilder
	{
	public:
		inline DrawElement* Build (const CString& sName)
		{
			if (CString(_T("rect")) == sName)			return new Rectangle();
			else if (CString(_T("ellipse")) == sName)	return new Ellipse();
			else if (CString(_T("line")) == sName)		return new Line();
			else if (CString(_T("circle")) == sName)	return new Circle();
			else if (CString(_T("path")) == sName)		return new Path();
			else if (CString(_T("polyline")) == sName)	return new Polyline();
			else if (CString(_T("polygon")) == sName)	return new Polygon();
			else if (CString(_T("text")) == sName)		return new Text();
			else if (CString(_T("image")) == sName)		return new Image();
			else if (CString(_T("use")) == sName)		return new Use();

			return NULL;
		}
	};
	class Symbol : public RefElement	//	content element
	{
	public:
		Symbol()
		{
			m_nodeType	=	ESymbol;
			m_pClip		=	NULL;
		}
		virtual ~Symbol()
		{
			for (size_t i = 0; i < m_arrRefElems.GetCount(); ++i)
				RELEASEOBJECT (m_arrRefElems[i]);

			m_arrRefElems.RemoveAll();
		}

		virtual BOOL FromXml(CXmlNode& oXmlNode, IRefStorage* pStorage, UnitSystem& oUs)
		{
			RefElement::FromXml (oXmlNode, pStorage, oUs);

			m_oViewBox.FromXml (oXmlNode);

			return TRUE;
		}

		inline void AddContent(DrawElement* pReference)	//	храним данные, поэтому сами и очищаем данные
		{
			if (pReference)
			{
				m_arrRefElems.Add (pReference);
			}
		}
		inline long GetCount() const
		{
			return (long)m_arrRefElems.GetCount();
		}
		inline DrawElement* GetAt(long nInd)
		{
			return m_arrRefElems[nInd];
		}

		// RefElement

		virtual BOOL RefreshXLinkSource(IRefStorage* pStorage)						//	NOT IMPLEMENTED
		{
			return 0;
		}
		virtual BOOL Normalize(const double& dAddFMX, const double& dAddFMY)		//	NOT IMPLEMENTED
		{
			return 0;
		}

	public:

		ViewBox					m_oViewBox;
		CAtlArray<DrawElement*>	m_arrRefElems;
	};
	class ClipPath : public RefElement	//	content element
	{
	public:
		ClipPath()
		{
			m_nodeType	=	EClipPath;
			m_pClip		=	NULL;
		}
		virtual ~ClipPath()
		{
			for (size_t i = 0; i < m_clips.GetCount(); ++i)
				RELEASEOBJECT (m_clips[i]);

			m_clips.RemoveAll();
		}

		virtual BOOL FromXml (CXmlNode& oXml, IRefStorage* pStorage, UnitSystem& oUs)
		{
			RefElement::FromXml (oXml, pStorage, oUs);
			Explore(oXml);

			return TRUE;
		}
		inline long GetCount ()
		{
			return (long)m_clips.GetCount();
		}
		inline ISvgRef* GetAt (long nInd)
		{
			return m_clips[nInd];
		}


		// RefElement
		virtual BOOL RefreshXLinkSource (IRefStorage* pStorage)						//	NOT IMPLEMENTED
		{
			return 0;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)		
		{
			for (size_t i = 0; i < m_clips.GetCount(); ++i)
				m_clips[i]->Normalize(dAfX, dAfY);

			return TRUE;
		}

	protected:

		inline BOOL Explore (CXmlNode& oXml)
		{
			Load (oXml);

			if (oXml.HasChildNodes())
			{
				XML::IXMLDOMNodeListPtr pXmlNodes = NULL;
				if (oXml.GetNodes (pXmlNodes))
				{
					CXmlNodes oXmlNodes;
					if (oXmlNodes.FromXmlNodes(pXmlNodes))
					{
						for (long i = 0; i < oXmlNodes.GetCount(); ++i)
						{
							CXmlNode oChild;
							if (oXmlNodes.GetAt(i, oChild))
							{
								if (!Explore(oChild))
								{
									return FALSE;
								}
							}
						}
					}
				}
			}

			return TRUE;
		}
		inline BOOL Load (CXmlNode& oXml)
		{
			if (L"clipPath" == oXml.GetName ())
				return FALSE;
#ifdef _DEBUG
			ATLTRACE (L"[svg] ClipPath-NodeName : %s\n", oXml.GetName());
#endif

			DrawElement* pClip = m_oBuilder.Build (oXml.GetName());
			if (pClip)
			{		
				pClip->FromXml(oXml,m_oUs); 
				m_clips.Add (pClip);
				return TRUE;
			}

			return FALSE;
		}

	protected:

		CAtlArray <DrawElement*>	m_clips;
		DrawBuilder					m_oBuilder;
		UnitSystem					m_oUs;
	};
	class Pattern : public RefElement, public IRefStorage	//	content element
	{
	public:
		Pattern()
		{
			m_nodeType	=	EPattern;
			m_pClip		=	NULL;
		}
		virtual ~Pattern()
		{
			for (size_t i = 0; i < m_elements.GetCount(); ++i)
				RELEASEOBJECT (m_elements[i]);

			m_elements.RemoveAll();
		}

		virtual BOOL FromXml(CXmlNode& oXml, IRefStorage* model, UnitSystem& oUs)
		{
			m_rect.X				=	DoubleValue(oXml, _T("x"), oUs, c_dirHorizontal);
			m_rect.Y				=	DoubleValue(oXml, _T("y"), oUs, c_dirVertical);
			m_rect.Width			=	DoubleValue(oXml, _T("width"),  oUs, c_dirHorizontal);
			m_rect.Height			=	DoubleValue(oXml, _T("height"), oUs, c_dirVertical);

			m_patternUnits			=	oXml.GetAttributeOrValue(_T("patternUnits"), _T(""));
			m_preserveAspectRatio	=	oXml.GetAttributeOrValue(_T("preserveAspectRatio"), _T(""));

			m_model					=	model;

			RefElement::FromXml (oXml, model, oUs);
			m_oViewBox.FromXml (oXml);
			Explore(oXml);

			//Pattern::FromXml (oXml, m_model, oUs);

			return TRUE;
		}

		// RefElement
		virtual BOOL RefreshXLinkSource(IRefStorage* pStorage)						//	NOT IMPLEMENTED
		{
			return 0;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)		
		{
			//for (size_t i = 0; i < m_elements.GetCount(); ++i)
			//	m_elements[i]->Normalize(dAfX, dAfY);

			return TRUE;
		}

		//
		virtual ISvgRef* Get(long index)
		{
			return m_elements[index];
		}

		virtual long GetSize()
		{
			return (long)m_elements.GetCount();
		}
		// NOT IMPLEMENTED
		virtual BOOL HashRef(ISvgRef* pRef, BOOL bDef)	
		{
			return FALSE;	
		}
		// NOT IMPLEMENTED
		virtual BOOL GetRef(const CString& ID, ISvgRef*& pRef)	
		{
			return FALSE;	
		}
		// NOT IMPLEMENTED
		virtual BOOL Push(ISvgRef* pRef)
		{
			return FALSE;
		}

		//
		inline const ViewBox& GetBox() const
		{
			return m_oViewBox;
		}
		inline const Rect& GetBound() const
		{
			return m_rect;
		}
		inline const CString& PreserveAspectRatio() const
		{
			return m_preserveAspectRatio;
		}

		inline BOOL NormalizeEx(const double& dAfX, const double& dAfY)
		{
			for (size_t i = 0; i < m_elements.GetCount(); ++i)
				m_elements[i]->Normalize(dAfX, dAfY);

			return TRUE;
		}

	protected:

		inline BOOL Explore(CXmlNode& oXml)
		{
			Load (oXml);

			if (oXml.HasChildNodes())
			{
				XML::IXMLDOMNodeListPtr pXmlNodes = NULL;
				if (oXml.GetNodes (pXmlNodes))
				{
					CXmlNodes oXmlNodes;
					if (oXmlNodes.FromXmlNodes(pXmlNodes))
					{
						for (long i = 0; i < oXmlNodes.GetCount(); ++i)
						{
							CXmlNode oChild;
							if (oXmlNodes.GetAt(i, oChild))
							{
								if (!Explore(oChild))
								{
									return FALSE;
								}
							}
						}
					}
				}
			}

			return TRUE;
		}
		inline BOOL Load(CXmlNode& oXml)
		{
#ifdef _DEBUG
			ATLTRACE (L"[svg] Pattern-NodeName : %s\n", oXml.GetName());
#endif

			DrawElement* element = m_oBuilder.Build (oXml.GetName());
			if (element)
			{		
				Style oStyle = m_oStyle;
				FontStyle oFontStyle = m_oFontStyle;

				CString css = oXml.GetAttribute(_T("style"));
				if (css.GetLength())
				{
					oStyle.SetStyle(css, FALSE, m_oUs, NULL, m_oColTable);
					oFontStyle.SetStyle(css, FALSE);
				}
				else
				{
					oStyle.UpdateStyle(oXml, m_oUs, NULL, m_oColTable);
					oFontStyle.UpdateStyle(oXml);
				}

				m_oUs.SetFontSizeForEM(oFontStyle.DoubleAttribute(FontSize));

				element->SetStyle(oStyle);

				if (EText == element->nodeType())
				{
					Text* pText = static_cast<Text*>(element);
					if (pText)
					{
						pText->m_oFontStyle = oFontStyle;
					}
				}

				CString transform = oXml.GetAttribute(_T("transform"));
				if (transform.GetLength())
				{
					m_transforms.Push(Matrix(transform, m_oUs));

					element->SetTransform(m_transforms.GetTop());

					m_transforms.Pop();
				}
				else
				{
					element->SetTransform(m_transforms.GetTop());
				}

				element->FromXml(oXml,m_oUs); 
				m_elements.Add (element);
				return TRUE;
			}

			return FALSE;
		}

	protected:

		CAtlArray <DrawElement*>	m_elements;
		DrawBuilder					m_oBuilder;
		UnitSystem					m_oUs;
		ColorTable					m_oColTable;

		Style						m_oStyle;
		FontStyle					m_oFontStyle;
		MatrixStack					m_transforms;

		ViewBox						m_oViewBox;
		Rect						m_rect;
		CString						m_patternUnits;
		CString						m_preserveAspectRatio;
	};
	class PatternImage
	{
	public:
		PatternImage() : m_pFrame(NULL), m_pattern(NULL), m_baseRender(NULL), m_render(NULL), m_basePainter(NULL)
		{
			m_pPatternFrame	=	NULL;
		}		
		PatternImage(Pattern* pattern, IAVSRenderer* baseRender, Painter* basePainter) : m_pFrame(NULL), m_baseRender(baseRender), m_pattern(pattern), m_render(NULL), m_basePainter(basePainter)		
		{
			m_pPatternFrame	=	NULL;
		}
		~PatternImage()
		{
			RELEASEINTERFACE(m_render);
			RELEASEINTERFACE(m_pFrame);
			RELEASEINTERFACE(m_pPatternFrame);

			if (m_sLivePath.GetLength())
			{
				DeleteFile(m_sLivePath);
			}
		}

		inline const CString& LivePath()
		{
			Build();

			return m_sLivePath;
		}

	private:

		BOOL Build();
		BOOL InitFrame();
		BOOL InitPatternFrame();
		BOOL InitRender(IUnknown* frame, int frameWidth, int frameHeight);
		BOOL Render();
		BOOL SaveImage(IUnknown* punkFrame, CString file);
		Point GetNormalizeFactor();

	private:

		IAVSRenderer* m_baseRender;
		IAVSGraphicsRenderer* m_render;
		MediaCore::IAVSUncompressedVideoFrame* m_pFrame;
		MediaCore::IAVSUncompressedVideoFrame* m_pPatternFrame;

		CString		m_sLivePath;	
		Pattern*	m_pattern;
		Painter*	m_basePainter;
	};
	class DefsBuilder
	{
	public:
		RefElement* Build (const CString& sName)
		{
			if (CString (L"linearGradient") == sName)		return new LinearGradient ();
			else if (CString (L"radialGradient") == sName)	return new RadialGradient ();
			else if (CString(L"symbol")== sName)			return new Symbol();
			else if (CString(L"clipPath") == sName)			return new ClipPath();
			else if (CString(L"pattern") == sName)			return new Pattern();

			return NULL;
		}
	};
	class GraphicsContainer : public DrawElement, public IRefStorage
	{
	public:
		GraphicsContainer(BOOL bRefMode = FALSE)		//	подчищает ссылки на объекты
		{
			m_nodeType		=	EGraphicsContainer;
			m_pClip			=	NULL;
			m_bRefMode		=	bRefMode;

			m_bAddNormMM	=	FALSE;
		}
		virtual ~GraphicsContainer()
		{
			GraphicsContainer::Clear ();
		}

		virtual BOOL FromXml(CXmlNode& oXmlNode, IRefStorage* model, const ViewBox& oViewBox, const UnitSystem& oUnitSystem, const Matrix& oTransform)
		{
			m_model			=	model;
			m_oViewBox		=	oViewBox;
			m_oUs			=	oUnitSystem;

			m_pClip			=	NULL;
			m_urlClipPath	=	oXmlNode.GetAttribute(_T("clip-path"));
			StrUtils::UrlRefValue2(m_urlClipPath);

			m_transforms.Push(oTransform);

			DrawElement::FromXml(oXmlNode, m_oUs);

			UpdateMainStyle(oXmlNode);
			UpdateMainTransform(oXmlNode);

			Explore(oXmlNode);

			m_model->HashRef(this, FALSE);

			m_oTransform = m_transforms.GetFinal();

			return TRUE;
		}

		virtual BOOL FromString(CString Str, IRefStorage* model)
		{
			return FALSE;
		}
		virtual BOOL RefreshXLinkSource(IRefStorage* model)
		{
			return FALSE;
		}

		// storage
		inline ISvgRef* Get(long index)
		{
			if (index > (long)m_arrGroup.GetCount())
				return NULL;

			return m_arrGroup[index];
		}
		inline long GetSize()
		{
			return (long)(m_arrGroup.GetCount());
		}

		virtual BOOL Normalize(const double& dAddFMX, const double& dAddFMY)
		{
			if ( FALSE == m_bAddNormMM )
			{
				for ( long i = 0; i < (long)m_arrGroup.GetCount (); ++i )
				{
					ISvgRef* pE	=	m_arrGroup [ i ];
					if ( pE )
					{
						pE->Normalize ( dAddFMX, dAddFMY );
					}
				}
			}

			m_bAddNormMM	=	TRUE;

			return TRUE;
		}

		inline void Add(ISvgRef* element)
		{
			if (m_bRefMode)
			{
				m_arrGroup.Add(element);
			}
		}

	private:

		// NOT IMPLEMENTED
		virtual BOOL Push (ISvgRef* Elem)			
		{
			return FALSE;	
		}
		virtual BOOL HashRef (ISvgRef* pElem, BOOL bDef)	
		{
			return FALSE;	
		}
		virtual BOOL GetRef (const CString& ID, ISvgRef*& pElem)
		{
			return FALSE;	
		}

	private:

		inline BOOL Explore (CXmlNode& oXmlNode)
		{
			LoadElement ( oXmlNode );

			if ( oXmlNode.HasChildNodes () )
			{
				XML::IXMLDOMNodeListPtr pXmlNodes = NULL;
				if ( oXmlNode.GetNodes ( pXmlNodes ) )
				{
					CXmlNodes oXmlNodes;
					if ( oXmlNodes.FromXmlNodes ( pXmlNodes ) )
					{
						for ( long i = 0; i < oXmlNodes.GetCount(); ++i )
						{
							CXmlNode oXmlNode2;
							if ( oXmlNodes.GetAt ( i, oXmlNode2 ) )
							{
								if ( _T("g") == oXmlNode2.GetName() )
								{
									GraphicsContainer* pContainer	=	new GraphicsContainer();
									if ( pContainer )
									{
										pContainer->FromXml(oXmlNode2, m_model, m_oViewBox, m_oUs, m_transforms.GetFinal());
										m_model->HashRef(pContainer, FALSE);

										m_arrGroup.Add(pContainer);

										continue;
									}

									// return TRUE;
								}

								if ( FALSE == Explore ( oXmlNode2 ) )
								{
									return FALSE;
								}
							}
						}
					}
				}
			}

			return TRUE;
		}
		inline BOOL LoadElement (CXmlNode& oXml, BOOL Defines = FALSE)
		{
			CString strXmlNode = oXml.GetName();

			RefElement* pReference = m_oDefsBuilder.Build(strXmlNode);
			if (pReference)
			{
				if (EPattern == pReference->nodeType())
				{
					((Pattern*)pReference)->FromXml(oXml, m_model, m_oUs);
				}
				else
				{
					pReference->FromXml(oXml, m_model, m_oUs);
				}

				if (m_model->HashRef(pReference, TRUE))
					UpdateSymbol(pReference, oXml);
#ifdef _DEBUG
				ATLTRACE(L"[svg] ref element (g) - : %s\n", strXmlNode);
#endif
				return TRUE;
			}

			if (NULL == Create(oXml))
				return FALSE;

			return TRUE;
		}

		inline DrawElement* Create(CXmlNode& oXml, BOOL bAddStorage = TRUE)
		{
			CString strXmlNode = oXml.GetName();
#ifdef _DEBUG
			ATLTRACE(L"[svg] render element (g) - : %s\n", strXmlNode);
#endif
			DrawElement* element		=	m_oDrawBuilder.Build(strXmlNode);
			if (element)
			{			
				Style oStyle			=	m_oStyle;
				FontStyle oFontStyle	=	m_oFontStyle;

				CString css = oXml.GetAttribute(_T("style"));
				if (css.GetLength())
				{
					oStyle.SetStyle(css, FALSE, m_oUs, m_model, m_oColTable);
					oFontStyle.SetStyle(css, FALSE);
				}
				else
				{
					oStyle.UpdateStyle(oXml, m_oUs, m_model, m_oColTable);
					oFontStyle.UpdateStyle(oXml);
				}

				m_oUs.SetFontSizeForEM(oFontStyle.DoubleAttribute(FontSize));

				element->SetStyle(oStyle);

				if (EText == element->nodeType())
				{
					Text* pText = static_cast<Text*>(element);
					if (pText)
					{
						pText->m_oFontStyle = oFontStyle;
					}
				}

				CString transform = oXml.GetAttribute(_T("transform"));
				if (transform.GetLength())
				{
					m_transforms.Push(Matrix(transform, m_oUs));

					element->SetTransform(m_transforms.GetTop());

					m_transforms.Pop();
				}
				else
				{
					element->SetTransform(m_transforms.GetTop());
				}

				element->FromXml(oXml, m_oUs);

				// ATLTRACE(L"GraphicsContainer : %s - push : %s\n", m_nodeId, oXmlNode.GetName());

				if (bAddStorage)
					m_arrGroup.Add(element);

				return element;
			}

			return NULL;
		}

		inline void UpdateMainTransform (CXmlNode& oXml)
		{
			CString css = oXml.GetAttribute(_T("transform"));
			if (css.GetLength())
			{
				Matrix oTransform(css, m_oUs);
				m_transforms.Push(oTransform);
			}
			else
			{
				m_transforms.Push(Matrix());
			}
		}
		inline void UpdateMainStyle (CXmlNode& oXml)
		{
			CString css = oXml.GetAttribute(_T("style"));
			if (css.GetLength())
			{
				m_oFontStyle.SetStyle(css, TRUE);
				m_oStyle.SetStyle(css, TRUE, m_oUs, m_model, m_oColTable);
			}
			else
			{
				m_oFontStyle.UpdateStyle(oXml);
				m_oStyle.UpdateStyle(oXml, m_oUs, m_model, m_oColTable);
			}
		}
		inline void Clear()
		{
			if (!m_bRefMode)
			{
				for (long i = 0; i < (long)m_arrGroup.GetCount (); ++i)
					RELEASEOBJECT(m_arrGroup[i]);
			}

			m_arrGroup.RemoveAll();
		}

		//
		inline void UpdateSymbol(RefElement* pReference, CXmlNode& oXml)
		{
			if (ESymbol == pReference->nodeType())
			{
				if (oXml.HasChildNodes())
				{
					XML::IXMLDOMNodeListPtr pXmlNodes = NULL;
					if (oXml.GetNodes(pXmlNodes))
					{
						CXmlNodes oXmlNodes;
						if (oXmlNodes.FromXmlNodes(pXmlNodes))
						{
							for (long i = 0; i < oXmlNodes.GetCount(); ++i)
							{
								CXmlNode oXml2;
								if (oXmlNodes.GetAt(i,oXml2))
								{
									((Symbol*)pReference)->AddContent(Create(oXml2, FALSE));
								}
							}
						}
					}
				}
			}
		}

	private:

		BOOL					m_bRefMode;

		BOOL					m_bAddNormMM;

		CAtlArray <ISvgRef*>	m_arrGroup;

		IRefStorage*			m_model;
		DrawBuilder				m_oDrawBuilder;
		DefsBuilder				m_oDefsBuilder;

		ViewBox					m_oViewBox;
		UnitSystem				m_oUs;
		ColorTable				m_oColTable;

		Style					m_oStyle;
		FontStyle				m_oFontStyle;
		MatrixStack				m_transforms;
	};
}

namespace SVG
{	
	class Storage : public IRefStorage
	{
	public:
		Storage()
		{
			m_bAddNormMM	=	FALSE;
		}
		virtual ~Storage ()
		{
			Clear ();
		}

		inline void Clear ()
		{
			for (size_t i = 0; i < m_arrGroup.GetCount(); ++i)
			{
				RELEASEOBJECT(m_arrGroup[i]);
			}

			m_arrGroup.RemoveAll();
			m_arrRef.RemoveAll();

			for (size_t i = 0; i < m_arFlush.GetCount(); ++i)
			{
				RELEASEOBJECT (m_arFlush[i]);
			}

			m_arFlush.RemoveAll();
		}
		inline BOOL JoinXLinkReference()
		{
			for (int i = 0; i < m_arrRef.GetSize(); ++i)
			{
				ISvgRef* pE = static_cast<ISvgRef*>(m_arrRef.GetValueAt(i));
				if (pE)
				{
					pE->RefreshXLinkSource (this);
				}
			}

			return TRUE;
		}
		inline BOOL JoinClipPathLinks()
		{
			for (size_t i = 0; i < m_arrGroup.GetCount(); ++i)
			{
				DrawElement* pRef = static_cast<DrawElement*>(m_arrGroup[i]);
				if (pRef)
				{
					CString clipId = pRef->GetUrlClip();
					if (clipId.GetLength())
					{
						ISvgRef* pClipRef = NULL;
						if (GetRef(clipId, pClipRef))
						{
							pRef->AttachClip (pClipRef);							
						}
					}
				}
			}

			return TRUE;
		}
		inline BOOL JoinStyleLinks()
		{
			for (size_t i = 0; i < m_arrGroup.GetCount(); ++i)
			{
				DrawElement* pRef = static_cast<DrawElement*>(m_arrGroup[i]);
				if (pRef)
				{
					const Style& style = pRef->GetStyle();
					if (style.GetFillUrlRef().GetLength() && (NULL == style.GetFill()))
					{
#ifdef _DEBUG
						ATLTRACE (_T("[svg] NEED JOIN FILL STYLE : id - %s"), pRef->nodeId());
#endif
					}
				}
			}

			return TRUE;
		}

		//	IRefStorage
		virtual ISvgRef* Get (long index)
		{
			if (index > (long)m_arrGroup.GetCount())
				return NULL;

			// ATLTRACE ( _T("get : %s\n"), m_arrGroup [nIndex]->nodeId () );

			return m_arrGroup [index];
		}
		virtual long GetSize ()
		{
			return (long)m_arrGroup.GetCount();
		}
		virtual BOOL Push (ISvgRef* Elem)
		{
			// ATLTRACE ( _T("push : %s\n"), Elem->nodeId () );

			return (0 == m_arrGroup.Add(Elem));
		}

		virtual BOOL HashRef (ISvgRef* element, BOOL bDef)
		{
			if (element)
			{
				if (element->nodeId().GetLength())
				{
					ISvgRef* search = m_arrRef.Lookup(element->nodeId());
					if (NULL == search)
					{
						//ATLTRACE(_T("IRefStorage - Hash : %s, %d\n"), element->nodeId(), element->nodeType());

						m_arrRef.Add(element->nodeId(), element);

						if (bDef)
						{
							m_arFlush.Add (element);
						}

						// объекты с id могут быть использованы вне описания другими элементами, поэтому их надо учитывать
						InternalHashElements(element);

						return TRUE;
					}
				}
			}

			return FALSE;
		}
		virtual BOOL GetRef (const CString& sId, ISvgRef*& pRef)
		{
			pRef = m_arrRef.Lookup (sId);
			if (NULL != pRef)
				return TRUE;

			return FALSE;
		}
		virtual BOOL Normalize(const double& dAfX, const double& dAfY)
		{
			if ( FALSE == m_bAddNormMM )
			{
				for ( long i = 0; i < (long)m_arrGroup.GetCount (); ++i )
				{
					ISvgRef* pE	=	m_arrGroup [ i ];
					if ( pE )
					{
						pE->Normalize(dAfX, dAfY);
					}
				}

				for (int i = 0; i < m_arrRef.GetSize(); ++i)
				{
					ISvgRef* pE = static_cast<ISvgRef*>(m_arrRef.GetValueAt(i));
					if (pE)
					{
						pE->Normalize(dAfX, dAfY);
					}
				}
			}

			m_bAddNormMM	=	TRUE;

			return TRUE;
		}
		virtual BOOL RefreshXLinkSource(IRefStorage* pStorage)
		{

			return FALSE;
		}

		// 
		inline void SetWorkingDirectory (const CString& sWorkingDirectory)
		{
			m_sWorkingDirectory	= sWorkingDirectory;
		}

	private:

		inline BOOL InternalHashElements (ISvgRef* element)
		{
			BOOL ret = FALSE;

			if (EClipPath == element->nodeType())
			{
				ClipPath* clip = static_cast<ClipPath*>(element);
				if (clip)
				{
					if (clip->GetCount())
					{
						for (long i = 0; i < clip->GetCount(); ++i)
						{
							ISvgRef* ref = clip->GetAt(i);
							if (ref)
							{
								if (ref->nodeId().GetLength())
								{
									m_arrRef.Add(ref->nodeId(), ref);
									ret = TRUE;
								}
							}
						}
					}
				}
			}

			return ret;
		}

	private:

		BOOL								m_bAddNormMM;

		CAtlArray <ISvgRef*>				m_arrGroup;
		CSimpleMap <CString, ISvgRef*>		m_arrRef;					// индексация (только хранения ссылок)
		CString								m_sWorkingDirectory;				
		CAtlArray<ISvgRef*>					m_arFlush;					// объекты которые нужно удалять
	};
	class Painter
	{
	public:
		Painter()
		{
			m_pManager		=	NULL;
			m_model			=	NULL;
			m_render		=	NULL;

			m_dpiX			=	0.0;	
			m_dpiY			=	0.0;

			m_widthMM		=	0.0;
			m_heightMM		=	0.0;

			m_bEnableFonts	=	TRUE;
			m_CSS			=	NULL;
		}
		~Painter()
		{
			RELEASEINTERFACE (m_pManager);

			POSITION pos = m_patterns.GetStartPosition();
			while (NULL != pos)
			{
				PatternImage* image = m_patterns.GetNextValue(pos);
				RELEASEOBJECT(image);
			}
		}

		inline void SetWorkingDirectory(const CString& sWorkingDirectory)
		{
			m_sWorkingDirectory	= sWorkingDirectory;
		}
		inline const CString& GetWorkingDirectory() const
		{
			return m_sWorkingDirectory;
		}
		inline const UnitSystem& GetUs() const
		{
			return m_oUs;
		}
		inline void SetCSS(CStyleCSS* css)
		{
			m_CSS	=	css;
		}

		BOOL Draw(IRefStorage* model, IAVSRenderer* render, const UnitSystem& oUs);

	private:

		BOOL DrawLine (Line* element, const Style& oStyle, const CString& strClassName = _T(""));
		BOOL DrawRectangle (Rectangle* element, const Style& oStyle, const CString& strClassName = _T(""));
		BOOL DrawCircle (Circle* element,const Style& oStyle, const CString& strClassName = _T(""));
		BOOL DrawEllipse (Ellipse* element, const Style& oStyle, const CString& strClassName = _T(""));
		BOOL DrawPolyline (Polyline* element, const Style& oStyle, const CString& strClassName = _T(""));
		BOOL DrawPolygon (Polygon* element, const Style& oStyle, const CString& strClassName = _T(""));		
		BOOL DrawPath (Path* element, const Style& oStyle, const CString& strClassName = _T(""));
		BOOL DrawText (Text* element, const Style& oStyle, const CString& strClassName = _T(""));
		BOOL DrawImage (Image* element, const Style& oStyle, const CString& strClassName = _T(""));
		BOOL DrawUse (Use* element, const Style& oStyle, const CString& strClassName = _T(""));

		BOOL DrawStorage (IRefStorage* pStorage, const Matrix& parentTransform = Matrix(), const Point& off = Point());
		BOOL DrawGraphicsContainer (GraphicsContainer* element, const Matrix& parentTransform = Matrix(), const Point& off = Point());
		BOOL DrawInternal (DrawElement* pE, const Matrix& parentTransform, const Point& off, const Style& oMainStyle);

		BOOL SetBrushStyle (const Style& style, const CString& strClassName = _T(""));
		BOOL SetStrokeStyle (const Style& style, const CString& strClassName = _T(""));

		// commands only

		void DoRectangle(Rectangle* element, long type, BOOL clipMode = FALSE);
		void DoCircle(Circle* element, long type, BOOL clipMode = FALSE);
		void DoEllipse(Ellipse* element, long type, BOOL clipMode = FALSE);
		void DoPolyline(Polyline* element, long type, BOOL clipMode = FALSE);
		void DoPolygon(Polygon* element, long type, BOOL clipMode = FALSE);
		void DoPath(Path* element, long type, BOOL clipMode = FALSE);

		// clip 
		BOOL DoClip(ISvgRef* pRef, BOOL enable);

		inline ISvgRef* FindEntry(Use* element)
		{
			if (element)
			{
				element->RefreshXLinkSource (m_model);

				ISvgRef* refLink = element->GetRefLink();
				if (refLink)
				{
					ENodeType code = refLink->nodeType();
					if (EUse == refLink->nodeType())
						return FindEntry(static_cast<Use*>(refLink));

					return refLink;
				}
			}

			return NULL;		
		}

		// image
		BOOL DrawImageFromFile(Image* element, CString texturePath = L"");
		BOOL DoPattern(Pattern* element);

		// path
		BOOL PushPathCommands(Path* element, long PathType);
		BOOL ClipPathCommands(Path* element, long PathType);
	private:	
		// for arc render
		inline BOOL RenderArcAppx(const double& dRotAngle, const Point& Center, Point Radi, const double& dStartAngle, const double& dSweep)
		{
			if (0.0 != dRotAngle)	
			{
				Matrix rotate			=	Matrix::RotateAtPoint(Point(Center.X, Center.Y), -dRotAngle * M_PI / 180);

				CArcToCubicBezier oSplitter(Center.X - Radi.X, Center.Y - Radi.Y, Radi.X * 2.0, Radi.Y * 2.0, dStartAngle - dRotAngle, dSweep);
				for (int i = 0; i < oSplitter.GetCurves().GetSize(); ++i)
				{
					CubicBezier oBezier	=	oSplitter.GetCurves()[i];						

					Point oPointU		=	rotate.TranformPoint(oBezier.m_Points[0]);
					Point oPointV		=	rotate.TranformPoint(oBezier.m_Points[1]);
					Point oPointE		=	rotate.TranformPoint(oBezier.m_Points[2]);

					m_render->PathCommandCurveTo(oPointU.X, oPointU.Y,	oPointV.X, oPointV.Y, oPointE.X, oPointE.Y);
				}
			}
			else
			{
				m_render->PathCommandArcTo(Center.X - Radi.X, Center.Y - Radi.Y, Radi.X * 2.0, Radi.Y * 2.0, dStartAngle, dSweep);
			}

			return TRUE;
		}
		inline BOOL ClipArcAppx(Aggplus::CGraphicsPathSimpleConverter& simplifier, const double& dRotAngle, const Point& Center, Point Radi, const double& dStartAngle, const double& dSweep)
		{
			if (0.0 != dRotAngle)
			{
				Matrix rotate			=	Matrix::RotateAtPoint(Point(Center.X, Center.Y), -dRotAngle * M_PI / 180);

				CArcToCubicBezier oSplitter(Center.X - Radi.X, Center.Y - Radi.Y, Radi.X * 2.0, Radi.Y * 2.0, dStartAngle - dRotAngle, dSweep);
				for (int i = 0; i < oSplitter.GetCurves().GetSize(); ++i)
				{
					CubicBezier oBezier	=	oSplitter.GetCurves()[i];						

					Point oPointU		=	rotate.TranformPoint(oBezier.m_Points[0]);
					Point oPointV		=	rotate.TranformPoint(oBezier.m_Points[1]);
					Point oPointE		=	rotate.TranformPoint(oBezier.m_Points[2]);

					simplifier.PathCommandCurveTo(oPointU.X, oPointU.Y, oPointV.X, oPointV.Y, oPointE.X, oPointE.Y);
				}
			}
			else
			{
				simplifier.PathCommandArcTo(Center.X - Radi.X, Center.Y - Radi.Y, Radi.X * 2.0, Radi.Y * 2.0, dStartAngle, dSweep);
			}

			return TRUE;
		}

		static double GetAngle(const double& CX, const double& CY, const double& X, const double& Y);
		static Point GetCenter(int LargeFlag, int SweepFlag, Point Radi, Point P1, Point P2);
		static BOOL GetArcAngles(int LargeFlag, int SweepFlag, const double& dStartAngle, const double& dEndAngle, double& dSweep);

		inline IAVSFontManager* GetFontManager()
		{
			if (NULL == m_pManager)
			{
				if (SUCCEEDED(CoCreateInstance(__uuidof(CAVSFontManager), NULL, CLSCTX_INPROC, __uuidof(IAVSFontManager), (void**)&m_pManager)))
				{
					m_pManager->Initialize(L"");
					m_pManager->SetDefaultFont(L"Arial");
				}
			}

			return m_pManager;
		}

		inline void UpdateClass(DrawElement* element)
		{
			if (element)
			{
				if (element->ClassName().GetLength ())
				{
					VARIANT vt;
					vt.vt		=	VT_BSTR;
					vt.bstrVal	=	CComBSTR (element->ClassName());

					m_render->SetAdditionalParam(L"AttributeClassName", vt);
				}
			}
		}
		inline Style ComposeStyles(DrawElement* element, const Style& style)
		{
			Style composeStyle = style;
			if (m_CSS)
			{
				Style elementStyle;
				if (m_CSS->GetStyleForType(element->nodeType(), elementStyle))
				{
					if (elementStyle.IsCSS())
					{
						Style::UpdateValidateAttributes(elementStyle, composeStyle); 
					}
				}

				Style classStyle;
				if (m_CSS->GetClassStyle(element->ClassName(), classStyle))
				{
					Style::UpdateValidateAttributes(classStyle, composeStyle); 
				}
			}

			return composeStyle;
		}

	private:

		IAVSRenderer*					m_render;
		IAVSFontManager*				m_pManager;
		IRefStorage*					m_model;
		UnitSystem						m_oUs;

		double							m_dAddMX;
		double							m_dAddMY;
		double							m_dpiX;
		double							m_dpiY;
		double							m_widthMM;
		double							m_heightMM;

		MatrixStack						m_transforms;
		BOOL							m_bEnableFonts;
		CString							m_sWorkingDirectory;
		CAtlMap<CString, PatternImage*>	m_patterns;
		CStyleCSS*						m_CSS;
	};

}
namespace SVG
{
	class ENTITY
	{
	public:
		ENTITY()
		{
		}

		inline BOOL Read (const CString& sTag)
		{
			int at = sTag.Find(_T("\""));
			int to = sTag.Find(_T("\""), at + 1);

			if (-1 != at && -1 != to)
			{
				m_sValue	=	StrUtils::RemoveSpaces(sTag.Mid(at + 1, to - at - 1));
				m_sName		=	StrUtils::RemoveSpaces(sTag.Mid(0, at - 1));

				return TRUE;
			}

			return FALSE;
		}
		inline const CString& GetName() const
		{
			return m_sName;
		}
		inline const CString& GetValue() const
		{
			return m_sValue;
		}

	private:

		CString	m_sName;
		CString	m_sValue;
	};
	class DOCTYPE
	{
	public:
		DOCTYPE()
		{

		}

		inline BOOL Read (const CString& sTag)
		{
			if (sTag.GetLength())
			{
				// READ TAG - <!ENTITY

				int at = sTag.Find(_T("<!ENTITY"));
				if (-1 == at)	return FALSE;
				int to = sTag.Find(_T(">"), at);
				if (-1 == to)	return FALSE;

				int length = CString("<!ENTITY").GetLength();

				if (-1 != at)
				{
					ENTITY entity;
					if (entity.Read(sTag.Mid(at + length, to - at - length)))
						m_ENTITY.Add(entity);

					while(-1 != at)
					{
						at = sTag.Find(_T("<!ENTITY"), to);						
						if (-1 == at)	break;

						to = sTag.Find(_T(">"), at);
						if (-1 == to)	break;

						ENTITY entity;
						if (entity.Read(sTag.Mid(at + length, to - at - length)))
							m_ENTITY.Add(entity);
					}
				}

				if (m_ENTITY.GetCount())
					return TRUE;
			}

			return FALSE;
		}

		template <typename T> BOOL ConnectEntities(T& sXml)
		{
			if (m_ENTITY.GetCount())
			{
				CAtlArray<T>	subStrings;

				T and	=	T(CString(L"&"));
				T sem	=	T(CString(L";"));

				int at = sXml.Find(and);
				if (-1 == at)	return FALSE;
				int to = sXml.Find(sem, at);
				if (-1 == to)	return FALSE;

				while (-1 != at && -1 != to) 
				{
					T replace =  sXml.Mid(at + 1, to - at - 1);
					subStrings.Add(replace);

					at = sXml.Find(and, to);
					if (-1 == at)	break;
					to = sXml.Find(sem, at);
					if (-1 == to)	break;
				}

				if (subStrings.GetCount())
				{
					for (long i = (long)subStrings.GetCount() - 1; i >= 0; --i)
					{
						T str = and + T(subStrings[i]) + sem;
						sXml.Replace(str, T(GetVal(CString(subStrings[i]))));
					}

					return TRUE;
				}
			}

			return FALSE;
		}

		inline CString GetVal(const CString& sName) const
		{
			for (size_t i = 0; i < m_ENTITY.GetCount(); ++i)
			{
				if (sName == m_ENTITY[i].GetName())
				{
					return m_ENTITY[i].GetValue();
				}
			}

			return CString(_T(""));
		}
		inline CString GetAt(long index, long type = 0) const 
		{
			if (index >= (long)m_ENTITY.GetCount())
				return CString(_T(""));

			return m_ENTITY[index].GetValue();
		}

		//
		inline void Clear()
		{
			m_ENTITY.RemoveAll();
		}

	private:

		CAtlArray<ENTITY> m_ENTITY;	//	<!ENTITY 
	};

	class Parser
	{
	public:
		Parser ()
		{
			m_model		=	NULL;

			m_nWidth		=	0;
			m_nHeight		=	0;

			m_nLayerLevel	=	0;

			m_bDefinesLayer	=	FALSE;
			m_nDefsLayer	=	0;

			m_nDefWidth		=	800;
			m_nDefHeight	=	600;
		}
		~Parser ()
		{

		}

		inline BOOL	LoadFromFile (const CString& strFile, Storage* model)
		{
			if (model)
			{
				m_model = model;

				CStringA sXmlA;
				if (StringHelpers::LoadXmlFile(strFile, sXmlA))
				{
					if (m_DOCTYPE.Read(CString(sXmlA)))
					{
						m_DOCTYPE.ConnectEntities<CStringA>(sXmlA);
						m_DOCTYPE.Clear();
					}

					if (sXmlA.GetLength())
					{
						StringHelpers::RemoveTagHTMLA (sXmlA, CStringA("<!ENTITY"), CStringA(">"));
						StringHelpers::RemoveTagHTMLA (sXmlA, CStringA("<!DOCTYPE"), CStringA(">"));
						StringHelpers::RemoveCommentsA (sXmlA);
					}

					CString sXml = XmlUtils::ConvertToUnicode(sXmlA);
					return LoadFromString(XmlUtils::ConvertToUnicode(sXmlA), model);
				}
			}

			return FALSE;
		}
		inline BOOL	LoadFromString (const CString& strXml, Storage* model)
		{
			if (model)
			{
				m_model = model;

				CString sXml = strXml;
				if (m_DOCTYPE.Read(sXml))
				{
					m_DOCTYPE.ConnectEntities<CString>(sXml);
					m_DOCTYPE.Clear();
				}

				if (sXml.GetLength())
				{
					StringHelpers::RemoveTagHTML (sXml, CString(L"<!ENTITY"), CString(L">"));
					StringHelpers::RemoveTagHTML (sXml, CString(L"<!DOCTYPE"), CString(L">"));
					StringHelpers::RemoveComments (sXml);
				}

				CXmlNode oXml;
				if (oXml.FromXmlString(sXml))
				{
					m_nLayerLevel = 0;

					if (Explore(oXml))
					{
						m_model->JoinXLinkReference();
						m_model->JoinClipPathLinks();
						m_model->JoinStyleLinks();

						return TRUE;
					}
				}
			}

			return FALSE;
		}
		inline BOOL Explore (CXmlNode& oXml)
		{
			CString strXmlNode = oXml.GetName();			// ATLTRACE ( L"%s\n", strXmlNode);

			BOOL ExploreLayer = FALSE;
			BOOL readInnerNodes = TRUE;

			if (m_bDefinesLayer)
				++m_nDefsLayer;

			if (_T("svg") == strXmlNode)
			{
				m_oViewBox.FromXml (oXml);

				m_Metrics			=	StrUtils::GetMetrics(oXml.GetAttribute(_T("width")));

				if (PCT == m_Metrics && m_oViewBox.m_bInUse)
				{
					if (0 == (int)m_oViewBox.m_nWidth && 0 == (int)m_oViewBox.m_nHeight)
					{
						return FALSE;
					}

					m_nWidth		=	m_oViewBox.m_nWidth;
					m_nHeight		=	m_oViewBox.m_nHeight; 

					if (0 == (int)m_oViewBox.m_nWidth)
						m_nWidth	=	__max (m_oViewBox.m_nWidth, m_oViewBox.m_nHeight);
					if (0 == (int)m_oViewBox.m_nHeight)
						m_nHeight	=	__max (m_oViewBox.m_nWidth, m_oViewBox.m_nHeight);
				}
				else
				{
					m_nWidth		=	static_cast<long>(m_oUs.GetPX(StrUtils::DoubleValue(oXml.GetAttribute(_T("width"))), m_Metrics));
					m_nHeight		=	static_cast<long>(m_oUs.GetPX(StrUtils::DoubleValue(oXml.GetAttribute(_T("height"))), m_Metrics)); 
				}

				m_oUs.SetViewBox(m_nWidth, m_nHeight, m_oViewBox, m_Metrics);

				SetDefaultSizes ();
			}
			else if (_T("g") == strXmlNode)
			{
				if (m_bDefinesLayer)
				{
					GraphicsContainer* pContainer = new GraphicsContainer ();
					if (pContainer)
					{
						pContainer->FromXml(oXml, m_model, m_oViewBox, m_oUs, Matrix());
						m_model->HashRef(pContainer, FALSE);
					}

					--m_nDefsLayer;
					if (0 == m_nDefsLayer)
						m_bDefinesLayer	= FALSE;

					return TRUE;
				}


				// ATLTRACE ( L"Node : %s\n", oXml.GetName() );

				ExploreLayer	=	TRUE;

				++m_nLayerLevel;

				CString ID		=	oXml.GetAttribute ( _T("id") );

				CString XmlTransform = oXml.GetAttribute ( _T("transform") );
				if (XmlTransform.GetLength ())
				{
					Matrix oTransform(XmlTransform, m_oUs);

					m_transforms.Push(oTransform);
				}
				else
				{
					m_transforms.Push(Matrix());
				}

				// m_oStyle.SetDefault ();

				m_oStyle.ClearFillColor();

				CString css = oXml.GetAttribute(_T("style"));
				if (css.GetLength())
				{
					m_oFontStyle.SetStyle (css, TRUE);
					m_oStyle.SetStyle (css, TRUE, m_oUs, m_model, m_oColTable);
				}
				else
				{
					m_oFontStyle.UpdateStyle (oXml);
					m_oStyle.UpdateStyle (oXml, m_oUs, m_model, m_oColTable);
				}

				m_oStyles.Push(m_oStyle);

				m_transforms.Pop();

				GraphicsContainer* pContainer = new GraphicsContainer();
				if (pContainer)
				{
					pContainer->FromXml (oXml, m_model, m_oViewBox, m_oUs, m_transforms.GetFinal());
					m_model->Push(pContainer);

					return TRUE;
				}
			}
			else if (_T("xml") == strXmlNode)
			{
				CXmlNode oXmlSub;
				if (oXml.GetSubNode(oXmlSub))
				{
					if (FALSE == Explore(oXmlSub))
						return FALSE;
				}
			}
			else if ( _T("defs") == strXmlNode)
			{
				m_bDefinesLayer	=	TRUE;
				m_nDefsLayer++;
			}
			else if ( _T("style") == strXmlNode)
			{
				if (_T("text/css") == oXml.GetAttribute(_T("type")))
				{
					m_CSS.Read(oXml, m_oUs, m_model, m_oColTable);
				}
			}
			else
			{
				LoadElement(oXml);

				if (_T("clipPath") == strXmlNode && !m_bDefinesLayer)
					return TRUE;

				if (_T("pattern") == strXmlNode && m_bDefinesLayer)
					readInnerNodes = FALSE;

				if ( _T("symbol") == strXmlNode)	//	контент хранится в соответствующем классе
					return TRUE;
			}

			if (readInnerNodes && oXml.HasChildNodes())
			{
				XML::IXMLDOMNodeListPtr pXmlNodes = NULL;
				if (oXml.GetNodes(pXmlNodes))
				{
					CXmlNodes oXmlNodes;
					if (oXmlNodes.FromXmlNodes(pXmlNodes))
					{
						for (long i = 0; i < oXmlNodes.GetCount(); ++i)
						{
							CXmlNode oXmlNode2;
							if (oXmlNodes.GetAt(i, oXmlNode2))
							{
								if (FALSE == Explore(oXmlNode2))
								{
									if (m_bDefinesLayer)
									{
										--m_nDefsLayer;
										if (0 == m_nDefsLayer)
											m_bDefinesLayer	= FALSE;
									}

									return FALSE;
								}
							}
						}
					}
				}
			}

			if (ExploreLayer)
			{
				m_transforms.Pop ();
				m_oStyles.Pop();

				--m_nLayerLevel;
			}

			if (m_bDefinesLayer)
			{
				--m_nDefsLayer;
				if ( 0 == m_nDefsLayer )
					m_bDefinesLayer	=	FALSE;
			}

			return TRUE;
		}

	public:

		inline long	GetWidth() const 
		{
			return m_nWidth; 
		}
		inline long	GetHeight() const
		{
			return m_nHeight; 
		}
		inline Metrics GetMetics() const
		{
			return m_Metrics;
		}
		inline const UnitSystem& GetUnitSystem ()
		{
			return m_oUs; 
		}
		inline CStyleCSS* GetCSS()
		{
			if (m_CSS.IsValid())
				return &m_CSS;

			return NULL;
		}
		//
		inline void SetDefaultWidth(const long& Width)
		{
			m_nDefWidth = Width;
		}

		inline void SetDefaultHeight(const long& Height)
		{
			m_nDefHeight = Height;
		}
		inline void SetWorkingDirectory(const CString& sWorkingDirectory)
		{
			m_sWorkingDirectory	= sWorkingDirectory;
		}

	private:

		inline BOOL LoadElement(CXmlNode& oXml, BOOL Defines = FALSE)
		{
			CString strXmlNode = oXml.GetName();
			if (strXmlNode.GetLength())
			{
				if (L'#' == strXmlNode[0]) 
					return FALSE;
			}

			// ATLTRACE ( L"LoadElement : %s\n", strXmlNode );

			if (m_model)
			{
				RefElement* pReference = m_oDefsBuilder.Build (strXmlNode);
				if (pReference)
				{
					if (EPattern == pReference->nodeType())
					{
						((Pattern*)pReference)->FromXml (oXml, m_model, m_oUs);
					}
					else
					{
						pReference->FromXml (oXml, m_model, m_oUs);
					}

					if (m_model->HashRef (pReference, TRUE))
						UpdateSymbol (pReference, oXml);

					return TRUE;
				}

				if (m_bDefinesLayer)
				{
					DrawElement* paintElem = Create (oXml, FALSE);
					if (paintElem)
					{
						if (m_model->HashRef (paintElem, FALSE))
						{

						}
					}

					return TRUE;
				}

				Create (oXml);				
			}

			return FALSE;
		}
		inline DrawElement* Create(CXmlNode& oXmlNode, BOOL bAddStorage = TRUE)
		{
			CString strXmlNode = oXmlNode.GetName();
			if (strXmlNode.GetLength())
			{
				if (L'#' == strXmlNode[0]) 
					return FALSE;
			}

#ifdef _DEBUG
			ATLTRACE (L"[svg] render element : %s\n", strXmlNode);
#endif

			DrawElement* element		=	m_oDrawBuilder.Build (strXmlNode);
			if (element)
			{
				Style oTopStyle			=	m_oStyles.GetTop();
				Style oStyle			=	m_oStyle;
				oStyle.ClearOpacity ();

				FontStyle oFontStyle	=	m_oFontStyle;

				CString css = oXmlNode.GetAttribute (_T("style"));
				if (css.GetLength())
				{
					oStyle.UpdateStyle(oXmlNode, m_oUs, m_model, m_oColTable);
					oStyle.SetStyle(css, FALSE, m_oUs, m_model, m_oColTable);
					oFontStyle.SetStyle(css, FALSE);
				}
				else
				{
					oStyle.UpdateStyle(oXmlNode, m_oUs, m_model, m_oColTable);
					oFontStyle.UpdateStyle(oXmlNode);
				}

				m_oUs.SetFontSizeForEM(oFontStyle.DoubleAttribute(FontSize));

				oStyle.Combine(oTopStyle);
				element->SetStyle(oStyle);

				if (EText == element->nodeType())
				{
					Text* pText = static_cast<Text*>(element);
					if (pText)
						pText->m_oFontStyle	= oFontStyle;
				}

				CString transforms = oXmlNode.GetAttribute(_T("transform"));
				if (transforms.GetLength())
				{
					Matrix transform(transforms, m_oUs);
					m_transforms.Push(transform);
					element->SetTransform(m_transforms.GetTop());
					m_transforms.Pop ();
				}
				else
				{
					element->SetTransform(m_transforms.GetTop());
				}

				element->FromXml(oXmlNode, m_oUs);

				if (bAddStorage)				
					m_model->Push(element);

				return element;
			}

			return NULL;
		}
		inline void UpdateSymbol(RefElement* pReference, CXmlNode& oXml)
		{
			if (ESymbol == pReference->nodeType())
			{
				if (oXml.HasChildNodes())
				{
					XML::IXMLDOMNodeListPtr pXmlNodes = NULL;
					if (oXml.GetNodes(pXmlNodes))
					{
						CXmlNodes oXmlNodes;
						if (oXmlNodes.FromXmlNodes(pXmlNodes))
						{
							for (long i = 0; i < oXmlNodes.GetCount(); ++i)
							{
								CXmlNode oXml2;
								if (oXmlNodes.GetAt(i,oXml2))
								{
									((Symbol*)pReference)->AddContent(Create(oXml2, FALSE));
								}
							}
						}
					}
				}
			}
		}
		inline BOOL SetDefaultSizes()
		{
			if ((0 == m_nWidth)||(0 == m_nHeight))
			{
				if ((0 == (int)m_oViewBox.m_nWidth) || (0 == (int)m_oViewBox.m_nHeight))
				{
					m_oViewBox.m_nWidth		=	m_nDefWidth;
					m_oViewBox.m_nHeight	=	m_nDefHeight;
				}

				m_Metrics					=	PX;

				m_nWidth					=	m_oViewBox.m_nWidth;
				m_nHeight					=	m_oViewBox.m_nHeight;

				if (0 == m_oViewBox.m_nWidth)
					m_nWidth				=	__max (m_oViewBox.m_nWidth, m_oViewBox.m_nHeight);
				if (0 == m_oViewBox.m_nHeight)
					m_nHeight				=	__max (m_oViewBox.m_nWidth, m_oViewBox.m_nHeight);

				m_oUs.SetViewBox (m_nWidth, m_nHeight, m_oViewBox, m_Metrics);

				return TRUE;
			}

			return FALSE;
		}

	private:

		DOCTYPE			m_DOCTYPE;

		Metrics			m_Metrics;

		LONG			m_nWidth;
		LONG			m_nHeight;

		LONG			m_nDefsLayer;
		BOOL			m_bDefinesLayer;

		Storage*		m_model;
		DrawBuilder		m_oDrawBuilder;
		DefsBuilder		m_oDefsBuilder;

		ColorTable		m_oColTable;
		Style			m_oStyle;
		FontStyle		m_oFontStyle;
		StyleStack		m_oStyles;

		MatrixStack		m_transforms;

		long			m_nLayerLevel;	//	for transforms

		ViewBox			m_oViewBox;
		UnitSystem		m_oUs;

		long			m_nDefWidth;
		long			m_nDefHeight;

		CString			m_sWorkingDirectory;
		CStyleCSS		m_CSS;
	};
}
