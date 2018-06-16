set ffmpeg=D:\GitHub\WT\Windows\ffmpeg\ffmpeg.exe
set filein=D:\_Temp\006982_1523254200_1523254800.mp4
set fileout=D:\_Temp\006982_1523254200_1523254800_O.mp4
%ffmpeg% -i %filein% -vcodec libx264 %fileout%
