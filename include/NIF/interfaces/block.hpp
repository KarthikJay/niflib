#pragma once

#include <vector>
#include <string>
#include <memory>

#include <NIF/export_visibility.hpp>

namespace NIF
{
	class File;
	class Header;

	//! Abstract NIF Block class
	//! This class and all derived classes can only be created by #BlockFactory
	class NIF_API Block
	{
	public:
		virtual ~Block() {}

		virtual std::string ToString() const = 0;
		virtual std::string GetBlockTypeName() const = 0;
		virtual uint32_t GetSizeInBytes() const = 0;
	
		NIF_API friend std::istream& operator>>(std::istream& in, Block& nib);
		NIF_API friend std::ostream& operator<<(std::ostream& out, const Block& nib);
	protected:
		File& owner;
		Header& header;
		std::vector<std::unique_ptr<Block>>& blocks;

		//! String formatting widths used in derived #ToString() functions
		const uint32_t kBlockTypeWidth = 30;
		const uint32_t kMemberTypeWidth = 30;
		const uint32_t kIndexWidth = 4;

		Block(File& file);
		Block(const Block& copy) = delete;
		Block& operator=(const Block& copy);

		virtual std::ostream& WriteBinary(std::ostream& out) const = 0;
		virtual std::istream& ReadBinary(std::istream& in) = 0;
	};
}