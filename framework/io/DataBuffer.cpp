#include <memory>
#include <stdexcept>

#include "DataBuffer.h"

namespace newNav {
namespace framework {
namespace io {

// Constructor.
DataBuffer::DataBuffer(
	const unsigned char*	buffer,
	size_t		    		size)
	: _size(size)
{
	if (size == 0 || buffer == nullptr)
	{
		throw std::logic_error("can't construct a null buffer");
	}

	_buffer = new unsigned char[size];
	std::memcpy(_buffer, buffer, size);
	_size = size;
}

// Copy construct.
DataBuffer::DataBuffer(
	const DataBuffer&	other)
{
	if (other.empty())
	{
		_buffer = nullptr;
		_size = 0;
	}
	else
	{
		_buffer = new unsigned char[other.size()];
		std::memcpy(_buffer, other._buffer, other.size());
		_size = other.size();
	}
}

// Move constructor.
DataBuffer::DataBuffer(
	DataBuffer&&	other)
{
	this->_buffer = other._buffer;
	this->_size = other._size;

	other._buffer = nullptr;
	other._size = 0;
}

// Destructor.
DataBuffer::~DataBuffer(
	)
{
	reset();
}

// Access to the raw data stored into the buffer.
DataBuffer::operator const unsigned char *(
	void) const
{
	return _buffer;
}

// Access the size of the buffer.
std::size_t DataBuffer::size(
	void) const
{
	return _size;
}

// Indicates if the buffer is empty.
bool	DataBuffer::empty(
	) const
{
	return _buffer == nullptr;
}

// Copy operator.
DataBuffer&	DataBuffer::operator =(
	const DataBuffer&	other)
{
	if (std::addressof(other) != this)
	{
		unsigned char*	newBuffer = nullptr;
		size_t			newSize = 0;

		if (other.size() > 0)
		{
			newBuffer = new unsigned char[other.size()];
			newSize = other.size();
			std::memcpy(newBuffer, other._buffer, other.size());
		}

		reset();
		_buffer = newBuffer;
		_size = newSize;		
	}

	return *this;
}

// Move assignment operator.
DataBuffer&	DataBuffer::operator =(
	DataBuffer&&	other)
{
	this->_buffer = other._buffer;
	this->_size = other._size;

	other._buffer = nullptr;
	other._size = 0;

	return *this;
}

// Append operator.
DataBuffer&	DataBuffer::operator +=(
	const DataBuffer&	other)
{
	if (other.empty() == false)
	{
		unsigned char*	newBuffer = new unsigned char[this->size() + other.size()];
		size_t			newSize = this->size() + other.size();

		if (this->empty() == false)
		{
			memcpy(newBuffer, this->_buffer, this->size());
		}

		memcpy(newBuffer + this->size(), other._buffer, other.size());

		reset();
		_buffer = newBuffer;
		_size = newSize;
	}

	return *this;
}

// Extract a part of the buffer from a given position to the end.
DataBuffer	DataBuffer::sub(
	size_t		pos) const
{
	if (pos >= size())
	{
		throw std::out_of_range("start index out of range");
	}

	return DataBuffer(_buffer + pos, size() - pos);
}

// Extract n bytes of the buffer from a position.
DataBuffer	DataBuffer::sub(
	size_t		pos,
	size_t		len) const
{
	if (pos >= size())
	{
		throw std::out_of_range("start index out of range");
	}

	if (pos + len > size())
	{
		throw std::length_error("size is out of range");
	}

	return DataBuffer(_buffer + pos, len);
}

// Clear the internal buffer.
void	DataBuffer::reset(
	)
{
	if (_buffer)
	{
		delete _buffer;
		_buffer = nullptr;
		_size = 0;
	}
}

} // namespace io
} // namespace framework
} // namespace newNav
