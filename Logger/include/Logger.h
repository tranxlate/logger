/*//////////////////////////////////////////////////////////////////////////////
// 개발자 : sjm
// 날짜 : 2015.01.15
// 명칭 : Logger
// 기능 : 프로세스의 로그를 관리한다.
//////////////////////////////////////////////////////////////////////////////*/

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define FILE_MAX_LEN 256

// Log Level

#define LOGGER_VERBOSE	5
#define LOGGER_V	5
#define LOGGER_DEBUG	4
#define LOGGER_D	4
#define LOGGER_INFO	3
#define LOGGER_I	3
#define LOGGER_WARN	2
#define LOGGER_W	2
#define LOGGER_ERROR	1
#define LOGGER_E	1
#define LOGGER_NONE	0
#define LOGGER_N	0

struct LOGTIME_PICKER
{
	char szTime[15];
	char szDate[9];
	int year;
	char szYear[5];
	int mon;
	char szMon[3];
	int day;
	char szDay[3];
	int hour;
	char szHour[3];
	int min;
	char szMin[3];
	int sec;
	char szSec[3];
};
typedef struct LOGTIME_PICKER logtime_t;

class Logger
{
private:
	char m_szLogFormat[FILE_MAX_LEN];
	char m_szLogName[FILE_MAX_LEN];
	int m_iLogLevel;
	FILE *m_fpLog;
private:
	int getdate(logtime_t *picker);
	void file_formatter();
	int write_log(const char *szHeader, const char *szLog);
public:
	Logger();
	~Logger();
	void SetLevel(int iLogLevel);
	void SetLogger(const char *szFileFormat);
	void SetLogger(const char *szFileFormat, int iLogLevel);
	int MakeLogger();
	int MakeLogger(const char *szFileFormat);
	int MakeLogger(const char *szFileFormat, int iLogLevel);
	int Verbose(const char *szLog);
	int V(const char *szLog);
	int v(const char *szLog);	
	int Debug(const char *szLog);
	int D(const char *szLog);
	int d(const char *szLog);
	int Info(const char *szLog);
	int I(const char *szLog);
	int i(const char *szLog);
	int Warn(const char *szLog);
	int W(const char *szLog);
	int w(const char *szLog);
	int Error(const char *szLog);
	int E(const char *szLog);
	int e(const char *szLog);
	void CloseLogger();
};

#endif