
ComTest1ps.dll: dlldata.obj ComTest1_p.obj ComTest1_i.obj
	link /dll /out:ComTest1ps.dll /def:ComTest1ps.def /entry:DllMain dlldata.obj ComTest1_p.obj ComTest1_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del ComTest1ps.dll
	@del ComTest1ps.lib
	@del ComTest1ps.exp
	@del dlldata.obj
	@del ComTest1_p.obj
	@del ComTest1_i.obj
