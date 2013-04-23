
#ifndef __LIB_INF_H
#define __LIB_INF_H
//#include "mtypes.h"
#include "lang.h"
#include <WinDef.h>

///////////////////////////////////

// ����ϵͳ���

#define __OS_WIN        0x80000000
#define __OS_LINUX      0x40000000
#define __OS_UNIX       0x20000000

#define OS_ALL     (__OS_WIN | __OS_LINUX | __OS_UNIX)

/*

���ڿ����ϵͳ���֧�ּ���˵����

  1����֧�ֿ���Ҫ˵���������Щ����ϵͳ�汾����֧�ֿ�����������������͡�
     �������ͷ��������������¼�����������������֧�ֵĲ���ϵͳ��������Щ��Ϣ��
     �ڸ�֧�ֿ������е����в���ϵͳ�汾�б���һ�¡�

  2��Ϊ�˺���ǰ��֧�ֿ�����ݣ�����m_nRqSysMajorVer.m_nRqSysMinorVer�汾��
     С��3.6�Ķ�Ĭ��Ϊ֧��Windows����ϵͳ�������ڲ�����������������͡�
     �������ͷ��������������¼��������������ԡ�

  3����������̶����Ժ͹̶��¼���֧�����в���ϵͳ��

  4�����ڴ����߿ⲻ���в���ϵͳ֧�ּ�顣

*/

typedef	SHORT		DTBOOL;		// SDT_BOOL���͵�ֵ����
typedef	DTBOOL*		PDTBOOL;
#define	BL_TRUE		-1			// SDT_BOOL���͵���ֵ
#define	BL_FALSE	0			// SDT_BOOL���͵ļ�ֵ
#define DATE double
typedef DATE*	PDATE;

///////////////////////////////////

// ��������ϵͳ����Ļ�����������

#define		_SDT_NULL		0           // �����ݣ��ڲ�ʹ�ã�����Ϊ�㣩
/*  �����ڿ������������򷵻�ֵ���������͡�
    1�������ڶ�����������ʱ��_SDT_ALL����ƥ�������������ͣ��������ͱ������Ҫ�󣩡�
    2�����ڶ���Ϊ����_SDT_ALL�������͵Ŀ��������������򸴺��������͵�����
    (���û�����Զ����������͵����������ڻ�˵����)������_SDT_ALL���͵�����ֻ
    ����Ϊ�������ϵͳ�������ͻ򴰿�������˵��������͡�*/
#define		_SDT_ALL		MAKELONG (MAKEWORD (0, 0), 0x8000)	// ���ڲ�ʹ�ã�
// ��ֵ��ƥ�������������֣������ڿ�����������������ֵ���������͡�
//#define		_SDT_NUM		MAKELONG (MAKEWORD (1, 0), 0x8000)	// ���ڲ�ʹ�ã���3.0�汾���Ѿ�������
	#define		SDT_BYTE		MAKELONG (MAKEWORD (1, 1), 0x8000)		// �ֽ�
	#define		SDT_SHORT		MAKELONG (MAKEWORD (1, 2), 0x8000)		// ������
	#define		SDT_INT			MAKELONG (MAKEWORD (1, 3), 0x8000)		// ����
	#define		SDT_INT64		MAKELONG (MAKEWORD (1, 4), 0x8000)		// ������
	#define		SDT_FLOAT		MAKELONG (MAKEWORD (1, 5), 0x8000)		// С��
	#define		SDT_DOUBLE		MAKELONG (MAKEWORD (1, 6), 0x8000)		// ˫����С��
#define		SDT_BOOL		MAKELONG (MAKEWORD (2, 0),	0x8000)		// �߼�
#define		SDT_DATE_TIME	MAKELONG (MAKEWORD (3, 0),	0x8000)		// ����ʱ��
#define		SDT_TEXT		MAKELONG (MAKEWORD (4, 0),	0x8000)		// �ı�
#define		SDT_BIN			MAKELONG (MAKEWORD (5, 0),	0x8000)		// �ֽڼ�
#define		SDT_SUB_PTR		MAKELONG (MAKEWORD (6, 0),	0x8000)		// �ӳ���ָ��
//#define		_SDT_VAR_REF	MAKELONG (MAKEWORD (7, 0),	0x8000)		// �ο���3.0�汾���Ѿ�������
#define		SDT_STATMENT	MAKELONG (MAKEWORD (8, 0),	0x8000)
	// ������ͣ������ڿ��������������������͡������ݳ���Ϊ����INT��
	// ��һ����¼����ӳ����ַ���ڶ�����¼������������ӳ���ı���ջ�ס�
    // !!! ע�����������������ʱ����������������Խ������л����������ͣ����Ա��������жϴ���
    /* �������ӣ�
        if (pArgInf->m_dtDataType == SDT_BOOL)
            return pArgInf->m_bool;

        if (pArgInf->m_dtDataType == SDT_STATMENT)
        {
            DWORD dwEBP = pArgInf->m_statment.m_dwSubEBP;
            DWORD dwSubAdr = pArgInf->m_statment.m_dwStatmentSubCodeAdr;
            DWORD dwECX, dwEAX;

            _asm
            {
                mov eax, dwEBP
                call dwSubAdr
                mov dwECX, ecx
                mov dwEAX, eax
            }

            if (dwECX == SDT_BOOL)
                return dwEAX != 0;

            // �ͷ��ı����ֽڼ�������������ڴ档
            if (dwECX == SDT_TEXT || dwECX == SDT_BIN)
                MFree ((void*)dwEAX);
        }

        GReportError ("�������������жϵ���������ֻ�ܽ����߼�������");
    */

// ��������ϵͳ���͡��û��Զ������͡��ⶨ����������
#define	DTM_SYS_DATA_TYPE_MASK		0x80000000
#define	DTM_USER_DATA_TYPE_MASK		0x40000000
#define	DTM_LIB_DATA_TYPE_MASK		0x00000000

// ����ϸ���û��Զ�����������
#define	UDTM_USER_DECLARE_MASK		0x00000000	// �û��Զ��帴����������
#define	UDTM_WIN_DECLARE_MASK		0x10000000	// �û��Զ��崰������

// �����������е������־�����ĳ��������ֵ��λ��1�����ʾΪ���������͵����顣
// ����־������������ʱΪ����AS_RECEIVE_VAR_OR_ARRAY��AS_RECEIVE_ALL_TYPE_DATA
// ��־�Ŀ��������˵����Ϊ�Ƿ�Ϊ�������ݣ��������Ͼ�δʹ�á���������ط���
// ���Ժ��Ա���־��
#define	DT_IS_ARY					0x20000000
// �����������еĴ�ַ��־�����ĳ��������ֵ��λ��1�����ʾΪ���������͵ı�����ַ��
// ����־������������ʱΪ����AS_RECEIVE_VAR_OR_OTHER��־�Ŀ��������˵����Ϊ�Ƿ�Ϊ
// ������ַ���������Ͼ�δʹ�á���������ط������Ժ��Ա���־��
// ����־���ϱ�־���ܹ��档
#define	DT_IS_VAR					0x20000000

typedef DWORD DATA_TYPE;
typedef DATA_TYPE* PDATA_TYPE;

// NES_ ��Ϊ�����ױ༭���������֪ͨ��
#define NES_GET_MAIN_HWND			        1
	// ȡ�ױ༭���������ڵľ��������֧��֧�ֿ��AddIn��
#define	NES_RUN_FUNC				        2
	// ֪ͨ�ױ༭��������ָ���Ĺ��ܣ�����һ��BOOLֵ��
	// dwParam1Ϊ���ܺš�
	// dwParam2Ϊһ��˫DWORD����ָ��,�ֱ��ṩ���ܲ���1��2��
#define NES_PICK_IMAGE_INDEX_DLG            7
    // ֪ͨ�ױ༭������ʾһ���Ի����г�ָ��ͼƬ���ڵ�����ͼƬ���������û���ѡ��ͼƬ�������š�
    // dwParam1Ϊ�����������Ч��ͼƬ������
    //   dwParam2�����ΪNULL����ϵͳ��Ϊ��Ϊһ���༭��HWND���ھ�������û�������Чѡ���
    // ϵͳ���Զ����Ĵ˱༭������ݲ�������ת����ȥ��
    // �����û���ѡ��ͼƬ��������(-1��ʾ�û�ѡ����ͼƬ)������û�δѡ���򷵻�-2��

// NAS_ ��Ϊ�ȱ��ױ༭�����ֱ������л��������֪ͨ��
#define	NAS_GET_APP_ICON			        1000
	// ֪ͨϵͳ���������س����ͼ�ꡣ
	// dwParam1ΪPAPP_ICONָ�롣
#define NAS_GET_LIB_DATA_TYPE_INFO          1002
    // ����ָ���ⶨ���������͵�PLIB_DATA_TYPE_INFO������Ϣָ�롣
    // dwParam1Ϊ�������������͡�
    // ���������������Ч���߲�Ϊ�ⶨ���������ͣ��򷵻�NULL�����򷵻�PLIB_DATA_TYPE_INFOָ�롣
#define NAS_GET_HBITMAP                     1003
    // dwParam1ΪͼƬ����ָ�룬dwParam2ΪͼƬ���ݳߴ硣
    // ����ɹ����ط�NULL��HBITMAP�����ע��ʹ����Ϻ��ͷţ������򷵻�NULL��
#define NAS_GET_LANG_ID                     1004
    // ���ص�ǰϵͳ�����л�����֧�ֵ�����ID������IDֵ���lang.h
#define NAS_GET_VER                         1005
    // ���ص�ǰϵͳ�����л����İ汾�ţ�LOWORDΪ���汾�ţ�HIWORDΪ�ΰ汾�š�
#define NAS_GET_PATH                        1006
    /* ���ص�ǰ���������л�����ĳһ��Ŀ¼���ļ�����Ŀ¼���ԡ�\��������
       dwParam1: ָ������Ҫ��Ŀ¼������Ϊ����ֵ��
         A�����������л����¾���Ч��Ŀ¼:
            1: ���������л���ϵͳ������Ŀ¼��
         B��������������Ч��Ŀ¼(��������������Ч):
            1001: ϵͳ���̺�֧�ֿ���������Ŀ¼��
            1002: ϵͳ��������Ŀ¼
            1003: ϵͳ������Ϣ����Ŀ¼
            1004: �������еǼǵ�ϵͳ����ģ���Ŀ¼
            1005: ֧�ֿ����ڵ�Ŀ¼
            1006: ��װ��������Ŀ¼
         C�����л�������Ч��Ŀ¼(�����л�������Ч):
            2001: �û�EXE�ļ�����Ŀ¼��
            2002: �û�EXE�ļ�����
       dwParam2: ���ջ�������ַ���ߴ����ΪMAX_PATH��
    */
#define NAS_CREATE_CWND_OBJECT_FROM_HWND    1007
    // ͨ��ָ��HWND�������һ��CWND���󣬷�����ָ�룬��ס��ָ�����ͨ������NRS_DELETE_CWND_OBJECT���ͷ�
    // dwParam1ΪHWND���
    // �ɹ�����CWnd*ָ�룬ʧ�ܷ���NULL
#define NAS_DELETE_CWND_OBJECT              1008
    // ɾ��ͨ��NRS_CREATE_CWND_OBJECT_FROM_HWND������CWND����
    // dwParam1Ϊ��ɾ����CWnd����ָ��
#define NAS_DETACH_CWND_OBJECT              1009
    // ȡ��ͨ��NRS_CREATE_CWND_OBJECT_FROM_HWND������CWND����������HWND�İ�
    // dwParam1ΪCWnd����ָ��
    // �ɹ�����HWND,ʧ�ܷ���0
#define NAS_GET_HWND_OF_CWND_OBJECT         1010
    // ��ȡͨ��NRS_CREATE_CWND_OBJECT_FROM_HWND������CWND�����е�HWND
    // dwParam1ΪCWnd����ָ��
    // �ɹ�����HWND,ʧ�ܷ���0
#define NAS_ATTACH_CWND_OBJECT              1011
    // ��ָ��HWND��ͨ��NRS_CREATE_CWND_OBJECT_FROM_HWND������CWND���������
    // dwParam1ΪHWND
    // dwParam2ΪCWnd����ָ��
    // �ɹ�����1,ʧ�ܷ���0
#define	NAS_IS_EWIN							1014
    // ���ָ������Ϊ�����Դ��ڻ�����������������棬���򷵻ؼ١�
    // dwParam1Ϊ�����Ե�HWND.

// NRS_ ��Ϊ���ܱ������л��������֪ͨ��
#define NRS_UNIT_DESTROIED			        2000
	// ֪ͨϵͳָ��������Ѿ������١�
	// dwParam1ΪdwFormID
	// dwParam2ΪdwUnitID
#define NRS_CONVERT_NUM_TO_INT              2001
	// ת��������ֵ��ʽ��������
	// dwParam1Ϊ PMDATA_INF ָ�룬�� m_dtDataType ����Ϊ��ֵ�͡�
    // ����ת���������ֵ��
#define NRS_GET_CMD_LINE_STR			    2002
	// ȡ��ǰ�������ı�
	// �����������ı�ָ�룬�п���Ϊ�մ���
#define NRS_GET_EXE_PATH_STR                2003
	// ȡ��ǰִ���ļ�����Ŀ¼����
	// ���ص�ǰִ���ļ�����Ŀ¼�ı�ָ�롣
#define NRS_GET_EXE_NAME				    2004
	// ȡ��ǰִ���ļ�����
	// ���ص�ǰִ���ļ������ı�ָ�롣
#define NRS_GET_UNIT_PTR				    2006
	// ȡ�������ָ��
	// dwParam1ΪWinForm��ID
	// dwParam2ΪWinUnit��ID
	// �ɹ�������Ч���������CWnd*ָ�룬ʧ�ܷ���0��
#define NRS_GET_AND_CHECK_UNIT_PTR			2007
	// ȡ�������ָ��
	// dwParam1ΪWinForm��ID
	// dwParam2ΪWinUnit��ID
	// �ɹ�������Ч���������CWnd*ָ�룬ʧ�ܱ�������ʱ�����˳�����
#define NRS_EVENT_NOTIFY				    2008
	// �Ե�һ�෽ʽ֪ͨϵͳ�������¼���
	// dwParam1ΪPEVENT_NOTIFYָ�롣
	//   ������� 0 ����ʾ���¼��ѱ�ϵͳ�����������ʾϵͳ�Ѿ��ɹ����ݴ��¼����û�
	// �¼������ӳ���
#define	NRS_DO_EVENTS			            2018
	// ֪ͨϵͳ�������д������¼���
#define NRS_GET_UNIT_DATA_TYPE              2022
	// dwParam1ΪWinForm��ID
	// dwParam2ΪWinUnit��ID
	// �ɹ�������Ч�� DATA_TYPE ��ʧ�ܷ��� 0 ��
#define NRS_FREE_ARY                        2023
    // �ͷ�ָ���������ݡ�
    // dwParam1Ϊ�����ݵ�DATA_TYPE��ֻ��Ϊϵͳ�������͡�
    // dwParam2Ϊָ����������ݵ�ָ�롣
#define NRS_MALLOC                          2024
    // ����ָ���ռ���ڴ棬�������׳��򽻻����ڴ涼����ʹ�ñ�֪ͨ���䡣
    //   dwParam1Ϊ�������ڴ��ֽ�����
    //   dwParam2��Ϊ0�����������ʧ�ܾ��Զ���������ʱ���˳�����
    // �粻Ϊ0�����������ʧ�ܾͷ���NULL��
    //   �����������ڴ���׵�ַ��
#define NRS_MFREE                           2025
    // �ͷ��ѷ����ָ���ڴ档
    // dwParam1Ϊ���ͷ��ڴ���׵�ַ��
#define NRS_MREALLOC                        2026
    // ���·����ڴ档
    //   dwParam1Ϊ�����·����ڴ�ߴ���׵�ַ��
    //   dwParam2Ϊ�����·�����ڴ��ֽ�����
    // ���������·����ڴ���׵�ַ��ʧ���Զ���������ʱ���˳�����
#define	NRS_RUNTIME_ERR			            2027
	// ֪ͨϵͳ�Ѿ���������ʱ����
	// dwParam1Ϊchar*ָ�룬˵�������ı���
#define	NRS_EXIT_PROGRAM                    2028
	// ֪ͨϵͳ�˳��û�����
	// dwParam1Ϊ�˳����룬�ô��뽫�����ص�����ϵͳ��
#define NRS_GET_PRG_TYPE                    2030
    // ���ص�ǰ�û���������ͣ�ΪPT_DEBUG_RUN_VER�����԰棩��PT_RELEASE_RUN_VER�������棩��
#define NRS_EVENT_NOTIFY2				    2031
	// �Եڶ��෽ʽ֪ͨϵͳ�������¼���
	// dwParam1ΪPEVENT_NOTIFY2ָ�롣
	//   ������� 0 ����ʾ���¼��ѱ�ϵͳ�����������ʾϵͳ�Ѿ��ɹ����ݴ��¼����û�
	// �¼������ӳ���
#define NRS_GET_WINFORM_COUNT               2032
    // ���ص�ǰ����Ĵ�����Ŀ��
#define NRS_GET_WINFORM_HWND                2033
    // ����ָ������Ĵ��ھ��������ô�����δ�����룬����NULL��
	// dwParam1Ϊ����������
#define NRS_GET_BITMAP_DATA                 2034
    // ����ָ��HBITMAP��ͼƬ���ݣ��ɹ����ذ���BMPͼƬ���ݵ�HGLOBAL�����ʧ�ܷ���NULL��
	// dwParam1Ϊ����ȡ��ͼƬ���ݵ�HBITMAP��
#define NRS_FREE_COMOBJECT                  2035
    // ֪ͨϵͳ�ͷ�ָ����DTP_COM_OBJECT����COM����
    // dwParam1Ϊ��COM����ĵ�ַָ�롣
#define NRS_CHK_TAB_VISIBLE                 2039
	// ��ѡ����Ӽб��л���, ʹ�ñ���Ϣ֪ͨ��ϵͳ


/*///////////////////////////////////////////////////////////////////*/
// ϵͳ����֪ͨ�����ֵ��
#define	NL_SYS_NOTIFY_FUNCTION		    1
	//   ��֪��֪ͨϵͳ�õĺ���ָ�룬��װ��֧�ֿ�ǰ֪ͨ�������ж�Σ�
	// ��֪ͨ��ֵӦ�ø���ǰ����֪ͨ��ֵ�������Է���ֵ��
	//   ��ɽ��˺���ָ���¼�����Ա�����Ҫʱʹ����֪ͨ��Ϣ��ϵͳ��
	//   dwParam1: (PFN_NOTIFY_SYS)
#define NL_FREE_LIB_DATA                6
    // ֪֧ͨ�ֿ��ͷ���Դ׼���˳����ͷ�ָ���ĸ������ݡ�


/*///////////////////////////////////////////////////////////////////*/

#define NR_OK		0
#define NR_ERR		-1

    typedef INT (WINAPI *PFN_NOTIFY_LIB) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
	    // �˺�������ϵͳ֪ͨ���й��¼���
    typedef INT (WINAPI *PFN_NOTIFY_SYS) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
	    // �˺���������֪ͨϵͳ�й��¼���
////////////////////////////

#define	WU_GET_WND_PTR			(WM_APP + 2)	// �����ڷǺ���֧�ֿ��еĴ������֧���¼�������

#define WU_INIT                 (WM_APP + 111)  //���ڴ�����Ϻ��������ÿһ��������������ڷ��ʹ���Ϣ

// ���ڴ�����Ϻ�,����Ϣ�����͸�������������������Ҫ�������������ϵĳ�ʼ������.
// ����Ϣ��WU_INIT������Ϊ���ڱ���Ϣ������������д�����windows��Ϣ����õ�����
// ����WU_INIT������������д�����windows��Ϣ���ᱻ���Ρ�
#define	WU_INIT2                (WM_APP + 118) 

typedef double DOUBLE;

#ifndef __GCC_
#pragma pack (push, old_value)   // ����VC++�������ṹ�����ֽ�����
#pragma pack (1)    // ����Ϊ��һ�ֽڶ��롣
#endif

	typedef struct
	{
		union
		{
			BYTE	      m_byte;         // SDT_BYTE
			SHORT	      m_short;        // SDT_SHORT
			INT		      m_int;          // SDT_INT
			DWORD	      m_uint;         // (DWORD)SDT_INT
			INT64	      m_int64;        // SDT_INT64
			FLOAT	      m_float;        // SDT_FLOAT
			DOUBLE	      m_double;       // SDT_DOUBLE
			DATE          m_date;         // SDT_DATE_TIME
			BOOL          m_bool;         // SDT_BOOL
			char*         m_pText;        // SDT_TEXT��������ΪNULL��
			// !!!Ϊ�˱����޸ĵ�������(m_pText�п���ָ����������)�е����ݣ�
			// ֻ�ɶ�ȡ�����ɸ������е����ݣ���ͬ��
			LPBYTE        m_pBin;         // SDT_BIN��������ΪNULL��!!!ֻ�ɶ�ȡ�����ɸ������е����ݡ�
			DWORD         m_dwSubCodeAdr; // SDT_SUB_PTR����¼�ӳ�������ַ��
			void*         m_pCompoundData;// ����������������ָ�룬ָ����ָ�����ݵĸ�ʽ��� run.h ��
			// ����ֱ�Ӹ������е����ݳ�Ա�����������Ҫ���������ͷŸó�Ա��
			void*         m_pAryData;     // ��������ָ�룬ָ����ָ�����ݵĸ�ʽ��� run.h ��
			// ע�����Ϊ�ı����ֽڼ����飬���Ա����ָ�����ΪNULL��
			// !!! ֻ�ɶ�ȡ�����ɸ������е����ݡ�

			// Ϊָ�������ַ��ָ�룬�������������������ʵ�ֺ���ʱ�����á�
			BYTE*	m_pByte;         // SDT_BYTE*
			SHORT*	m_pShort;        // SDT_SHORT*
			INT*	m_pInt;          // SDT_INT*
			DWORD*	m_pUInt;         // ((DWORD)SDT_INT)*
			INT64*	m_pInt64;        // SDT_INT64*
			FLOAT*	m_pFloat;        // SDT_FLOAT*
			DOUBLE*	m_pDouble;       // SDT_DOUBLE*
			DATE*   m_pDate;         // SDT_DATE_TIME*
			BOOL*   m_pBool;         // SDT_BOOL*
			char**  m_ppText;        // SDT_TEXT��*m_ppText����ΪNULL��
			// ע��д����ֵ֮ǰ�����ͷ�ǰֵ������MFree (*m_ppText)��
			// !!!����ֱ�Ӹ���*m_ppText��ָ������ݣ�ֻ���ͷ�ԭָ�������ָ�롣
			LPBYTE* m_ppBin;         // SDT_BIN��*m_ppBin����ΪNULL��
			// ע��д����ֵ֮ǰ�����ͷ�ǰֵ������MFree (*m_ppBin)��
			// !!!����ֱ�Ӹ���*m_ppBin��ָ������ݣ�ֻ���ͷ�ԭָ�������ָ�롣
			DWORD*  m_pdwSubCodeAdr; // SDT_SUB_PTR���ӳ�������ַ������
			void**  m_ppCompoundData;   // �����������ͱ�����
			// ����ֱ�Ӹ������е����ݳ�Ա�����������Ҫ���������ͷŸó�Ա��
			void**  m_ppAryData;        // �������ݱ�����ע�⣺
			// 1��д����ֵ֮ǰ�����ͷ�ԭֵ��ʹ��NRS_FREE_VAR֪ͨ����
			// 2���������Ϊ�ı����ֽڼ����飬���Ա����ָ�����ΪNULL��
			// !!!����ֱ�Ӹ���*m_ppAryData��ָ������ݣ�ֻ���ͷ�ԭָ�������ָ�롣
		};

		// 1���������������ʱ������ò������� AS_RECEIVE_VAR_OR_ARRAY ��
		//    AS_RECEIVE_ALL_TYPE_DATA ��־����Ϊ�������ݣ�����������־ DT_IS_ARY ��
		//    ��Ҳ�� DT_IS_ARY ��־��Ψһʹ�ó��ϡ�
		// 2�����������ݲ�������ʱ�����Ϊ�հ����ݣ���Ϊ _SDT_NULL ��
		DATA_TYPE m_dtDataType;
	} MDATA_INF;
	typedef MDATA_INF* PMDATA_INF;

#ifndef __GCC_
#pragma pack (pop, old_value)    // �ָ�VC++�������ṹ�����ֽ�����
#endif


#endif

