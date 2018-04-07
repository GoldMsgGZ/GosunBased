#ifndef _GxxGmPlayBase_H_
#define _GxxGmPlayBase_H_

class GxxGmPlayBase
{
public:
	static void DebugStringOutput(const char *format, ...);
	static void DebugStringOutput(const wchar_t *format, ...);

	static void SetupMiniDumpMonitor(const char *aMiniDumpSavePath);
	static void SetupMiniDumpMonitor(const wchar_t *aMiniDumpSavePath);
};

#endif//_GxxGmPlayBase_H_