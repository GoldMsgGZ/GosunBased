#ifndef _GxxGmStatic_H_
#define _GxxGmStatic_H_

#include <afx.h>
#include <afxwin.h>

//////////////////////////////////////////////////////////////////////////
//
// ���ڲ����Ӵ��ڣ��߱����¹���
// - ���Ʋ��Ŵ��ڱ����Լ�LOGO
// - ���ƹرհ�ť������Ӧ�ر���Ϣ
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	// �������������
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);	// �����뷶Χ
	afx_msg void OnMouseLeave();							// ����뿪��Χ
	//}}AFX_MSG  
	DECLARE_MESSAGE_MAP() 

private:
	// ����Ƿ��ڿؼ���
	bool is_in_;

	// �ؼ��Ƿ��н���
	bool is_on_focus_;

public:
	CRect logo_pic_rect_;

public:
	// ������Ϣ��������
	// 
	// - ������ؼ���Χ��ʱ����Ʊ߿�
	// - ����Ƴ��ؼ���Χ��ʱ��ȡ�����Ʊ߿�
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