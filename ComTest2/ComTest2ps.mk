
ComTest2ps.dll: dlldata.obj ComTest2_p.obj ComTest2_i.obj
	link /dll /out:ComTest2ps.dll /def:ComTest2ps.def /entry:DllMain dlldata.obj ComTest2_p.obj ComTest2_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del ComTest2ps.dll
	@del ComTest2ps.lib
	@del ComTest2ps.exp
	@del dlldata.obj
	@del ComTest2_p.obj
	@del ComTest2_i.obj
