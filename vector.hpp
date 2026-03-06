#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <utility> 

namespace softacademy {
    
template <typename T>
class Vector {
public:
    using value_type = T;
    using size_type = std::size_t;

	Vector() noexcept
		: m_size(0)
		, m_capacity(0)
		, m_data(nullptr) {}

	Vector(size_type size, size_type capacity, T* data)
		: m_size(size)
		, m_capacity(capacity) {
		m_data = new T[m_capacity];
		for (size_type i = 0; i < m_size; i++) {
			m_data[i] = data[i];
		}
	}

	Vector(const Vector& other)
		: m_size(other.m_size)
		, m_capacity(other.m_capacity) {
		m_data = new T[m_capacity];
		for (size_type i = 0; i < m_size; i++) {
			m_data[i] = other.m_data[i];
		}
	}

	Vector(Vector&& other) noexcept {
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;
		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
	}

	Vector& operator=(const Vector& other) {
		if (this != &other) {
			delete[] m_data;
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_data = new T[m_capacity];
			for (size_type i = 0; i < m_size; i++) {
				m_data[i] = other.m_data[i];
			}
		}
		return *this;
	}

	Vector& operator=(Vector&& other) noexcept {
		if (this != &other) {
			delete[] m_data;
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_data = other.m_data;
			other.m_size = 0;
			other.m_capacity = 0;
			other.m_data = nullptr;
		}
		return *this;
	}

	~Vector() {
		delete[] m_data;
		m_data = nullptr;
	}

public:
	size_type size() const noexcept {
		return m_size;
	}

	size_type capacity() const noexcept {
		return m_capacity;
	}

	bool empty() const noexcept {
		return m_size == 0;
	}

	void reserve(size_type new_cap) {
		if (new_cap <= m_capacity) {
		    return;
		}
		if (new_cap < 0) {
			throw std::invalid_argument("invalid argument");
		}
		T* new_data = new T[new_cap];
		for (size_type i = 0; i < m_size; i++) {
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = new_cap;
	}

	void shrink_to_fit() {
		if (m_capacity == m_size) {
		    return;
		}
		if (m_size == 0) {
			delete[] m_data;
			m_data = nullptr;
			m_capacity = 0;
			return;
		}
		T* new_data = new T[m_size];
		for (size_type i = 0; i < m_size; i++) {
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = m_size;
	}


	T& operator[](int index) {
	    if(index < 0 || index >= m_size) {
	        throw std::out_of_range("index is out of range");
	    }
	    return m_data[index];
	}
	const T& operator[](int index) {
	    if(index < 0 || index >= m_size) {
	        throw std::out_of_range("index is out of range");
	    }
	    return m_data[index];
	}
	T& at(int index) {
	    if(index < 0 || index >= m_size) {
	        throw std::out_of_range("index is out of range");
	    }
	    return m_data[index];
	}
	const T& at(int index) {
	    if(index < 0 || index >= m_size) {
	        throw std::out_of_range("index is out of range");
	    }
	    return m_data[index];
	}


	T& front() {
		if (m_size == 0) {
			throw std::out_of_range("Vector is empty");
		}
		return m_data[0];
	}

	const T& front() const {
		if (m_size == 0) {
			throw std::out_of_range("Vector is empty");
		}
		return m_data[0];
	}

	T& back() {
		if (m_size == 0) {
			throw std::out_of_range("Vector is empty");
		}
		return m_data[m_size - 1];
	}
	const T& back() const {
		if (m_size == 0) {
			throw std::out_of_range("Vector is empty");
		}
		return m_data[m_size - 1];
	}

	T* data() noexcept {
		return m_data;
	}
	const T* data() const noexcept {
		return m_data;
	}

	void clear() noexcept {
		m_size = 0;
	}

	void push_back(const T& value) {
		if (m_size == m_capacity) {
			if (m_capacity == 0) {
				m_capacity = 1;
			} 
			else {
				m_capacity *= 2;
			}
			T* new_data = new T[m_capacity];
			for (int i = 0; i < m_size; i++) {
				new_data[i] = m_data[i];
			}
			delete[] m_data;
			m_data = new_data;
		}
		m_data[m_size] = value;
		m_size++;
	}

	void push_back(T&& value) {
		if (m_size == m_capacity) {
			if (m_capacity == 0) {
				m_capacity = 1;
			} 
			else {
				m_capacity *= 2;
			}
			T* new_data = new T[m_capacity];
			for (size_type i = 0; i < m_size; i++) {
				new_data[i] = m_data[i];
			}
			delete[] m_data;
			m_data = new_data;
		}
		m_data[m_size] = value;
		m_size++;
	}
	void pop_back() {
		if (m_size == 0) {
			throw std::out_of_range("Vector is empty");
		}
		m_size--;
	}

	void resize(size_type new_size) {
		if (new_size == m_size) {
		    return;
		}
		if (new_size < 0) {
			throw std::invalid_argument("invalid argument");
		}
		if (new_size < m_size) {
			m_size = new_size;
		}
		else if (new_size > m_size) {
			if (new_size > m_capacity) {
				reserve(new_size);
			}
			for (size_type i = m_size; i < new_size; i++) {
				m_data[i] = T();
			}
			m_size = new_size;
		}
	}

	void resize(size_type new_size, const T& value) {
		if (new_size == m_size) {
            return;
        }
		if (new_size < 0) {
			throw std::invalid_argument("negative size");
		}
		if (new_size < m_size) {
			m_size = new_size;
		}
        else if (new_size > m_size) {
			if (new_size > m_capacity) {
				reserve(new_size);
			}
			for (size_type i = m_size; i < new_size; i++) {
				m_data[i] = value;
			}
			m_size = new_size;
		}
	}

	void swap(Vector& other) noexcept {
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_data, other.m_data);
	}

private:
	size_type m_size;
	size_type m_capacity;
	T* m_data;
};

}
#endif