#include "GxxGmStatic.h"
#include "..\GxxGmPlayBase\GxxGmPlayBase.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__;  
#endif  

GxxGmStatic::GxxGmStatic()
: is_in_(false)
{
	b_FillBackColor = 0;
	m_Font = 0;
	m_DisBackColro = RGB(200, 200, 200);
	Set_BackColor(GetSysColor(COLOR_3DFACE));
	Set_TextColor(0);
}

GxxGmStatic::~GxxGmStatic()
{
	if(m_Font)
	{
		m_Font->DeleteObject();
		delete m_Font;
	}

	m_BackBrush.DeleteObject();
	m_DisBackBrush.DeleteObject();
}

CFont* GxxGmStatic::GetFont()
{
	return m_Font;
}

void GxxGmStatic::SetFont(LOGFONT *LogFont, BOOL bRedraw)
{
	if(m_Font)
		m_Font->DeleteObject();

	if(m_Font == NULL)
		m_Font = new CFont();

	if(m_Font)
	{
		if(!m_Font->CreatePointFontIndirect( LogFont ))
		{
			delete m_Font;
			m_Font = NULL;
		}
	}
}

void GxxGmStatic::SetFont(CFont* pFont, BOOL bRedraw)
{
	LOGFONT LogFont;
	pFont->GetLogFont(&LogFont);
	SetFont(&LogFont, bRedraw);
}

void GxxGmStatic::SetFont(int nHeight, LPCTSTR fontName, BOOL bRedraw)
{
	if(m_Font)
		m_Font->DeleteObject();

	if(m_Font == NULL)
		m_Font = new CFont();

	if(m_Font)
	{
		if(!m_Font->CreatePointFont(nHeight, fontName))
		{
			delete m_Font; 
			m_Font = NULL;
		}
	}

	if(bRedraw && GetSafeHwnd())
		Invalidate();
}

/////////////////////////////////////////////////////////////////////////////  
// CColorText_Static message handlers  

HBRUSH GxxGmStatic::CtlColor(CDC* pDC, UINT nCtlColor)   
{  
	// TODO: Change any attributes of the DC here  
	pDC->SetBkMode(TRANSPARENT);  
	pDC->SetTextColor(m_TextColor);  

	if(m_Font)  
		pDC->SelectObject(m_Font);  

	HBRUSH hBrush = (HBRUSH) m_BackBrush;  
	if(!IsWindowEnabled())  
		hBrush = (HBRUSH) m_DisBackBrush;  
	return ( hBrush );      
	// TODO: Return a non-NULL brush if the parent's handler should not be called   return NULL;  
}  

BOOL GxxGmStatic::OnEraseBkgnd(CDC* pDC)  
{  
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ  
	return TRUE;  
	return CStatic::OnEraseBkgnd(pDC);  
}  

void GxxGmStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	GxxGmPlayBase::DebugStringOutput("����Ҽ�����˴���...\n");
	is_on_focus_ = true;
}

BEGIN_MESSAGE_MAP(GxxGmStatic, CStatic)  
	//{{AFX_MSG_MAP(CColorText_Static)  
	ON_WM_CTLCOLOR_REFLECT()  
	ON_WM_ERASEBKGND()  
	//}}AFX_MSG_MAP  
END_MESSAGE_MAP()  

void GxxGmStatic::OnMouseHover(UINT nFlags, CPoint point)
{
	if (!is_in_)
	{
		GxxGmPlayBase::DebugStringOutput("�������ؼ�...����Ϊ��%d, %d��\n", point.x, point.y);
		is_in_ = true;

		// ���Ʊ߿�
		CPaintDC dc(this);
		CBrush newbrush, *oldbrush;
		newbrush.CreateSolidBrush(RGB(89, 168, 237));
		oldbrush=dc.SelectObject(&newbrush);
		CRect rect; 
		GetClientRect(rect);
		dc.FrameRect(rect, &newbrush);
		dc.SelectObject(oldbrush);
	}
}

void GxxGmStatic::Set_BackColor(COLORREF cr)
{
	m_BackColor = cr;
	b_FillBackColor = true;

	m_BackBrush.DeleteObject();
	m_BackBrush.CreateSolidBrush(m_BackColor);

	m_DisBackBrush.DeleteObject();
	m_DisBackBrush.CreateSolidBrush(m_DisBackColro);

	if(GetSafeHwnd())
		Invalidate();
}

COLORREF GxxGmStatic::Get_BackColor()
{
	return(m_BackColor);
}

void GxxGmStatic::Set_TextColor(COLORREF cr)   
{   
	m_TextColor = cr;
	if(GetSafeHwnd())
		Invalidate();
}  

COLORREF GxxGmStatic::Get_TextColor()
{  
	return m_TextColor;
}  

void GxxGmStatic::OnMouseLeave()
{
	GxxGmPlayBase::DebugStringOutput("����Ƴ��ؼ�...\n");
	if (!is_on_focus_)
	{
		// û�н��㣬�Ƴ���ʱ��ͻָ��߿�
	}
}

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