
//////////////////////////////////////////////////
#if !defined(AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CHyperLink window

class CHyperLink : public CStatic
{
// Construction/destruction
public:
    CHyperLink();
    virtual ~CHyperLink();

// Attributes
public:

// Operations
public:

    void SetURL(CString strURL);
    CString GetURL() const;

    void SetColours(COLORREF crLinkColour, COLORREF crVisitedColour, 
                    COLORREF crHoverColour = -1);
    COLORREF GetLinkColour() const;
    COLORREF GetVisitedColour() const;
    COLORREF GetHoverColour() const;

    void SetVisited(BOOL bVisited = TRUE);
    BOOL GetVisited() const;

    void SetLinkCursor(HCURSOR hCursor);
    HCURSOR GetLinkCursor() const;

    void SetUnderline(BOOL bUnderline = TRUE);
    BOOL GetUnderline() const;

    void SetAutoSize(BOOL bAutoSize = TRUE);
    BOOL GetAutoSize() const;

	HINSTANCE GotoURL(LPCTSTR url, int showcmd);
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHyperLink)
    public:
    //预先传递消息
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    //连接显示提示字符的窗口
	virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
protected:
    
    void ReportError(int nError);
    //注册键值
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
    //窗口的位置
	void PositionWindow();
	//设置缺省鼠标
    void SetDefaultCursor();

// Protected attributes
protected:
    //连接颜色，访问过的颜色
	COLORREF m_crLinkColour, m_crVisitedColour;     // Hyperlink colours
    //鼠标在上方的颜色
	COLORREF m_crHoverColour;                       // Hover colour
    //是否停留在控件上方
	BOOL     m_bOverControl;                        // cursor over control?
    //是否已经访问过url
	BOOL     m_bVisited;                            // Has it been visited?
    //下划线是否存在
	BOOL     m_bUnderline;                          // underline hyperlink?
    //调整窗口的位置
	BOOL     m_bAdjustToFit;                        // Adjust window size to fit text?
    //url地址
	CString  m_strURL;                              // hyperlink URL
    //下划线对应的字体
	CFont    m_Font;                                // Underline font if necessary
    //url上光标的形状
	HCURSOR  m_hLinkCursor;                         // Cursor for hyperlink
    //鼠标点击在url上的提示
	CToolTipCtrl m_ToolTip;                         // The tooltip

    // Generated message map functions
protected:
    //{{AFX_MSG(CHyperLink)
	//重新显示控件上的画面
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//设置光标的形状
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    //移动鼠标
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    afx_msg void OnClicked();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
