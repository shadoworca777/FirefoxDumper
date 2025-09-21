#pragma once

#include "Forwards.h"

namespace IO
{
	inline  bool is_exist_dir(String& dir)
	{
		DWORD dwAttr = GetFileAttributesA(dir.c_str());
		if (dwAttr != 0xffffffff && (dwAttr & FILE_ATTRIBUTE_DIRECTORY)) { return true; }
		return false;
	}

	
	inline  bool is_file_exists(const std::string& file)
	{
		WIN32_FIND_DATAA FindFileData;
		HANDLE handle = FindFirstFileA(file.c_str(), &FindFileData);
		int found = handle != INVALID_HANDLE_VALUE;
		if (found)
		{
			FindClose(handle);
		}
		return found;
	}


	inline bool read_file(const String& path_to_file, String& out_data)
	{
		if(!is_file_exists(path_to_file)) return false;
		
		auto hFile = CreateFileA(path_to_file.c_str(), GENERIC_READ, 0, 0, OPEN_ALWAYS, 0, 0);
		
		if (hFile == INVALID_HANDLE_VALUE)		
			return false;

		const auto fileSize = GetFileSize(hFile, NULL);

		if (fileSize == 0)
			return false;
		
		auto tempBuff = new char[fileSize];
		
		DWORD numToRead;
		if (!ReadFile(hFile, tempBuff, fileSize, &numToRead, NULL))
			return false;


		//tempBuff[numToRead] = L'\0';
		out_data = tempBuff;
		out_data.resize(numToRead);		
		delete[] tempBuff;
		tempBuff = nullptr;
		
		if (!CloseHandle(hFile))
			return false;
		
		return true;
	}

	inline void remove_directory(LPCSTR dir) // Fully qualified name of the directory being deleted, without trailing backslash
	{
		try
		{
			//const auto func_SHFileOperation = WinApiImport<f_SHFileOperation>::get("SHFileOperation", "shell32.dll");

			SHFILEOPSTRUCTA file_op = {
				NULL,
				FO_DELETE,
				dir,
				"",
				FOF_NOCONFIRMATION |
				FOF_NOERRORUI |
				FOF_SILENT,
				false,
				0,
				"" };
			auto result = SHFileOperationA(&file_op);
			int z = 0;
		}
		catch (...)
		{
		}	
	}
	
	inline void get_subdirs(List<String>& output, const String& path)
	{
	    WIN32_FIND_DATAA findfiledata;
	    HANDLE hFind = INVALID_HANDLE_VALUE;
	
	    char fullpath[MAX_PATH];
	    DWORD ret = GetFullPathNameA(path.c_str(), MAX_PATH, fullpath, nullptr);
	    if (ret == 0 || ret >= MAX_PATH)
	    {
	        return;
	    }
	    std::string fp(fullpath);

	    hFind = FindFirstFileA((fp + "\\*").c_str(), &findfiledata);
	    if (hFind != INVALID_HANDLE_VALUE)
	    {
	        do
	        {
	            if ((findfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0
	                && strcmp(findfiledata.cFileName, ".") != 0
	                && strcmp(findfiledata.cFileName, "..") != 0)
	            {
	                output.push_back(findfiledata.cFileName);
	            }
	        } while (FindNextFileA(hFind, &findfiledata) != 0);
		
	        FindClose(hFind);
	    }
	}

	inline bool create_directory_recursively(LPCSTR path)
	{
		//const auto func_SHCreateDirectoryEx = WinApiImport<f_SHCreateDirectoryEx>::get("SHCreateDirectoryEx", "shell32.dll");		
		return SHCreateDirectoryExA(NULL, path, NULL) == ERROR_SUCCESS;
	}


	inline bool copy_file(const String& from, const String& to)
	{
		return CopyFileA(from.c_str(), to.c_str(), false);
	}


	inline String get_app_folder(int CSIDL_FLAG = CSIDL_APPDATA)
	{
		char m_path_local_data[MAX_PATH];

		if (SHGetFolderPathA(NULL, CSIDL_FLAG, NULL, 0, m_path_local_data) != S_OK) return "";
		
		return m_path_local_data;
	}

	inline String get_temp_folder()
	{
		char wcharPath[MAX_PATH];
		if (GetTempPathA(MAX_PATH, wcharPath))
			return wcharPath;
		
		return "";
	}
	
}
