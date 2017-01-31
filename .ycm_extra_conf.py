import os
import ycm_core
from clang_helpers import PrepareClangFlags

compilation_database_folder = ''
scriptdir = os.path.dirname(os.path.realpath(__file__))
testdir = os.path.join(scriptdir, 'tests')

gmock_dir = os.path.join(os.path.join(os.path.join(
    'build', 'googletest-src'), 'googlemock'), 'include')
gtest_dir = os.path.join(os.path.join(os.path.join(
    'build', 'googletest-src'), 'googletest'), 'include')

flags = [
         '-std=c++11',
         '-x',
         'c++',
         '-I', scriptdir,
         '-I', os.path.join(scriptdir, 'include'),
         '-I', os.path.join(scriptdir, gmock_dir),
         '-I', os.path.join(scriptdir, gtest_dir),
         '-I', os.path.join(testdir, 'include'),
         '-D_POSIX_C_SOURCE 199309LL',
         '-D_DARWIN_C_SOURCE',
         '-D_XOPEN_SOURCE 500'
]

if compilation_database_folder:
    database = ycm_core.CompilationDatabase(compilation_database_folder)
else:
    database = None


def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))


def MakeRelativePathsInFlagsAbsolute(flags, working_directory):
    if not working_directory:
        return flags
    new_flags = []
    make_next_absolute = False
    path_flags = ['-isystem', '-I', '-iquote', '--sysroot=']
    for flag in flags:
        new_flag = flag

        if make_next_absolute:
            make_next_absolute = False
            if not flag.startswith('/'):
                new_flag = os.path.join(working_directory, flag)

        for path_flag in path_flags:
            if flag == path_flag:
                make_next_absolute = True
                break

            if flag.startswith(path_flag):
                path = flag[len(path_flag):]
                new_flag = path_flag + os.path.join(working_directory, path)
                break

        if new_flag:
            new_flags.append(new_flag)
    return new_flags


def FlagsForFile(filename):
    if database:
        # Bear in mind that compilation_info.compiler_flags_ does NOT return a
        # python list, but a "list-like" StringVec object
        compilation_info = database.GetCompilationInfoForFile(filename)
        final_flags = PrepareClangFlags(
            MakeRelativePathsInFlagsAbsolute(
                compilation_info.compiler_flags_,
                compilation_info.compiler_working_dir_),
            filename)
    else:
        relative_to = DirectoryOfThisScript()
        final_flags = MakeRelativePathsInFlagsAbsolute(flags, relative_to)

    return {
        'flags': final_flags,
        'do_cache': True
    }
