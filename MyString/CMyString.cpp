#include "CMyString.h"

constexpr char STRING_END = '\0';

CMyString::CMyString()
	: m_data(new char[1])
	, m_length(0)
	, m_capacity(0)
{
	m_data[0] = STRING_END;
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, pString != nullptr ? std::strlen(pString) : 0)
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	// в memcpy низя nullptr => invalid
	if (pString == nullptr)
	{
		length = 0;
	}

	m_data = new char[length + 1];
	m_length = length;
	m_capacity = length;
	std::memcpy(m_data, pString, m_length);
	m_data[m_length] = STRING_END;
}

CMyString::CMyString(CMyString const& other)
	: CMyString(new char[other.m_capacity + 1], other.m_length, other.m_capacity)
{
	std::uninitialized_copy_n(other.m_data, m_length + 1, m_data);
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_data(other.m_data)
	, m_length(other.m_length)
	, m_capacity(other.m_capacity)
{
	//invalid state
	other.m_data[0] = STRING_END;
	other.m_capacity = 0;
	other.m_length = 0;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (std::addressof(other) != this)
	{
		if (m_capacity >= other.m_length)
		{
			std::copy_n(other.m_data, other.m_length + 1, m_data);
			m_length = other.m_length;
		}
		else
		{
			CMyString copyStr(other);
			std::swap(m_data, copyStr.m_data);
			std::swap(m_length, copyStr.m_length);
			std::swap(m_capacity, copyStr.m_capacity);
		}
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (std::addressof(other) != this)
	{
		delete[] m_data;

		m_data = other.m_data;
		m_length = other.m_length;
		m_capacity = other.m_capacity;

		//invalid state (other)
		other.m_data = nullptr;
		other.m_length = 0;
		other.m_capacity = 0;
	}
	return *this;
}

CMyString::~CMyString() noexcept
{
	delete[] m_data;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

char const* CMyString::GetStringData() const
{
	return m_data;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		throw std::out_of_range("index out of range");
	}

	size_t copyLength = length;
	if (length > m_length - start)
	{
		copyLength = m_length - start;
	}

	return { m_data + start, copyLength };
}

void CMyString::Clear()
{
	//1. сделать невыбрасывающим, 2. не должен удалять данные, а должен обнулить длину а вместимость оставить ту же
	delete[] m_data;
	m_data = new char[1];
	m_data[0] = STRING_END;
	m_length = 0;
}

CMyString::iterator CMyString::begin()
{
	return m_data;
}

CMyString::iterator CMyString::end()
{
	return m_data + m_length;
}

CMyString::const_iterator CMyString::begin() const
{
	return m_data;
}

CMyString::const_iterator CMyString::end() const
{
	return m_data + m_length;
}

CMyString::const_iterator CMyString::cbegin() const
{
	return m_data;
}

CMyString::const_iterator CMyString::cend() const
{
	return m_data + m_length;
}

CMyString::reverse_iterator CMyString::rbegin()
{
	return m_data + m_length - 1;
}

CMyString::reverse_iterator CMyString::rend()
{
	//неопределённое поведение 
	return m_data - 1;
}

CMyString::const_reverse_iterator CMyString::crbegin() const
{
	return m_data + m_length - 1;
}

CMyString::const_reverse_iterator CMyString::crend() const
{
	return m_data - 1;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	//может быть такое, что вместимость строки достаточна
	size_t resultLength = m_length + other.m_length;
	char* result = new char[resultLength + 1];

	std::memcpy(result, m_data, m_length);
	std::memcpy(result + m_length, other.m_data, other.m_length);
	result[resultLength] = STRING_END;

	size_t length = GetLength() + other.GetLength();
	size_t capacity = std::max(length, m_capacity * 2);
	
	delete[] m_data;
	m_data = result;
	m_length = resultLength;
	m_capacity = capacity;

	return *this;
}

char const& CMyString::operator[](size_t index) const
{
	if (index > m_length)
	{
		throw std::out_of_range("index out of range");
	}

	return m_data[index];
}

char& CMyString::operator[](size_t index)
{
	if (index > m_length)
	{
		throw std::out_of_range("index out of range");
	}

	return m_data[index];
}

static char* Reallocate(char* ptr, size_t length, size_t newLength)
{
	if (newLength < length)
	{
		return ptr;
	}

	char* newPtr = new char[newLength];
	std::memcpy(newPtr, ptr, length);
	delete[] ptr;

	return newPtr;
}	

std::istream& operator>>(std::istream& stream, CMyString & s)
{
	std::string copyStr;
	char ch;
	while (stream.get(ch) && ch != ' ' && copyStr.size() < SIZE_MAX && ch != '\n')
	{
		copyStr += ch;
	}

	s = copyStr;

	return stream;
}

CMyString const operator+(CMyString s1, CMyString const& s2)
{
	//определить суммарную длинну строки, выделить и занять. 2. константную строку не возвращаьт

	return s1 += s2;
}

static int StrCmp(CMyString const& s1, CMyString const& s2)
{
	size_t minLength = std::min(s1.GetLength(), s2.GetLength());
	int result = std::memcmp(s1.GetStringData(), s2.GetStringData(), minLength);

	if (result != 0)
	{
		return result;
	}

	if (s2.GetLength() > minLength)
	{
		return -1;
	}

	if (s1.GetLength() > minLength)
	{
		return 1;
	}

	return result;
}

bool operator==(CMyString const& s1, CMyString const& s2)
{
	//не эффективно, если разная длинна то смысла то и нету
	return StrCmp(s1, s2) == 0;
}

std::strong_ordering operator<=>(CMyString const& s1, CMyString const& s2)
{
	return StrCmp(s1, s2) <=> 0;
}

std::ostream& operator<<(std::ostream& stream, CMyString const& s)
{
	for (size_t i = 0; i < s.GetLength(); ++i)
	{
		stream << s.GetStringData()[i];
	}
	return stream;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

CMyString::CMyString(char* pString, size_t length, size_t capacity) noexcept
	: m_data(pString)
	, m_length(length)
	, m_capacity(capacity)
{
}