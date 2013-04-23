/*
    ��Ȩ������
    ���ļ���ȨΪ�����������������У�����Ȩ����������������������֧�ֿ⣬��ֹ���������κγ��ϡ�
*/
#include "fnshare.h"
EXTERN_C PVOID WINAPIV krnl_MMalloc(DWORD dwBytes);
EXTERN_C void WINAPIV krnl_MFree(PVOID lpMem);
EXTERN_C void WINAPIV krnl_MReportError(UINT uErrCode);

// ʹ��ָ���ı����ݽ����׳�����ʹ�õ��ı����ݡ�
char* WINAPIV CloneTextData (char* ps)
{
	INT nTextLen;
	char* pd;
    if (ps == NULL || *ps == '\0')
        return NULL;
	
	nTextLen = strlen (ps);

	pd = (char*)krnl_MMalloc (nTextLen + 1);
    memcpy (pd, ps, nTextLen);
    pd [nTextLen] = '\0';
    return pd;
}

// ʹ��ָ���ı����ݽ����׳�����ʹ�õ��ı����ݡ�
//   nTextLen����ָ���ı����ֵĳ��ȣ������������㣩��
// ���Ϊ-1����ȡps��ȫ�����ȡ�
char* WINAPIV _CloneTextData (char* ps, INT nTextLen)
{
	char* pd;
    if (nTextLen <= 0)
        return NULL;

    pd = (char*)krnl_MMalloc (nTextLen + 1);
    memcpy (pd, ps, nTextLen);
    pd [nTextLen] = '\0';
    return pd;
}

// ʹ��ָ�����ݽ����׳�����ʹ�õ��ֽڼ����ݡ�
LPBYTE WINAPIV CloneBinData (LPBYTE pData, INT nDataSize)
{
	LPBYTE pd;
    if (nDataSize == 0)
        return NULL;

    pd = (LPBYTE)krnl_MMalloc (sizeof (INT) * 2 + nDataSize);
    *(LPINT)pd = 1;
    *(LPINT)(pd + sizeof (INT)) = nDataSize;
    memcpy (pd + sizeof (INT) * 2, pData, nDataSize);
    return pd;
}

// ��������ʱ����
void GReportError (char* szErrText)
{
	//krnl_MReportError(szErrText);
}

void* WINAPIV MMalloc (INT nSize)
{
	return (void*)krnl_MMalloc (nSize);
}

void WINAPIV MFree (void* p)
{
	krnl_MFree( p );
}

// ������������ݲ����׵�ַ����Ա��Ŀ��
LPBYTE GetAryElementInf (void* pAryData, LPINT pnElementCount)
{
	INT nElementCount;
	LPINT pnData = (LPINT)pAryData;
	INT nArys = *pnData++;  // ȡ��ά����
	// �����Ա��Ŀ��
	nElementCount = 1;
	while (nArys > 0)
	{
		nElementCount *= *pnData++;
		nArys--;
	}

	if (pnElementCount != NULL)
		*pnElementCount = nElementCount;
	return (LPBYTE)pnData;
}

#define DTT_IS_NULL_DATA_TYPE   0
#define DTT_IS_SYS_DATA_TYPE    1
#define DTT_IS_USER_DATA_TYPE   2
#define DTT_IS_LIB_DATA_TYPE    3
// ȡ���������͵����
INT GetDataTypeType (DATA_TYPE dtDataType)
{
	DWORD dw;
	if (dtDataType == _SDT_NULL)
		return DTT_IS_NULL_DATA_TYPE;

	dw = dtDataType & 0xC0000000;
	return dw == DTM_SYS_DATA_TYPE_MASK ? DTT_IS_SYS_DATA_TYPE :
			dw == DTM_USER_DATA_TYPE_MASK ? DTT_IS_USER_DATA_TYPE :
			DTT_IS_LIB_DATA_TYPE;
}