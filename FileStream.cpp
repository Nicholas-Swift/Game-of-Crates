#include "stdafx.h"
#include "FileStream.h"
#include <string>
#include <cstdio>

//#include <physfs.h>

/*FileStream::FileStream(std::string archive) :
m_file(NULL)
{
}

FileStream::~FileStream()
{
    if (m_file)
        std::fclose(m_file);
}

bool FileStream::open(std::string filename)
{
    if (m_file)
        std::fclose(m_file);

    m_file = std::fopen(filename.c_str(), "rb");

    return m_file != NULL;
}

sf::Int64 FileStream::read(void* data, sf::Int64 size)
{
    if (m_file)
        return std::fread(data, 1, static_cast<std::size_t>(size), m_file);
    else
        return -1;
}

sf::Int64 FileStream::seek(sf::Int64 position)
{
    if (m_file)
    {
        std::fseek(m_file, static_cast<std::size_t>(position), SEEK_SET);
        return tell();
    }
    else
    {
        return -1;
    }
}

sf::Int64 FileStream::tell()
{
    if (m_file)
        return std::ftell(m_file);
    else
        return -1;
}

sf::Int64 FileStream::getSize()
{
    if (m_file)
    {
        sf::Int64 position = tell();
        std::fseek(m_file, 0, SEEK_END);
        sf::Int64 size = tell();
        seek(position);
        return size;
    }
    else
    {
        return -1;
    }
} */

/*
FileStream::FileStream(const char* filename) : m_File(0x0)
{
	if (filename)
		open(filename);
}

FileStream::~FileStream()
{
	close();
}

bool FileStream::isOpen() const
{
	return (m_File != 0x0);
}

bool FileStream::open(const char* filename)
{
	close();
	m_File = PHYSFS_openRead(filename);
	return isOpen();
}

void FileStream::close()
{
	if (isOpen())
		PHYSFS_close(m_File);
	m_File=0x0;
}

sf::Int64 FileStream::read(void* data, sf::Int64 size)
{
	if (!isOpen())
		return -1;

	// PHYSFS_read returns the number of 'objects' read or -1 on error.
	// We assume our objects are single bytes and request to read size
	// amount of them.
	return PHYSFS_read(m_File, data, 1, static_cast<PHYSFS_uint32>(size));
}

sf::Int64 FileStream::seek(sf::Int64 position)
{
	if (!isOpen())
		return -1;

	// PHYSFS_seek return 0 on error and non zero on success
	if (PHYSFS_seek(m_File, position))
		return tell();
	else
		return -1;
}

sf::Int64 FileStream::tell()
{
	if (!isOpen())
		return -1;

	// PHYSFS_tell returns the offset in bytes or -1 on error just like SFML wants.
	return PHYSFS_tell(m_File);
}

sf::Int64 FileStream::getSize()
{
	if (!isOpen())
		return -1;

	// PHYSFS_fileLength also the returns length of file or -1 on error just like SFML wants.
	return PHYSFS_fileLength(m_File);
} */