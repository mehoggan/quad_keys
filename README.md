/****************************************************************************/
/* GLOSSARY
/****************************************************************************/
* ${REPO_ROOT} - This variable refers to the top directory where the .git
                 folder is located.
* "#" - When the pound is included at the front of a step it implies that the
        command should be run from the command line. Do not include the "#" in
        the command.
* "\" - When used at the end of a line that contains a command implies the
        command continues on the next line.
* "[]" - When enclosed brackets are used around a command line argument it
         means that the contents contained inside are optional.
* "()" - When enclosed parentheses are used around a command line argument it
         means that the contents contained inside are required.
* "|" - When multiple argumenst enclosed in "[]" or "()" and seperated by a
        pipe. The arguments are mutually exclusive of eath other.
* "..." - When "..." is used it implies that you know the answer and I cannot
          fill in the blanks.

/############################################################################/
/* LINUX:
/############################################################################/
/****************************************************************************/
/* BUILD LINUX (SHARED|STATIC) LIBRARY WITH NO SWIG
/****************************************************************************/
1.  # cd ${REPO_ROOT}.
2.  # mkdir ${REPO_ROOT}/build
3.  # cd ${REPO_ROOT}/build
4.  Run cmake with (if you want a static lib do not define BUILD_SHARED_LIBS):
    a. # cmake
            [-DBUILD_SHARED_LIBS=(ON)] \
            [-DCMAKE_BUILD_TYPE=(Debug|Release)] \
            ../
5.  Run make:
    a. # make
6.  Look for library in ${REPO_ROOT}/build/QuadKey
7.  To run Unit Tests:
    a. # ${REPO_ROOT}/build/UnitTest/UnitTest


/****************************************************************************/
/* BUILD LINUX SHARED LIBRARY WITH SWIG FOR JAVA OR PYTHON
/****************************************************************************/
1.  $ cd ${REPO_ROOT}.
2.  $ mkdir ${REPO_ROOT}/build
3.  $ cd ${REPO_ROOT}/build
4.  Run cmake with:
    a. $ cmake
            [-DBUILD_SHARED_LIBS=(ON)] \
            [-DCMAKE_BUILD_TYPE=(Debug|Release)] \
            [-DQUADKEY_SWIG_HINT=...] \
            [-DQUADKEY_SWIG_URL=...] \
            [-DQUADKEY_SWIG_VERSION=...] \
            (-DQUADKEY_SWIG_LANGUAGE=(java|python)) \
            ../
5.  Run make:
    a. $ make
6.  Look for library in ${REPO_ROOT}/build/QuadKey
7.  To run native Unit Tests:
    a. $ ${REPO_ROOT}/build/UnitTest/UnitTest

/****************************************************************************/
/* LINUX RUNNING JAVA UNIT TESTS FROM COMMAND LINE
/****************************************************************************/
1.  Install maven 3 and ensure it is on your path.
2.  Make sure you have built the native library for java. See the steps above.
3.  $ cd ${REPO_ROOT}/Swig/
4.  $ mvn clean package
5.  $ cd ${REPO_ROOT}/UnitTestJava/
6.  $ mvn clean test -P(linux-release|linux-debug)

/****************************************************************************/
/* LINUX RUNNING PYTHON UNIT TESTS FROM COMMAND LINE
/****************************************************************************/
1.  Install python(2|3). Both should work. Ensure python is on your path.
2.  Make sure you have built the native library for python. See the steps
    above.
3.  $ cd ${REPO_ROOT}/UnitTestPython/
4.  $ python main.py

/############################################################################/
/* WINDOWS:
/############################################################################/
/****************************************************************************/
/* BUILD WINDOWS (SHARED|STATIC) WITH NO SWIG
/****************************************************************************/
1.  PS > cd ${REPO_ROOT}
2.  PS > mkdir ${REPO_ROOT}/build
3.  PS > cd ${REPO_ROOT}/build
4.  Run cmake with (if you want a static lib do not define BUILD_SHARED_LIBS):
    a. PS > cmake
            [-DBUILD_SHARED_LIBS=(ON)] \
            (-G "Visual Studio 14 2015 Win64") \
            ../
5.  Open up the Visual Studio Solution generated in ${REPO_ROOT}/build/
    QuadKeys.sln
6.  Right Click the UnitTest Project and select "Set as Startup Project".
7.  Run the Solution (F5).

/****************************************************************************/
/* BUILD WINDOWS SHARED LIBRARY WITH SWIG FOR JAVA, PYTHON, OR CSHARP
/****************************************************************************/
1.  PS > cd ${REPO_ROOT}
2.  PS > mkdir ${REPO_ROOT}/build
3.  PS > cd ${REPO_ROOT}/build
4.  Run cmake with (if you want a static lib do not define BUILD_SHARED_LIBS):
    a. PS > cmake
            [-DBUILD_SHARED_LIBS=(ON)] \
            [-DQUADKEY_SWIG_HINT=...] \
            [-DQUADKEY_SWIG_URL=...] \
            [-DQUADKEY_SWIG_VERSION=...] \
            (-DQUADKEY_SWIG_LANGUAGE=(java|python|csharp)) \
            (-G(Visual Studio 14 2015 Win64|Visual Studio 14 2015)) \
            ../
5.  Open up the Visual Studio Solution generated in ${REPO_ROOT}/build/
    QuadKeys.sln
6.  Right Click the UnitTest Project and select "Set as Startup Project".
7.  Run the Solution (F5).

/****************************************************************************/
/* WINDOWS RUNNING JAVA UNIT TESTS FROM COMMAND LINE
/****************************************************************************/
1.  Install maven 3 and ensure it is on your path.
2.  Make sure you have built the native library for java. See the steps above.
3.  PS > cd ${REPO_ROOT}/Swig/
4.  PS > mvn clean package
5.  PS > cd ${REPO_ROOT}/UnitTestJava/
6.  PS > mvn clean test -P(windows-release|windows-debug)

/****************************************************************************/
/* WINDOWS RUNNING PYTHON UNIT TESTS FROM COMMAND LINE
/****************************************************************************/
1.  Install python(2|3). Both should work. Ensure python is on your path.
2.  Make sure you have built the native library for python. See the steps
    above.
3.  PS > cd ${REPO_ROOT}/UnitTestPython/
4.  PS > main.ps1 -Configuration "(Debug|Release)"

/****************************************************************************/
/* WINDOWS RUNNING CSHARP UNIT TESTS FROM VISUAL STUDIO
/****************************************************************************/
1.  Follow steps 1-5 under BUILD WINDOWS SHARED LIBRARY WITH SWIG FOR JAVA,
    PYTHON, OR CSHARP. Set QUADKEY_SWIG_LANGUAGE to csharp.
2.  Build the QuadKeys Solution.
    a. If you get an error while building the QuadKeys solution form the
       QuadKeyCSharp project. Build the QuadKey Project only. This will
       generate the source needed by the QuadKeyCSharp library.
3.  Go to Test ==> Test Settings ==> Default Processor Architecture ==> Select
    the Architecture used to build the shared library.
4.  Go to Test ==> Run ==> All Tests
5.  View  "Test Explorer" Dock Windows for Test Results.
 
/****************************************************************************/
/* WINDOWS RUNNING CSHARP UNIT TESTS FROM COMMAND LINE
/****************************************************************************/
1.  Build the QuadKey Project. NOTE: Make sure that Configuration property is
    the same across all steps. Also ensure that Platform is consistant.
2.  PS > & 'C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\ `
          vcvarsall.bat'
3.  PS > cd ${REPO_ROOT}\build\
4.  PS > & 'C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe' `
          .\QuadKey\QuadKey.vcxproj `
          /t:Clean,Build /p:Configuration=(Debug|Release) `
          /p:Platform=(x86|x64)
5. PS > cd ..\Swig
6. PS > & 'C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe' `
          /p:Configuration=(Release|Debug) `
          .\Swig\QuadKeyCSharp.csproj
7. PS > cd ..\UnitTestCSharp\
8. PS > & 'C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe' `
          /p:Configuration=(Release|Debug) `
          .\UnitTestCSharp\UnitTestCSharp.csproj
9. PS > & 'C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\
          CommonExtensions\Microsoft\TestWindow\vstest.console.exe' `
          /Platform:(x64|x86) bin\(Release|Debug)\UnitTestCSharp.dll
 
/############################################################################/
/* LINUX AND WINDOWS:
/############################################################################/
/****************************************************************************/
/* RUNNING JAVA UNIT TESTS FROM INTELLIJ IDEA
/****************************************************************************/
1.  Install IntelliJ IDEA (ver >= 15.0)
2.  Make sure you have built the native library. See the steps above.
3.  Open an existing project using the pom.xml file located in
    ${REPO_ROOT}/Swig
    a. File ==> Open
4.  Go to View ==> Tool Windows ==> Maven Projects
    a. Expand 'QuadKey Java Wrapper'.
        i ) Expand 'Lifecycle'.
            a) Double click 'clean'.
            b) Double click 'package'.
5.  Open an existing project using the pom.xml file located in ${REPO_ROOT}/
    UnitTestJava.
    a. File ==> Open
6.  Go to View ==> Tool Windows ==> Maven Projects
    a. Expand 'Profiles'. Select the profile suitable to your build.
    b. Expand 'QuadKey Java Wrapper Unit Tests'
        i ) Expand 'Lifecycle'.
            a) Double click 'clean'.
            b) Double click 'test'.

/****************************************************************************/
/* RUNNING PYTHON UNIT TESTS FROM PYCHARM
/****************************************************************************/
1.  Install JetBRAINS PyCharm (ver >= 4.5.1)
2.  Make sure you have built the native library. See the steps above.
3.  When you ran CMake above it told you the version of the python library the
    native library linked against. It should read "Found PythonLibs:
    C:/Python27/libs/python27.lib (found version "2.7")". Make sure the Project
    Interpreter is set to this version. To do so File ==> Project Settings ==>
    Project: UnitTestPython ==> Project Interpreter. If the version is not
    listed click the "Gear" button in upper right. Select Add Local. Browse
    to the version of Python CMake found.
4.  Open an existing project using the directory ${REPO_ROOT}/UnitTestPython
5.  Open main.py
6.  Run ==> Edit Configurations
7.  In the "Script parameters:' input box type -c (Release|Debug)
8.  Hit "Ok" button.
9.  Run ==> Debug 'main'
