#pragma once

#include <string>
#include <iostream>
#include <climits>
#include <cstdint>
#include <type_traits>
#include <utility>

#include <NIF/enums.hpp>

namespace NIF
{
	//! ---NIF read utility constants---
	const uint32_t kLineBufferSize = 256;
	const uint32_t kMaxVersionStringLength = 16;
	const uint32_t kMaxHeaderStringLength = 22;

	//! ---NIF general utility functions---
	//! Fold expressions not available in MSVC 15.3
	//! https://blogs.msdn.microsoft.com/vcblog/2017/05/10/c17-features-in-vs-2017-3/
	//! Source taken from: https://goo.gl/d8QpCg
	/*
	template<class T, std::size_t... N>
	constexpr T bswap_impl(T i, std::index_sequence<N...>)
	{
		return ((((i >> (N * CHAR_BIT)) & (T)(unsigned char)(-1))
				<< ((sizeof(T) - 1 - N) * CHAR_BIT)) | ...);
	}

	template<class T, class U = typename std::make_unsigned<T>::type>
	constexpr U EndianSwap(T i)
	{
		return bswap_impl<U>(i, std::make_index_sequence<sizeof(T)>{});
	}
	*/

	template<class T>
	constexpr typename std::enable_if<std::is_unsigned<T>::value, T>::type
	EndianSwap(T i, T j = 0u, std::size_t n = 0u)
	{
		return n == sizeof(T) ? j :
			EndianSwap<T>(i >> CHAR_BIT, (j << CHAR_BIT) | (i & (T)(unsigned char)(-1)), n + 1);
	}

	template<class T>
	void WriteUnsignedIntegral(std::ostream& out, T val)
	{
		out.write(reinterpret_cast<char*>(&val), static_cast<std::streamsize>(sizeof(val)));
	}

	uint32_t ValidNIF(const std::string &header_line);
	uint32_t ParseVersionString(const std::string& version_string);
	std::string FormatVersionString(uint32_t version);
	std::string GetNifHeaderLine(NIFVersion version);

	//! \todo Figure out template way of Reading/Writing strings
	//! ---NIF read utility functions---
	//! \todo Add endianness support for reading strings (just the length part)
	std::string ReadLine(std::istream& in);
	std::string ReadByteString(std::istream& in);
	std::string ReadIntString(std::istream& in);

	//! ---NIF write utility functions---
	void WriteLine(std::ostream& out, const std::string& line);
	void WriteByteString(std::ostream& out, const std::string& line);
	//! \todo Add endianness support for writing strings (just the length part)
	void WriteIntString(std::ostream& out, const std::string& line);
}