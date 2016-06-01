/*****************************************************************
Copyright (c) 2016 Jung-Min, Shin (tranxlate3@gmail.com)

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*****************************************************************/


#ifndef WIN32
#include "../include/Logger.h"
#else
#include "Logger.h"
#endif
/*//////////////////////////////////////////////////////////////////////////////
//
// 				Internal Functions
//
//////////////////////////////////////////////////////////////////////////////*/

int Logger::getdate(logtime_t *picker)
{
	time_t Time_t = time(NULL);
	struct tm *pTmNow = localtime(&Time_t);
	if(pTmNow)
	{
		memset(picker->szTime, 0, sizeof(picker->szTime));
		memset(picker->szDate, 0, sizeof(picker->szDate));
		memset(picker->szYear, 0, sizeof(picker->szYear));
		memset(picker->szMon , 0, sizeof(picker->szMon ));
		memset(picker->szDay , 0, sizeof(picker->szDay ));
		memset(picker->szHour, 0, sizeof(picker->szHour));
		memset(picker->szMin , 0, sizeof(picker->szMin ));		
		memset(picker->szSec , 0, sizeof(picker->szSec ));		
		picker->year = pTmNow->tm_year+1900;
		picker->mon = pTmNow->tm_mon+1;
		picker->day = pTmNow->tm_mday;
		picker->hour = pTmNow->tm_hour;
		picker->min = pTmNow->tm_min;
		picker->sec = pTmNow->tm_sec;
		sprintf(picker->szYear, "%d", picker->year);
		if(picker->mon<10) sprintf(picker->szMon, "0%d", picker->mon);
		else sprintf(picker->szMon, "%d", picker->mon);
		if(picker->day<10) sprintf(picker->szDay, "0%d", picker->day);
		else sprintf(picker->szDay, "%d", picker->day);
		if(picker->hour<10) sprintf(picker->szHour, "0%d", picker->hour);
		else sprintf(picker->szHour, "%d", picker->hour);
		if(picker->min<10) sprintf(picker->szMin, "0%d", picker->min);
		else sprintf(picker->szMin, "%d", picker->min);
		if(picker->sec<10) sprintf(picker->szSec, "0%d", picker->sec);
		else sprintf(picker->szSec, "%d", picker->sec);
		strcpy(picker->szTime, picker->szYear);
		strcat(picker->szTime, picker->szMon );
		strcat(picker->szTime, picker->szDay );
		strcat(picker->szTime, picker->szHour);
		strcat(picker->szTime, picker->szMin );
		strcat(picker->szTime, picker->szSec );
		strcpy(picker->szDate, picker->szYear);
		strcat(picker->szDate, picker->szMon );
		strcat(picker->szDate, picker->szDay );
	}
	else return -1;
	return 0;
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : File Formatter
// 기능 : Log 파일 이름에 포맷된 양식을 변환하여 재 지정한다.
//        %Y - Year, %M - Month,  %D - Day
//        %h - Hour, %m - Minute, %s - Second
//////////////////////////////////////////////////////////////////////////////*/

void Logger::file_formatter()
{
	int i=0, idx=0;
	//char szNewFileName[FILE_MAX_LEN];
	char szBuf[FILE_MAX_LEN];
	logtime_t now;
	
	//memset(szNewFileName, 0, sizeof(szNewFileName));
	memset(m_szLogName, 0, sizeof(m_szLogName));
	if(getdate(&now)!=0)
	{
		printf("Time Error.\n");
		exit(1);
	}	
	for(i=0;i<strlen(m_szLogFormat);i++)
	{
		if(m_szLogFormat[i]=='%')
		{
			memset(szBuf, 0, sizeof(szBuf));
			switch(m_szLogFormat[i+1])
			{
			case 'Y':
				idx+=4;
				sprintf(szBuf, "%d", now.year);
				break;
			case 'M':
				idx+=2;
				if(now.mon<10) sprintf(szBuf, "0%d", now.mon);
				else sprintf(szBuf, "%d", now.mon);
				break;
			case 'D':
				idx+=2;
				if(now.day<10) sprintf(szBuf, "0%d", now.day);
				else sprintf(szBuf, "%d", now.day);
				break;
			case 'h':
				idx+=2;
				if(now.hour<10) sprintf(szBuf, "0%d", now.hour);
				else sprintf(szBuf, "%d", now.hour);
				break;
			case 'm':
				idx+=2;
				if(now.min<10) sprintf(szBuf, "0%d", now.min);
				else sprintf(szBuf, "%d", now.min);
				break;
			case 's':
				idx+=2;
				if(now.sec<10) sprintf(szBuf, "0%d", now.sec);
				else sprintf(szBuf, "%d", now.sec);
				break;
			default:
				idx+=1;
				i--;
				strcpy(szBuf, "%");
				break;
			}
			i++;
			strncat(m_szLogName, szBuf, strlen(szBuf));
		}
		else
		{
			m_szLogName[idx] = m_szLogFormat[i];
			idx++;
		}
	}
	//memset(m_szLogName, 0, sizeof(m_szLogName));
	//strncpy(m_szLogName, szNewFileName, strlen(szNewFileName));
}


/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Write Log
// 기능 : Log 파일에 [시간][Header]로그 형식으로 작성한다.
//////////////////////////////////////////////////////////////////////////////*/

int Logger::write_log(const char *szHeader, const char *szLog)
{
	logtime_t now;
	CloseLogger();
	if(getdate(&now)!=0) return -1;
	if(m_szLogFormat==0) return -1;
	file_formatter();
	m_fpLog = fopen(m_szLogName,"a");
	if(m_fpLog==0) return -1;
	fprintf(m_fpLog,"[%s-%s-%s %s:%s:%s]%s %s\n",
		now.szYear,now.szMon,now.szDay,
		now.szHour,now.szMin,now.szSec,
		szHeader,szLog);
	CloseLogger();
	return 0;
}

/*//////////////////////////////////////////////////////////////////////////////
//
// 				External Functions
//
//////////////////////////////////////////////////////////////////////////////*/


/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Logger
// 기능 : Logger 생성자.
//////////////////////////////////////////////////////////////////////////////*/

Logger::Logger()
{
	m_iLogLevel = LOGGER_NONE;
	memset(m_szLogName, 0, sizeof(m_szLogName));
	memset(m_szLogFormat, 0, sizeof(m_szLogFormat));
	m_fpLog = 0;
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Logger
// 기능 : Logger 소멸자.
//////////////////////////////////////////////////////////////////////////////*/

Logger::~Logger()
{
	CloseLogger();
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.23
// 명칭 : Setting Level
// 기능 : 로그레벨을 지정한다.
//////////////////////////////////////////////////////////////////////////////*/

void Logger::SetLevel(int iLogLevel)
{
	m_iLogLevel = iLogLevel;
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.23
// 명칭 : Setting Level
// 기능 : 로그파일을 지정한다.
//////////////////////////////////////////////////////////////////////////////*/

void Logger::SetLogger(const char *szFileFormat)
{
	memset(m_szLogFormat, 0, sizeof(m_szLogFormat));
	strncpy(m_szLogFormat, szFileFormat, strlen(szFileFormat));
}

void Logger::SetLogger(const char *szFileFormat, int iLogLevel)
{
	SetLevel(iLogLevel);
	SetLogger(szFileFormat);
}


/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.23
// 명칭 : Setting Level
// 기능 : 로그를 생성한다.
//////////////////////////////////////////////////////////////////////////////*/

int Logger::MakeLogger()
{
	if(m_szLogFormat==0) return -1;
	file_formatter();
	m_fpLog = fopen(m_szLogName,"a");
	if(!m_fpLog) return -1;
	CloseLogger();
	return 0;
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Make Logger
// 기능 : 로그파일을 생성한다.
//////////////////////////////////////////////////////////////////////////////*/

int Logger::MakeLogger(const char *szFileFormat)
{
	SetLogger(szFileFormat);
	return MakeLogger();
}

int Logger::MakeLogger(const char *szFileFormat, int iLogLevel)
{
	SetLogger(szFileFormat, iLogLevel);
	return MakeLogger();
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Logger Verbose
// 기능 : Verbose 모드로 로그파일을 작성한다.
//////////////////////////////////////////////////////////////////////////////*/

int Logger::Verbose(const char *szLog)
{
	if(m_iLogLevel >= LOGGER_VERBOSE) return write_log("",szLog);
	return 0;
}

int Logger::V(const char *szLog)
{
	return Verbose(szLog);
}

int Logger::v(const char *szLog)
{
	return Verbose(szLog);
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Logger Debug
// 기능 : Debug 모드로 로그파일을 작성한다.
//////////////////////////////////////////////////////////////////////////////*/

int Logger::Debug(const char *szLog)
{
	if(m_iLogLevel >= LOGGER_DEBUG) return write_log("[DEBUG]",szLog);
	return 0;
}

int Logger::D(const char *szLog)
{
	return Debug(szLog);
}

int Logger::d(const char *szLog)
{
	return Debug(szLog);
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Logger Info
// 기능 : Info 모드로 로그파일을 작성한다.
//////////////////////////////////////////////////////////////////////////////*/

int Logger::Info(const char *szLog)
{
	if(m_iLogLevel >= LOGGER_INFO) return write_log("[INFO]",szLog);
	return 0;
}


int Logger::I(const char *szLog)
{
	return Info(szLog);
}

int Logger::i(const char *szLog)
{
	return Info(szLog);
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Logger Warning
// 기능 : Warning 모드로 로그파일을 작성한다.
//////////////////////////////////////////////////////////////////////////////*/

int Logger::Warn(const char *szLog)
{
	if(m_iLogLevel >= LOGGER_WARN) return write_log("[WARN]",szLog);
	return 0;
}

int Logger::W(const char *szLog)
{
	return Warn(szLog);
}

int Logger::w(const char *szLog)
{
	return Warn(szLog);
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Logger Error
// 기능 : Error 모드로 로그파일을 작성한다.
//////////////////////////////////////////////////////////////////////////////*/

int Logger::Error(const char *szLog)
{
	if(m_iLogLevel >= LOGGER_ERROR) return write_log("[ERROR]",szLog);
	return 0;
	
}

int Logger::E(const char *szLog)
{
	return Error(szLog);
}

int Logger::e(const char *szLog)
{
	return Error(szLog);
}

/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Logger Close
// 기능 : 로그파일 작성을 종료한다.
//////////////////////////////////////////////////////////////////////////////*/

void Logger::CloseLogger()
{
	if(m_fpLog) fclose(m_fpLog);
	m_fpLog = 0;
}