@if exist ..\..\e.exe goto j_check
@echo ��ѱ��ļ�������\e\tools\drv\��
@pause
@exit

:j_check
@if not exist krnln_static_raw.lib goto j_start
@echo �����ظ�����
@pause
@exit


:j_start
copy ..\..\static_lib\krnln_static.lib krnln_static_raw.lib
copy ..\..\static_lib\krnln_static.res krnln_static_raw.res
copy ..\link.ini link_win32.ini

@echo.
@echo ʹ��switch_win32/switch_drvΪ�л� win�������/win�������� �ı���
@echo �����޸�link_drv.ini�е�libpath��ddk��(��E�ܱ���objͨ��)
@echo ����ʱ�븴������Ҫ��lib��.eĿ¼�У����߽�ddkĿ¼������%%path%%��(���ֹ�linkʱ��ʶ��)
@echo.

@pause