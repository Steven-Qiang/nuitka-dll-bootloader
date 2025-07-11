#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

typedef const wchar_t filename_char_t;
typedef wchar_t native_command_line_argument_t;

typedef int(__stdcall *nuitka_dll_function_ptr)(int, native_command_line_argument_t **);

int runPythonCodeDLL(filename_char_t const *dll_filename, int argc, native_command_line_argument_t **argv)
{
    HINSTANCE hGetProcIDDLL = LoadLibraryExW(dll_filename, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

    if (!hGetProcIDDLL)
    {
        wprintf(L"Error loading DLL: %lu\n", GetLastError());
        return EXIT_FAILURE;
    }

    nuitka_dll_function_ptr nuitka_dll_function = (nuitka_dll_function_ptr)GetProcAddress(hGetProcIDDLL, "run_code");

    if (nuitka_dll_function == NULL)
    {
        wprintf(L"Error, DLL entry point not found.\n");
        FreeLibrary(hGetProcIDDLL);
        return EXIT_FAILURE;
    }

    int result = (*nuitka_dll_function)(argc, argv);
    FreeLibrary(hGetProcIDDLL);
    return result;
}

int wmain(int argc, wchar_t *argv[])
{
    const filename_char_t *dll_filename = L"main.dll";

    if (argc < 2)
    {
        wprintf(L"Usage: %ls real_program.exe [arguments...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int new_argc = argc - 1;
    native_command_line_argument_t **new_argv = (native_command_line_argument_t **)malloc((new_argc + 1) * sizeof(native_command_line_argument_t *));

    if (new_argv == NULL)
    {
        wprintf(L"Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < new_argc; i++)
    {
        new_argv[i] = argv[i + 1];
    }
    new_argv[new_argc] = NULL;

    for (int i = 0; i < new_argc; i++)
    {
        wprintf(L"argv[%d]: %ls\n", i, new_argv[i]);
    }

    int result = runPythonCodeDLL(dll_filename, new_argc, new_argv);

    free(new_argv);
    return result;
}