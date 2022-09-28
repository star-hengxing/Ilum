#pragma once

#include "Precompile.hpp"

namespace Ilum
{
class Cursor;

class CursorType
{
  public:
	CursorType(const CXType &handle);

	~CursorType() = default;

	std::string GetDispalyName() const;

	int32_t GetArgumentCount() const;

	CursorType GetArgument(uint32_t index) const;

	CursorType GetCanonicalType() const;

	Cursor GetDeclaration() const;

	CXTypeKind GetKind() const;

	bool IsConstant() const;

  private:
	CXType m_handle;
};

class Cursor
{
  public:
	Cursor(const CXCursor &handle);

	~Cursor() = default;

	CXCursorKind GetKind() const;

	std::string GetSpelling() const;

	std::string GetDisplayName() const;

	std::string GetSourceFile() const;

	bool IsDefinition() const;

	CursorType GetType() const;

	std::vector<Cursor> GetChildren() const;

	void VisitChildren(CXCursorVisitor visitor, void *data = nullptr);

  private:
	CXCursor m_handle;
};
}        // namespace Ilum