// 获取网络驱动列表

#include "stdafx.h"
#include <windows.h>
#include <winnetwk.h>
#pragma comment(lib, "Mpr.lib")

#define MAX_NET_RESOURCES 1024

int EnumNetRes(NETRESOURCE *lpNetRes)
{
	DWORD dwCount = -1;
	DWORD dwSize = sizeof(NETRESOURCE) * MAX_NET_RESOURCES;
	HANDLE hEnum;  

	if (NO_ERROR == WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_DISK, RESOURCEUSAGE_ALL, lpNetRes, &hEnum))
	{
		NETRESOURCE NetResources[MAX_NET_RESOURCES];
		if (NO_ERROR == WNetEnumResource(hEnum, &dwCount, NetResources, &dwSize))
		{
			for (size_t i = 0; i < dwCount; i ++)
			{
				wprintf(L"%ws\n", NetResources[i].lpRemoteName);
				if (NetResources[i].dwUsage & RESOURCEUSAGE_CONTAINER)
				{
					EnumNetRes(&NetResources[i]);
				}
			}
		}
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	NETRESOURCE *initial = NULL;
	EnumNetRes(initial);
	return 0;
}

