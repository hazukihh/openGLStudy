#pragma once


namespace Engine
{
	// floatֵ��wrapper��
	//ʱ�䲽��
	class Timestep
	{
	private:
		float m_Time;
	public:
		Timestep(float time = 0.0f)
			:m_Time(time)
		{
		}

		/*��������ת�������
		* ���� Timestep ������ʽת��Ϊ float ����
		* ����ζ�ſ�����ʹ�� float ����һ��ʹ�� Timestep �������罫�丳ֵ��һ�� float ������
		*/
		operator float() const { return m_Time; }

		//��
		float GetSeconds() { return m_Time; }
		//����
		float GetMilliseconds() { return m_Time * 1000.0f; };

	};
}

