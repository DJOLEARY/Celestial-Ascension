#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H

template<typename T>
class CircularArray
{
private:
	T *m_array[];
	uint32_t m_capacity;
	uint32_t m_count;

public:
	CircularArray(uint32_t capacity);
	{
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
		retunr m_count;
	}

	void setCount(const uint32_t value)
	{
		m_count = value;
	}

	T &opertator[](const uint32_t index) const
	{
		return m_array[index];
	}
};

#endif