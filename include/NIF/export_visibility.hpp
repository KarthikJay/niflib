#pragma once

// Example taken from: https://gcc.gnu.org/wiki/Visibility
#if defined _WIN32 || defined __CYGWIN__
	#define NIF_SHARED_IMPORT __declspec(dllimport)
	#define NIF_SHARED_EXPORT __declspec(dllexport)
	#define NIF_SHARED_LOCAL
#else
	#if __GNUC__ >= 4
		#define NIF_SHARED_IMPORT __attribute__ ((visibility ("default")))
		#define NIF_SHARED_EXPORT __attribute__ ((visibility ("default")))
		#define NIF_SHARED_LOCAL __attribute__ ((visibility ("hidden")))
	#else
		#define NIF_SHARED_IMPORT
		#define NIF_SHARED_EXPORT
		#define NIF_SHARED_LOCAL
	#endif
#endif

// NIF_API & NIF_LOCAL definitions
#ifndef BUILD_STATIC
	#define NIF_API NIF_SHARED_EXPORT
#else
	#define NIF_API
#endif

// \note Un-needed with CMake setting visibility default to hidden
// #define NIF_HIDDEN NIF_SHARED_LOCAL