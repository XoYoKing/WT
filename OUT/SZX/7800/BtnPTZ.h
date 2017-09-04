#pragma once


// CBtnPTZ

class CBtnPTZ : public CButton
{
    DECLARE_DYNAMIC(CBtnPTZ)

public:
    CBtnPTZ();
    virtual ~CBtnPTZ();

protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


