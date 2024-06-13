// ComTimer.h: interface for the CComTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMTIMER_H__14830681_C344_11D3_B433_006097AAFB65__INCLUDED_)
#define AFX_COMTIMER_H__14830681_C344_11D3_B433_006097AAFB65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <Arduino.h>

class CComTimer
{
public:
	CComTimer();
	virtual ~CComTimer();

	void StartTimer();
	bool DoTimerEvent();

	void SetTimeout(unsigned long ms);
	void SetMaxRetry(int nMax);
	
	bool AddRetry();
	void ClearRetry();

public:
	int m_nRetry, m_nMaxRetry;
	unsigned long m_start;
	unsigned long m_timeout;
};

#endif // !defined(AFX_COMTIMER_H__14830681_C344_11D3_B433_006097AAFB65__INCLUDED_)
