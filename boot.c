#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

// Forward declaration of our main logic function
int wmain(int argc, wchar_t *argv[]);

// --- WinMain Shim ---
// This is a workaround for compilers that incorrectly force a GUI subsystem (-mwindows)
// and look for a WinMain entry point, even when a console app is intended.
// This WinMain satisfies the linker and then calls our actual wmain function.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int argc;
    wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    if (argv == NULL) {
        return 1; // Or handle error appropriately
    }

    int result = wmain(argc, argv);

    LocalFree(argv);

    return result;
}
// --- End Shim ---


typedef const wchar_t filename_char_t;
typedef wchar_t native_command_line_argument_t;

typedef int(__stdcall *nuitka_dll_function_ptr)(int, native_command_line_argument_t **);

int runPythonCodeDLL(filename_char_t const *dll_filename, int argc, native_command_line_argument_t **argv)
{
    // Use LoadLibraryExW to ensure the DLL's own directory is searched for dependencies.
    HINSTANCE hGetProcIDDLL = LoadLibraryExW(dll_filename, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

    if (!hGetProcIDDLL)
    {
        wprintf(L"Error loading DLL: %lu\n", GetLastError());
        return EXIT_FAILURE;
    }

    // Find the "run_code" entry point in the loaded DLL.
    nuitka_dll_function_ptr nuitka_dll_function = (nuitka_dll_function_ptr)GetProcAddress(hGetProcIDDLL, "run_code");

    if (nuitka_dll_function == NULL)
    {
        wprintf(L"Error, DLL entry point 'run_code' not found.\n");
        FreeLibrary(hGetProcIDDLL);
        return EXIT_FAILURE;
    }

    // Call the DLL's function.
    int result = (*nuitka_dll_function)(argc, argv);
    
    FreeLibrary(hGetProcIDDLL);
    return result;
}

int wmain(int argc, wchar_t *argv[])
{
    // Expect at least one argument: the path to the DLL to load.
    if (argc < 2)
    {
        wprintf(L"Usage: %ls <path_to_dll> [arguments...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // The first argument (argv[1]) is the DLL filename.
    const filename_char_t *dll_filename = argv[1];

    // The remaining arguments (including the DLL name itself) will be passed to the DLL.
    int new_argc = argc - 1;
    native_command_line_argument_t **new_argv = (native_command_line_argument_t **)malloc((new_argc + 1) * sizeof(native_command_line_argument_t *));

    if (new_argv == NULL)
    {
        wprintf(L"Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Copy argument pointers from argv[1] onwards.
    for (int i = 0; i < new_argc; i++)
    {
        new_argv[i] = argv[i + 1];
    }
    new_argv[new_argc] = NULL;

    // Optional: Print the arguments being passed to the DLL for debugging.
    for (int i = 0; i < new_argc; i++)
    {
        wprintf(L"argv[%d]: %ls\n", i, new_argv[i]);
    }

    int result = runPythonCodeDLL(dll_filename, new_argc, new_argv);

    free(new_argv);
    return result;
}