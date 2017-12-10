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

	uint32_t getStart() const
	{
		return m_start;
	}

	void setStart(const uint32_t value)
	{
		m_start = value;
	}

	T &operator[](const uint32_t index) const
	{
		return m_array[(m_start + index) % m_count];
	}

	void swap(const uint32_t index0, const uint32_t index1)
	{
		T temp = m_array[index0];
		m_array[index0] = m_array[index1];
		m_array[index1] = temp;
	}

private:
	T *m_array;
	uint32_t m_capacity;
	uint32_t m_count;
	uint32_t m_start;
};

#endif