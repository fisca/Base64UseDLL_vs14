#include <Windows.h>
#include <stdio.h>
#include <conio.h>

typedef int(*SampleFunction)(int, int);
typedef char* (*base64_encode)(const unsigned char*, size_t, size_t*);
// const unsigned char* data, size_t input_length, size_t* output_length

int LoadDLL(int*, char*);
char* EncodeB64(unsigned char*, char*, char*, size_t*, int*);

int main()
{
	int output = 0;
	char msg[256];

	//if (LoadDLL(&output, msg) == EXIT_SUCCESS)
		//printf("%s\nOutput: %d\n", msg, output);
	//else
		//printf("%s\n", msg);

	msg[0] = '\0';
	unsigned char text[] = "Suttipong Srikok";
	char op[256];
	
	printf("\n*** Encode Base 64 ***\n");
	printf("Original text: %s\n", text);
	size_t encodeLength;
	int result;
	char* enc = EncodeB64(text, op, msg, &encodeLength, &result);

	printf("\n%s\n", msg);
	if (result == EXIT_SUCCESS)
	{
		printf("Encode text: %s\n", enc);
		printf("Encode length: %d\n", encodeLength);
	}	

	_getch();

	return 0;
}

int LoadDLL(int *op, char *msg)
{
	HINSTANCE hDLL = LoadLibrary(L"Base64Test.dll");

	if (hDLL == NULL)
	{
		strcpy_s(msg, 256, "Could not load the dynamic library\n");
		FreeLibrary(hDLL);
		return EXIT_FAILURE;
	}

	// resolve function address here
	SampleFunction func = (SampleFunction)GetProcAddress(hDLL, "SampleFunction");

	if (func == NULL)
	{
		strcpy_s(msg, 256, "Could not locate the function\n");
		FreeLibrary(hDLL);
		return EXIT_FAILURE;
	}

	*op = func(3, 5);

	FreeLibrary(hDLL);

	strcpy_s(msg, 256, "Process Test Success");

	return EXIT_SUCCESS;
}

char* EncodeB64(unsigned char *inp, char *op, char *msg, size_t *encodeLength, int *result)
{
	HINSTANCE hDLL = LoadLibrary(L"Base64Test.dll"); //("C:\\Documents and Settings\\User\\Desktop\\fgfdg\\dgdg\\test.dll");

	if (hDLL == NULL)
	{
		strcpy_s(msg, 256, "Could not load the dynamic library\n");
		FreeLibrary(hDLL);
		*result = EXIT_FAILURE;
		return ""; // EXIT_FAILURE;
	}

	base64_encode enfunc = (base64_encode)GetProcAddress(hDLL, "base64_encode");

	if (enfunc == NULL)
	{
		strcpy_s(msg, 256, "Could not locate the function\n");
		FreeLibrary(hDLL);
		*result = EXIT_FAILURE;
		return ""; // EXIT_FAILURE;
	}

	//printf("inp: %s\n", inp);

	op = enfunc(inp, strlen((char*)inp), encodeLength);
	//printf("op: %s\n", op);

	FreeLibrary(hDLL);

	strcpy_s(msg, 256, "Process Encode Success");

	*result = EXIT_SUCCESS;

	return op; // EXIT_SUCCESS;
}

