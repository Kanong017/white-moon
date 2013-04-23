#pragma once 

#include <ntddk.h>
#include <devioctl.h>
#include "common.h"

EXTERN_C NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObj, IN PUNICODE_STRING pRegistryString);
EXTERN_C VOID WINAPIV EStartup (VOID);

//DriverUnLoad���ͷ���Դ
EXTERN_C __declspec(naked) __stdcall DriverUnLoader(IN PDRIVER_OBJECT pDriverObj)		
{
	
	__asm
	{
			push ebp
			mov  ebp,esp
			push ebx
			push esi
			push edi
			cmp DriverUnLoad,0h						//�ж�DriverUnLoad�Ƿ�Ϊ0
			jz L01			
			mov eax,pDriverObj
			push eax
			call DriverUnLoad						//�����û����õ�DriverUnLoad
L01:
			mov eax,ReleaseAddr
			test eax,eax							//�ж��ͷ���Դ�ĵ�ַ�Ƿ�Ϊ0
			jz L02
			call eax								//�ͷŵ���������ڴ���Դ				
L02:
			xor eax,eax
			pop edi
			pop esi
			pop ebx
			mov esp,ebp
			pop ebp
			retn 04h
	}
}

//Link���ӵ����������
EXTERN_C __declspec(naked) __stdcall DriverLoader(IN PDRIVER_OBJECT pDriverObj, IN PUNICODE_STRING pRegistryString)
{
	__asm
	{
			push ebp
			mov  ebp,esp
			push ebx
			push esi
			push edi
			mov ecx,dword ptr ss:[pDriverObj]
			mov edx,dword ptr ds:[ecx + 0x14]							//(PLDR_DATA_TABLE_ENTRY)DriverObject->DriverSection
			mov ecx,dword ptr ds:[edx + 0x18]							//(PLDR_DATA_TABLE_ENTRY)->DllBase
			mov DriverBase,ecx											//����������������ַ
			call EStartup												//�����׵ĳ�ʼ������
			mov eax,pRegistryString
			push eax
			mov ecx,pDriverObj
			push ecx
			call DriverEntry											//�����׵�������ں���
			test eax,eax
			jnz L01
			mov ecx,dword ptr ss:[pDriverObj]
			lea ebx,dword ptr ds:[ecx + 0x34]							//ȡ��DriverEntry���õ�DriverUnLoad��ַ
			mov ecx,dword ptr ds:[ebx]
			test ecx,ecx												//�ж��Ƿ�������DriverUnload
			jz L01
			mov DriverUnLoad,ecx										//����DriverUnLoad��ַ��DriverUnLoader���е���
			mov ecx,DriverUnLoader
			mov dword ptr ds:[ebx],ecx									//�����µ�DriverUnLoad�ӿ�
L01:
			pop edi
			pop esi
			pop ebx
			mov esp,ebp
			pop ebp
			retn 08h
	}
}