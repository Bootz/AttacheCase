

@rem �o�[�W�����ԍ����擾����
for /F "delims=" %%s in ('tools\getver\getver\bin\Release\getver.exe installer\AttacheCase.exe') do @set NUM=%%s

echo %NUM%


@pause

