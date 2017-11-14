#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

#include <cstdint>
#include <string>

template<typename T>
class CircularArray
{
public:
	CircularArray(uint32_t capacity)
	{
		m_capacity = capacity;
		m_count = 0;
		m_array = new T[capacity];
		memset(m_array, 0, sizeof(T) * capacity);
	}

	~CircularArray()
	{
		if (m_array)
			delete[] m_array;
	}

	uint32_t getCapacity() const
	{
		return m_capacity;
	}

	uint32_t getCount() const
	{
		return m_count;
	}

	void setCount(const uint32_t value)
	{
		m_count = value;
	}

	void decreaseCount(const uint32_t decreaseBy)
	{
		m_count -= decreaseBy;
	}

	T &operator[](const uint32_t index) const
	{
		return m_array[index];
	}

private:
	T *m_array;
	uint32_t m_capacity;
	uint32_t m_count;
};

#endif