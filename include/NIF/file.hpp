#pragma once

#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <cstdint>
#include <memory>

#include <NIF/export_visibility.hpp>
#include <NIF/enums.hpp>
#include <NIF/interfaces/block.hpp>

namespace NIF
{
	class NIF_API File
	{
	public:
		File() : file_name("output") {}
		File(const std::string& file_path);

		uint32_t GetVersion() const;
		uint32_t GetUserVersion1() const;
		uint32_t GetUserVersion2() const;

		void SetFileName(std::string file_name);

		//! Read from little endian binary stream
		NIF_API friend std::istream& operator>>(std::ostream& in, File& obj);
		//! Write to little endian binary stream
		NIF_API friend std::ostream& operator<<(std::ostream& out, const File& obj);

		friend Block;
	private:
		//! Information about the layout of the file and what data it holds.
		//! \note A valid NIF header is always in little endian
		class Header
		{
		public:
			Header() : version(0x14020007), endian(EndianType::ENDIAN_LITTLE)
			{
				header_line.reserve(kMaxHeaderLineSize);
			}

			std::string ToString() const;
			NIF_API friend std::istream& operator>>(std::istream& in, Header& obj)
			{
				obj.ReadBinary(in);

				return in;
			}
			NIF_API friend std::ostream& operator<<(std::ostream& out, const Header& obj)
			{
				obj.WriteBinary(out);

				return out;
			}
			friend File;

			//! Information about how the NIF was exported, part of the #Header.
			class ExportInfo
			{
			public:
				ExportInfo() : use_extended_info(false) {}

				std::string ToString() const;
				NIF_API friend std::istream& operator>>(std::istream& in, ExportInfo& obj)
				{
					obj.ReadBinary(in);

					return in;
				}
				NIF_API friend std::ostream& operator<<(std::ostream& out, const ExportInfo& obj)
				{
					obj.WriteBinary(out);

					return out;
				}
				friend File;

				const uint32_t kNumOldInfo = 2;

				bool use_extended_info;
				std::string creator;
				std::array<std::string, 3> info;
			private:
				void ReadBinary(std::istream& in);
				void WriteBinary(std::ostream& out) const;
			};

			const uint32_t kMaxHeaderLineSize = 45;

			std::string header_line;
			std::array<std::string, 3> copyright;
			uint32_t version;
			uint32_t user_version_1;
			uint32_t user_version_2;
			uint32_t image_preview_size;
			EndianType endian;
			ExportInfo export_info;
			std::vector<std::string> block_type_names;
			std::vector<uint16_t> block_type_index;
			std::vector<uint32_t> block_sizes;
			uint32_t max_name_length;
			std::vector<std::string> block_names;
			uint32_t num_groups;

		private:
			void ReadBinary(std::istream& in);
			void WriteBinary(std::ostream& out) const;
		};

		//! File name of NIF without extension
		std::string file_name;
		Header header;
		std::vector<std::unique_ptr<Block>> blocks;
	};
}