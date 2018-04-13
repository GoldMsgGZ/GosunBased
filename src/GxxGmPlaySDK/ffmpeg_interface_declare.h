#ifndef _ffmpeg_interface_declare_H_
#define _ffmpeg_interface_declare_H_

#define FFMPEG_INTERFACE_DECLARE(func) _##func pFunc_##func
#define FFMPEG_INTERFCE(func) pFunc_##func
#define FFMPEG_INTERFCE_TYPE(func) _##func

#endif//_ffmpeg_interface_declare_H_
