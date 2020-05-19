// ComTimer.cpp: implementation of the CComTimer class.
// Email : yhnam@web.dwe.co.kr 
//         caram55@hanmail.net
// Phone : 031-428-5519
// Pager : 017-204-7786
//////////////////////////////////////////////////////////////////////

#include "ComTimer.h"
#include <limits.h>
#include <Arduino.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComTimer::CComTimer()
{

	ClearRetry();
	SetMaxRetry(1);


	SetTimeout(1000);				
	StartTimer();
}

CComTimer::~CComTimer()
{

}

void CComTimer::StartTimer()
{
	m_start = millis();
}

bool CComTimer::DoTimerEvent()
{
	unsigned long cur;
	long          span;

	cur = millis();

	span = cur - m_start;
	if (span < 0) span += LONG_MAX;

	if (span >= m_timeout)
		return false;

	return true;
}

void CComTimer::SetTimeout(unsigned long ms)
{
	m_timeout = ms;
}

void CComTimer::SetMaxRetry(int nMax)
{
	m_nMaxRetry = nMax;
}

bool CComTimer::AddRetry()
{
	if (++m_nRetry > m_nMaxRetry)
		return false;
	return true;
}

void CComTimer::ClearRetry()
{
	m_nRetry = 0;
}
