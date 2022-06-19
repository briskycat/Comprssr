// ==========================================================================
//                          Class Implementation : 
//              COX3DTabViewContainer & COX3DTabViewDropTarget
// ==========================================================================

// Source file : OX3DTabView.cpp

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      

// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OX3DTabView.h"

#ifndef __OXMFCIMPL_H__
#include <..\src\afximpl.h>
#define __OXMFCIMPL_H__
#endif

#ifndef __AFXPRIV_H__
#include <afxpriv.h>
#define __AFXPRIV_H__
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Change tab on drag over handler
DROPEFFECT COX3DTabViewDropTarget::OnDragOver(CWnd* pWnd, 
                                              COleDataObject* pDataObject,
                                              DWORD dwKeyState, 
                                              CPoint point)
{
    UNREFERENCED_PARAMETER(pDataObject);
    UNREFERENCED_PARAMETER(dwKeyState);

    // get the pointer to tab control
    COX3DTabViewContainer* pTabViewContainer=(COX3DTabViewContainer*)pWnd;
    TC_HITTESTINFO hitTest;
    hitTest.pt=point;
    
    // find the drop target item 
    int nItem=pTabViewContainer->HitTest(&hitTest);

    // if found ...
    if(nItem>=0 && m_nOldItem!=nItem)
    {
        // activate corresponding page
        pTabViewContainer->SetActivePageIndex(nItem);
        m_nOldItem=pTabViewContainer->HitTest(&hitTest);
    }   

    return DROPEFFECT_NONE;
}


void COX3DTabViewDropTarget::OnDragLeave(CWnd* pWnd)
{
    m_nOldItem=-1;
    COleDropTarget::OnDragLeave(pWnd);
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(COX3DTabViewContainer, CTabCtrl)

COX3DTabViewContainer::COX3DTabViewContainer() :
    m_rectPage(0,0,0,0),
    m_bAcceptDraggedObject(TRUE),
    m_dwOffsetExternal(ID_3DTABVIEW_OFFSET_EXTERNAL),
    m_dwOffsetInternal(ID_3DTABVIEW_OFFSET_INTERNAL),
    m_nActivePageIndex(-1),
    m_bDrawingNCBackground(FALSE)
{
    m_arrUniqueIDs.Add(1);
}


COX3DTabViewContainer::~COX3DTabViewContainer()
{
}


BEGIN_MESSAGE_MAP(COX3DTabViewContainer, CTabCtrl)
    //{{AFX_MSG_MAP(COX3DTabViewContainer)
    ON_NOTIFY_REFLECT_EX(TCN_SELCHANGE, OnSelchange)
    ON_WM_NCCALCSIZE()
    ON_WM_NCPAINT()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL COX3DTabViewContainer::Create(CWnd* pParentWnd, CRect rect/*=CRect(0,0,0,0)*/,
                                   DWORD dwStyle/*=DEFAULT_3DTABCTRLSTYLE*/, 
                                   UINT nID/*=AFX_IDW_PANE_FIRST*/)
{
    ASSERT(pParentWnd != NULL);
    ASSERT(dwStyle & WS_CHILD);
    ASSERT(nID!=0);

    if(!CTabCtrl::Create(dwStyle,rect,pParentWnd,nID))
    {
        TRACE(_T("COX3DTabViewContainer::Create: Failed to create the tab control\n"));
        return FALSE;      
    }

    return TRUE;
}

void COX3DTabViewContainer::OnNcCalcSize(BOOL bCalcValidRects, 
                                         NCCALCSIZE_PARAMS FAR* lpncsp) 
{
    // TODO: Add your message handler code here and/or call default
    
    CTabCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);

    // add an offset
    if(lpncsp->rgrc[0].bottom-lpncsp->rgrc[0].top>2*(int)m_dwOffsetExternal)
    {
        lpncsp->rgrc[0].top+=m_dwOffsetExternal;
        lpncsp->rgrc[0].bottom-=m_dwOffsetExternal;
    }
    else
    {
        lpncsp->rgrc[0].top=lpncsp->rgrc[0].bottom;
    }

    if(lpncsp->rgrc[0].right-lpncsp->rgrc[0].left>2*(int)m_dwOffsetExternal)
    {
        lpncsp->rgrc[0].left+=m_dwOffsetExternal;
        lpncsp->rgrc[0].right-=m_dwOffsetExternal;
    }
    else
    {
        lpncsp->rgrc[0].left=lpncsp->rgrc[0].right;
    }
}

void COX3DTabViewContainer::OnNcPaint() 
{
    // TODO: Add your message handler code here
    CWindowDC dc(this);
    CRect rectClient;
    GetClientRect(rectClient);
    CRect rectWindow;
    GetWindowRect(rectWindow);
    ScreenToClient(rectWindow);
    rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
    if(rectClient.top<rectClient.bottom && rectClient.top<rectClient.bottom)
    {
        dc.ExcludeClipRect(rectClient);
    }

    m_bDrawingNCBackground=TRUE;
    // erase parts not drawn
    SendMessage(WM_ERASEBKGND,(WPARAM)dc.m_hDC);
    m_bDrawingNCBackground=FALSE;

    // draw borders in non-client area
    rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);
    dc.Draw3dRect(rectWindow,::GetSysColor(COLOR_BTNSHADOW),
        ::GetSysColor(COLOR_BTNHILIGHT));

    // Do not call CTabCtrl::OnNcPaint() for painting messages
}


void COX3DTabViewContainer::OnSize(UINT nType, int cx, int cy) 
{
    CTabCtrl::OnSize(nType, cx, cy);
    
    // TODO: Add your message handler code here
    if(nType!=SIZE_MINIMIZED && cx>0 && cy>0)
    {
        UpdatePages();
    }
}


BOOL COX3DTabViewContainer::OnEraseBkgnd(CDC* pDC) 
{
    // TODO: Add your message handler code here and/or call default

    if(GetPageCount()!=0 && !m_bDrawingNCBackground)
    {
        CRect rectPage=GetPageRect();
        pDC->ExcludeClipRect(rectPage);
    } 
    
    return CTabCtrl::OnEraseBkgnd(pDC);
}


void COX3DTabViewContainer::OnDestroy() 
{
    SetActivePageIndex(-1);
    int nCount=GetPageCount();
    for(int nIndex=nCount-1; nIndex>=0; nIndex--)
    {
        DeletePage(nIndex,TRUE);
    }
    CTabCtrl::OnDestroy();
}


void COX3DTabViewContainer::OnSetFocus(CWnd* pOldWnd)
{
    UNREFERENCED_PARAMETER(pOldWnd);

}

//////////////////////////////////////////////////////////////////////////////
// Description: Selection change handler
//////////////////////////////////////////////////////////////////////////////
BOOL COX3DTabViewContainer::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
    UNREFERENCED_PARAMETER(pNMHDR);

    int nItem=GetCurSel();
    if(nItem>=0)
    {
        SetActivePageIndex(nItem);
    }

    *pResult = 0;

    return FALSE;
}




BOOL COX3DTabViewContainer::InsertPage(int nIndex, 
                                       CRuntimeClass* pClass, 
                                       CCreateContext* pContext,
                                       LPCTSTR lpszTitle/*=NULL*/, 
                                       const int nImage/*=-1*/)
{
    ASSERT_VALID(this);
    ASSERT(nIndex>=0 && nIndex<=GetPageCount());
    ASSERT(pClass!=NULL);
    ASSERT(pClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
    ASSERT(AfxIsValidAddress(pClass,sizeof(CRuntimeClass),FALSE));

    if(!(nIndex>=0 && nIndex<=GetPageCount()) || pClass==NULL)
        return FALSE;

    BOOL bSendInitialUpdate=FALSE;

    CCreateContext context;
    if(pContext==NULL)
    {
        // if no context specified, generate one from the currently active
        // view if possible
        CView* pOldView=(CView*)GetActivePage();
        if(pOldView!=NULL && pOldView->IsKindOf(RUNTIME_CLASS(CView)))
        {
            // set info about last pane
            ASSERT(context.m_pCurrentFrame==NULL);
            context.m_pLastView=pOldView;
            context.m_pCurrentDoc=pOldView->GetDocument();
            if(context.m_pCurrentDoc!=NULL)
            {
                context.m_pNewDocTemplate=context.m_pCurrentDoc->
                    GetDocTemplate();
            }
            bSendInitialUpdate=TRUE;
        }
        pContext=&context;
    }

    CWnd* pWnd;
    TRY
    {
        pWnd=(CWnd*)pClass->CreateObject();
        if(pWnd==NULL)
            AfxThrowMemoryException();
    }
    CATCH_ALL(e)
    {
        TRACE(_T("COX3DTabViewContainer::InsertPage: Out of memory inserting new page\n"));
        // Note: DELETE_EXCEPTION(e) not required
        return FALSE;
    }
    END_CATCH_ALL

    ASSERT_KINDOF(CWnd,pWnd);
    ASSERT(pWnd->m_hWnd==NULL);       // not yet created

    DWORD dwStyle=AFX_WS_DEFAULT_VIEW;
    if(afxData.bWin4)
        dwStyle&=~WS_BORDER;

    DWORD dwID=GetUniqueId();

    // Create with the right size
    if(!pWnd->Create(NULL,NULL,dwStyle,CRect(0,0,0,0),this,dwID,pContext))
    {
        TRACE(_T("COX3DTabViewContainer::InsertPage: couldn't create new page\n"));
        // pWnd will be cleaned up by PostNcDestroy
        return FALSE;
    }

    if(InsertPage(nIndex,pWnd,lpszTitle,nImage))
    {
        CWnd* pWnd=GetPage(nIndex);
        ASSERT(pWnd!=NULL);
        ASSERT(::IsWindow(pWnd->m_hWnd));
        if(bSendInitialUpdate && pWnd->IsKindOf(RUNTIME_CLASS(CView)))
        {
            // send initial notification message
            pWnd->SendMessage(WM_INITIALUPDATE);
        }
        return TRUE;
    }

    return FALSE;
}

BOOL COX3DTabViewContainer::InsertPage(int nIndex, CWnd* pWnd, 
                                       LPCTSTR lpszTitle/*=NULL*/, 
                                       int nImage/*=-1*/)
{
    ASSERT_VALID(this);
    ASSERT(nIndex>=0 && nIndex<=GetPageCount());
    ASSERT(pWnd!=NULL);
    ASSERT(::IsWindow(pWnd->m_hWnd));

    if(!(nIndex>=0 && nIndex<=GetPageCount()) || 
        pWnd==NULL || !::IsWindow(pWnd->m_hWnd))
    {
        TRACE(_T("COX3DTabViewContainer::InsertPage: failed to insert page, some of the parameters has been specified wrong\n"));
        return FALSE;
    }

    TCITEM tcItem;
    tcItem.mask=TCIF_IMAGE|TCIF_PARAM|TCIF_TEXT;
    tcItem.pszText=(LPTSTR)lpszTitle;
    tcItem.iImage=nImage;
    tcItem.lParam=(LPARAM)pWnd;
    if(InsertItem(nIndex,&tcItem)!=nIndex)
    {
        TRACE(_T("COX3DTabViewContainer::InsertPage: failed to insert new button in the tab control\n"));
        return FALSE;
    }

    pWnd->ModifyStyleEx(NULL,WS_EX_CLIENTEDGE);
    SetActivePageIndex(nIndex);

    return TRUE;
}

BOOL COX3DTabViewContainer::DeletePage(int nIndex, BOOL bDestroy/*=TRUE*/)
{
    ASSERT_VALID(this);
    ASSERT(nIndex>=0 && nIndex<GetPageCount());

    if(nIndex>=0 && nIndex<GetPageCount())
    {
        // if active page is being deleted - activate next
        int nActivePage=GetActivePageIndex();
        if(nActivePage==nIndex)
        {
            if(nActivePage==GetPageCount()-1)
                SetActivePageIndex(0);
            else
                SetActivePageIndex(GetPageCount()>1 ? nActivePage+1 : 0);
        }
        CWnd* pWnd=GetPage(nIndex);
        ASSERT(pWnd!=NULL);
        m_arrUniqueIDs.Add(pWnd->GetDlgCtrlID());
        if(bDestroy && ::IsWindow(pWnd->m_hWnd))
            VERIFY(pWnd->DestroyWindow());

        DeleteItem(nIndex);

        return TRUE;
    }

    return FALSE;
}

BOOL COX3DTabViewContainer::SetActivePageIndex(int nIndex)
{
    if(nIndex==m_nActivePageIndex)
        return TRUE;
 
    CWnd* pWndOld=GetActivePage();
    if(pWndOld!=NULL)
    {
        ASSERT(::IsWindow(pWndOld->m_hWnd));
        if(::IsWindow(pWndOld->m_hWnd))
            pWndOld->ShowWindow(SW_HIDE);
    }

    m_nActivePageIndex=nIndex;
    SetCurSel(nIndex);

    if(m_nActivePageIndex>=0 && m_nActivePageIndex<GetPageCount())
    {
        CWnd* pWnd=GetPage(m_nActivePageIndex);
        if(pWnd!=NULL)
        {
            ASSERT(::IsWindow(pWnd->m_hWnd));
            if(::IsWindow(pWnd->m_hWnd))
            {
                RecalcPageRect();
                CRect rectPage=GetPageRect();
                CRect rect;
                pWnd->GetWindowRect(rect);
                if(rect.Width()!=rectPage.Width() || rect.Height()!=rectPage.Height())
                    pWnd->MoveWindow(rectPage);
                else
                {
                    pWnd->SendMessage(WM_SIZE,SIZE_RESTORED,
                        MAKELPARAM(rect.Width(),rect.Height()));
                }
                pWnd->ShowWindow(SW_SHOW);

                // set the focus to the page
                CFrameWnd* pFrameWnd=(CFrameWnd*)GetParent();
                ASSERT(pFrameWnd!=NULL);
                if(pFrameWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
                {
                    if(pWnd->IsKindOf(RUNTIME_CLASS(CView)))
                    {
                        pFrameWnd->SetActiveView((CView*)pWnd);
                    }
                    else
                    {
                        if(pWndOld!=NULL && 
                            pWndOld->IsKindOf(RUNTIME_CLASS(CView)))
                        {
                            pFrameWnd->SetActiveView(NULL);
                        }
                        pWnd->SetFocus();
                    }
                }
                else
                {
                    pWnd->SetFocus();
                }

                pWnd->RedrawWindow();
            }
        }
    }
    else
        return FALSE;

    return TRUE;
}


void COX3DTabViewContainer::RecalcPageRect() 
{
    CRect rectPage(0,0,0,0);
    GetWindowRect(rectPage);
    rectPage.DeflateRect(GetOffsetExternal(),GetOffsetExternal());
    ScreenToClient(rectPage);
    if(!rectPage.IsRectEmpty() && rectPage.left<rectPage.right && 
        rectPage.top<rectPage.bottom)
    {
        CTabCtrl* pTab=(CTabCtrl*)this;
        pTab->AdjustRect(FALSE,rectPage);
        rectPage.DeflateRect(GetOffsetInternal(),GetOffsetInternal());
    }
    m_rectPage=rectPage;
}
