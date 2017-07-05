#pragma once

#include <cstdint>
// #include <cstddef>

namespace NIF
{
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
		VER_2_3			= 0x02030000, //! NIF Version 2.3
		VER_3_0			= 0x03000000, //! NIF Version 3.0
		VER_3_03		= 0x03000300, //! NIF Version 3.03
		VER_3_1			= 0x03010000, //! NIF Version 3.1
		VER_3_3_0_13	= 0x0303000D, //! NIF Version 3.3.0.13
		VER_4_0_0_0		= 0x04000000, //! NIF Version 4.0.0.0
		VER_4_0_0_2		= 0x04000002, //! NIF Version 4.0.0.2
		VER_4_1_0_12	= 0x0401000C, //! NIF Version 4.1.0.12
		VER_4_2_0_2		= 0x04020002, //! NIF Version 4.2.0.2
		VER_4_2_1_0		= 0x04020100, //! NIF Version 4.2.1.0
		VER_4_2_2_0		= 0x04020200, //! NIF Version 4.2.2.0
		VER_10_0_1_0	= 0x0A000100, //! NIF Version 10.0.1.0
		VER_10_0_1_2	= 0x0A000102, //! NIF Version 10.0.1.2
		VER_10_0_1_3	= 0x0A000103, //! NIF Version 10.0.1.3
		VER_10_1_0_0	= 0x0A010000, //! NIF Version 10.1.0.0
		VER_10_1_0_101	= 0x0A010065, //! NIF Version 10.1.0.101
		VER_10_1_0_106	= 0x0A01006A, //! NIF Version 10.1.0.106
		VER_10_2_0_0	= 0x0A020000, //! NIF Version 10.2.0.0
		VER_10_4_0_1	= 0x0A040001, //! NIF Version 10.4.0.1
		VER_20_0_0_4	= 0x14000004, //! NIF Version 20.0.0.4
		VER_20_0_0_5	= 0x14000005, //! NIF Version 20.0.0.5
		VER_20_1_0_3	= 0x14010003, //! NIF Version 20.1.0.3
		VER_20_2_0_7	= 0x14020007, //! NIF Version 20.2.0.7
		VER_20_2_0_8	= 0x14020008, //! NIF Version 20.2.0.7
		VER_20_3_0_1	= 0x14030001, //! NIF Version 20.3.0.1
		VER_20_3_0_2	= 0x14030002, //! NIF Version 20.3.0.2
		VER_20_3_0_3	= 0x14030003, //! NIF Version 20.3.0.3
		VER_20_3_0_6	= 0x14030006, //! NIF Version 20.3.0.6
		VER_20_3_0_9	= 0x14030009, //! NIF Version 20.3.0.9
		VER_30_0_0_2	= 0x1E000002, //! NIF Version 30.0.0.2
		VER_30_1_0_3	= 0x1E010003, //! NIF Version 30.1.0.3
		VER_UNSUPPORTED	= 0xFFFFFFFF //! Unsupported NIF Version
		// VER_INVALID		= 0xFFFFFFFE //! Not a NIF file
	};

	//! \todo Add operator overload 
	enum class EndianType : uint8_t
	{
		ENDIAN_BIG,		//! The numbers are stored in big endian format, such as those used by PowerPC Mac pro
		ENDIAN_LITTLE	//! The numbers are stored in little endian format, such as those used by x86 processors.
	};
}