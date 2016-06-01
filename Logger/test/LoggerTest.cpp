#include "../include/Logger.h"
#include <stdio.h>

int main()
{
	Logger logger;
	char szLogName[] = "test_%Y-%M-%D.log";
	
	printf("===================\n");
	printf("Logger Module Check\n");
	printf("===================\n");
	printf("Function : logger.MakeLogger\n");
	printf("Log File : %s\n",szLogName);
	printf("MakeLogger(file, DEBUG) Result : %d\n",logger.MakeLogger(szLogName, LOGGER_VERBOSE));
	printf("Press Enter Key.\n");
	getchar();
	printf("=====================\n");
	printf("Function : logger.Vervose\n");
	printf("Vervose(test) Result : %d\n",logger.Verbose("test"));
	printf("Press Enter Key.\n");
	getchar();
	printf("=====================\n");
	printf("Function : logger.Debug\n");
	printf("Debug(aaa) Result : %d\n",logger.Debug("aaa"));
	printf("Press Enter Key.\n");
	getchar();
	printf("=====================\n");
	printf("Function : logger.Debug\n");
	printf("Info(222) Result : %d\n",logger.Info("222"));
	printf("Press Enter Key.\n");
	getchar();
	printf("=====================\n");
	printf("Function : logger.Debug\n");
	printf("Warn(ccc) Result : %d\n",logger.Warn("ccc"));
	printf("Press Enter Key.\n");
	getchar();
	printf("=====================\n");
	printf("Function : logger.Error\n");
	printf("Error(444.4) Result : %d\n",logger.Error("444.4"));
	printf("Press Enter Key.\n");
	getchar();
	printf("=====================\n");
	printf("Function : logger.CloseLogger()\n");
	logger.CloseLogger();
	printf("Press Enter Key.\n");
	getchar();
	printf("=====================\n");
	printf("End.\n\n");
	return 0;
}