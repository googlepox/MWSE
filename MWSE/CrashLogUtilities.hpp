
inline int ExceptionFilter(unsigned int code)
{
	return EXCEPTION_EXECUTE_HANDLER;
}

inline std::string& SanitizeStringBySize(std::string& str)
{
	for (UINT32 i = 0; i < MAX_PATH; i++) if (str[i] == 0)
		return str;
	str = "";
	return str;
}

inline std::string& SanitizeStringFromBadData(std::string& str)
{
	str.erase(std::remove_if(str.begin(), str.end(), [](char c) { return !(c >= 0 && c <= 0x128); }), str.end());

	std::replace_if(str.begin(), str.end(), [](char c) { return c == '\n' || c == '\r' || c == '\0' || c == '\v'; }, ' ');

	return str;
}

inline std::string pcName;
inline std::string userName;

inline std::string& SanitizeStringFromUserInfo(std::string& str)
{
	[[unlikely]]
	if (pcName.empty())
	{
		TCHAR infoBuf[MAX_PATH];
		DWORD bufCharCount = MAX_PATH;
		if (GetComputerName(infoBuf, &bufCharCount)) pcName = infoBuf;
	}

	[[unlikely]]
	if (userName.empty())
	{
		TCHAR infoBuf[MAX_PATH];
		DWORD bufCharCount = MAX_PATH;
		if (GetUserName(infoBuf, &bufCharCount)) userName = infoBuf;
	}

	if (pcName.size() > 1)
		while (str.find(pcName) != -1) str.replace(str.find(pcName), pcName.size(), pcName.size(), '*');

	if (userName.size() > 1)
		while (str.find(userName) != -1) str.replace(str.find(userName), userName.size(), userName.size(), '*');

	return str;
}

inline const std::string& SanitizeString(std::string&& str)
{
	SanitizeStringBySize(str);
	SanitizeStringFromBadData(str);
	SanitizeStringFromUserInfo(str);

	return str;
}

inline float ConvertToKiB(const UINT64 size) {
	return (float)size / 1024.0f;
}

inline float ConvertToMiB(const UINT64 size) {
	return (float)size / 1024.0f / 1024.0f;
}

inline float ConvertToGiB(const UINT64 size) {
	return (float)size / 1024.0f / 1024.0f / 1024.0f;
}

inline std::string FormatSize(const UINT64 size) {
	std::string result;
	if (size < 1024) {
		result = fmt::format("{:>6d} B", size);
	}
	else if (size < 1024ull * 1024ull) {
		result = fmt::format("{:>6.2f} KiB", ConvertToKiB(size));
	}
	else if (size < 1024ull * 1024ull * 1024ull) {
		result = fmt::format("{:>6.2f} MiB", ConvertToMiB(size));
	}
	else {
		result = fmt::format("{:>6.2f} GiB", ConvertToGiB(size));
	}
	return result;
}

inline std::string GetMemoryUsageString(const UINT64 used, const UINT64 total) {
	float usedPercent = (float)used / total * 100.0f;
	return fmt::format("{:10} / {:10} ({:.2f}%)", FormatSize(used), FormatSize(total), usedPercent);
}

inline std::string GetErrorAsString(UINT32 errorMessageID)
{
	if (errorMessageID == 0) return ""; //No error message has been recorded

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return message;
}

inline std::string GetExceptionAsString(UINT32 exceptionMessageID)
{
	switch (exceptionMessageID) {
	case EXCEPTION_ACCESS_VIOLATION:			return "EXCEPTION_ACCESS_VIOLATION";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:		return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
	case EXCEPTION_BREAKPOINT:					return "EXCEPTION_BREAKPOINT >>";
	case EXCEPTION_DATATYPE_MISALIGNMENT:		return "EXCEPTION_DATATYPE_MISALIGNMENT >>";
	case EXCEPTION_FLT_DENORMAL_OPERAND:		return "EXCEPTION_FLT_DENORMAL_OPERAND";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:			return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
	case EXCEPTION_FLT_INEXACT_RESULT:			return "EXCEPTION_FLT_INEXACT_RESULT";
	case EXCEPTION_FLT_INVALID_OPERATION:		return "EXCEPTION_FLT_INVALID_OPERATION";
	case EXCEPTION_FLT_OVERFLOW:				return "EXCEPTION_FLT_OVERFLOW";
	case EXCEPTION_FLT_STACK_CHECK:				return "EXCEPTION_FLT_STACK_CHECK";
	case EXCEPTION_FLT_UNDERFLOW:				return "EXCEPTION_FLT_UNDERFLOW";
	case EXCEPTION_ILLEGAL_INSTRUCTION:			return "EXCEPTION_ILLEGAL_INSTRUCTION";
	case EXCEPTION_IN_PAGE_ERROR:				return "EXCEPTION_IN_PAGE_ERROR";
	case EXCEPTION_INT_DIVIDE_BY_ZERO:			return "EXCEPTION_INT_DIVIDE_BY_ZERO";
	case EXCEPTION_INT_OVERFLOW:				return "EXCEPTION_INT_OVERFLOW";
	case EXCEPTION_INVALID_DISPOSITION:			return "EXCEPTION_INVALID_DISPOSITION";
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:	return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
	case EXCEPTION_PRIV_INSTRUCTION:			return "EXCEPTION_PRIV_INSTRUCTION";
	case EXCEPTION_SINGLE_STEP:					return "EXCEPTION_SINGLE_STEP";
	case EXCEPTION_STACK_OVERFLOW:				return "EXCEPTION_STACK_OVERFLOW";
	default: return "UKNOWN_EXCEPTION";
	}
}
