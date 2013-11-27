/*
Copyright 2014 Mona
mathieu.poux[a]gmail.com
jammetthomas[a]gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License received along this program for more
details (or else see http://www.gnu.org/licenses/).

This file is a part of Mona.
*/

#pragma once

#include "Mona/Mona.h"
#include "Mona/MapParameters.h"
#include "Mona/Options.h"
#include "Mona/HelpFormatter.h"
#include "Mona/Logger.h"
#include <memory>
#include <fstream>


namespace Mona {


class Application : public MapParameters, public Logger, virtual Object {
public:
	enum ExitCode {
		EXIT_OK = 0,  /// successful termination
		EXIT_USAGE = 64, /// command line usage error
		EXIT_DATAERR = 65, /// data format error
		EXIT_NOINPUT = 66, /// cannot open input
		EXIT_NOUSER = 67, /// addressee unknown
		EXIT_NOHOST = 68, /// host name unknown
		EXIT_UNAVAILABLE = 69, /// service unavailable
		EXIT_SOFTWARE = 70, /// internal software error
		EXIT_OSERR = 71, /// system error (e.g., can't fork)
		EXIT_OSFILE = 72, /// critical OS file missing
		EXIT_CANTCREAT = 73, /// can't create (user) output file
		EXIT_IOERR = 74, /// input/output error
		EXIT_TEMPFAIL = 75, /// temp failure; user is invited to retry
		EXIT_PROTOCOL = 76, /// remote error in protocol
		EXIT_NOPERM = 77, /// permission denied
		EXIT_CONFIG = 78,  /// configuration error
	};

	const Options&			options() const { return _options; }

	bool					hasArgument(const std::string& name) { return hasKey("application."+name); }
	bool					argument(const std::string& name, std::string& value) { return getRaw("application." + name, value); }

	void					displayHelp();

    int						run(int argc, const char* argv[]);

	virtual bool			isInteractive() const { return true; }

protected:
	Application();

    bool					init(int argc, const char* argv[]);
	virtual int				main() = 0;

	virtual bool			loadLogFiles(std::string& directory, std::string& fileName, UInt32& sizeByFile, UInt16& rotation);
	virtual bool			loadConfigurations(std::string& path);
	virtual void			defineOptions(Exception& ex, Options& options);

	virtual void			log(std::thread::id threadId, const std::string& threadName, Priority priority, const char *filePath, std::string& shortFilePath, long line, std::string& message);
	virtual void			dump(const UInt8* data, UInt32 size);
	
private:
#if defined(_OS_UNIX)
	static void HandleSignal(int sig);
#endif


	
	virtual	bool	onHelp(HelpFormatter& helpFormatter) { return true; }


	void			manageLogFiles();
	void			initApplicationPaths(const char* command);

	std::vector<std::string>    _args;
	Options						_options;

	// logs
	UInt32						_logSizeByFile;
	UInt16						_logRotation;
	std::string					_logPath;
	std::ofstream				_logStream;
	std::mutex					_logMutex;
};


} // namespace Mona
