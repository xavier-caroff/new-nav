#pragma once

namespace newNav {
namespace framework {
namespace io {

///
/// Holds a buffer of bytes to exchange data between components.
///
class DataBuffer
{
// Construction, destruction
public:
	
	/// Constructor with initialization.
	///
	/// @param buffer Pointer to the data to be copied into the buffer.
	/// @param size Number of bytes into the buffer.
	DataBuffer(
		const unsigned char*	buffer,
		size_t		    		size);

	/// Copy construct.
    ///
    /// @param other Object to copy.
	DataBuffer(
		const DataBuffer&	other);

	/// Move constructor.
    ///
    /// @param other Object to be steal.
	DataBuffer(
		DataBuffer&&	other);

	/// Destructor.
	virtual ~DataBuffer(
		);

// Operations
public:

	/// Access to the raw data stored into the buffer.
	 operator const unsigned char*(
		void) const;

	/// Access the size of the buffer.
	size_t	size(
		void) const;

	/// Indicates if the buffer is empty.
	bool	empty(
		) const;

	/// Copy operator.
	///
	/// @param other Object to be copied.
	DataBuffer&	operator =(
		const DataBuffer&	other);

	/// Move assignment operator.
	///
	/// @param other Object to be steal.
	DataBuffer&	operator =(
		DataBuffer&&	other);

	/// Append operator.
	///
	/// @param other Object to be appended.
	DataBuffer&	operator +=(
		const DataBuffer&	other);

	/// Extract a part of the buffer from a given position to the end.
	DataBuffer	sub(
		size_t		pos) const;

	/// Extract n bytes of the buffer from a position.
	DataBuffer	sub(
		size_t		pos,
		size_t		len) const;

// Implementation
private:

	/// Clear the internal buffer.
	void	reset(
		);
	
// Private attributes
private:

	/// Pointer to the data hold by the buffer.
	unsigned char*	_buffer;

	/// Number of bytes into the buffer.
	size_t	    	_size;
}; 

} // namespace io
} // namespace framework
} // namespace newNav
