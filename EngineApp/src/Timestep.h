#pragma once


namespace Engine
{
	// float值的wrapper？
	//时间步长
	class Timestep
	{
	private:
		float m_Time;
	public:
		Timestep(float time = 0.0f)
			:m_Time(time)
		{
		}

		/*重载类型转换运算符
		* 允许将 Timestep 对象隐式转换为 float 类型
		* 这意味着可以像使用 float 类型一样使用 Timestep 对象，例如将其赋值给一个 float 变量。
		*/
		operator float() const { return m_Time; }

		//秒
		float GetSeconds() { return m_Time; }
		//毫秒
		float GetMilliseconds() { return m_Time * 1000.0f; };

	};
}

