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
	TRACE("����Ҽ�����˴���...\n");
	is_on_focus_ = true;
}

//void GxxGmStatic::OnMouseHover(UINT nFlags, CPoint point)
//{
//	if (!is_in_)
//	{
//		is_in_ = true;
//
//		// ���Ʊ߿�
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
//		// û�н��㣬�Ƴ���ʱ��ͻָ��߿�
//	}
//}

//BOOL GxxGmStatic::PreTranslateMessage(MSG* pMsg)
//{
//	switch (pMsg->message)
//	{
//	case WM_MOUSEHOVER:
//		// ������
//		break;
//	case WM_MOUSELEAVE:
//		// ����Ƴ�
//		break;
//	default:
//	}
//	return TRUE;
//}