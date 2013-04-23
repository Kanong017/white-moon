#include "stdafx.h"

EXTERN_C int EStartup();
EXTERN_C INT WINAPI krnl_ProcessNotifyLib (INT nMsg, DWORD dwParam1, DWORD dwParam2);
INT WINAPI krnl_NotifySys (INT nMsg, DWORD dwParam1, DWORD dwParam2);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	krnl_ProcessNotifyLib(NL_SYS_NOTIFY_FUNCTION, (DWORD)krnl_NotifySys, 0);
	return EStartup();
}

void ReportAllocMemError(SIZE_T dwBytes)
{

}


EXTERN_C INT krnl_MOtherHelp()
{
	return 0;
}

EXTERN_C INT krnl_MMessageLoop()
{
	return 0;
}

EXTERN_C INT WINAPI krnl_ProcessNotifyLib (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
	return ProcessNotifyLib(nMsg, dwParam1, dwParam2);
}

EXTERN_C void krnl_MReportError(UINT uErrCode)
{
};

EXTERN_C INT krnl_MCallDllCmd()
{
	return 0;
};

EXTERN_C __declspec(naked) void krnl_MCallLibCmd()
{
	__asm
	{
		lea		edx, dword ptr [esp + 0x8]
		sub		esp, 0xC
		push		edx
		push		dword ptr [esp + 0x14]
		mov		dword ptr [esp + 0x8], 0
		mov		dword ptr [esp + 0xC], 0
		mov		dword ptr [esp + 0x10], 0
		lea		edx, dword ptr [esp + 0x8]
		push		edx
		call		ebx
		mov		eax, dword ptr [esp + 0xC]
		mov		edx, dword ptr [esp + 0x10]
		mov		ecx, dword ptr [esp + 0x14]
		add		esp, 0x18
		retn
	}
};

EXTERN_C __declspec(naked) void krnl_MCallKrnlLibCmd()
{
	__asm
	{
		lea		eax, dword ptr [esp + 0x8]
		sub		esp, 0xC
		push		eax
		push		dword ptr [esp + 0x14]
		xor		eax, eax
		mov		dword ptr [esp + 0x8], eax
		mov		dword ptr [esp + 0xC], eax
		mov		dword ptr [esp + 0x10], eax
		lea		edx, dword ptr [esp + 0x8]
		push		edx
		call		ebx
		mov		eax, dword ptr [esp + 0xC]
		mov		edx, dword ptr [esp + 0x10]
		mov		ecx, dword ptr [esp + 0x14]
		add		esp, 0x18
		retn
	}
};
/*
EXTERN_C MDATA_INF krnl_MCallKrnlLibCmd(INT nArgCount, MDATA_INF ArgInf)
{
	MDATA_INF RetData = { 0 };
	__asm
	{
		lea		eax, ArgInf
		push		eax
		push		nArgCount
		lea		eax, RetData
		push		eax
		call		ebx
		add		esp, 0xC
	}
	return RetData;
}
*/

EXTERN_C INT krnl_MReadProperty()
{
	return 0;
};

EXTERN_C INT krnl_MWriteProperty()
{
	return 0;
};

EXTERN_C PVOID krnl_MMalloc(DWORD dwBytes)
{
	PVOID lpMem = malloc(dwBytes);
	if ( !lpMem )
	{
		ReportAllocMemError(dwBytes);
	}
	return lpMem;
};

EXTERN_C PVOID krnl_MRealloc(PVOID lpMem, DWORD dwBytes)
{
	lpMem = realloc(lpMem, dwBytes);
	if ( !lpMem )
	{
		ReportAllocMemError(dwBytes);
	}
	return lpMem;
};

EXTERN_C void krnl_MFree(PVOID lpMem)
{
	if ( lpMem )
	{
		free(lpMem);
	}
};

EXTERN_C void krnl_MExitProcess(UINT uExitCode)
{
	exit(uExitCode);
};

EXTERN_C void krnl_MLoadBeginWin()
{

};
/*
�����Ժ������ݵ�ÿ1������ΪpArgInf [0] ��2��ΪpArgInf [1]...
����ֵ������pRetData��
krnl_MCallKrnlLibCmd �������ǶԲ����������� ��������ֵ���浽��Ӧ�ļĴ���
*/
//	��˫����С���͡� ���� ��˫����С���� ��������˫����С���� ������... ��
EXTERN_C void krnln_fnIDiv(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	DOUBLE db = pArgInf [0].m_double;
	for (INT i = 1; i < nArgCount; i++)
	{
		pArgInf++;
		if (pArgInf->m_double == 0)
		{
			GReportError ("���ܳ���Ϊ��");
		}
		db =  db / pArgInf->m_double;
	}
	// ���÷��ص�˫����С�����ݡ�
	if ( db > 0 )
	{
		pRetData->m_double = floor(db);
	}
	else
	{
		pRetData->m_double = ceil(db);
	}
}

//	��˫����С���͡� ������ ��˫����С���� ��������˫����С���� ������... ��
EXTERN_C void krnln_fnMod (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	DOUBLE db = pArgInf [0].m_double;
	for (INT i = 1; i < nArgCount; i++)
	{
		pArgInf++;
		if (pArgInf->m_double == 0)
		{
			GReportError ("��������������");
		}
		db = fmod (db, pArgInf->m_double);
	}

	// ���÷��ص�˫����С�����ݡ�
	pRetData->m_double = db;
}

//	�������͡� ȡ���� ��˫����С���� ��ȡ����ŵ���ֵ��
EXTERN_C void krnln_fnSgn (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT nRet = 0;
	if( pArgInf [0].m_double > 0 )
	{
		nRet = 1;
	}
	else if ( pArgInf[0].m_double < 0 )
	{
		nRet = -1;
	}
	pRetData->m_int = nRet;
}

//	��˫����С���͡� ȡ����ֵ ��˫����С���� ��ȡ�����ֵ����ֵ��
EXTERN_C void krnln_fnAbs(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = fabs(pArgInf [0].m_double);
}

//	�������͡� ȡ�� ��˫����С���� ��ȡ����С����
EXTERN_C void krnln_fnInt(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = (INT)floor(pArgInf [0].m_double);
}

//	�������͡� ����ȡ�� ��˫����С���� ��ȡ����С����
EXTERN_C void krnln_fnFix(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = (INT)ceil(pArgInf [0].m_double);
}

//	��˫����С���͡� �������� ��˫����С���� ���������������ֵ���������� �������λ�ãݣ�
EXTERN_C void krnln_fnRound(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
}

//	��˫����С���͡� ��η� ��˫����С���� ����η���ֵ��˫����С���� �η�����
EXTERN_C void krnln_fnPow(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = pow(pArgInf[0].m_double, pArgInf[1].m_double);
}

//	��˫����С���͡� ��ƽ���� ��˫����С���� ������ƽ��������ֵ��
EXTERN_C void krnln_fnSqr(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = sqrt(pArgInf[0].m_double);
}

//	��˫����С���͡� ������ ��˫����С���� �����м���Ľǣ�
EXTERN_C void krnln_fnSin(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = sin(pArgInf[0].m_double);
}
//	��˫����С���͡� ������ ��˫����С���� �����м���Ľǣ�
EXTERN_C void krnln_fnCos(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = cos(pArgInf[0].m_double);
}
//	��˫����С���͡� ������ ��˫����С���� �����м���Ľ�
EXTERN_C void krnln_fnTan(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = tan(pArgInf[0].m_double);
}
//	��˫����С���͡� ������ ��˫����С���� �����䷴����ֵ����ֵ��
EXTERN_C void krnln_fnAtn(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = atan(pArgInf[0].m_double);
}
//	��˫����С���͡� ����Ȼ���� ��˫����С���� ��������Ȼ��������ֵ��
EXTERN_C void krnln_fnLog(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = log(pArgInf[0].m_double);
}
//	��˫����С���͡� �󷴶��� ��˫����С���� �����䷴��������ֵ��
EXTERN_C void krnln_fnExp(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_double = exp(pArgInf[0].m_double);
}
//	���߼��͡� �Ƿ�������ȷ ��˫����С���� ��У��ļ�����
EXTERN_C void krnln_IsCalcOK(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = BL_TRUE;
}
//	���޷���ֵ�� ����������� ���������� �������������ֵ�ݣ�
EXTERN_C void krnln_fnRandomize(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if( pArgInf[0].m_int )		 //		���ӷ�0ʱ
	{
		srand(pArgInf[0].m_int);
	}
	else
	{
		srand(time(NULL));
	}
}
//	�������͡� ȡ����� ���������� ��ȡ���������Сֵ�ݣ��������� ��ȡ����������ֵ�ݣ�
EXTERN_C void krnln_fnRnd(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[1].m_int )	//	�����ֵ����ʱ
	{
		pRetData->m_int = rand() % (pArgInf[1].m_int - pArgInf[0].m_int) + pArgInf[0].m_int;
	}
	else
	{
		pRetData->m_int = rand() + pArgInf[0].m_int;
	}
}

//	���߼��͡� ���Ƶ��� ���ı��� ���Ƚ��ı����ı��� �Ƚ��ı���
EXTERN_C void krnln_fnTextLikeEqu(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	char *pText1 = pArgInf[0].m_pText;
	char *pText2 = pArgInf[1].m_pText;
	if ( pText1 == NULL )
	{
		if ( pText2 == NULL )
		{
			pRetData->m_bool = BL_TRUE;
		}
		{
			pRetData->m_bool = BL_FALSE;
		}
	}
	else
	{
		if ( pText2 == NULL )
		{
			pRetData->m_bool = BL_TRUE;
		}
		else
		{
			size_t nLen1 = strlen(pText1);
			size_t nLen2 = strlen(pText2);
			if ( nLen1 >= nLen2 )
			{
				if ( (nLen2 == 0) || (memcmp(pText1, pText2, nLen2) == 0) )
				{
					pRetData->m_bool = BL_TRUE;
				}
				else
				{
					pRetData->m_bool = BL_FALSE;
				}
			}
			else
			{
				pRetData->m_bool = BL_FALSE;
			}
		}
	}
}

//	�������͡� λȡ�� �������� ��ȡ������ֵ��
EXTERN_C void krnln_fnBNot(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = !pArgInf[0].m_int;
}
//	�������͡� λ�� �������� λ������ֵһ�������� λ������ֵ����... ��
EXTERN_C void krnln_fnBAnd(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT n = pArgInf [0].m_int;
	for (INT i = 1; i < nArgCount; i++)
	{
		pArgInf++;
		n &=pArgInf->m_int;
	}
	pRetData->m_int = n;
}
//	�������͡� λ�� �������� λ������ֵһ�������� λ������ֵ����... ��
EXTERN_C void krnln_fnBOr(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT nRet = pArgInf [0].m_int;
	for (INT i = 1; i < nArgCount; i++)
	{
		pArgInf++;
		nRet |=pArgInf->m_int;
	}
	pRetData->m_int = nRet;
}
//	�������͡� λ��� �������� λ������ֵһ�������� λ������ֵ����... ��
EXTERN_C void krnln_fnBXor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT nRet = pArgInf [0].m_int;
	for (INT i = 1; i < nArgCount; i++)
	{
		pArgInf++;
		nRet ^=pArgInf->m_int;
	}
	pRetData->m_int = nRet;
}
//	�������͡� ���� �������� ���ƶ��������������� ���ƶ���λ����
EXTERN_C void krnln_fnSHL(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = pArgInf[0].m_int << pArgInf[1].m_int;
}
//	�������͡� ���� �������� ���ƶ��������������� ���ƶ���λ����
EXTERN_C void krnln_fnSHR(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = pArgInf[0].m_int >> pArgInf[1].m_int;
}
//	 �������͡� �ϲ����� �������� �����ϲ�������1�������� �����ϲ�������2��
EXTERN_C void krnln_fnMAKELONG(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = MAKELONG(pArgInf[0].m_int, pArgInf[1].m_int);
}
//	���������͡� �ϲ������� �������� �����ϲ�������1�������� �����ϲ�������2��
EXTERN_C void krnln_fnMAKEWORD(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = MAKEWORD(pArgInf[0].m_int, pArgInf[1].m_int);
}

//	 ���޷���ֵ�� �������� ��ͨ���ͱ������� ��ֵ���������
EXTERN_C void krnln_fnZeroAry(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	/*
	if ( pArgInf[0].m_ppAryData )
	{
		INT *pArg = (INT*)*pArgInf[0].m_ppAryData;
		if ( pArg )
		{
			INT nLen = 1;
			for (int i=1; i<pArg[0]+1; i++)
			{
				nLen *= pArg[i];
			}
			if ( (pArgInf[0].m_dtDataType == SDT_TEXT) || (pArgInf[0].m_dtDataType == SDT_BIN) )
			{
				for (int i=pArg[0]+1; i<pArg[0]+1+nLen; i++)
				{
					MFree((void*)pArg[i]);		//		�ı����ֽڼ����ͷ��ڴ�
				}
			}
			ZeroMemory(pArg + pArg[0] + 1, nLen * sizeof(INT));
		}
	}
	*/
}
//	���޷���ֵ�� �������� ��ͨ���ͱ������� ��ֵ������������߼��� �������Ƿ�Ϊ��С����ݣ�
EXTERN_C void krnln_fnSortAry(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
}

#define IS_CC(x) ((x) == 0xCC)
//	���޷���ֵ�� ȡ������ ���ı��ͱ������� ��ű�ȡ���������ı������������
EXTERN_C void krnln_fnGetCmdLine (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	/*
	LPBYTE p = (LPBYTE)GetCommandLine (), pb;
	// �������ó�������
	BYTE ch = ' ';
	if (*p++ == '\"')
		ch = '\"';
	while (*p++ != ch);
	if (ch != ' ' && *p == ' ')  p++;    // ������һ���ո�

	CMyDWordArray aryText;

	while (*p != '\0')
	{
		if (*p == '\"')
		{
			p++;
			pb = p;
			while (*pb != '\0' && *pb != '\"')
			{
				if (IS_CC (*pb) == TRUE)
				{
					if (pb [1] == 0)  break;
					pb++;
				}
				pb++;
			}

			aryText.Add ((DWORD)CloneTextData ((char*)p, pb - p));

			p = pb;
			if (*p != '\0')  p++;
		}
		else if (*p > ' ')
		{
			pb = p;
			while (*pb != '\0' && *pb != '\"' && *pb > ' ')
			{
				if (IS_CC (*pb) == TRUE)
				{
					if (pb [1] == 0)  break;
					pb++;
				}
				pb++;
			}

			aryText.Add ((DWORD)CloneTextData ((char*)p, pb - p));

			p = pb;
		}
		else
			p++;
	}

	//!!! �������ͷ�ԭ����������������ݡ�
	NotifySys (NRS_FREE_ARY, (DWORD)pArgInf->m_dtDataType, (DWORD)*pArgInf->m_ppAryData);

	// �����±����������ݡ�
	INT nSize = aryText.GetDWordCount () * sizeof (DWORD);
	p = (LPBYTE)MMalloc (sizeof (INT) * 2 + nSize);
	*(LPINT)p = 1;  // ����ά����
	*(LPINT)(p + sizeof (INT)) = aryText.GetDWordCount ();
	memcpy (p + sizeof (INT) * 2, aryText.GetPtr (), nSize);

	*pArgInf->m_ppAryData = p;  // ��������д�ظ����������
	*/
}

//	���ı��͡� ȡ����Ŀ¼ ����
EXTERN_C void krnln_fnGetRunPath(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CHAR strPath[MAX_PATH];
	DWORD dwLen = GetModuleFileName(GetModuleHandle(NULL), strPath, MAX_PATH);
	while( dwLen )
	{
		if ( strPath[dwLen - 1] == '\\' )
		{
			pRetData->m_pText = CloneTextData(strPath);
			break;
		}
		strPath[dwLen - 1] = '\0';
		dwLen--;
	}
}

//	���ı��͡� ȡִ���ļ��� ����
EXTERN_C void krnln_fnGetRunFileName(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CHAR strPath[MAX_PATH];
	DWORD dwLen = GetModuleFileName(GetModuleHandle(NULL), strPath, MAX_PATH);
	while( dwLen )
	{
		if (strPath[dwLen - 1] == '\\' )
		{
			pRetData->m_pText = CloneTextData(&strPath[dwLen]);
			break;
		}
		dwLen--;
	}
}

//	���ı��͡� ���������� ���ı��� �����������ƣ�
EXTERN_C void krnln_fnGetEnv(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	DWORD dwLen = MAX_PATH;
	CHAR* pstrVar = (CHAR*)MMalloc(dwLen);
	while ( GetEnvironmentVariable(pArgInf[0].m_pText, pstrVar, dwLen) == dwLen )	//	�ڴ治�� �����·����ڴ�
	{
		MFree(pstrVar);
		dwLen *= 2;
		pstrVar = (CHAR*)MMalloc(dwLen);
	}
	pRetData->m_pText = CloneTextData(pstrVar);
	MFree(pstrVar);
}

//	���߼��͡� д�������� ���ı��� �����������ƣ��ı��� ��д�����ݣ�
EXTERN_C void krnln_fnPutEnv(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = SetEnvironmentVariable(pArgInf[0].m_pText, pArgInf[1].m_pText) ? BL_TRUE : BL_FALSE;
}

//	�������͡� ȡ�ı����� ���ı��� �ı����ݣ�
EXTERN_C void krnln_fnLen(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_pText )
	{
		pRetData->m_int = strlen(pArgInf[0].m_pText );
	}
}

//	���ı��͡� ȡ�ı���� ���ı��� ��ȡ�䲿�ֵ��ı��������� ��ȡ���ַ�����Ŀ
EXTERN_C void krnln_fnLeft(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_pText )
	{
		INT nLen = pArgInf[1].m_int;
		INT nStrLen = strlen(pArgInf[0].m_pText);
		if ( nLen > nStrLen )	//	���ȴ����ַ�������
		{
			nLen = nStrLen;
		}
		pRetData->m_pText = CloneTextData(pArgInf[0].m_pText, nLen);
	}
}

//	���ı��͡� ȡ�ı��ұ� ���ı��� ��ȡ�䲿�ֵ��ı��������� ��ȡ���ַ�����Ŀ��
EXTERN_C void krnln_fnRight(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_pText )
	{
		INT nLen = pArgInf[1].m_int;
		INT nStrLen = strlen(pArgInf[0].m_pText);
		if ( nLen > nStrLen )	//	���ȴ����ַ�������
		{
			nLen = nStrLen;
		}
		pRetData->m_pText = CloneTextData(pArgInf[0].m_pText + nStrLen - nLen, nLen);
	}
}

//	���ı��͡� ȡ�ı��м� ���ı��� ��ȡ�䲿�ֵ��ı��������� ��ʼȡ��λ�ã������� ��ȡ���ַ�����Ŀ��
EXTERN_C void krnln_fnMid(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_pText )
	{
		INT nLen = pArgInf[2].m_int;
		INT nStrLen = strlen(pArgInf[0].m_pText);
		if ( nLen + (pArgInf[1].m_int - 1) > nStrLen )	//	���ȴ����ַ�������
		{
			nLen = nStrLen - (pArgInf[1].m_int - 1);
		}
		pRetData->m_pText = CloneTextData(pArgInf[0].m_pText + (pArgInf[1].m_int - 1), nLen);
	}
}

//	���ı��͡� �ַ� ���ֽ��� ��ȡ���ַ����ַ����룩
EXTERN_C void krnln_fnChr(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_byte )	//	δ���� ��֪���ַ�0�ǲ��Ƿ��ؿ��ı���
	{
		pRetData->m_pText = CloneTextData((char*)&pArgInf[0].m_byte, 1);
	}
}

//	�������͡� ȡ���� ���ı��� ��ȡ�ַ�������ı����������� ��ȡ�������ַ�λ�ãݣ�
EXTERN_C void krnln_fnAsc(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_pText )
	{
		size_t nIdx = 1;
		if ( pArgInf[1].m_dtDataType != _SDT_NULL )
		{
			nIdx = pArgInf[1].m_int;
		}
		if ( strlen(pArgInf[0].m_pText) >= nIdx )	//	λ�ó����ַ�������
		{
			pRetData->m_int = pArgInf[0].m_pText[nIdx - 1];
		}
	}
}

//	�������͡� Ѱ���ı� ���ı��� ����Ѱ���ı����ı��� ��Ѱ�ҵ��ı����������� ��ʼ��Ѱλ�ãݣ��߼��� �Ƿ����ִ�Сд��
EXTERN_C void krnln_fnInStr(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = -1;
	if ( pArgInf[0].m_pText )
	{
		if ( pArgInf[1].m_pText == NULL )
		{
			pRetData->m_int = 1;
		}
		else
		{
			size_t nIdx = 1;
			if ( pArgInf[2].m_dtDataType != _SDT_NULL )
			{
				nIdx = pArgInf[2].m_int;
			}
			if ( strlen(pArgInf[0].m_pText) >= nIdx )
			{
				CHAR *pStr = pArgInf[0].m_pText + (nIdx - 1);
				if ( pArgInf[3].m_bool )
				{
					pStr = StrStrI(pStr, pArgInf[1].m_pText);
				}
				else
				{
					pStr = StrStr(pStr, pArgInf[1].m_pText);
				}
				if ( pStr )
				{
					pRetData->m_int = pStr - pArgInf[0].m_pText + 1;
				}
			}
		}
	}
}

//	�������͡� �����ı� ���ı��� ����Ѱ���ı����ı��� ��Ѱ�ҵ��ı����������� ��ʼ��Ѱλ�ãݣ��߼��� �Ƿ����ִ�Сд��
//	����Ч������
EXTERN_C void krnln_fnInStrRev(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = -1;
	if ( pArgInf[0].m_pText )
	{
		if ( pArgInf[1].m_pText == NULL )
		{
			pRetData->m_int = 1;
		}
		else
		{
			size_t nIdx = 1;
			if ( pArgInf[2].m_dtDataType != _SDT_NULL )
			{
				nIdx = pArgInf[2].m_int;
			}
			if ( strlen(pArgInf[0].m_pText) >= nIdx )
			{
				CHAR *pStr = pArgInf[0].m_pText + (nIdx - 1);
				CHAR *pLastStr = NULL;
				do 
				{
					if ( pArgInf[3].m_bool )
					{
						pStr = StrStrI(pStr, pArgInf[1].m_pText);
					}
					else
					{
						pStr = StrStr(pStr, pArgInf[1].m_pText);
					}
					if ( pStr )
					{
						pLastStr = pStr;
					}
				} while ( pStr++ );

				if ( pLastStr )
				{
					pRetData->m_int = pLastStr - pArgInf[0].m_pText + 1;
				}
			}
		}
	}
}

//	���ı��͡� ����д ���ı��� ���任���ı���
EXTERN_C void krnln_fnUCase(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = CloneTextData(pArgInf[0].m_pText);
	if ( pRetData->m_pText )
	{
		INT nIdx = 0;
		do
		{
			if ( pRetData->m_pText[nIdx] == '\0' )
			{
				break;
			}
			pRetData->m_pText[nIdx] = toupper(pRetData->m_pText[nIdx]);
			nIdx++;
		} while ( TRUE );
	}
}

//	���ı��͡� ��Сд ���ı��� ���任���ı���
EXTERN_C void krnln_fnLCase(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pText = CloneTextData(pArgInf[0].m_pText);
	if ( pRetData->m_pText )
	{
		INT nIdx = 0;
		do
		{
			if ( pRetData->m_pText[nIdx] == '\0' )
			{
				break;
			}
			pRetData->m_pText[nIdx] = tolower(pRetData->m_pText[nIdx]);
			nIdx++;
		} while ( TRUE );
	}
}

//	���ı��͡� ���ı� ��ͨ��������/������ ��ת�������ݣ�
EXTERN_C void krnln_fnStr(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CHAR strText[30] = {0};
	switch ( pArgInf[0].m_dtDataType )
	{
	case SDT_BYTE:
		sprintf(strText, "%d", pArgInf[0].m_byte);
		break;
	case SDT_SHORT:
		sprintf(strText, "%d", pArgInf[0].m_short);
		break;
	case SDT_INT:
		sprintf(strText, "%d", pArgInf[0].m_int);
		break;
	case SDT_INT64:
		sprintf(strText, "%ld", pArgInf[0].m_int64);
		break;
	case SDT_FLOAT:
		sprintf(strText, "%.12f", pArgInf[0].m_float);
		break;
	case SDT_DOUBLE:
		sprintf(strText, "%.12lf", pArgInf[0].m_double);
		break;
	case SDT_BOOL:
		pArgInf[0].m_bool ? strcpy(strText, " ��") : strcpy(strText, "��");
		break;
	case SDT_DATE_TIME:
		break;
	case SDT_TEXT:
		pRetData->m_pText = CloneTextData(pArgInf[0].m_pText);
		return;
		break;
	case SDT_BIN:
		pRetData->m_pText = CloneTextData((CHAR*)pArgInf[0].m_pBin+ sizeof (INT)*2,  *(LPINT)(pArgInf[0].m_pBin + sizeof (INT)));
		return;
		break;
	case SDT_SUB_PTR:
		sprintf(strText, "%d", (INT)pArgInf[0].m_pdwSubCodeAdr);
		break;
	}
	pRetData->m_pText = CloneTextData(strText);
}

//	���ı��͡� ɾ�׿� ���ı��� ��ɾ���ո���ı���
EXTERN_C void krnln_fnLTrim(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CHAR *pstrText = pArgInf[0].m_pText ;
	if ( pstrText )
	{
		while ( *pstrText )
		{
			if ( *pstrText == ' '  )
			{
				pstrText++;
			}
			 else if ( *pstrText == -95  && *(pstrText + 1) == -95 )	//	ȫ��
			{
				pstrText += 2;
			}
			else
			{
				break;
			}
		};
		pRetData->m_pText = CloneTextData(pstrText);
	}
}

//	���ı��͡� ɾβ�� ���ı��� ��ɾ���ո���ı���
EXTERN_C void krnln_fnRTrim(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CHAR *pstrText = pArgInf[0].m_pText ;
	if ( pstrText )
	{
		size_t nLen = strlen(pstrText);
		if ( nLen )
		{
			pstrText += nLen;
			pstrText--;
			INT nLen1 = 0;
			while ( pstrText >= pArgInf[0].m_pText )
			{
				if ( *pstrText == ' '  )
				{
					nLen1++;
					pstrText--;
				}
				else if ( *pstrText == -95  && *(pstrText - 1) == -95 )	//	ȫ��
				{
					nLen1 += 2;
					pstrText -= 2;
				}
				else
				{
					break;
				}
			};
			pRetData->m_pText = CloneTextData(pArgInf[0].m_pText, nLen - nLen1);
		}
	}
}

//	���ı��͡� ɾ��β�� ���ı��� ��ɾ���ո���ı���
EXTERN_C void krnln_fnTrim(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CHAR *pstrText1, *pstrText = pArgInf[0].m_pText ;
	if ( pstrText )
	{
		while ( *pstrText )
		{
			if ( *pstrText == ' '  )
			{
				pstrText++;
			}
			else if ( *pstrText == -95  && *(pstrText + 1) == -95 )	//	ȫ��
			{
				pstrText += 2;
			}
			else
			{
				break;
			}
		};

		pstrText1 = pstrText;
		size_t nLen = strlen(pstrText);
		if ( nLen )
		{
			pstrText += nLen;
			pstrText--;
			INT nLen1 = 0;
			while ( pstrText >= pstrText1 )
			{
				if ( *pstrText == ' '  )
				{
					nLen1++;
					pstrText--;
				}
				else if ( *pstrText == -95  && *(pstrText - 1) == -95 )	//	ȫ��
				{
					nLen1 += 2;
					pstrText -= 2;
				}
				else
				{
					break;
				}
			};
			pRetData->m_pText = CloneTextData(pstrText1, nLen - nLen1);
		}
	}
}

//	���ı��͡� ɾȫ���� ���ı��� ��ɾ���ո���ı���
EXTERN_C void krnln_fnTrimAll(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CHAR *pstrText = pArgInf[0].m_pText ;
	if ( pstrText )
	{
		CHAR *pstrText1 = (CHAR *)MMalloc(strlen(pstrText)+ 1);
		INT nLen = 0;
		while ( *pstrText )
		{
			if ( *pstrText == ' '  )
			{
				pstrText++;
			}
			else if ( *pstrText == -95  && *(pstrText + 1) == -95 )	//	ȫ��
			{
				pstrText += 2;
			}
			else if ( *pstrText < 0 && *(pstrText + 1) < 0 )
			{
				pstrText1[nLen++] = *pstrText++;
				pstrText1[nLen++] = *pstrText++;
			}
			else
			{
				pstrText1[nLen++] = *pstrText++;
			}
		};
		pRetData->m_pText = CloneTextData(pstrText1, nLen);
		MFree(pstrText1);
	}
}

//	���ı��͡� �ı��滻 ���ı��� �����滻���ı��������� ��ʼ�滻λ�ã������� �滻���ȣ����ı��� �����滻���ı��ݣ�
EXTERN_C void krnln_fnReplaceText(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_pText )
	{
		int nLen1, nLen = (int)strlen(pArgInf[0].m_pText);
		if ( pArgInf[1].m_int > nLen)
		{
			pArgInf[1].m_int = nLen + 1;
			pArgInf[2].m_int = 0;
		}
		else if ( pArgInf[1].m_int + pArgInf[2].m_int - 1 >= nLen )
		{
			pArgInf[2].m_int = nLen - (pArgInf[1].m_int - 1);
		}
		if ( (pArgInf[3].m_dtDataType == _SDT_NULL) || pArgInf[3].m_pText )
		{
			nLen1 = nLen - pArgInf[2].m_int;
		}
		else
		{
			nLen1 = nLen + strlen(pArgInf[3].m_pText) - pArgInf[2].m_int;
		}
		pRetData->m_pText = (CHAR *)MMalloc(nLen1 + 1);
		ZeroMemory(pRetData->m_pText, nLen1 + 1);
		memcpy(pRetData->m_pText, pArgInf[0].m_pText,  pArgInf[1].m_int - 1);

		if ( pArgInf[1].m_int + pArgInf[2].m_int - 1 >= nLen )
		{
			strcat(pRetData->m_pText, pArgInf[0].m_pText + pArgInf[1].m_int + pArgInf[2].m_int - 1);

			if ( (pArgInf[3].m_dtDataType != _SDT_NULL) && pArgInf[3].m_pText )
			{
				strcat(pRetData->m_pText, pArgInf[3].m_pText);
			}
		}
		else
		{
			if ( (pArgInf[3].m_dtDataType != _SDT_NULL) && pArgInf[3].m_pText )
			{
				strcat(pRetData->m_pText, pArgInf[3].m_pText);
			}
			strcat(pRetData->m_pText, pArgInf[0].m_pText + pArgInf[1].m_int + pArgInf[2].m_int - 1);
		}
	}
}

//	���ı��͡� ���ı��滻 ���ı��� �����滻���ı����ı��� �����滻�����ı������ı��� �����滻�����ı��ݣ��������� �����滻����ʼλ�ãݣ��������� �滻���еĴ����ݣ��߼��� �Ƿ����ִ�Сд��
EXTERN_C void krnln_fnRpSubText(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CHAR *pstrText = pArgInf[0].m_pText;
	CHAR *pstrText1 = pArgInf[1].m_pText;
	if ( pstrText && pstrText1 )
	{
		int nLen = (int) strlen(pstrText);
		int nLen1 = (int) strlen(pstrText1);
		if ( nLen1 && nLen >= nLen1 )
		{
			CHAR *pstrText2 = (CHAR *)MMalloc(0);
			while( *pstrText )
			{
				if ( memcmp(pstrText, pstrText1, nLen) == 0 )
				{

				}
			}
		}
	}
}

//	���ı��͡� ȡ�հ��ı� �������� �ظ�������
EXTERN_C void krnln_fnSpace(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_int )	//	pArgInf[0].m_int ���ظ�����
	{
		pRetData->m_pText = (CHAR *)MMalloc(pArgInf[0].m_int + 1);	//	�����ı����ڴ�
		memset(pRetData->m_pText, ' ', pArgInf[0].m_int);	//	���ÿհ��ı�
		pRetData->m_pText[pArgInf[0].m_int] = '\0';		//	�����ı�������
	}
}

//	���ı��͡� ȡ�ظ��ı� �������� �ظ��������ı��� ���ظ��ı���
EXTERN_C void krnln_fnString(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_int )	//	pArgInf[0].m_int ���ظ�����
	{
		if ( pArgInf[1].m_pText )
		{
			int nLen = (int)strlen(pArgInf[1].m_pText);
			if ( nLen )
			{
				pRetData->m_pText = (CHAR *)MMalloc(pArgInf[0].m_int * nLen + 1);	//	�����ı����ڴ�
				pRetData->m_pText[pArgInf[0].m_int * nLen] = '\0';		//	�����ı�������
				do 
				{
					memcpy(pRetData->m_pText + nLen * (pArgInf[0].m_int - 1), pArgInf[1].m_pText, nLen);
				} while ( --pArgInf[0].m_int );
			}
		}
	}
}

//	�������͡� �ı��Ƚ� ���ı��� ���Ƚ��ı�һ���ı��� ���Ƚ��ı������߼��� �Ƿ����ִ�Сд��
EXTERN_C void krnln_fnStrComp(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[2].m_bool )
	{
		pRetData->m_int = strcmp(pArgInf[0].m_pText, pArgInf[1].m_pText);
	}
	else
	{
		pRetData->m_int = strcmpi(pArgInf[0].m_pText, pArgInf[1].m_pText);
	}
}

//	���ı������页 �ָ��ı� ���ı��� ���ָ��ı������ı��� �����ָ���ı��ݣ��������� Ҫ���ص����ı���Ŀ�ݣ�
EXTERN_C void krnln_fnSplit(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
}

//	���ı��͡� ָ�뵽�ı� �������� �ڴ��ı�ָ�룩
EXTERN_C void krnln_fnpstr(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if( !IsBadReadPtr((PVOID)pArgInf[0].m_int, 1) )
	{
		pRetData->m_pText = CloneTextData((CHAR*) pArgInf[0].m_int);
	}
}

//	��Ϣ��
EXTERN_C void krnln_fnMsgBox(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	CHAR *lpText = pArgInf[2].m_pText;
	CHAR strText[30] = {0};
	if ( pArgInf[2].m_dtDataType == _SDT_NULL )
	{
		lpText = "��Ϣ��";
	}
	switch ( pArgInf[0].m_dtDataType )
	{
	case SDT_BYTE:
		sprintf(strText, "%d", pArgInf[0].m_byte);
		break;
	case SDT_SHORT:
		sprintf(strText, "%d", pArgInf[0].m_short);
		break;
	case SDT_INT:
		sprintf(strText, "%d", pArgInf[0].m_int);
		break;
	case SDT_INT64:
		sprintf(strText, "%ld", pArgInf[0].m_int64);
		break;
	case SDT_FLOAT:
		sprintf(strText, "%.12f", pArgInf[0].m_float);
		break;
	case SDT_DOUBLE:
		sprintf(strText, "%.12lf", pArgInf[0].m_double);
		break;
	case SDT_BOOL:
		pArgInf[0].m_bool ? strcpy(strText, " ��") : strcpy(strText, "��");
		break;
	case SDT_DATE_TIME:
		break;
	case SDT_TEXT:
		pRetData->m_int = MessageBox(NULL, pArgInf[0].m_pText, lpText, pArgInf[1].m_int);
		return;
		break;
	case SDT_BIN:
		break;
	case SDT_SUB_PTR:
		sprintf(strText, "%d", (INT)pArgInf[0].m_pdwSubCodeAdr);
		break;
	}
	pRetData->m_int = MessageBox(NULL, strText,  lpText, pArgInf[1].m_int);
}


//	���ֽڼ�
EXTERN_C void krnln_fnBinLen(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_pBin )
	{
		pRetData->m_int = *(LPINT)(pArgInf[0].m_pBin + sizeof (INT));
	}
}


//	��С��
EXTERN_C void krnln_fnToFloat(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if ( pArgInf[0].m_pText )
	{
		pRetData->m_float = (float)strtod(pArgInf[0].m_pText, NULL);
	}
}

//	������
EXTERN_C void krnln_fnToInt(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	switch ( pArgInf[0].m_dtDataType )
	{
	case SDT_BYTE:
		pRetData->m_int = pArgInf[0].m_byte;
		break;
	case SDT_SHORT:
		pRetData->m_int = pArgInf[0].m_short;
		break;
	case SDT_INT:
		pRetData->m_int = pArgInf[0].m_int;
		break;
	case SDT_INT64:
		pRetData->m_int = (INT)pArgInf[0].m_int64;
		break;
	case SDT_FLOAT:
		pRetData->m_int = (INT)pArgInf[0].m_float;
		break;
	case SDT_DOUBLE:
		pRetData->m_int = (INT)pArgInf[0].m_double;
		break;
	case SDT_BOOL:
		pRetData->m_int = pArgInf[0].m_bool;
		break;
	case SDT_DATE_TIME:
		break;
	case SDT_TEXT:
		if ( pArgInf[0].m_pText )
		{
			pRetData->m_int = strtol(pArgInf[0].m_pText, NULL, 10);
		}
		break;
	case SDT_BIN:
		break;
	case SDT_SUB_PTR:
		pRetData->m_int = (INT)pArgInf[0].m_pdwSubCodeAdr;
		break;
	}
}

//	����ֵ
EXTERN_C void krnln_fnVal(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	switch ( pArgInf[0].m_dtDataType )
	{
	case SDT_BYTE:
		pRetData->m_double = pArgInf[0].m_byte;
		break;
	case SDT_SHORT:
		pRetData->m_double = pArgInf[0].m_short;
		break;
	case SDT_INT:
		pRetData->m_double = pArgInf[0].m_int;
		break;
	case SDT_INT64:
		pRetData->m_double = (DOUBLE)pArgInf[0].m_int64;
		break;
	case SDT_FLOAT:
		pRetData->m_double = (DOUBLE)pArgInf[0].m_float;
		break;
	case SDT_DOUBLE:
		pRetData->m_double = (DOUBLE)pArgInf[0].m_double;
		break;
	case SDT_BOOL:
		pRetData->m_double = pArgInf[0].m_bool;
		break;
	case SDT_DATE_TIME:
		break;
	case SDT_TEXT:
		if ( pArgInf[0].m_pText )
		{
			pRetData->m_double = strtod(pArgInf[0].m_pText, NULL);
		}
		break;
	case SDT_BIN:
		break;
	case SDT_SUB_PTR:
		pRetData->m_double = (DOUBLE)(INT)pArgInf[0].m_pdwSubCodeAdr;
		break;
	}
}



INT WINAPI krnl_NotifySys (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
	INT nRet = NR_ERR;
	switch (nMsg)
	{
	case NRS_FREE_ARY:
		break;
	case NRS_MALLOC:
		nRet = (INT)krnl_MMalloc(dwParam1);
		break;
	case NRS_MFREE:
		krnl_MFree((PVOID)dwParam1);
		nRet = NR_OK;
		break;
	case NRS_MREALLOC:
		nRet = (INT)krnl_MRealloc((PVOID)dwParam1, (DWORD)dwParam2);
		break;
	}
	return nRet;
}