/*
 *  Logger.h
 *  CubicVR
 *
 *  Created by Charles J. Cliffe on 24/05/09.
 *  Copyright 2009 Cubic Productions. All rights reserved.
 *
 */

#pragma once

#include <string>
#include <set>
#include <stdio.h>
#include <stdarg.h>

typedef enum logLevel
{
		LOG_DEBUG  = 0,
		LOG_WARNING = 1,
		LOG_ERROR = 2,
		LOG_NOTICE = 3
};

class LogHook
{
public:
	LogHook();
	~LogHook();
	
	virtual void doLog(logLevel lev, const char *log_str);
};


//class LogFileHook : public LogHook
//{
//public:
//	LogFileHook(char *fn);
//	doLog(char *log_str);
//};


class Logger
{
private:
	static bool std_out_val;
	static std::set<LogHook *> logSet;
	static void doLog(logLevel lev, const char *log_str);
	
public:
	static void addHook(LogHook *logger);
	static void removeHook(LogHook *logger);
	
	static void log(char *format, ...);
	static void log(const char *log_str);
	static void log(std::string &log_str);

	static void log(logLevel lev, char *format, ...);
	static void log(logLevel lev, const char *log_str);
	static void log(logLevel lev, std::string &log_str);
	
	static void setStandardOutput(bool val);
};