#pragma once

#include <NIF/interfaces/block.hpp>
#include <NIF/export_visibility.hpp>

namespace NIF
{
	//! Abstract Time Controller for animations
	class NIF_API Controller : public virtual Block
	{
	public:
		std::string ToString() const override;
		uint32_t GetSizeInBytes() const override;
		
		enum class AnimType : uint16_t
		{
			APP_TIME	= 0b0000000000000000,
			APP_INIT	= 0b0000000000000001,
		};

		enum class CycleType : uint16_t
		{
			LOOP	= 0b0000000000000000,
			REVERSE	= 0b0000000000000010,
			CLAMP	= 0b0000000000000100,
		};

		enum class ActiveState : uint16_t
		{
			INACTIVE	= 0b0000000000000000,
			ACTIVE		= 0b0000000000001000,
		};

		enum class Direction : uint16_t
		{
			FORWARD		= 0b0000000000000000,
			BACKWARD	= 0b0000000000010000,
		};

		enum class ManagerState : uint16_t
		{
			UNMANAGED		= 0b0000000000000000,
			MANAGED			= 0b0000000000100000,
		};

		enum class TimeScale : uint16_t
		{
			DISABLED	= 0b0000000000000000,
			ENABLED		= 0b0000000001000000,
		};

		enum class ForceUpdate : uint16_t
		{
			DISABLED	= 0b0000000000000000,
			ENABLED		= 0b0000000010000000,
		};

		void SetAnimType(AnimType anim);
		AnimType GetAnimType() const;
		void SetCycleType(CycleType cycle);
		CycleType GetCycleType() const;
		ActiveState IsActive() const;
		void ToggleActive();
		Direction GetDirection() const;
		void ToggleDirection();
		ManagerState IsManaged() const;
		void ToggleManagement();
		TimeScale IsTimeScaled() const;
		void ToggleTimeScale();
		ForceUpdate IsUpdateForced() const;
		void ToggleForceUpdate();
		float GetFrequency() const;
		void SetFrequency(float frequency);
		float GetPhase() const;
		void SetPhase(float phase);
		float GetStartTime() const;
		float GetEndTime() const;
		void SetTime(float start, float end);
		void Normalize();
		/*
		void LinkNextController(uint32_t block_index);
		uint32_t GetTarget();
		void SetTarget(uint32_t block_index);
		*/

	protected:
		//! Block index of next #Controller
		uint32_t next_controller;
		uint16_t flags;
		float frequency;
		float phase;
		float time_start;
		float time_end;
		//! Block index of target object
		uint32_t target;

		Controller() :	next_controller(UINT32_MAX), flags(0), frequency(1.0),
						phase(0.0), time_start(0.0), time_end(0.0), target(UINT32_MAX) {}

		const uint16_t kMaskAnimType	= 0b0000000000000001;
		const uint16_t kMaskCycleType	= 0b0000000000000110;
		const uint16_t kMaskActive		= 0b0000000000001000;
		const uint16_t kMaskDirection	= 0b0000000000010000;
		const uint16_t kMaskManager		= 0b0000000000100000;
		const uint16_t kMaskTimeScale	= 0b0000000001000000;
		const uint16_t kMaskForceUpdate	= 0b0000000010000000;

		std::istream& ReadBinary(std::istream& in) override;
		std::ostream& WriteBinary(std::ostream& out) const override;
	};
}