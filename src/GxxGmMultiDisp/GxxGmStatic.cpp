#include "GxxGmStatic.h"

GxxGmStatic::GxxGmStatic()
: is_in_(false)
{

}

GxxGmStatic::~GxxGmStatic()
{

}

void GxxGmStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	TRACE("鼠标右键点击了窗口...\n");
	is_on_focus_ = true;
}

//void GxxGmStatic::OnMouseHover(UINT nFlags, CPoint point)
//{
//	if (!is_in_)
//	{
//		is_in_ = true;
//
//		// 绘制边框
//		CPaintDC dc(this);
//		CBrush newbrush, *oldbrush;
//		newbrush.CreateSolidBrush(RGB(89, 168, 237));
//		oldbrush=dc.SelectObject(&newbrush);
//		CRect rect; 
//		GetClientRect(rect);
//		dc.FrameRect(rect, &newbrush);
//		dc.SelectObject(oldbrush);
//	}
//}
//
//void GxxGmStatic::OnMouseLeave()
//{
//	if (!is_on_focus_)
//	{
//		// 没有焦点，移出的时候就恢复边框
//	}
//}

//BOOL GxxGmStatic::PreTranslateMessage(MSG* pMsg)
//{
//	switch (pMsg->message)
//	{
//	case WM_MOUSEHOVER:
//		// 鼠标进入
//		break;
//	case WM_MOUSELEAVE:
//		// 鼠标移出
//		break;
//	default:
//	}
//	return TRUE;
//}