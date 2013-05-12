/*
 * =====================================================================================
 *
 *       filename:  log.h
 *
 *    description:  simple log system
 *
 *        version:  1.0
 *        created:  2013-05-08
 *       revision:  none
 *       compiler:  g++
 *
 *         author:  amadeuzou
 *        company:  blog.youtueye.com
 *
 *      copyright:  2013 amadeuzou#gmail.com. All Rights Reserved.
 *      
 * =====================================================================================
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>


/**
 * @brief       streambuf for null stream
 * @author      amadeu zou
 */
class NullStreamBuffer : public std::streambuf
{
public:
	NullStreamBuffer() : _pos(0), _size(32)
	{
		_buf= new char[_size];
	}
	~NullStreamBuffer()
	{
		delete [] _buf;
	}
	
protected:

	// central output function
	virtual int_type overflow(int_type c)
	{
		if (c != EOF)
	    {
	  
			if(_pos >= _size)
		    {
				_pos %= _size;
			}
	  
			if(c == '\n')
			{
				_pos = 0; 
			}
			else   // 
			{
				_buf[_pos++] = c;
			}
		}
		return c;
	}
	
private:
	char* _buf;    
	int _pos;
	int _size;  
};



/**
 * @brief       null stream
 * @author      amadeu zou
 */
class NullStream : public std::ostream
{
public:
    NullStream() : std::ostream(new NullStreamBuffer()), std::ios(0) {}
    ~NullStream() { delete rdbuf(); }
};





// log level
enum LogLevel{
	INFO = 0,  WARNING,  ERROR,  FATAL, NONE
};

// log info header
const std::string LOGSTR[5] = {
		"[INFO]", "[WARNING]", "[ERROR]", "[FATAL]", ""
	};


/**
 * @brief       log
 * @author      amadeu zou
 */
class Logger
{
	
public:

	/**
	 * @brief       constructor
	 *
	 */
	Logger()
		:_os(&std::cerr), _level(INFO)
	{
		
	}

	/**
	 * @brief       destructor
	 *
	 */
	~Logger()
	{
		_os = NULL;
	}

	/**
	 * @brief       copy
	 *
	 */
	Logger(const Logger &log)
		:_os(log._os), _level(log._level)
	{
		
	}

	/**
	 * @brief       copy
	 *
	 */
	Logger& operator=(Logger &log)
	{
		if ( this != &log )
		{
			this->_os = log._os;
			this->_level = log._level;
		}
		
		return *this;
	}
	
	/**
	 * @brief       set log file
	 *
	 * @param       log file
	 */
	void set_file(const std::string &log_file)
	{
		_os = new std::ofstream(log_file.c_str());
		if(NULL == _os)
			_os = &std::cerr;
	}

	/**
	 * @brief       info log
	 *
	 */
	std::ostream& info()
	{
		if(_level > INFO)
			return _ns;

		*_os<<get_time()<<LOGSTR[INFO];
		return *_os;
		
	}

	/**
	 * @brief       warning log
	 *
	 */
	std::ostream& warning()
	{
		if(_level > WARNING)
			return _ns;

		*_os<<get_time()<<LOGSTR[WARNING];
		return *_os;	
	}

	/**
	 * @brief       error log
	 *
	 */
	std::ostream& error()
	{
		if(_level > ERROR)
			return _ns;

		*_os<<get_time()<<LOGSTR[ERROR];
		return *_os;
		
	}

	/**
	 * @brief       fatal log
	 *
	 */
	std::ostream& fatal()
	{
		if(_level > FATAL)
			return _ns;

		*_os<<get_time()<<LOGSTR[FATAL];
		return *_os;
		
	}

	/**
	 * @brief       overwrite operator
	 *
	 */
	friend std::ostream& operator<<(std::ostream &os, Logger &t)
	{
		return *t._os;
	}

	/**
	 * @brief       get system time
	 *
	 */
	std::string get_time()
	{
		_time = time(NULL);
		std::string str(ctime(&_time));
		// rm /r/n
		return "[" + str.substr(0, str.length() - 1) + "]";
	}

	/**
	 * @brief       set log level
	 *
	 */
	void set_level(int v)
	{
		_level = static_cast<LogLevel>(v);
	}
	
private:
	std::ostream *_os;
	time_t _time;
	LogLevel _level;
	NullStream _ns;
   
};
#endif
