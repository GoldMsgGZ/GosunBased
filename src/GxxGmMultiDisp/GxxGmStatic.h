#ifndef _GxxGmStatic_H_
#define _GxxGmStatic_H_

#include <afx.h>
#include <afxwin.h>

//////////////////////////////////////////////////////////////////////////
//
// 用于播放子窗口，具备以下功能
// - 绘制播放窗口背景以及LOGO
// - 绘制关闭按钮，并响应关闭消息
// - 

class GxxGmStatic : public CStatic
{
public:
	GxxGmStatic();
	virtual ~GxxGmStatic();

public:
	virtual CFont* GetFont();
	virtual void SetFont(LOGFONT *LogFont, BOOL bRedraw = TRUE);  
	virtual void SetFont(CFont* pFont, BOOL bRedraw = TRUE);  
	virtual void SetFont(int nHeight, LPCTSTR fontName, BOOL bRedraw = true);  

	void Set_BackColor(COLORREF cr);   
	COLORREF Get_BackColor();
	void Set_TextColor(COLORREF cr);
	COLORREF Get_TextColor();

protected:
	//{{AFX_MSG(CColorText_Static)  
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	// 当发生了鼠标点击
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);	// 鼠标进入范围
	afx_msg void OnMouseLeave();							// 鼠标离开范围
	//}}AFX_MSG  
	DECLARE_MESSAGE_MAP() 

private:
	// 鼠标是否在控件上
	bool is_in_;

	// 控件是否有焦点
	bool is_on_focus_;

public:
	CRect logo_pic_rect_;

public:
	// 重载消息处理函数：
	// 
	// - 鼠标进入控件范围的时候绘制边框
	// - 鼠标移出控件范围的时候取消绘制边框
	// - 
	//virtual BOOL PreTranslateMessage(MSG* pMsg);

	BOOL b_FillBackColor;  
	COLORREF m_DisBackColro;  
	COLORREF m_BackColor;  
	COLORREF m_TextColor;  
	CFont *m_Font;  
	CBrush m_BackBrush;  
	CBrush m_DisBackBrush; 
};

#endif//_GxxGmStatic_H_