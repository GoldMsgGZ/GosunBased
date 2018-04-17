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
	// 当发生了鼠标点击
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//// 鼠标进入范围
	//afx_msg void OnMouseHover(UINT nFlags, CPoint point);

	//// 鼠标离开范围
	//afx_msg void OnMouseLeave();

private:
	// 鼠标是否在控件上
	bool is_in_;

	// 控件是否有焦点
	bool is_on_focus_;

public:
	// 重载消息处理函数：
	// 
	// - 鼠标进入控件范围的时候绘制边框
	// - 鼠标移出控件范围的时候取消绘制边框
	// - 
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#endif//_GxxGmStatic_H_