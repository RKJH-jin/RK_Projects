#pragma once

namespace Figure
{

	class FloatRect final
	{
	public:
		float left;
		float top;
		float right;
		float bottom;
	public:
		FloatRect();
		explicit FloatRect(const float& left, const float& top, const float& right, const float& bottom);
		explicit FloatRect(const int& left, const int& top, const int& right, const int& bottom);
		explicit FloatRect(const Vector2& pos, const Vector2& size, const Pivot& pivot);
		explicit FloatRect(const RECT& rc);

		const RECT GetRect();
		float GetWidth();
		float GetHeight();
		Vector2 GetCenter();
		Vector2 GetBottom();
		Vector2 GetSize();
		void Update(const Vector2& pos, const Vector2& size, const Pivot& pivot);
		void Move(const Vector2& moveValue);

		const FloatRect& operator=(const RECT& rc);

		bool PtInRect(Vector2& pos);
	};
}