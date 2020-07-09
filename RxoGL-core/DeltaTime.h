#pragma once
namespace rxogl
{
	class DeltaTime
	{
	private:
		float m_Time;
	public:
		DeltaTime(float time = 0)
			: m_Time(time)
		{

		}

		operator float() const { return m_Time; }
	};
}