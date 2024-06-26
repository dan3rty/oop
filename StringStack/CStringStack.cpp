#include "CStringStack.h"

// make_shared ������ ������ ����� (��� ����� ������� ��������� �� ���������)
CStringStack::CStringStack(CStringStack const& other)
{
	if (other.m_top != nullptr)
	{
		CStringStack tempStack;
		auto tmp = other.m_top;

		tempStack.m_top = std::make_shared<Node>(tmp->Value);
		auto current = tempStack.m_top;

		tmp = tmp->Next;
		while (tmp)
		{
			current->Next = std::make_shared<Node>(tmp->Value);
			current = current->Next;
			tmp = tmp->Next;
		}

		std::swap(m_top, tempStack.m_top);
		m_size = other.m_size;
	}
}

// �������� ���������� ����� std::exchange (����������)
CStringStack::CStringStack(CStringStack&& other) noexcept
	: m_top(std::exchange(other.m_top, nullptr))
	, m_size(std::exchange(other.m_size, 0))
{
}

CStringStack& CStringStack::operator=(CStringStack const& other)
{
	if (std::addressof(other) != this)
	{
		CStringStack copy(other);
		std::swap(m_top, copy.m_top);
		std::swap(m_size, copy.m_size);
	}
	return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& other) noexcept
{
	if (std::addressof(other) != this)
	{
		// ����������� �����
		m_top = other.m_top;
		m_size = other.m_size;

		other.m_top = nullptr;
		other.m_size = 0;
	}
	return *this;
}

CStringStack::~CStringStack() noexcept
{
	while (!IsEmpty())
	{
		Pop();
	}
}

void CStringStack::Push(const std::string& str)
{
	auto newTop = std::make_shared<Node>(str, m_top);
	m_top = newTop;
	++m_size;
}

void CStringStack::Push(std::string&& str)
{
	auto newTop = std::make_shared<Node>(std::move(str), m_top);
	m_top = newTop;
	++m_size;
}

std::string& CStringStack::Top() const
{
	if (IsEmpty())
	{
		throw CStringStackUnderflowError();
	}

	return m_top->Value;
}

std::string& CStringStack::Top()
{
	if (IsEmpty())
	{
		throw CStringStackUnderflowError();
	}

	return m_top->Value;
}

void CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw CStringStackUnderflowError();
	}

	auto newTop = m_top->Next;
	m_top = newTop;
	--m_size;
}

bool CStringStack::IsEmpty() const
{
	return m_size == 0;
}

CStringStack::size_type CStringStack::GetSize() const
{
	return m_size;
}