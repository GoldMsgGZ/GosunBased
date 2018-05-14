#ifndef _PluginSet_H_
#define _PluginSet_H_

#include <vector>
#include "Plugin.h"

/**
 * 这里定义了一个插件集合类，用于响应NPAPI插件框架下支持的多个插件实例
 * 我们可以这样认为，一个插件类代表了一个插件实例
 */

class GxxGmNPAPIPluginSet
{
public:
	GxxGmNPAPIPluginSet();
	~GxxGmNPAPIPluginSet();

public:
	std::vector<CPlugin *> plugin_instances_;
};

#endif//_PluginSet_H_
