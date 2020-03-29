#include "stdafx.h"

CEncode gEncode;

BYTE XorTableLock[]	= {0x4,0x2,0x1};

CEncode::CEncode()
{
	m_pBuffer		= NULL;
	m_iBufferSize	= 0;
	m_iBufferCount	= 0;
	m_hFile			= INVALID_HANDLE_VALUE;
}

CEncode::~CEncode()
{
	Close();
}

int CEncode::Load(char * File)
{
	if( m_hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle(m_hFile);
	}
	
	m_hFile = CreateFile(File, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0x80, NULL);
	
	if( m_hFile == INVALID_HANDLE_VALUE )
	{
		return 0;
	}
	
	int filesize = GetFileSize(m_hFile, NULL);
	
	char* pBuffer = (char*)malloc(filesize);
	
	DWORD iReadFileSize = 0;
	
	ReadFile(m_hFile, pBuffer, filesize, &iReadFileSize, 0);
	
	if(iReadFileSize == 0)
	{
		Close();
	}
	
	Encode(pBuffer,iReadFileSize);
	
	SetScriptBuffer(pBuffer, iReadFileSize);
	
	CloseHandle(m_hFile);
	
	return 1;
}

void CEncode::Close()
{
	if(m_pBuffer != 0)
	{
		free(m_pBuffer);
	}
}

void CEncode::Encode(char* buffer,int size)
{
	for(int i = 0;i < size;i++)
	{
		buffer[i] = buffer[i] ^ XorTableLock[i % 3];
	}
}

int CEncode::GetC()
{
	if ( m_iBufferCount >= m_iBufferSize )
	{
		return -1;
	}
	else
	{
		return m_pBuffer [ m_iBufferCount++ ];
	}
}

void CEncode::UnGetC(int ch)
{
	if ( m_iBufferCount <= 0)
	{
		return;
	}
	else
	{
		m_iBufferCount--;

		m_pBuffer [ m_iBufferCount ] = ch;
	}
}

void CEncode::SetScriptBuffer( char* buffer, int size)
{
	m_pBuffer = buffer;
	m_iBufferSize = size;
	m_iBufferCount = 0;
}

int CEncode::GetInt()
{
	return (int)TokenNumber;
}

float CEncode::GetFloat()
{
	return TokenNumber;
}

char* CEncode::GetString()
{
	return TokenString;
}

WZSMDToken CEncode::GetToken()
{
	char ch;
	TokenString[0] = '\0';
	do
	{
		if ( (ch =(char) GetC() ) == EOF) return T_END;

		if (ch == '/')
		{
			if ((ch =(char) GetC() )=='/')
			{
				while ((ch != '\n') && (ch != EOF))	ch =(char) GetC();
			}
		}
	} while(  isspace(ch) );

	char *p, TempString[100];
	switch(ch)
	{
	case '#':
		return CurrentToken = T_COMMAND;
	case ';':
		return CurrentToken = T_SEMICOLON;
	case ',':
		return CurrentToken = T_COMMA;
	case '{':
		return CurrentToken = T_LP;
	case '}':
		return CurrentToken = T_RP;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '.':
	case '-':
		UnGetC(ch);
		p = TempString;
		while ( (  (ch = GetC() ) !=EOF) && (ch=='.' || isdigit(ch) || ch=='-') )
			*p++ = ch;
		*p = 0;
		TokenNumber = (float)atof(TempString);
		return CurrentToken = T_NUMBER;
	case '"':
		p = TokenString;
		while ( (  (ch = GetC() ) !=EOF) && (ch!='"'))
			*p++ = ch;
		if (ch!='"')
			UnGetC(ch);
		*p = 0;
		return CurrentToken = T_NAME;
	default:
		if (isalpha(ch))
		{
			p = TokenString;
			*p++ = ch;
			while ( (  (ch = GetC() ) !=EOF) && (ch=='.' || ch=='_' || isalnum(ch)) )
				*p++ = ch;
			UnGetC(ch);
			*p = 0;
			return CurrentToken = T_NAME;
		}
		return CurrentToken = T_SMD_ERROR;
	}
}