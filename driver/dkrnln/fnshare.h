/*
    ��Ȩ������
    ���ļ���ȨΪ�����������������У�����Ȩ����������������������֧�ֿ⣬��ֹ���������κγ��ϡ�
*/

//����Ԫ��ʹ��MFC��, �ɹ���д��ƽ̨��֧�ֿ��Ǵ������֧�ֿ�ʹ��

#ifndef __FN_SHARE_H
#define __FN_SHARE_H
#include "lib2.h"
#include "lang.h"
#include <windef.h>

char* CloneTextData (char* ps);
char* _CloneTextData (char* ps, INT nTextLen);
LPBYTE CloneBinData (LPBYTE pData, INT nDataSize);
void GReportError (char* szErrText);
void* MMalloc (INT nSize);
void MFree (void* p);
LPBYTE GetAryElementInf (void* pAryData, LPINT pnElementCount);
INT GetDataTypeType (DATA_TYPE dtDataType);

#endif //__FN_SHARE_H
