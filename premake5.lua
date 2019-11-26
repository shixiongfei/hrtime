solution ( "hrtime-test" )
  configurations { "Release", "Debug" }
  platforms { "x64" }

  if _ACTION == "clean" then
    os.rmdir(".vs")
    os.rmdir("test")
    os.remove("hrtime-test.VC.db")
    os.remove("hrtime-test.sln")
    os.remove("hrtime-test.vcxproj")
    os.remove("hrtime-test.vcxproj.filters")
    os.remove("hrtime-test.vcxproj.user")
    os.remove("hrtime-test.make")
    os.remove("Makefile")
    return
  end

  -- A project defines one build target
  project ( "hrtime-test" )
  kind ( "ConsoleApp" )
  language ( "C" )
  targetname ("hrtime-test")
  files { "./*.h", "./*.c" }
  defines { "_UNICODE" }
  staticruntime "On"

  configuration ( "Release" )
    optimize "On"
    objdir ( "./test/tmp" )
    targetdir ( "./test" )
    defines { "NDEBUG", "_NDEBUG" }

  configuration ( "Debug" )
    symbols "On"
    objdir ( "./test/tmp" )
    targetdir ( "./test" )
    defines { "DEBUG", "_DEBUG" }

  configuration ( "vs*" )
    defines { "WIN32", "_WIN32", "_WINDOWS",
              "_CRT_SECURE_NO_WARNINGS", "_CRT_SECURE_NO_DEPRECATE",
              "_CRT_NONSTDC_NO_DEPRECATE", "_WINSOCK_DEPRECATED_NO_WARNINGS" }
    links { "Winmm" }

  configuration ( "gmake" )
    warnings  "Default" --"Extra"
    defines { "LINUX_OR_MACOSX" }

  configuration { "gmake", "macosx" }
    defines { "__APPLE__", "__MACH__", "__MRC__", "macintosh" }

  configuration { "gmake", "linux" }
    defines { "__linux__" }
