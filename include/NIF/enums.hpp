#pragma once

#include <iostream>
#include <cstdint>
#include <utility>
#include <type_traits>

#include <NIF/export_visibility.hpp>

namespace NIF
{
	template<typename E>
	constexpr auto ToIntegral(E e) -> typename std::underlying_type<E>::type
	{
		return static_cast<typename std::underlying_type<E>::type>(e);
	}

	constexpr uint32_t Version(uint8_t major, uint8_t minor, uint8_t patch, uint8_t internal)
	{
		return (major << 24) | (minor << 16) | (patch << 8) | internal;
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

	//! List of supported NIF's by this library
	enum class NIF_API NIFVersion : uint32_t
	{
		V2_3		= 0x02030000,	//! Dark Age of Camelot
		V3_0		= 0x03000000,	//! Star Trek: Bridge Commander
		V3_03		= 0x03000300,	//! Dark Age of Camelot
		V3_1		= 0x03010000,	//! Dark Age of Camelot, Star Trek: Bridge Commander
		V4_0_0_0	= 0x04000000,	//! Freedom Force
		V4_0_0_2	= 0x04000002,	//! Morrowind, Freedom Force
		V4_1_0_12	= 0x0401000C,	//! Dark Age of Camelot
		V4_2_0_2	= 0x04020002,	//! Civilization IV
		V4_2_1_0	= 0x04020100,	//! Dark Age of Camelot, Civilization IV
		V4_2_2_0	= 0x04020200,	//! Dark Age of Camelot, Civilization IV, Empire Earth II, Culpa Innata
		V10_0_1_0	= 0x0A000100,	//! Zoo Tycoon 2, Civilization IV, Oblivion
		V10_0_1_2	= 0x0A000102,	//! Oblivion
		V10_1_0_0	= 0x0A010000,	//! Dark Age of Camelot, Civilization IV, Freedom Force vs. the 3rd Reich, Axis and Allies, Kohan 2, Entropia Universe, Wildlife Park 2, The Guild 2, NeoSteam, Empire Earth II
		V10_2_0_0	= 0x0A020000,	//! Civilization IV, Oblivion, Loki, Pro Cycling Manager, Prison Tycoon, Red Ocean, Wildlife Park 2
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
		V30_1_0_3	= 0x1E010003	//! Rocksmith 2014
	};

	enum class EndianType : uint8_t
	{
		ENDIAN_BIG		= 0,	//! The numbers are stored in big endian format.
		ENDIAN_LITTLE	= 1		//! The numbers are stored in little endian format.
	};

	enum class BSLightingShaderPropertyShaderType : uint32_t
	{
		DEFAULT								= 0,	//! Default
		ENVIRONMENT_MAP						= 1,	//! Enables Environment Map
		GLOW_MAP							= 2,	//! Enables Glow Map
		HEIGHT_MAP							= 3,	//! Enables Height Map
		FACE_TINT							= 4,	//! Enables SubSurface, Detail & Tint
		SKIN_TINT							= 5,	//! Enables Skin Tint Color
		HAIR_TINT							= 6,	//! Enables Hair Tint Color
		PARALLAX_OCC						= 7,	//! Enables Height, Max Passes & Scale
		MULTI_TEXTURE_LANDSCAPE				= 8,	//! Enables Multi-texture for landscapes
		LOD_LANDSCAPE						= 9,	//! Enabled Level of Detail for landscapes
		SNOW								= 10,	//! Enables Snow
		MULTI_LAYER_PARALLAX				= 11,	//! Enables EnvMap Mask, Layer, Parallax Layer Thickness, Parallax Refraction Scale, Parallax Inner Layer U Scale, Parallax Inner Layer V Scale, EnvMap Scale
		TREE_ANIM							= 12,	//! Enables Tree Animations
		LOD_OBJECTS							= 13,	//! Enables Level of Detail for objects
		MULTI_INDEX_TRISHAPE_SNOW			= 14,	//! Enables Snow Sparkles
		LOD_OBJECTS_HD						= 15,	//! Enables Level of Detail in HD for objects
		EYE									= 16,	//! Enables EnvMap Mask, Eye EnvMap Scale
		CLOUD								= 17,	//! Enables Cloud
		LOD_LANDSCAPE_NOISE					= 18,	//! Enables Level of Detail noise for landscapes
		MULTI_TEXTURE_LANDSCAPE_LOD_BLEND	= 19,	//! Enables multi-texture Level of Detail blending for landscapes
		DISMEMBERMENT						= 20,	//! Enables Dismemberment
	};

	inline bool operator== (const EndianType lhs, const EndianType rhs)
	{
		return ToIntegral(lhs) == ToIntegral(rhs);
	}

	inline std::ostream& operator<< (std::ostream& out, const EndianType& et)
	{
		return out << (et == EndianType::ENDIAN_BIG ? "Big Endian" : "Little Endian");
	}

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