#include "GxxGmStatic.h"
#include "..\GxxGmPlayBase\GxxGmPlayBase.h"
#include <afxglobals.h>

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__;  
#endif  

GxxGmStatic::GxxGmStatic()
: is_in_(false)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
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

BOOL GxxGmStatic::SetLogoImage(LPCTSTR logo_path)
{
	BOOL bRet = FALSE;  
	m_logoImage_.Destroy(); //���ͷ���ǰ��Դ  
	bRet = (m_logoImage_.Load(logo_path) == S_OK); //��������Դ  
	if(m_hWnd)  
		Invalidate(FALSE);  
	return bRet;  
}

LRESULT GxxGmStatic::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = S_OK;
	switch (message)
	{
	case WM_ERASEBKGND:
		ret = S_FALSE;
		return ret;
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;  
			CDC *pDstDC = BeginPaint(&ps);  

			//�ͻ���λ��  
			CRect rcClient;  
			GetClientRect(&rcClient);  

			//˫�����ͼ  
			{  
				CMemDC memDC(*pDstDC, rcClient);  
				CDC *pDC = &memDC.GetDC();  

				//��䱳��ɫ  
				pDC->FillSolidRect(&rcClient, RGB(25, 25, 25));  
				pDC->SetStretchBltMode(HALFTONE);  

				if(!m_logoImage_.IsNull())  
				{  
					//ԭͼ��С  
					CRect rcSrc(0, 0, m_logoImage_.GetWidth(), m_logoImage_.GetHeight());  
					//����ԭͼ����  
					double fZoomRate = 1;//min((double)rcClient.Width() / (double)rcSrc.Width(), (double)rcClient.Height() / (double)rcSrc.Height());  
					int cx = (int)(rcSrc.Width()*fZoomRate), cy = (int)(rcSrc.Height()*fZoomRate);  
					CRect rcDst(0, 0, cx, cy); //Ŀ���С  
					rcDst.OffsetRect((rcClient.Width()-cx)/2, (rcClient.Height()-cy)/2);//����  
					//rcDst.OffsetRect((rcSrc.Width()-cx)/2, (rcSrc.Height()-cy)/2);//����  

					//��ͼ  
					m_logoImage_.Draw(pDC->m_hDC, rcDst, rcSrc);  
				}  
			}  

			EndPaint(&ps); 
			ret = S_OK;
		}
		break;
	}

	return CStatic::WindowProc(message, wParam, lParam);
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
