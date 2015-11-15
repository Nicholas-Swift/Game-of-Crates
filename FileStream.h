#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <SFML/System.hpp>
#include <string>
#include <cstdio>
//#include <physfs.h>

/*class FileStream : public sf::InputStream
{
public :

    FileStream(std::string archive);

    ~FileStream();

    bool open(std::string filename);

    virtual sf::Int64 read(void* data, sf::Int64 size);

    virtual sf::Int64 seek(sf::Int64 position);

    virtual sf::Int64 tell();

    virtual sf::Int64 getSize();

private :

    std::FILE* m_file;
}; */

/*class FileStream : public sf::InputStream
{
public:
	FileStream(const char* filename);
    virtual ~FileStream();
    bool isOpen() const;
    bool open(const char* filename);
    void close();

    virtual sf::Int64 read(void* data, sf::Int64 size);
    virtual sf::Int64 seek(sf::Int64 position);
    virtual sf::Int64 tell();
    virtual sf::Int64 getSize();

private:
    PHYSFS_File* m_File;

};
*/
#endif