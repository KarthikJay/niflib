#include <sstream>

#include <NIF/interfaces/controller.hpp>
#include <NIF/utility.hpp>
#include <NIF/enums.hpp>
#include <NIF/file.hpp>

using namespace std;

namespace NIF
{
	string Controller::ToString() const
	{
		stringstream ss;

		return ss.str();
	}

	uint32_t Controller::GetSizeInBytes() const
	{
		return	sizeof(next_controller) + sizeof(flags) + sizeof(frequency) +
				sizeof(phase) + sizeof(time_start) + sizeof(time_end) + sizeof(target);
	}

	Controller::AnimType Controller::GetAnimType() const
	{
		return AnimType(flags & kMaskAnimType);
	}

	void Controller::SetAnimType(AnimType anim)
	{
		flags = ~kMaskAnimType & flags;
		flags |= ToIntegral(anim);
	}

	Controller::CycleType Controller::GetCycleType() const
	{
		return CycleType(flags & kMaskCycleType);
	}

	void Controller::SetCycleType(CycleType cycle)
	{
		flags = ~kMaskCycleType & flags;
		flags |= ToIntegral(cycle);
	}

	Controller::ActiveState Controller::IsActive() const
	{
		return ActiveState(flags & kMaskActive);
	}

	void Controller::ToggleActive()
	{
		flags = (~flags & kMaskActive) | (flags & ~kMaskActive);
	}

	Controller::Direction Controller::GetDirection() const
	{
		return Direction(flags & kMaskDirection);
	}

	void Controller::ToggleDirection()
	{
		flags = (~flags & kMaskDirection) | (flags & ~kMaskDirection);
	}

	Controller::ManagerState Controller::IsManaged() const
	{
		return ManagerState(flags & kMaskManager);
	}

	void Controller::ToggleManagement()
	{
		flags = (~flags & kMaskManager) | (flags & ~kMaskManager);
	}

	Controller::TimeScale Controller::IsTimeScaled() const
	{
		return TimeScale(flags & kMaskTimeScale);
	}

	void Controller::ToggleTimeScale()
	{
		flags = (~flags & kMaskTimeScale) | (flags & ~kMaskTimeScale);
	}

	Controller::ForceUpdate Controller::IsUpdateForced() const
	{
		return ForceUpdate(flags & kMaskForceUpdate);
	}

	void Controller::ToggleForceUpdate()
	{
		flags = (~flags & kMaskForceUpdate) | (flags & ~kMaskForceUpdate);
	}

	float Controller::GetFrequency() const
	{
		return frequency;
	}

	void Controller::SetFrequency(float frequency)
	{
		this->frequency = frequency;
	}

	float Controller::GetPhase() const
	{
		return phase;
	}

	void Controller::SetPhase(float phase)
	{
		this->phase = phase;
	}

	float Controller::GetStartTime() const
	{
		return time_start;
	}
	
	float Controller::GetEndTime() const
	{
		return time_end;
	}

	void Controller::SetTime(float start, float end)
	{
		time_start = start;
		time_end = end;
	}

	void Controller::Normalize()
	{
		time_start = frequency * time_start + phase;
		time_end = frequency * time_end + phase;
		frequency = 1.0f;
		phase = 0.0f;
	}

	istream& Controller::ReadBinary(istream& in)
	{
		in.read(reinterpret_cast<char*>(&next_controller), sizeof(next_controller));
		in.read(reinterpret_cast<char*>(&flags), sizeof(flags));
		in.read(reinterpret_cast<char*>(&frequency), sizeof(frequency));
		in.read(reinterpret_cast<char*>(&phase), sizeof(phase));
		in.read(reinterpret_cast<char*>(&time_start), sizeof(time_start));
		in.read(reinterpret_cast<char*>(&time_end), sizeof(time_end));
		in.read(reinterpret_cast<char*>(&target), sizeof(target));

		return in;
	}

	ostream& Controller::WriteBinary(ostream& out) const
	{
		WriteUnsignedIntegral(out, next_controller);
		WriteUnsignedIntegral(out, flags);
		WriteUnsignedIntegral(out, frequency);
		WriteUnsignedIntegral(out, phase);
		WriteUnsignedIntegral(out, time_start);
		WriteUnsignedIntegral(out, time_end);
		WriteUnsignedIntegral(out, target);

		return out;
	}
}