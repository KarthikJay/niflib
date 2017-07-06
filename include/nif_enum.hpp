#pragma once

#include <cstdint>
#include <utility>
#include <type_traits>

namespace NIF
{
	template<typename E>
	constexpr auto ToIntegral(E e) -> typename std::underlying_type<E>::type
	{
		return static_cast<typename std::underlying_type<E>::type>(e);
	}

	enum class KFGame : uint32_t
	{
		KF_MW,		//! Morrowind keyframe files: NiSequenceStreamHelper (.kf)
		KF_DAOC,	//! Dark Age of Camelot keyframe files: NiNode (.kfa)
		KF_CIV4,	//! Civ 4 keyframe files: NiControllerSequence (.kf)
		KF_FFVT3R	//! Freedom Force keyframe files: NiControllerSequence (.kf)
	};

	enum class ExportOptions : uint32_t
	{
		EXPORT_NIF,				//! Output single NIF
		EXPORT_NIF_KF,			//! Output single NIF, KF and KFM
		EXPORT_NIF_KF_MULTI,	//! Output single NIF, multiple KF and KFM
		EXPORT_KF,				//! Output single KF
		EXPORT_KF_MULTI			//! Output multiple KF
	};

	enum class NIFVersion : uint32_t
	{
		V2_3		= 0x02030000,	//! NIF Version 2.3
		V3_0		= 0x03000000,	//! NIF Version 3.0
		V3_03		= 0x03000300,	//! NIF Version 3.03
		V3_1		= 0x03010000,	//! NIF Version 3.1
		V3_3_0_13	= 0x0303000D,	//! NIF Version 3.3.0.13
		V4_0_0_0	= 0x04000000,	//! NIF Version 4.0.0.0
		V4_0_0_2	= 0x04000002,	//! NIF Version 4.0.0.2
		V4_1_0_12	= 0x0401000C,	//! NIF Version 4.1.0.12
		V4_2_0_2	= 0x04020002,	//! NIF Version 4.2.0.2
		V4_2_1_0	= 0x04020100,	//! NIF Version 4.2.1.0
		V4_2_2_0	= 0x04020200,	//! NIF Version 4.2.2.0
		V10_0_1_0	= 0x0A000100,	//! NIF Version 10.0.1.0
		V10_0_1_2	= 0x0A000102,	//! NIF Version 10.0.1.2
		V10_0_1_3	= 0x0A000103,	//! NIF Version 10.0.1.3
		V10_1_0_0	= 0x0A010000,	//! NIF Version 10.1.0.0
		V10_1_0_101	= 0x0A010065,	//! NIF Version 10.1.0.101
		V10_1_0_106	= 0x0A01006A,	//! NIF Version 10.1.0.106
		V10_2_0_0	= 0x0A020000,	//! NIF Version 10.2.0.0
		V10_4_0_1	= 0x0A040001,	//! NIF Version 10.4.0.1
		V20_0_0_4	= 0x14000004,	//! NIF Version 20.0.0.4
		V20_0_0_5	= 0x14000005,	//! NIF Version 20.0.0.5
		V20_1_0_3	= 0x14010003,	//! NIF Version 20.1.0.3
		V20_2_0_7	= 0x14020007,	//! NIF Version 20.2.0.7
		V20_2_0_8	= 0x14020008,	//! NIF Version 20.2.0.7
		V20_3_0_1	= 0x14030001,	//! NIF Version 20.3.0.1
		V20_3_0_2	= 0x14030002,	//! NIF Version 20.3.0.2
		V20_3_0_3	= 0x14030003,	//! NIF Version 20.3.0.3
		V20_3_0_6	= 0x14030006,	//! NIF Version 20.3.0.6
		V20_3_0_9	= 0x14030009,	//! NIF Version 20.3.0.9
		V30_0_0_2	= 0x1E000002,	//! NIF Version 30.0.0.2
		V30_1_0_3	= 0x1E010003,	//! NIF Version 30.1.0.3
		UNSUPPORTED	= 0xFFFFFFFF	//! Unsupported NIF Version
	};

	enum class EndianType : uint8_t
	{
		ENDIAN_BIG,		//! The numbers are stored in big endian format.
		ENDIAN_LITTLE	//! The numbers are stored in little endian format.
	};

	inline bool operator== (const NIFVersion& v1, const uint32_t& v2)
	{
		return ToIntegral(v1) == v2;
	}

	inline bool operator!= (const NIFVersion& v1, const uint32_t& v2)
	{
		return ToIntegral(v1) != v2;
	}

	inline bool operator== (const uint32_t& v1, const NIFVersion& v2)
	{
		return ToIntegral(v2) == v1;
	}
	
	inline bool operator!= (const uint32_t& v1, const NIFVersion& v2)
	{
		return ToIntegral(v2) != v1;
	}

	inline bool operator== (const NIFVersion v1, const NIFVersion v2)
	{
		return ToIntegral(v1) == ToIntegral(v2);
	}

	inline bool operator!= (const NIFVersion v1, const NIFVersion v2)
	{
		return ToIntegral(v1) != ToIntegral(v2);
	}

	inline bool operator> (const NIFVersion& v1, const uint32_t& v2)
	{
		return ToIntegral(v1) > v2;
	}
	
	inline bool operator< (const NIFVersion& v1, const uint32_t& v2)
	{
		return ToIntegral(v1) < v2;
	}

	inline bool operator> (const uint32_t& v1, const NIFVersion& v2)
	{
		return v1 > ToIntegral(v2);
	}
	
	inline bool operator< (const uint32_t& v1, const NIFVersion& v2)
	{
		return v1 < ToIntegral(v2);
	}

	inline bool operator> (const NIFVersion v1, const NIFVersion v2)
	{
		return ToIntegral(v1) > ToIntegral(v2);
	}

	inline bool operator< (const NIFVersion v1, const NIFVersion v2)
	{
		return ToIntegral(v1) < ToIntegral(v2);
	}

	inline bool operator>= (const NIFVersion& v1, const uint32_t& v2)
	{
		return ToIntegral(v1) >= v2;
	}
	
	inline bool operator<= (const NIFVersion& v1, const uint32_t& v2)
	{
		return ToIntegral(v1) <= v2;
	}

	inline bool operator>= (const uint32_t& v1, const NIFVersion& v2)
	{
		return v1 >= ToIntegral(v2);
	}
	
	inline bool operator<= (const uint32_t& v1, const NIFVersion& v2)
	{
		return v1 <= ToIntegral(v2);
	}

	inline bool operator>= (const NIFVersion v1, const NIFVersion v2)
	{
		return ToIntegral(v1) >= ToIntegral(v2);
	}

	inline bool operator<= (const NIFVersion v1, const NIFVersion v2)
	{
		return ToIntegral(v1) <= ToIntegral(v2);
	}
}