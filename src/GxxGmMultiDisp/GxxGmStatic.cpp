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
	// TODO: 在此添加消息处理程序代码和/或调用默认值  
	return TRUE;  
	return CStatic::OnEraseBkgnd(pDC);  
}  

void GxxGmStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	GxxGmPlayBase::DebugStringOutput("鼠标右键点击了窗口...\n");
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
		GxxGmPlayBase::DebugStringOutput("鼠标移入控件...坐标为（%d, %d）\n", point.x, point.y);
		is_in_ = true;

		// 绘制边框
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
	m_logoImage_.Destroy(); //先释放以前资源  
	bRet = (m_logoImage_.Load(logo_path) == S_OK); //加载新资源  
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

			//客户区位置  
			CRect rcClient;  
			GetClientRect(&rcClient);  

			//双缓冲绘图  
			{  
				CMemDC memDC(*pDstDC, rcClient);  
				CDC *pDC = &memDC.GetDC();  

				//填充背景色  
				pDC->FillSolidRect(&rcClient, RGB(25, 25, 25));  
				pDC->SetStretchBltMode(HALFTONE);  

				if(!m_logoImage_.IsNull())  
				{  
					//原图大小  
					CRect rcSrc(0, 0, m_logoImage_.GetWidth(), m_logoImage_.GetHeight());  
					//锁定原图比例  
					double fZoomRate = 1;//min((double)rcClient.Width() / (double)rcSrc.Width(), (double)rcClient.Height() / (double)rcSrc.Height());  
					int cx = (int)(rcSrc.Width()*fZoomRate), cy = (int)(rcSrc.Height()*fZoomRate);  
					CRect rcDst(0, 0, cx, cy); //目标大小  
					rcDst.OffsetRect((rcClient.Width()-cx)/2, (rcClient.Height()-cy)/2);//居中  
					//rcDst.OffsetRect((rcSrc.Width()-cx)/2, (rcSrc.Height()-cy)/2);//居中  

					//绘图  
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
	GxxGmPlayBase::DebugStringOutput("鼠标移出控件...\n");
	if (!is_on_focus_)
	{
		// 没有焦点，移出的时候就恢复边框
	}
}

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
