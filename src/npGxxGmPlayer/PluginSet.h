#ifndef _PluginSet_H_
#define _PluginSet_H_

#include <vector>
#include "Plugin.h"

/**
 * ���ﶨ����һ����������࣬������ӦNPAPI��������֧�ֵĶ�����ʵ��
 * ���ǿ���������Ϊ��һ������������һ�����ʵ��
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
