#pragma once

namespace Cubes {

	class TimeStep {
	public:
		TimeStep(float time = 0.f)
			: _time(time)
		{

		}

		float GetSeconds() const { return _time; }
		float GetMilliseconds() const { return _time * 1000; }

		inline operator float() { return _time; }

	private:
		float _time;
	};

}