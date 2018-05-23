//download by http://down.liehuo.net
#include "stdafx.h"
#include "HyperLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TOOLTIP_ID 1

/////////////////////////////////////////////////////////////////////////////
// CHyperLink

CHyperLink::CHyperLink()
{
    //链接时光标
	m_hLinkCursor       = NULL;                 
    //链接时的颜色
	m_crLinkColour      = RGB(  0,   0, 238); 
	//已访问过的颜色
    m_crVisitedColour   = RGB( 85,  26, 139); 
    //位于控件上方的颜色
	m_crHoverColour     = ::GetSysColor(COLOR_HIGHLIGHT);
    //鼠标在控件上方
	m_bOverControl      = FALSE;                
    //已访问过url
	m_bVisited          = FALSE;
    //超链接地址的下划线
	m_bUnderline        = TRUE;                 
    //调整窗口的大小
	m_bAdjustToFit      = TRUE;                 
    //存放url的字符串
	m_strURL.Empty();
}

CHyperLink::~CHyperLink()
{
    m_Font.DeleteObject();
}

BEGIN_MESSAGE_MAP(CHyperLink, CStatic)
    //{{AFX_MSG_MAP(CHyperLink)
    ON_CONTROL_REFLECT(STN_CLICKED, OnClicked)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_SETCURSOR()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//消息响应函数
//延时发送消息
BOOL CHyperLink::PreTranslateMessage(MSG* pMsg) 
{
    //延时发送消息
	m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}
//点击链接地址事件
void CHyperLink::OnClicked()
{
    int result = (int)GotoURL(m_strURL, SW_SHOW);
    m_bVisited = (result > HINSTANCE_ERROR);
    if (!m_bVisited) {
        MessageBeep(MB_ICONEXCLAMATION);     // Unable to follow link
        ReportError(result);
    } else
		//url设为已经被访问过的状态
        SetVisited();                        
}
//重画控件事件
HBRUSH CHyperLink::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	//保证控件具有可画性
    ASSERT(nCtlColor == CTLCOLOR_STATIC);

    if (m_bOverControl)
        pDC->SetTextColor(m_crHoverColour);
    else if (m_bVisited)
        pDC->SetTextColor(m_crVisitedColour);
    else
        pDC->SetTextColor(m_crLinkColour);

    // 设置控件为透明模式
    pDC->SetBkMode(TRANSPARENT);
    return (HBRUSH)GetStockObject(NULL_BRUSH);
}
//鼠标移动事件
void CHyperLink::OnMouseMove(UINT nFlags, CPoint point) 
{
    CStatic::OnMouseMove(nFlags, point);
    //鼠标目前正处于url上方
    if (m_bOverControl)        
    {
        CRect rect;
        GetClientRect(rect);

        if (!rect.PtInRect(point))
        {
            m_bOverControl = FALSE;
            ReleaseCapture();
            RedrawWindow();
            return;
        }
    }
    else                      // Cursor has just moved over control
    {
        m_bOverControl = TRUE;
        RedrawWindow();
        SetCapture();
    }
}
//设置鼠标光标的形状
BOOL CHyperLink::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
    if (m_hLinkCursor)
    {
        ::SetCursor(m_hLinkCursor);
        return TRUE;
    }
    return FALSE;
}

void CHyperLink::PreSubclassWindow() 
{
    //通过stn的点击事件获取鼠标的移动
    DWORD dwStyle = GetStyle();
    ::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);
    
    //将url设置为提示信息栏的文本
    if (m_strURL.IsEmpty())
        GetWindowText(m_strURL);

    //检查提示栏中的文本是否为空，如果不是，则作为url地址.
    CString strWndText;
    GetWindowText(strWndText);
    if (strWndText.IsEmpty()) {
        ASSERT(!m_strURL.IsEmpty());
        SetWindowText(m_strURL);
    }

    //创建字体，加上下划线
    LOGFONT lf;
    GetFont()->GetLogFont(&lf);
    lf.lfUnderline = m_bUnderline;
    m_Font.CreateFontIndirect(&lf);
    SetFont(&m_Font);

    PositionWindow();        // 调整窗口的形状，以便能容纳下url地址
    SetDefaultCursor();      // 设置鼠标光标的形状为手状

    //创建提示栏
    CRect rect; 
    GetClientRect(rect);
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(this, m_strURL, rect, TOOLTIP_ID);

    CStatic::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CHyperLink operations
//成员函数
//设置url
void CHyperLink::SetURL(CString strURL)
{
    m_strURL = strURL;

    if (::IsWindow(GetSafeHwnd())) {
        //调整窗口大小以便适应url文本
		PositionWindow();
        m_ToolTip.UpdateTipText(strURL, this, TOOLTIP_ID);
    }
}
//获取url地址
CString CHyperLink::GetURL() const
{ 
    return m_strURL;   
}
//设置url在不同状态下的颜色
void CHyperLink::SetColours(COLORREF crLinkColour, COLORREF crVisitedColour,
                            COLORREF crHoverColour /* = -1 */) 
{ 
    m_crLinkColour    = crLinkColour; 
    m_crVisitedColour = crVisitedColour;

	if (crHoverColour == -1)
		m_crHoverColour = ::GetSysColor(COLOR_HIGHLIGHT);
	else
		m_crHoverColour = crHoverColour;

    if (::IsWindow(m_hWnd))
        Invalidate(); 
}

COLORREF CHyperLink::GetLinkColour() const
{ 
    return m_crLinkColour; 
}

COLORREF CHyperLink::GetVisitedColour() const
{
    return m_crVisitedColour; 
}

COLORREF CHyperLink::GetHoverColour() const
{
    return m_crHoverColour;
}

void CHyperLink::SetVisited(BOOL bVisited /* = TRUE */) 
{ 
    m_bVisited = bVisited; 

    if (::IsWindow(GetSafeHwnd()))
        Invalidate(); 
}

BOOL CHyperLink::GetVisited() const
{ 
    return m_bVisited; 
}

void CHyperLink::SetLinkCursor(HCURSOR hCursor)
{ 
    m_hLinkCursor = hCursor;
    if (m_hLinkCursor == NULL)
        SetDefaultCursor();
}

HCURSOR CHyperLink::GetLinkCursor() const
{
    return m_hLinkCursor;
}

void CHyperLink::SetUnderline(BOOL bUnderline /* = TRUE */)
{
    m_bUnderline = bUnderline;

    if (::IsWindow(GetSafeHwnd()))
    {
        LOGFONT lf;
        GetFont()->GetLogFont(&lf);
        lf.lfUnderline = m_bUnderline;

        m_Font.DeleteObject();
        m_Font.CreateFontIndirect(&lf);
        SetFont(&m_Font);

        Invalidate(); 
    }
}

BOOL CHyperLink::GetUnderline() const
{ 
    return m_bUnderline; 
}

void CHyperLink::SetAutoSize(BOOL bAutoSize /* = TRUE */)
{
    m_bAdjustToFit = bAutoSize;

    if (::IsWindow(GetSafeHwnd()))
        PositionWindow();
}

BOOL CHyperLink::GetAutoSize() const
{ 
    return m_bAdjustToFit; 
}


// Move and resize the window so that the window is the same size
// as the hyperlink text. This stops the hyperlink cursor being active
// when it is not directly over the text. If the text is left justified
// then the window is merely shrunk, but if it is centred or right
// justified then the window will have to be moved as well.

void CHyperLink::PositionWindow()
{
    if (!::IsWindow(GetSafeHwnd()) || !m_bAdjustToFit) 
        return;

    //获取当前窗口的位置
    CRect rect;
    GetWindowRect(rect);

    CWnd* pParent = GetParent();
    if (pParent)
        pParent->ScreenToClient(rect);

    //获取窗口的文本
    CString strWndText;
    GetWindowText(strWndText);

    CDC* pDC = GetDC();
    CFont* pOldFont = pDC->SelectObject(&m_Font);
    CSize Extent = pDC->GetTextExtent(strWndText);
    pDC->SelectObject(pOldFont);
    ReleaseDC(pDC);

    //获取窗口的类型
    DWORD dwStyle = GetStyle();

    //根据窗口的类型，重新计算窗口的大小和位置
    if (dwStyle & SS_CENTERIMAGE)
        rect.DeflateRect(0, (rect.Height() - Extent.cy)/2);
    else
        rect.bottom = rect.top + Extent.cy;

    if (dwStyle & SS_CENTER)   
        rect.DeflateRect((rect.Width() - Extent.cx)/2, 0);
    else if (dwStyle & SS_RIGHT) 
        rect.left  = rect.right - Extent.cx;
    else 
        rect.right = rect.left + Extent.cx;

    //移动窗口
    SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
}

/////////////////////////////////////////////////////////////////////////////
// CHyperLink implementation

//设置手形鼠标光标
void CHyperLink::SetDefaultCursor()
{
    if (m_hLinkCursor == NULL)                //自定义鼠标光标
    {
        // 获取窗口的目录
        CString strWndDir;
        GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
        strWndDir.ReleaseBuffer();

        strWndDir += _T("\\winhlp32.exe");
        //生成winhlp32.exe中的106#鼠标光标，手形
        HMODULE hModule = LoadLibrary(strWndDir);
        if (hModule) {
            HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
            if (hHandCursor)
                m_hLinkCursor = CopyCursor(hHandCursor);
        }
        FreeLibrary(hModule);
    }
}
//获取注册表的键值，
LONG CHyperLink::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
    HKEY hkey;
    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

    if (retval == ERROR_SUCCESS) {
        long datasize = MAX_PATH;
        TCHAR data[MAX_PATH];
        RegQueryValue(hkey, NULL, data, &datasize);
        lstrcpy(retdata,data);
        RegCloseKey(hkey);
    }
    return retval;
}

void CHyperLink::ReportError(int nError)
{
    CString str;
    switch (nError) {
        case 0:                       str = "The operating system is out\nof memory or resources."; break;
        case SE_ERR_PNF:              str = "The specified path was not found."; break;
        case SE_ERR_FNF:              str = "The specified file was not found."; break;
        case ERROR_BAD_FORMAT:        str = "The .EXE file is invalid\n(non-Win32 .EXE or error in .EXE image)."; break;
        case SE_ERR_ACCESSDENIED:     str = "The operating system denied\naccess to the specified file."; break;
        case SE_ERR_ASSOCINCOMPLETE:  str = "The filename association is\nincomplete or invalid."; break;
        case SE_ERR_DDEBUSY:          str = "The DDE transaction could not\nbe completed because other DDE transactions\nwere being processed."; break;
        case SE_ERR_DDEFAIL:          str = "The DDE transaction failed."; break;
        case SE_ERR_DDETIMEOUT:       str = "The DDE transaction could not\nbe completed because the request timed out."; break;
        case SE_ERR_DLLNOTFOUND:      str = "The specified dynamic-link library was not found."; break;
        case SE_ERR_NOASSOC:          str = "There is no application associated\nwith the given filename extension."; break;
        case SE_ERR_OOM:              str = "There was not enough memory to complete the operation."; break;
        case SE_ERR_SHARE:            str = "A sharing violation occurred. ";
        default:                      str.Format("Unknown Error (%d) occurred.", nError); break;
    }
    str = "Unable to open hyperlink:\n\n" + str;
    AfxMessageBox(str, MB_ICONEXCLAMATION | MB_OK);
}
//链接url
HINSTANCE CHyperLink::GotoURL(LPCTSTR url, int showcmd)
{
    TCHAR key[MAX_PATH + MAX_PATH];

    //首先尝试使用ShellExecute()
    HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

    //如果使用失败,则获取.htm注册键值并查找程序
    if ((UINT)result <= HINSTANCE_ERROR) {

        if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) {
            lstrcat(key, _T("\\shell\\open\\command"));

            if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) {
                TCHAR *pos;
                pos = _tcsstr(key, _T("\"%1\""));
                //未发现引用%1
				if (pos == NULL) {                     
                    // 则检查 %1
					pos = strstr(key, _T("%1")); 
                   // 如果还是空
					if (pos == NULL)                 
                        pos = key+lstrlen(key)-1;
                    else
                        //删除参数
						*pos = '\0';                
                }
                else
                    //删除参数
					*pos = '\0';

                lstrcat(pos, _T(" "));
                lstrcat(pos, url);
                result = (HINSTANCE) WinExec(key,showcmd);
            }
        }
    }

    return result;
}
