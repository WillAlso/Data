
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
    //Ԥ�ȴ�����Ϣ
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    //������ʾ��ʾ�ַ��Ĵ���
	virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
protected:
    
    void ReportError(int nError);
    //ע���ֵ
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
    //���ڵ�λ��
	void PositionWindow();
	//����ȱʡ���
    void SetDefaultCursor();

// Protected attributes
protected:
    //������ɫ�����ʹ�����ɫ
	COLORREF m_crLinkColour, m_crVisitedColour;     // Hyperlink colours
    //������Ϸ�����ɫ
	COLORREF m_crHoverColour;                       // Hover colour
    //�Ƿ�ͣ���ڿؼ��Ϸ�
	BOOL     m_bOverControl;                        // cursor over control?
    //�Ƿ��Ѿ����ʹ�url
	BOOL     m_bVisited;                            // Has it been visited?
    //�»����Ƿ����
	BOOL     m_bUnderline;                          // underline hyperlink?
    //�������ڵ�λ��
	BOOL     m_bAdjustToFit;                        // Adjust window size to fit text?
    //url��ַ
	CString  m_strURL;                              // hyperlink URL
    //�»��߶�Ӧ������
	CFont    m_Font;                                // Underline font if necessary
    //url�Ϲ�����״
	HCURSOR  m_hLinkCursor;                         // Cursor for hyperlink
    //�������url�ϵ���ʾ
	CToolTipCtrl m_ToolTip;                         // The tooltip

    // Generated message map functions
protected:
    //{{AFX_MSG(CHyperLink)
	//������ʾ�ؼ��ϵĻ���
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//���ù�����״
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    //�ƶ����
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    afx_msg void OnClicked();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
