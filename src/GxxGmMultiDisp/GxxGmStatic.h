#ifndef _GxxGmStatic_H_
#define _GxxGmStatic_H_

#include <afx.h>
#include <afxwin.h>

class GxxGmStatic : public CStatic
{
public:
	GxxGmStatic();
	virtual ~GxxGmStatic();

protected:
	// �������������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//// �����뷶Χ
	//afx_msg void OnMouseHover(UINT nFlags, CPoint point);

	//// ����뿪��Χ
	//afx_msg void OnMouseLeave();

private:
	// ����Ƿ��ڿؼ���
	bool is_in_;

	// �ؼ��Ƿ��н���
	bool is_on_focus_;

public:
	// ������Ϣ��������
	// 
	// - ������ؼ���Χ��ʱ����Ʊ߿�
	// - ����Ƴ��ؼ���Χ��ʱ��ȡ�����Ʊ߿�
	// - 
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#endif//_GxxGmStatic_H_